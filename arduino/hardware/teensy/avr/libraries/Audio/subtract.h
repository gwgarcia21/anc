#ifndef subtract_h_
#define subtract_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "arm_math.h"

class AudioSubtract : public AudioStream
{
public:
	AudioSubtract(void): AudioStream(2,inputQueueArray){}

	virtual void update(void) {
		audio_block_t * in0, * in1, * out=NULL;

		in0 = receiveReadOnly(0);
		if (!in0) return;
		
		in1 = receiveReadOnly(1);
		if (!in1) return;
		
		out = allocate();

		if (out) {
			arm_sub_q15((q15_t *)in0->data, (q15_t *)in1->data, (q15_t *)out->data, AUDIO_BLOCK_SAMPLES);
			transmit(out);
			release(out);
		}
		release(in0);
		release(in1);
	}
private:
	audio_block_t *inputQueueArray[2];
};

#endif
