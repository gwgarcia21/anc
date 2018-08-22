#include "global_def.h"

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=175,252
AudioInputI2S            mic;            //xy=201,549
AudioFilterFIR           sw;             //xy=302,357
AudioAdaptiveFIR         adaptive_fir1;  //xy=525,354
AudioMixer4              mixer1;         //xy=709,227
AudioOutputI2S           headphone;      //xy=823,356
AudioConnection          patchCord1(noise1, 0, adaptive_fir1, 0);
AudioConnection          patchCord2(noise1, sw);
AudioConnection          patchCord3(noise1, 0, headphone, 1);
AudioConnection          patchCord4(sw, 0, adaptive_fir1, 1);
AudioConnection          patchCord5(sw, 0, mixer1, 0);
AudioConnection          patchCord6(adaptive_fir1, 0, mixer1, 1);
AudioConnection          patchCord7(mixer1, 0, headphone, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=514,86
// GUItool: end automatically generated code

#define T 128 // audio block size
#define MODE 0 // 0: low-pass filter 1: random filter

////////////////////////////////////////////////////////////////////////
#if MODE == 0

#define N 56 // filter length
#define MAX_LOOP 50 // maximum number of loops
float32_t Shw[N] = { 0.0 }; // Shw coefficients
float32_t mu = 0.01; // learning coefficient
const q15_t filtroSw[N] = {
		-999, -129, -137, -129, -114, -97, -73, -32, -2, 50,
		109, 169, 233, 308, 383, 460, 541, 619, 693, 772, 844,
		905, 973, 1020, 1057, 1083, 1119, 1120, 1119, 1119,
		1084, 1058, 1022, 974, 905, 844, 773, 693, 620, 542,
		461, 384, 307, 233, 169, 110, 50, -3, -33, -72, -97,
		-114, -128, -136, -128, -1001
}; // Low-pass filter 1.5 kHz 20 dB

q15_t Sw[N] = {
		-999, -129, -137, -129, -114, -97, -73, -32, -2, 50,
		109, 169, 233, 308, 383, 460, 541, 619, 693, 772, 844,
		905, 973, 1020, 1057, 1083, 1119, 1120, 1119, 1119,
		1084, 1058, 1022, 974, 905, 844, 773, 693, 620, 542,
		461, 384, 307, 233, 169, 110, 50, -3, -33, -72, -97,
		-114, -128, -136, -128, -1001
}; // Low-pass filter 1.5 kHz 20 dB
////////////////////////////////////////////////////////////////////////
#elif MODE == 1
////////////////////////////////////////////////////////////////////////
#define N 128 // filter length
#define MAX_LOOP 50 // maximum number of loops
float32_t Shw[N] = { 0.0 }; // Shw coefficients
float32_t mu = 0.01; // learning coefficient
const q15_t filtroSw[N] = {
		-2785, 789, 669, 1189, 3120, 292, -1138, 939, 1316, -761,
		2623, -2708, -3029, -1575, -1153, 1548, 2595, 1588, 168,
		3021, -1653, 426, 643, 1193, 665, -1292, -1158, -2244,
		636, 507, 2076, -1855, -2147, 1072, -1235, 1438, -2374,
		-9, -912, -2232, -1020, -2975, -1193, -1738, -763, -1462,
		-153, 2916, -1071, -628, -764, -1056, 542, -12, 226,
		-2042, 2781, 1714, 2512, -234, 553, -199, 1565, -1428,
		-2398, 2491, -1721, 2142, -448, -574, 2540, -1245, 1658,
		2136, 65, -1189, 2047, 2419, -1404, -2656, -364, 1460,
		-733, 1908, 926, -3101, -2724, 455, 2795, -2328, 772,
		-886, 2076, 449, 3187, 1003, -1971, -2719, -2448, 3192,
		3032, 2446, 1755, 453, -2916, 1974, -164, -388, 2777,
		-1587, -2268, -3099, -1734, 1999, -2905, 2521, -829,
		-1968, -1269, -2609, -1865, -1106, 915, 717, -1208,
		-2769, 40, 323
}; // Random filter

q15_t Sw[N] = {
		-2785, 789, 669, 1189, 3120, 292, -1138, 939, 1316, -761,
		2623, -2708, -3029, -1575, -1153, 1548, 2595, 1588, 168,
		3021, -1653, 426, 643, 1193, 665, -1292, -1158, -2244,
		636, 507, 2076, -1855, -2147, 1072, -1235, 1438, -2374,
		-9, -912, -2232, -1020, -2975, -1193, -1738, -763, -1462,
		-153, 2916, -1071, -628, -764, -1056, 542, -12, 226,
		-2042, 2781, 1714, 2512, -234, 553, -199, 1565, -1428,
		-2398, 2491, -1721, 2142, -448, -574, 2540, -1245, 1658,
		2136, 65, -1189, 2047, 2419, -1404, -2656, -364, 1460,
		-733, 1908, 926, -3101, -2724, 455, 2795, -2328, 772,
		-886, 2076, 449, 3187, 1003, -1971, -2719, -2448, 3192,
		3032, 2446, 1755, 453, -2916, 1974, -164, -388, 2777,
		-1587, -2268, -3099, -1734, 1999, -2905, 2521, -829,
		-1968, -1269, -2609, -1865, -1106, 915, 717, -1208,
		-2769, 40, 323
}; // Low-pass filter 1.5 kHz 20 dB
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
	sgtl5000_1.volume(0.7);
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.lineInLevel(15); // default = 5
	noise1.amplitude(0.5);
	sw.begin(filtroSw,N);
	//sw.begin(FIR_PASSTHRU,0); // pass thru
	adaptive_fir1.begin(mu, Shw, N);
	mixer1.gain(0,1.0);
	mixer1.gain(1,1.0);
	//==================================================================================================================//
}

void loop()
{
	//==================================================================================================================//
	int k = 0;
	int i = 0;
	float32_t minCoeff;
	uint32_t index;
	float32_t Sw_f32[N] = { 0.0 };
	float32_t w[N] = { 0.0 };
	float32_t mse[256] = { 0.0 };

	arm_q15_to_float(Sw,Sw_f32,N);

	Serial.println("Start!");
	/// Signals
	for(k = 0 ; k < MAX_LOOP ; k++) {
		Serial.println("%%%%%%%%%%%%%%%NLMS%%%%%%%%%%%%%%%");

		Serial.print("Frame = ");
		Serial.println(k);

		Serial.print("mu = ");
		Serial.print(mu,8);
		Serial.println(";");

		float32_t x_f32[256], d_f32[256], y_f32[256], e_f32[256], w_f32[256];
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

		arm_sub_f32(Sw_f32, w_f32, w, N);
		arm_abs_f32(w, w, N);
		arm_min_f32(w, N, &minCoeff, &index);

		if (minCoeff > DELTA_COEFF)
		{
			Serial.print("Fail = ");
			Serial.println(minCoeff,8);
		}
		else {
			Serial.print("Success = ");
			Serial.println(minCoeff,8);
			//n_success++;
			//break;
		}

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

	Serial.print("AudioMemoryUsageMax = ");
	Serial.println(AudioMemoryUsageMax());
	Serial.print("AudioProcessorUsageMax = ");
	Serial.println(AudioProcessorUsageMax());

	/// Finish program
	while(1);
	//==================================================================================================================//
}


