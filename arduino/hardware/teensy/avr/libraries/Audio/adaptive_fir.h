/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Pete (El Supremo)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef adaptive_fir_h_
#define adaptive_fir_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "arm_math.h"

// Indicates that the code should just pass through the audio
// without any filtering (as opposed to doing nothing at all)
#define LMS_PASSTHRU ((float32_t *) 1)

#define LMS_MAX_COEFFS 400

#define DELTA_ERROR         0.000001f
#define DELTA_COEFF         0.0001f

class AudioAdaptiveFIR : public AudioStream
{
public:
	AudioAdaptiveFIR(void): AudioStream(2,inputQueueArray), coeff_p(NULL) {
	} 

	void begin(float32_t mu, float32_t *ww, uint16_t n_coeffs) {
		coeff_p = ww;
		// Initialize FIR instance (ARM DSP Math Library)
		if (coeff_p && (coeff_p != LMS_PASSTHRU) && n_coeffs <= LMS_MAX_COEFFS) {
			arm_lms_norm_init_f32(&lms_inst, n_coeffs, (float32_t *)coeff_p,
				&StateF32[0], mu, AUDIO_BLOCK_SAMPLES);
		}
	}

	arm_lms_norm_instance_f32 * print(void) {
		return &lms_inst;
	}
	
	q15_t * print_coeff(void) {
		return (q15_t *)coeff_p;
	}

	void end(void) {
		coeff_p = NULL;
	}

	virtual void update(void);
private:
	audio_block_t *inputQueueArray[2];

	// pointer to current coefficients or NULL or FIR_PASSTHRU
	float32_t *coeff_p;

	// ARM DSP Math library filter instance
	arm_lms_norm_instance_f32 lms_inst;
	float32_t StateF32[AUDIO_BLOCK_SAMPLES + LMS_MAX_COEFFS];
};

#endif
