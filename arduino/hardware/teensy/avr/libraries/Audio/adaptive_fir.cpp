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

#include "adaptive_fir.h"
#include "adaptive_fir_results.h"

void AudioAdaptiveFIR::update(void)
{
	audio_block_t *in, *ref, *out=NULL, *err=NULL;

	float32_t x_data[128] = { 0.0 };
	float32_t d_data[128] = { 0.0 };
	float32_t y_data[128] = { 0.0 };
	float32_t e_data[128] = { 0.0 };
	
	in = receiveReadOnly(0);
	if (!in) return;
	
	ref = receiveReadOnly(1);
	if (!ref) return;

	// If there's no coefficient table, give up.  
	if (coeff_p == NULL) {
		release(in);
		release(ref);
		return;
	}

	// do passthru
	if (coeff_p == LMS_PASSTHRU) {
		// Just passthrough
		transmit(in);
		release(in);
		//transmit(ref,1);
		release(ref);
		return;
	}
	
	arm_q15_to_float((q15_t *)in->data, (float32_t *)x_data, AUDIO_BLOCK_SAMPLES);
	arm_q15_to_float((q15_t *)ref->data, (float32_t *)d_data, AUDIO_BLOCK_SAMPLES);
	//arm_scale_f32(in->data, 5, wire3, BLOCKSIZE); // se necessário para aumentar/diminuir sinal
	
	/// FxLMS experimental
	//arm_scale_f32((float32_t *)x_data, 10.0, (float32_t *)x_data, AUDIO_BLOCK_SAMPLES);
	//arm_scale_f32((float32_t *)d_data, 10.0, (float32_t *)d_data, AUDIO_BLOCK_SAMPLES);
	
	// get a block for the FIR output
	out = allocate();
	err = allocate();
	if (out && err) {
		arm_lms_norm_f32(&lms_inst, (float32_t *)x_data,
				(float32_t *)d_data, (float32_t *)y_data,
				(float32_t *)e_data, AUDIO_BLOCK_SAMPLES);
				
		//arm_negate_f32((float32_t *)y_data, (float32_t *)y_data, AUDIO_BLOCK_SAMPLES); // FxLMS?
		
		//arm_sub_f32((float32_t *)y_data, (float32_t *)y_data, AUDIO_BLOCK_SAMPLES); // FxLMS?
		
		arm_float_to_q15((float32_t *)y_data, (q15_t *)out->data, AUDIO_BLOCK_SAMPLES);
		arm_float_to_q15((float32_t *)e_data, (q15_t *)err->data, AUDIO_BLOCK_SAMPLES);
		
		AdaptiveFIRResults* adapter = AdaptiveFIRResults::getInstance();
		adapter->x = x_data;
		adapter->d = d_data;
		adapter->y = y_data;
		adapter->e = e_data;
		adapter->w = coeff_p;
		//arm_power_f32((float32_t *)e_data, AUDIO_BLOCK_SAMPLES, (float32_t *)adapter->mse);
		//arm_mean_f32((float32_t *)adapter->mse, AUDIO_BLOCK_SAMPLES, (float32_t *)adapter->mse);
		
		transmit(out); // LMS
		release(out);
		//transmit(err); // FxLMS
		release(err);
	}
	release(in);
	release(ref);
}
