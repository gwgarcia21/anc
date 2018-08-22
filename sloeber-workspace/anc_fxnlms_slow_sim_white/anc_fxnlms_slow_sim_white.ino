#include "global_def.h"

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=60,165.00000286102295
AudioFilterFIR           shw;            //xy=219,264
AudioInputI2S            mic;            //xy=250,549
AudioAdaptiveFxFIR       adaptive_fx_fir1; //xy=417,279
AudioFilterFIR           pw;             //xy=490,213
AudioFilterFIR           sw;             //xy=569,281
AudioMixer4              mixer1;         //xy=740,217
AudioOutputI2S           headphone;      //xy=941,411
AudioConnection          patchCord1(noise1, pw);
AudioConnection          patchCord2(noise1, 0, headphone, 1);
AudioConnection          patchCord3(noise1, shw);
AudioConnection          patchCord4(shw, 0, adaptive_fx_fir1, 1);
AudioConnection          patchCord5(shw, 0, adaptive_fx_fir1, 0);
AudioConnection          patchCord6(adaptive_fx_fir1, sw);
AudioConnection          patchCord7(pw, 0, mixer1, 0);
AudioConnection          patchCord8(sw, 0, mixer1, 1);
AudioConnection          patchCord9(mixer1, 0, headphone, 0);
AudioConnection          patchCord10(mixer1, 0, adaptive_fx_fir1, 2);
AudioControlSGTL5000     sgtl5000_1;     //xy=563,86
// GUItool: end automatically generated code


#define T 128 // audio block size
#define MODE 1 // 0: low-pass filter 1: random filter
////////////////////////////////////////////////////////////////////////

#if MODE == 0

#define MAX_LOOP 1000 // maximum number of loops
#define N 56 // filter length
float32_t Shw[N] = { 0.0 }; // Shw coefficients
float32_t mu = 0.0001; // learning coefficient
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

#elif MODE == 1

#define MAX_LOOP 1000 // maximum number of loops
#define N 128 // filter length
float32_t Shw[N] = { 0.0 }; // Shw coefficients
float32_t mu = 0.00001; // learning coefficient
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
};

const q15_t filtroShw[N] = {
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
};

const q15_t filtroPw[N] = {
		1648, -487, 1530, -229, -2616, 502, -318, 1144, -1402,
		1493, 2480, -3057, 1605, 1258, 2459, -1696, 2138, 1962,
		1979, -2655, 871, 2519, -1347, -1581, 385, 2164, 1575,
		-2071, 2302, 1268, -2821, 2863, 346, 211, -1146, 1523,
		-1297, -1893, -2287, -2625, -2092, 2220, -1061, 1647,
		2643, 103, -466, -1777, -805, 3247, -1392, -2415, 76,
		1531, -1204, -2862, 2405, 1041, -2324, 981, -2007, 2623,
		3148, 259, -1558, -328, -3245, -749, 344, 2567, -1563,
		1436, -2931, 1797, 1486, -711, 479, -789, -862, 1486,
		2327, 1076, 951, 562, -1133, -1747, 527, 1769, -1916,
		1601, -199, 3181, -758, 3178, 123, 1448, -1581, 3043,
		2801, -2223, -2792, -1939, 282, -205, -1413, 2668,
		-1013, 265, -2789, -369, 1252, -2845, 455, -327,
		-3160, 1750, 358, -3153, -1042, 770, -2333, -3183,
		529, 791, 653, -1078, 2068, -714
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
	sgtl5000_1.volume(0.7);
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.lineInLevel(15); // default = 5
	noise1.amplitude(0.5);
	pw.begin(filtroPw,N);
	sw.begin(filtroSw,N);
	//sw.begin(FIR_PASSTHRU,0); // pass thru
	shw.begin(filtroShw,N);
	//shw.begin(FIR_PASSTHRU,0); // pass thru
	adaptive_fx_fir1.begin(mu, Shw, N);
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
	//float32_t Sw_f32[N] = { 0.0 };
	float32_t w[N] = { 0.0 };
	float32_t mse[1024] = { 0.0 };

	Serial.println("Start!");

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

	/// Finish program
	while(1);
	//==================================================================================================================//
}


