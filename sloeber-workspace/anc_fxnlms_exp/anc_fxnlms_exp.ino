#include "global_def.h"

// GUItool: begin automatically generated code
AudioInputI2S            mic;            //xy=124,288
AudioMixer4              mixer1;         //xy=268,255
AudioMixer4              mixer2;         //xy=270.00000381469727,361.0000057220459
AudioFilterFIR           shw;            //xy=432.0000057220459,327.0000047683716
AudioAdaptiveFxFIR       adaptive_fx_fir1; //xy=752,361
AudioOutputI2S           headphone;      //xy=972.0000152587891,358.00000381469727
AudioConnection          patchCord1(mic, 0, mixer2, 0);
AudioConnection          patchCord2(mic, 1, mixer1, 0);
AudioConnection          patchCord3(mixer1, shw);
AudioConnection          patchCord4(mixer1, 0, adaptive_fx_fir1, 0);
AudioConnection          patchCord5(mixer2, 0, adaptive_fx_fir1, 2);
AudioConnection          patchCord6(shw, 0, adaptive_fx_fir1, 1);
AudioConnection          patchCord7(adaptive_fx_fir1, 0, headphone, 1);
AudioConnection          patchCord8(adaptive_fx_fir1, 0, headphone, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=617,56
// GUItool: end automatically generated code

#define T 128 // audio block size
#define F_LEN 56 // filter length 1.5 kHz
#define N_PARTS 50 // number of print parts
#define MAX_LOOP 100 // number of loops before print
#define SAMPLES MAX_LOOP*T // number of samples per part
#define mu 0.00002 // learning coefficient
#define N 156 // adaptive filter length
#define DELTA_COEFF 0.0001f

q15_t filtroPB[F_LEN] = {
		-1604,   -228,   -231,   -224,   -207,   -178,   -138,    -86,    -22,
		54,    140,    237,    343,    458,    577,    701,    826,    953,
		1078,   1196,   1310,   1414,   1508,   1588,   1655,   1707,   1742,
		1759,   1759,   1742,   1707,   1655,   1588,   1508,   1414,   1310,
		1196,   1078,    953,    826,    701,    577,    458,    343,    237,
		140,     54,    -22,    -86,   -138,   -178,   -207,   -224,   -231,
		-228,  -1604
}; // Low-pass filter 1.5 kHz 20 dB

float32_t min_Shw[N] = { 0.0 };

q15_t filtroShw[N] = {
		48, -256, -19, 136, 182, -208, -46, 7, -28, 146, -50,
		-218, 171, 235, -19, -180, 21, -36, -16, -50, -117, 475,
		-216, -52, -45, 6, 144, -18, -280, 31, 321, -217, -58,
		361, -12, -272, 200, -57, 99, -160, -108, -108, -78,
		-93, -44, 290, -16, 100, -102, -177, -88, 71, 94, -121,
		-172, 420, 148, -227, -30, 352, -198, -223, -22, 29,
		116, -39, 148, -93, 143, -448, -7, 393, -51, -127, 5,
		71, 45, 56, -47, 22, -61, 36, -24, 229, -50, -199, 363,
		154, -331, 141, -10, -271, 309, -85, -178, 256, 11, 42,
		211, -239, -234, 88, -35, 160, 89, -187, 427, 167,
		-169, -78, 124, -225, 111, -162, -153, 432, -295, 43,
		44, 237, -34, 134, -325, -468, 468, -116, -432, -48,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

arm_lms_norm_instance_f32 * fxlms;

AdaptiveFxFIRResults* AdaptiveFxFIRResults::instance = 0;

#define DEBUG 1 // 0: print nothing 1: print signals 2: print coefficients

/// Buffer variables
RingBuffer *ringBuffSaveX = criarRB(); // save x buffer (LMS)
RingBuffer *ringBuffSaveD = criarRB(); // save d buffer (LMS)
RingBuffer *ringBuffSaveY = criarRB(); // save y buffer (LMS)
RingBuffer *ringBuffSaveE = criarRB(); // save error mic buffer (LMS)
RingBuffer *ringBuffSaveShw = criarRB(); // save filter coefficients buffer (LMS)

void setup() {
	//==================================================================================================================//
	// Enable serial communication, set audio memory and enable chip
	Serial.begin(38400);
	AudioMemory(200);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.7);
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.lineInLevel(15); // default = 5
	mixer1.gain(0,10.0);
	mixer2.gain(0,5.0);
	//shw.begin(filtroShw,N);
	//shw.begin(FIR_PASSTHRU,0); // pass thru
	shw.begin(filtroShw,N);
	//sw.begin(FIR_PASSTHRU,0); // pass thru
	adaptive_fx_fir1.begin(mu, min_Shw, N);
	//adaptive_fx_fir1.begin(mu, filtroShw, N);
	//==================================================================================================================//
}

void loop()
{
	//==================================================================================================================//
	int k = 0;
	int p = 0;
	int i = 0;
	int n = 0;
	int j = 0;
	float32_t minValue;
	uint32_t index;
	int n_success = 0;

	Serial.println("Start!");
	//while(1);
	//delay(1000);

	/// Signals
	//for(k = 0 ; k < MAX_LOOP ; k++) {
	while(1) {
		q15_t x_q15[256], fx_q15[256], d_q15[256], y_q15[256], e_q15[256], w_q15[256];
		AdaptiveFxFIRResults * adapter = AdaptiveFxFIRResults::getInstance();

		arm_float_to_q15(adapter->x,x_q15,T);
		arm_float_to_q15(adapter->fx,fx_q15,T);
		arm_float_to_q15(adapter->d,d_q15,T);
		arm_float_to_q15(adapter->y,y_q15,T);
		arm_float_to_q15(adapter->e,e_q15,T);
		arm_float_to_q15(adapter->w,w_q15,T);

		Serial.print("x");
		Serial.println(" = [");
		for(i = 0; i < T; i++) {
			Serial.print(x_q15[i]);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("fx");
		Serial.println(" = [");
		for(i = 0; i < T; i++) {
			Serial.print(fx_q15[i]);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("d");
		Serial.println(" = [");
		for(i = 0; i < T; i++) {
			Serial.print(d_q15[i]);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("y");
		Serial.println(" = [");
		for(i = 0; i < T; i++) {
			Serial.print(y_q15[i]);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("e");
		Serial.println(" = [");
		for(i = 0; i < T; i++) {
			Serial.print(e_q15[i]);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("e_f32");
		Serial.println(" = [");
		for(i = 0; i < T; i++) {
			Serial.print(adapter->e[i],8);
			Serial.print(", ");
		}
		Serial.println("];");

		arm_abs_f32(adapter->e,adapter->e,T);
		arm_min_f32(adapter->e,T,&minValue,&index);
		arm_abs_f32(&minValue,&minValue,T);

		Serial.print("Ww_f32");
		Serial.println(" = [");
		for(i = 0; i < N; i++) {
			Serial.print(adapter->w[i],6);
			Serial.print(", ");
		}
		Serial.println("];");

		Serial.print("Ww");
		Serial.println(" = [");
		for(i = 0; i < N; i++) {
			Serial.print(w_q15[i]);
			Serial.print(", ");
		}
		Serial.println("];");

		if (minValue > DELTA_COEFF || minValue == 0.0)
		{
			//status = ARM_MATH_TEST_FAILURE;
			Serial.print("FAIL = ");
			Serial.println(minValue,8);
		}
		else {
			Serial.print("SUCCESS = ");
			Serial.println(minValue,8);
			n_success++;
			//break;
		}

		delay(100);
	}


	/// Free ring buffers
	destroiRB(ringBuffSaveX);
	destroiRB(ringBuffSaveD);
	destroiRB(ringBuffSaveY);
	destroiRB(ringBuffSaveE);
	destroiRB(ringBuffSaveShw);

	/// Finish program
	while(1);
	//==================================================================================================================//
}


