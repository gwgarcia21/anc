#include "global_def.h"

// MIC LEFT
/*
// GUItool: begin automatically generated code
AudioInputI2S            mic;            //xy=231,374
AudioSynthWaveformSine   sine1;          //xy=235.00000381469727,316.0000033378601
AudioMixer4              mixer1;         //xy=390,385
AudioFilterFIR           fir1;           //xy=392,322
AudioAdaptiveFIR         adaptive_fir1;  //xy=580,354
AudioOutputI2S           headphone;      //xy=878,356
AudioConnection          patchCord1(mic, 0, mixer1, 0);
AudioConnection          patchCord2(sine1, fir1);
AudioConnection          patchCord3(mixer1, 0, adaptive_fir1, 1);
AudioConnection          patchCord4(fir1, 0, adaptive_fir1, 0);
AudioConnection          patchCord5(fir1, 0, headphone, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=569,86
// GUItool: end automatically generated code
*/

// MIC RIGHT
// GUItool: begin automatically generated code
AudioInputI2S            mic;            //xy=231,374
AudioSynthWaveformSine   sine1;          //xy=235.00000381469727,316.0000033378601
AudioMixer4              mixer1;         //xy=390,385
AudioFilterFIR           fir1;           //xy=392,322
AudioAdaptiveFIR         adaptive_fir1;  //xy=580,354
AudioOutputI2S           headphone;      //xy=878,356
AudioConnection          patchCord1(mic, 1, mixer1, 0);
AudioConnection          patchCord2(sine1, fir1);
AudioConnection          patchCord3(mixer1, 0, adaptive_fir1, 1);
AudioConnection          patchCord4(fir1, 0, adaptive_fir1, 0);
AudioConnection          patchCord5(fir1, 0, headphone, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=569,86
// GUItool: end automatically generated code


#define T 128 // audio block size
#define F_LEN 56 // filter length 1.5 kHz
#define N_PARTS 50 // number of print parts
#define MAX_LOOP 100 // number of loops before print
#define SAMPLES MAX_LOOP*T // number of samples per part

const q15_t filtroPB[F_LEN] = {
		-1604,   -228,   -231,   -224,   -207,   -178,   -138,    -86,    -22,
		54,    140,    237,    343,    458,    577,    701,    826,    953,
		1078,   1196,   1310,   1414,   1508,   1588,   1655,   1707,   1742,
		1759,   1759,   1742,   1707,   1655,   1588,   1508,   1414,   1310,
		1196,   1078,    953,    826,    701,    577,    458,    343,    237,
		140,     54,    -22,    -86,   -138,   -178,   -207,   -224,   -231,
		-228,  -1604
}; // Low-pass filter 1.5 kHz 20 dB

float32_t min_Shw[156] = { 0.0 };
uint16_t N = 156; // adaptive filter length
float32_t mu = 0.3; // learning coefficient
float32_t *ww = min_Shw;

arm_lms_norm_instance_f32 * lms;

AdaptiveFIRResults* AdaptiveFIRResults::instance = 0;

#define DEBUG 1 // 0: print nothing 1: print signals 2: print coefficients
#define DELTA_COEFF 0.0001f

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
	sgtl5000_1.volume(0.4);
	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
	sgtl5000_1.lineInLevel(15); // default = 5
	//noise1.amplitude(0.6);
	sine1.amplitude(0.6);
	sine1.frequency(400);
	//fir1.begin(filtroPB,F_LEN);
	fir1.begin(FIR_PASSTHRU,0);
	mixer1.gain(0,5.0);
	//sw.begin(FIR_PASSTHRU,0); // pass thru
	adaptive_fir1.begin(mu, min_Shw, N);
	//adaptive_fir1.begin(mu, LMS_PASSTHRU, 0);
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
	//delay(100);

	/// Signals
	for(k = 0 ; k < MAX_LOOP ; k++) {
		q15_t x_q15[256], d_q15[256], y_q15[256], e_q15[256];

		AdaptiveFIRResults * adapter = AdaptiveFIRResults::getInstance();

		arm_float_to_q15(adapter->x,x_q15,T);
		arm_float_to_q15(adapter->d,d_q15,T);
		arm_float_to_q15(adapter->y,y_q15,T);
		arm_float_to_q15(adapter->e,e_q15,T);

		Serial.print("x");
		Serial.println(" = [");
		for(i = 0; i < T; i++) {
			Serial.print(x_q15[i]);
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
		//delay(100);
	}

	q15_t * shw;
	lms = adaptive_fir1.print();
	shw = adaptive_fir1.print_coeff();

	Serial.print("Shw_f32");
	Serial.println(" = [");
	for(i = 0; i < lms->numTaps; i++) {
		Serial.print(lms->pCoeffs[i],6);
		Serial.print(", ");
	}
	Serial.println("];");

	arm_float_to_q15(lms->pCoeffs,shw,lms->numTaps);

	Serial.print("Shw");
	Serial.println(" = [");
	for(i = 0; i < lms->numTaps; i++) {
		Serial.print(shw[i]);
		Serial.print(", ");
	}
	Serial.println("];");

	Serial.print("N_SUCCESS = ");
	Serial.println(n_success);

	sine1.amplitude(0.0);
	//noise1.amplitude(0.0);

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


