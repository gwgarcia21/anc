#include "global_def.h"

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=181,311
AudioInputI2S            mic;            //xy=182,433.00000381469727
AudioMixer4              mixer1;         //xy=341,444.00000381469727
AudioFilterFIR           fir1;           //xy=343,381
AudioAdaptiveFIR         adaptive_fir1;  //xy=531,413
AudioOutputI2S           headphone;      //xy=829,415
AudioConnection          patchCord1(noise1, fir1);
AudioConnection          patchCord2(mic, 0, mixer1, 0);
AudioConnection          patchCord3(mixer1, 0, adaptive_fir1, 1);
AudioConnection          patchCord4(fir1, 0, adaptive_fir1, 0);
AudioConnection          patchCord5(fir1, 0, headphone, 0);
AudioConnection          patchCord6(fir1, 0, headphone, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=520,145
// GUItool: end automatically generated code

#define T 128 // audio block size
#define MODE 1 // 0: white noise 1: low-pass filtered white noise 2: tests

////////////////////////////////////////////////////////////////////////
#if MODE == 0
////////////////////////////////////////////////////////////////////////
#define N 128 // filter length
#define MAX_LOOP 200 // maximum number of loops
float32_t Shw[N] = { 0.0 }; // Shw coefficients
float32_t mu = 0.05; // learning coefficient
////////////////////////////////////////////////////////////////////////
#elif MODE == 1
////////////////////////////////////////////////////////////////////////
#define N 128 // filter length
#define MAX_LOOP 200 // maximum number of loops
float32_t Shw[N] = { 0.0 }; // Shw coefficients
float32_t mu = 0.01; // learning coefficient
#define F_LEN 56

const q15_t filtroPB[F_LEN] = {
		-999, -129, -137, -129, -114, -97, -73, -32, -2, 50,
		109, 169, 233, 308, 383, 460, 541, 619, 693, 772, 844,
		905, 973, 1020, 1057, 1083, 1119, 1120, 1119, 1119,
		1084, 1058, 1022, 974, 905, 844, 773, 693, 620, 542,
		461, 384, 307, 233, 169, 110, 50, -3, -33, -72, -97,
		-114, -128, -136, -128, -1001
}; // Low-pass filter 1.5 kHz 20 dB
////////////////////////////////////////////////////////////////////////
#elif MODE == 2
////////////////////////////////////////////////////////////////////////
#define N 56 // filter length
#define MAX_LOOP 50 // maximum number of loops
float32_t Shw[N] = { 0.0 }; // Shw coefficients
float32_t mu = 0.01; // learning coefficient
////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////

arm_lms_norm_instance_f32 * lms; // LMS data structure

AdaptiveFIRResults* AdaptiveFIRResults::instance = 0; // results instance

void setup() {
	//==================================================================================================================//
	// Enable serial communication, set audio memory and enable chip
	Serial.begin(38400);
	AudioMemory(200);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.3);
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.lineInLevel(5); // default = 5
	noise1.amplitude(0.5); // white noise amplitude
#if MODE == 0
    fir1.begin(FIR_PASSTHRU,0); // pass thru
#elif MODE == 1
	fir1.begin(filtroPB,F_LEN);
#endif
    mixer1.gain(0,1.0); // mic gain
	adaptive_fir1.begin(mu, Shw, N);
	//==================================================================================================================//
}

void loop()
{
	//==================================================================================================================//
	int k = 0;
	int i = 0;
	float32_t minCoeff;
	uint32_t index;
	float32_t w[N] = { 0.0 };
	float32_t mse[1024] = { 0.0 };
	float32_t x_f32[256], d_f32[256], y_f32[256], e_f32[256], w_f32[256];

	Serial.println("Start!");
	/// Signals
	for(k = 0 ; k < MAX_LOOP ; k++) {
		Serial.println("%%%%%%%%%%%%%%%NLMS%%%%%%%%%%%%%%%");

		Serial.print("Frame = ");
		Serial.println(k);

		Serial.print("mu = ");
		Serial.print(mu,8);
		Serial.println(";");

		//float32_t x_f32[256], d_f32[256], y_f32[256], e_f32[256], w_f32[256];
		AdaptiveFIRResults * adapter = AdaptiveFIRResults::getInstance();

		arm_copy_f32(adapter->x,x_f32,T);
		arm_copy_f32(adapter->d,d_f32,T);
		arm_copy_f32(adapter->y,y_f32,T);
		arm_copy_f32(adapter->e,e_f32,T);
		arm_copy_f32(adapter->w,w_f32,N);

		Serial.print("x = [");
		for(i = 0; i < T; i++) {
			Serial.print(x_f32[i],8);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("d = [");
		for(i = 0; i < T; i++) {
			Serial.print(d_f32[i],8);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("y = [");
		for(i = 0; i < T; i++) {
			Serial.print(y_f32[i],8);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("e = [");
		for(i = 0; i < T; i++) {
			Serial.print(e_f32[i],8);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("Shw = [");
		for(i = 0; i < N; i++) {
			Serial.print(w_f32[i],8);
			Serial.print(", ");
		}
		Serial.println("];");

		arm_power_f32(e_f32,T,&mse[k]);
		arm_mean_f32(&mse[k],1,&mse[k]);

		Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");

		delay(100);
	}

	Serial.println("inf = 0");
	Serial.println("nan = 0");
	Serial.println("ovf = 0");

	Serial.print("MSE = [");
	for(i = 0; i < MAX_LOOP; i++) {
		Serial.print(mse[i],8);
		Serial.print(", ");
	}
	Serial.println("];");

	q15_t w_q15[256];

	arm_float_to_q15(w_f32,w_q15,N);
	Serial.print("Shw_q15 = [");
	for(i = 0; i < N; i++) {
		Serial.print(w_q15[i]);
		Serial.print(", ");
	}
	Serial.println("];");

	Serial.print("AudioMemoryUsageMax = ");
	Serial.println(AudioMemoryUsageMax());
	Serial.print("AudioProcessorUsageMax = ");
	Serial.println(AudioProcessorUsageMax());

	noise1.amplitude(0.0); // disable white noise

	/// Finish program
	while(1);
	//==================================================================================================================//
}



