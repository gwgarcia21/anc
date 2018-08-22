#include "global_def.h"

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=223,300
AudioInputI2S            mic;            //xy=249,597
AudioFilterFIR           sw;             //xy=350,405
AudioRecordQueue         varX;           //xy=366,191
AudioRecordQueue         varD;           //xy=539,504
AudioAdaptiveFIR         adaptive_fir1;  //xy=573,402
AudioMixer4              mixer1;         //xy=757,275
AudioRecordQueue         varY;           //xy=854,506
AudioOutputI2S           headphone;      //xy=871,404
AudioRecordQueue         varE;         //xy=912.0000305175781,275.00000953674316
AudioConnection          patchCord1(noise1, 0, adaptive_fir1, 0);
AudioConnection          patchCord2(noise1, sw);
AudioConnection          patchCord3(noise1, 0, headphone, 1);
AudioConnection          patchCord4(noise1, varX);
AudioConnection          patchCord5(sw, 0, adaptive_fir1, 1);
AudioConnection          patchCord6(sw, varD);
AudioConnection          patchCord7(sw, 0, mixer1, 0);
AudioConnection          patchCord8(adaptive_fir1, varY);
AudioConnection          patchCord9(adaptive_fir1, 0, mixer1, 1);
AudioConnection          patchCord10(mixer1, 0, headphone, 0);
AudioConnection          patchCord11(mixer1, varE);
AudioControlSGTL5000     sgtl5000_1;     //xy=562,134
// GUItool: end automatically generated code

#define T 128 // audio block size
#define F_LEN 56 // filter length 1.5 kHz
#define N_PARTS 50 // number of print parts
#define MAX_LOOP 50 // number of loops before print
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

const q15_t filtroRand[F_LEN] = {
		-7367, -16188, 9892, -86, 1239, 12153, 7301, 5507, -10525, 1654,
		15068, 3145, 10110, 15876, 12645, -9378, -15250, -1603, -15932, -862,
		14783, -8227, -3723, -2248, 10841, 10637, -1541, -3915, 13953, 7891,
		7786, 14643, 330, 9563, -1568, 11441, -3591, 7810, 15610, 762, -2297,
		-9597, -5788, -12752, -4090, -5575, -5175, 10390, 1037, 691, 8987,
		-12444, 4110, -5026, -5420, 2444
};

float32_t min_Shw[56] = { 0.0 };
uint16_t N = 56; // adaptive filter length
float32_t mu = 0.2; // learning coefficient
float32_t *ww = min_Shw;

arm_lms_norm_instance_f32 * lms;

AdaptiveFIRResults* AdaptiveFIRResults::instance = 0;

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
	noise1.amplitude(0.6);
	//sw.begin(filtroPB,F_LEN);
	sw.begin(filtroRand,F_LEN);
	//sw.begin(FIR_PASSTHRU,0); // pass thru
	adaptive_fir1.begin(mu, min_Shw, N);
	mixer1.gain(0,1.0);
	mixer1.gain(1,1.0);
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

	Serial.println("Start!");
	//while(1);
	delay(2500);

	/// Signals
	q15_t x_q15[256], d_q15[256], y_q15[256], e_q15[256];
	q15_t * shw;
	lms = adaptive_fir1.print();
	shw = adaptive_fir1.print_coeff();
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

	arm_float_to_q15(lms->pCoeffs,shw,lms->numTaps);

	Serial.print("Shw");
	Serial.println(" = [");
	for(i = 0; i < lms->numTaps; i++) {
		Serial.print(shw[i]);
		Serial.print(", ");
	}
	Serial.println("];");

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


