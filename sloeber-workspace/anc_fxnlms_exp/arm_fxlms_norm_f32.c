

#include "arm_math.h"

void arm_fxlms_norm_f32(arm_lms_norm_instance_f32 * S, float32_t * pInp, float32_t * pSrc, float32_t * pRef, float32_t * pOut, float32_t * pErr, uint32_t blockSize)
{
	/// coeff -> w
	/// px -> state
	/// pb -> coeff
	/// numTaps -> N
	/// w -> w
	/// x0 -> inp
	///

	float32_t *pState = S->pState;                 /* State pointer */
	float32_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
	float32_t *pStateCurnt;                        /* Points to the current sample of the state */
	float32_t *px, *pb;                            /* Temporary pointers for state and coefficient buffers */
	float32_t mu = S->mu;                          /* Adaptive factor */
	uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
	uint32_t tapCnt, blkCnt;                       /* Loop counters */
	float32_t energy;                              /* Energy of the input */
	float32_t sum, e, d;                           /* accumulator, error, reference data sample */
	float32_t w, x0, in;                           /* weight factor, temporary variable to hold input sample and state */

	/* Initializations of error,  difference, Coefficient update */
	e = 0.0f;
	d = 0.0f;
	w = 0.0f;

	energy = S->energy;
	x0 = S->x0;

	/* S->pState points to buffer which contains previous frame (numTaps - 1) samples */
	/* pStateCurnt points to the location where the new input data should be written */
	pStateCurnt = &(S->pState[(numTaps - 1u)]);

	/* Loop over blockSize number of values */
	blkCnt = blockSize;

	/* Run the below code for Cortex-M4 and Cortex-M3 */

	while(blkCnt > 0u)
	{
		/* Copy the new input sample into the state buffer */
		*pStateCurnt++ = *pInp;

		/* Initialize pState pointer */
		px = pState;

		/* Initialize coeff pointer */
		pb = (pCoeffs);

		/* Read the sample from input buffer */
		in = *pInp++;

		/* Update the energy calculation */
		energy -= x0 * x0;
		energy += in * in;

		/* Set the accumulator to zero */
		sum = 0.0f;

		/* Loop unrolling.  Process 4 taps at a time. */
		tapCnt = numTaps >> 2;

		while(tapCnt > 0u)
		{
			/* Perform the multiply-accumulate */
			sum += (*px++) * (*pb++);
			sum += (*px++) * (*pb++);
			sum += (*px++) * (*pb++);
			sum += (*px++) * (*pb++);

			/* Decrement the loop counter */
			tapCnt--;
		}

		/* If the filter length is not a multiple of 4, compute the remaining filter taps */
		tapCnt = numTaps % 0x4u;

		while(tapCnt > 0u)
		{
			/* Perform the multiply-accumulate */
			sum += (*px++) * (*pb++);

			/* Decrement the loop counter */
			tapCnt--;
		}

		/* The result in the accumulator, store in the destination buffer. */
		*pOut++ = sum;

		/* Compute and store error */
		d = (float32_t) (*pSrc++);
		//e = d - sum;
		e = (float32_t) (*pRef++);
		*pErr++ = e;

		/* Calculation of Weighting factor for updating filter coefficients */
		/* epsilon value 0.000000119209289f */
		w = (e * mu) / (energy + 0.000000119209289f);

		/* Initialize pState pointer */
		px = pState;

		/* Initialize coeff pointer */
		pb = (pCoeffs);

		/* Loop unrolling.  Process 4 taps at a time. */
		tapCnt = numTaps >> 2;

		/* Update filter coefficients */
		while(tapCnt > 0u)
		{
			/* Perform the multiply-accumulate */
			*pb += w * (*px++);
			pb++;

			*pb += w * (*px++);
			pb++;

			*pb += w * (*px++);
			pb++;

			*pb += w * (*px++);
			pb++;


			/* Decrement the loop counter */
			tapCnt--;
		}

		/* If the filter length is not a multiple of 4, compute the remaining filter taps */
		tapCnt = numTaps % 0x4u;

		while(tapCnt > 0u)
		{
			/* Perform the multiply-accumulate */
			*pb += w * (*px++);
			pb++;

			/* Decrement the loop counter */
			tapCnt--;
		}

		x0 = *pState;

		/* Advance state pointer by 1 for the next sample */
		pState = pState + 1;

		/* Decrement the loop counter */
		blkCnt--;
	}

	S->energy = energy;
	S->x0 = x0;

	/* Processing is complete. Now copy the last numTaps - 1 samples to the
	     satrt of the state buffer. This prepares the state buffer for the
	     next function call. */

	/* Points to the start of the pState buffer */
	pStateCurnt = S->pState;

	/* Loop unrolling for (numTaps - 1u)/4 samples copy */
	tapCnt = (numTaps - 1u) >> 2u;

	/* copy data */
	while(tapCnt > 0u)
	{
		*pStateCurnt++ = *pState++;
		*pStateCurnt++ = *pState++;
		*pStateCurnt++ = *pState++;
		*pStateCurnt++ = *pState++;

		/* Decrement the loop counter */
		tapCnt--;
	}

	/* Calculate remaining number of copies */
	tapCnt = (numTaps - 1u) % 0x4u;

	/* Copy the remaining q31_t data */
	while(tapCnt > 0u)
	{
		*pStateCurnt++ = *pState++;

		/* Decrement the loop counter */
		tapCnt--;
	}
}
