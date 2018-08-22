#include "global_def.h"

// GUItool: begin automatically generated code
AudioInputI2S            mic;            //xy=121,322
AudioMixer4              mixer1;         //xy=265,289
AudioMixer4              mixer2;         //xy=267,395
AudioFilterFIR           shw;            //xy=429,361
AudioAdaptiveFxFIR       adaptive_fx_fir1; //xy=749,395
AudioMixer4              mixer3;         //xy=943.4000358581543,389.0000057220459
AudioOutputI2S           headphone;      //xy=1130.0001373291016,396.0000057220459
AudioConnection          patchCord1(mic, 0, mixer2, 0);
AudioConnection          patchCord2(mic, 1, mixer1, 0);
AudioConnection          patchCord3(mixer1, shw);
AudioConnection          patchCord4(mixer2, 0, adaptive_fx_fir1, 2);
AudioConnection          patchCord5(shw, 0, adaptive_fx_fir1, 1);
AudioConnection          patchCord6(shw, 0, adaptive_fx_fir1, 0);
AudioConnection          patchCord7(adaptive_fx_fir1, 0, mixer3, 0);
AudioConnection          patchCord8(mixer3, 0, headphone, 0);
AudioConnection          patchCord9(mixer3, 0, headphone, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=614,90
// GUItool: end automatically generated code

#define T 128 // audio block size
#define MODE 3 // 0: pipe 1: headphone 2: simulation 3: tests
////////////////////////////////////////////////////////////////////////

#if MODE == 0

#define N 128 // filter length
#define MAX_LOOP 50 // maximum number of loops
float32_t Ww[N] = { 0.0 }; // Ww coefficients
float32_t mu = 0.000005; // learning coefficient

const q15_t filtroShw[N] = {
    -313, -380, -310, -236, 21, -59, -71, -154, -273, -103,
    -47, 68, 72, 40, -48, 30, 34, 17, 342, 71, 28, 93, -181,
    269, 192, -111, 270, 315, -241, 177, 221, -169, 228, -81,
    480, 56, -533, 614, 30, -561, 417, 451, -297, -3,193, 78,
    27, -169, 303, -24, -483, 262, -176, -411, 183, -43, -209,
    -190, -35, -48, -125, -91, -64, 78, -40, 44, 52, -15, -94,
    198, 44, -177, 465, -114, -185, 118, 40, 180, -82, 54,
    223, 50, -56, 251, -75, -81, 296, 51, -229, -19, 465,
    -231, -163, 276, 20, 126, -103, -94, 178, 22, 8, 394, -92,
    -99, 232, -470, -170, 481, -51, -182, 28, -308, -36, 0,
    -315, 195, 16, -526, -47, 385, -232, -18, 17, -453, 304,
    -398, -204, 697
};

#elif MODE == 1

#define N 128 // filter length
#define MAX_LOOP 50 // maximum number of loops
float32_t Ww[N] = { 0.0 }; // Ww coefficients
float32_t mu = 0.00005; // learning coefficient

#elif MODE == 2

#define N 56 // filter length
#define MAX_LOOP 50 // maximum number of loops
float32_t Ww[N] = { 0.0 }; // Ww coefficients
float32_t mu = 0.001; // learning coefficient
const q15_t filtroSw[N] = {
		-999, -129, -137, -129, -114, -97, -73, -32, -2, 50,
		109, 169, 233, 308, 383, 460, 541, 619, 693, 772, 844,
		905, 973, 1020, 1057, 1083, 1119, 1120, 1119, 1119,
		1084, 1058, 1022, 974, 905, 844, 773, 693, 620, 542,
		461, 384, 307, 233, 169, 110, 50, -3, -33, -72, -97,
		-114, -128, -136, -128, -1001
}; // Low-pass filter 1.5 kHz 20 dB

const q15_t filtroShw[N] = {
		-999, -129, -137, -129, -114, -97, -73, -32, -2, 50,
		109, 169, 233, 308, 383, 460, 541, 619, 693, 772, 844,
		905, 973, 1020, 1057, 1083, 1119, 1120, 1119, 1119,
		1084, 1058, 1022, 974, 905, 844, 773, 693, 620, 542,
		461, 384, 307, 233, 169, 110, 50, -3, -33, -72, -97,
		-114, -128, -136, -128, -1001
};

const q15_t filtroPw[N] = {
		-1997, -258, -273, -258, -229, -195, -146, -65, -4, 100,
		218, 337, 467, 615, 767, 921, 1083, 1239, 1385, 1545,
		1687, 1810, 1945, 2041, 2114, 2167, 2237, 2240, 2239,
		2237, 2169, 2116, 2044, 1947, 1810, 1688, 1545, 1386,
		1240, 1084, 922, 768, 615, 466, 338, 220, 100, -5,
		-66, -145, -194, -228, -255, -271, -257, -2002
}; // Low-pass filter 1.5  kHz 20 dB

#elif MODE == 3

#define N 128 // filter length
#define MAX_LOOP 200 // maximum number of loops
float32_t Ww[N] = { 0.0 }; // Ww coefficients
float32_t mu = -0.000001; // learning coefficient

const q15_t filtroShw[N] = {
		201, -91, -58, 80, 195, 331, -105, -44, 203, 212, 406, 229, 197, 135, -56, -18, 232, 426, 113, 31, 208, 333, 404, 179, -134, -30, 171, 188, 271, 91, -91, 15, 138, 144, 83, -86, 42, 139, 126, -12, -86, 219, 209, 111, -148, -101, 158, 78, -45, -16, 273, 295, 41, -190, -100, -26, 64, 301, -245, -159, 215, 229, 307, -9, -35, -68, 71, 253, -193, 36, 427, 262, 224, 29, 217, 353, -85, -318, -207, 260, 296, -130, -11, 90, 107, -14, -126, 2, -207, -150, -30, -148, 23, -52, -39, 6, -180, -209, -140, -66, -169, -254, -387, -81, 157, -101, -121, -207, -196, -78, -151, -146, -147, -233, -297, -145, 13, -178, -295, -50, -46, -83, -231, -299, -87, 45, 34, -188
};

#endif

arm_lms_norm_instance_f32 * fxlms; // FxLMS data structure

AdaptiveFxFIRResults* AdaptiveFxFIRResults::instance = 0;

void setup() {
	//==================================================================================================================//
	// Enable serial communication, set audio memory and enable chip
	Serial.begin(38400);
	AudioMemory(200);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.2);
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.lineInLevel(1); // default = 5
    mixer1.gain(0,1.0); // input mic gain
	mixer2.gain(0,1.0); // error mic gain
	shw.begin(filtroShw,N); // Shw filter
	//shw.begin(FIR_PASSTHRU,0); // pass thru
	adaptive_fx_fir1.begin(mu, Ww, N);
    mixer3.gain(0,1.0); // adaptive filter output gain
	//==================================================================================================================//
}

void loop()
{
	//==================================================================================================================//
	int k = 0;
	int i = 0;
	float32_t minCoeff;
	uint32_t index;
	//float32_t Sw_f32[N] = { 0.0 };
	float32_t w[N] = { 0.0 };
	float32_t mse[1024] = { 0.0 };

	Serial.println("Start!");

	//while(1); // !!! INFINITE !!!

	/// Signals
	for(k = 0 ; k < MAX_LOOP ; k++) {
	//while(1) {
		Serial.println("%%%%%%%%%%%%%%%FxNLMS%%%%%%%%%%%%%%%");
		Serial.print("Frame = ");
		Serial.println(k);

		Serial.print("mu = ");
		Serial.print(mu,8);
		Serial.println(";");

		float32_t x_f32[256], fx_f32[256], d_f32[256], y_f32[256], e_f32[256], w_f32[256];
		AdaptiveFxFIRResults * adapter = AdaptiveFxFIRResults::getInstance();

		arm_copy_f32(adapter->x,x_f32,T);
		arm_copy_f32(adapter->fx,fx_f32,T);
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

		Serial.print("fx = [");
		for(i = 0; i < T; i++) {
			Serial.print(fx_f32[i],8);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("e_in = [");
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

		Serial.print("Ww = [");
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

	Serial.print("AudioMemoryUsageMax = ");
	Serial.println(AudioMemoryUsageMax());
	Serial.print("AudioProcessorUsageMax = ");
	Serial.println(AudioProcessorUsageMax());

    mixer3.gain(0,0.0); // disable adaptive filter

	/// Finish program
	while(1);
	//==================================================================================================================//
}
