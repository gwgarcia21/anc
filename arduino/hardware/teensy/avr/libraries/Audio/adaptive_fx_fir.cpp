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

#include "adaptive_fx_fir.h"
#include "adaptive_fx_fir_results.h"

void AudioAdaptiveFxFIR::update(void)
{
	audio_block_t *inp, *src, *ref, *out=NULL, *err=NULL;

	float32_t x_data[128] = { 0.0 };
    float32_t fx_data[128] = { 0.0 };
	float32_t d_data[128] = { 0.0 };
	float32_t y_data[128] = { 0.0 };
	float32_t e_data[128] = { 0.0 };
	
	inp = receiveReadOnly(0);
	if (!inp) return;

    src = receiveReadOnly(1);
	if (!src) return;
	
	ref = receiveReadOnly(2);
	if (!ref) return;

	// If there's no coefficient table, give up.  
	if (coeff_p == NULL) {
		transmit(inp);
		release(inp);
        release(src);
		release(ref);
		return;
	}

	// do passthru
	if (coeff_p == FXLMS_PASSTHRU) {
		// Just passthrough
		transmit(inp,0);
		release(inp);
        transmit(src,1);
		release(src);
        transmit(ref,2);
        release(ref);
		return;
	}
	
	arm_q15_to_float((q15_t *)inp->data, (float32_t *)x_data, AUDIO_BLOCK_SAMPLES);
    arm_q15_to_float((q15_t *)src->data, (float32_t *)fx_data, AUDIO_BLOCK_SAMPLES);
	arm_q15_to_float((q15_t *)ref->data, (float32_t *)d_data, AUDIO_BLOCK_SAMPLES);
	
	// get a block for the FIR output
	out = allocate();
	err = allocate();
	if (out && err) {
		arm_fxlms_norm_f32(&fxlms_inst, (float32_t *)x_data, (float32_t *)fx_data,
				(float32_t *)d_data, (float32_t *)y_data,
				(float32_t *)e_data, AUDIO_BLOCK_SAMPLES);
		
		arm_float_to_q15((float32_t *)y_data, (q15_t *)out->data, AUDIO_BLOCK_SAMPLES);
		arm_float_to_q15((float32_t *)e_data, (q15_t *)err->data, AUDIO_BLOCK_SAMPLES);
		
		AdaptiveFxFIRResults* adapter = AdaptiveFxFIRResults::getInstance();
		adapter->x = x_data;
        adapter->fx = fx_data;
		adapter->d = d_data;
		adapter->y = y_data;
		adapter->e = e_data;
		adapter->w = coeff_p;
		
		transmit(out);
		release(out);
		release(err);
	}
	release(inp);
    release(src);
	release(ref);
}
