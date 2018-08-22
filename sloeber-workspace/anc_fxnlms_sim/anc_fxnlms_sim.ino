#include "global_def.h"

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=327.9999694824219,321.9999848008156
AudioFilterFIR           shw;            //xy=491.9999694824219,372.9999848008156
AudioRecordQueue         varX;           //xy=503.9999694824219,245.99998480081558
AudioInputI2S            mic;            //xy=522.9999694824219,657.9999848008156
AudioRecordQueue         varXhx;         //xy=668.9999694824219,251.99998480081558
AudioAdaptiveFxFIR       adaptive_fx_fir1; //xy=689.0000076293945,387.0000190734863
AudioFilterFIR           pw;             //xy=762.9999694824219,321.9999848008156
AudioFilterFIR           sw;             //xy=841.9999694824219,389.9999848008156
AudioRecordQueue         varY;           //xy=841.9999694824219,490.9999848008156
AudioRecordQueue         varD;           //xy=1007.9999694824219,264.9999848008156
AudioMixer4              mixer1;         //xy=1012.9999694824219,325.9999848008156
AudioRecordQueue         varYl;          //xy=1027.9999694824219,416.9999848008156
AudioOutputI2S           headphone;      //xy=1213.9999694824219,519.9999848008156
AudioRecordQueue         varE;           //xy=1243.9999694824219,325.9999848008156
AudioConnection          patchCord1(sine1, varX);
AudioConnection          patchCord2(sine1, pw);
AudioConnection          patchCord3(sine1, shw);
AudioConnection          patchCord4(sine1, 0, headphone, 1);
AudioConnection          patchCord5(sine1, 0, adaptive_fx_fir1, 0);
AudioConnection          patchCord6(shw, varXhx);
AudioConnection          patchCord7(shw, 0, adaptive_fx_fir1, 1);
AudioConnection          patchCord8(adaptive_fx_fir1, sw);
AudioConnection          patchCord9(pw, 0, mixer1, 0);
AudioConnection          patchCord10(pw, varD);
AudioConnection          patchCord11(sw, 0, mixer1, 1);
AudioConnection          patchCord12(sw, varYl);
AudioConnection          patchCord13(mixer1, 0, headphone, 0);
AudioConnection          patchCord14(mixer1, varE);
AudioConnection          patchCord15(mixer1, 0, adaptive_fx_fir1, 2);
AudioControlSGTL5000     sgtl5000_1;     //xy=835.9999694824219,194.99998480081558
// GUItool: end automatically generated code

#define T 128 // audio block size
#define F_LEN 56 // filter length 1.5 kHz
#define N_PARTS 50 // number of print parts
#define MAX_LOOP 50 // number of loops before print
#define SAMPLES MAX_LOOP*T // number of samples per part
#define mu 0.002 // learning coefficient
#define N 56 // adaptive filter length

q15_t filtroPZ[F_LEN] = {
		-3208, -456, -462, -448, -414, -356, -276, -172, -44,
		108, 280, 474, 686, 916, 1154, 1402, 1652, 1906, 2156,
		2392, 2620, 2828, 3016, 3176, 3310, 3414, 3484, 3518,
		3518, 3484, 3414, 3310, 3176, 3016, 2828, 2620, 2392,
		2156, 1906, 1652, 1402, 1154, 916, 686, 474, 280, 108,
		-44, -172, -276, -356, -414, -448, -462, -456, -3208
}; // Low-pass filter 1.5  kHz 20 dB

q15_t filtroPB[F_LEN] = {
		-1604,   -228,   -231,   -224,   -207,   -178,   -138,    -86,    -22,
		54,    140,    237,    343,    458,    577,    701,    826,    953,
		1078,   1196,   1310,   1414,   1508,   1588,   1655,   1707,   1742,
		1759,   1759,   1742,   1707,   1655,   1588,   1508,   1414,   1310,
		1196,   1078,    953,    826,    701,    577,    458,    343,    237,
		140,     54,    -22,    -86,   -138,   -178,   -207,   -224,   -231,
		-228,  -1604
}; // Low-pass filter 1.5 kHz 20 dB

float32_t min_Shw[56] = { 0.0 };

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
	sine1.amplitude(0.1);
	sine1.frequency(400);
	pw.begin(filtroPZ,F_LEN);
	sw.begin(filtroPB,F_LEN);
	shw.begin(filtroPB,F_LEN);
	//shw.begin(FIR_PASSTHRU,0); // pass thru
	//sw.begin(FIR_PASSTHRU,0); // pass thru
	//adaptive_fir1.begin(mu, min_Shw, N);
	adaptive_fx_fir1.begin(mu, min_Shw, N);
    mixer1.gain(0,1.0);
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
	delay(10000);

	/// Signals
	q15_t x_q15[256], fx_q15[256], d_q15[256], y_q15[256], e_q15[256];
	q15_t ww[N];
	fxlms = adaptive_fx_fir1.print();
	AdaptiveFxFIRResults * adapter = AdaptiveFxFIRResults::getInstance();

	arm_float_to_q15(adapter->x,x_q15,T);
    arm_float_to_q15(adapter->fx,fx_q15,T);
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

	arm_float_to_q15(fxlms->pCoeffs,ww,N);

	Serial.print("Ww");
	Serial.println(" = [");
	for(i = 0; i < fxlms->numTaps; i++) {
		Serial.print(fxlms->pCoeffs[i], 8);
		Serial.print(", ");
	}
	Serial.println("];");

	Serial.print("Ww");
	Serial.println(" = [");
	for(i = 0; i < fxlms->numTaps; i++) {
		Serial.print(ww[i]);
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


