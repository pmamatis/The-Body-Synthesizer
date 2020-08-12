/*****************************
 * @file    filters.c
 * @author  Max Lehmer
 * @date 	 07 May 2020
 * @brief	 Filter-Library
 * @brief	 Based on Audio-EQ cookbook
 * @brief   https://github.com/libaudioverse/libaudioverse/blob/master/audio%20eq%20cookbook.txt
 ******************************/
#include "filters.h"

/* ------------------------------------------------------------------
 * Global variables for FIR LPF Example
 * ------------------------------------------------------------------- */
uint32_t samplerate = LUT_SR;
float tempo[BLOCKSIZE];

DSP_Status Filters_Init(){

	SetupLowpass(&EQ_BAND1, 20, 0.707);

	return DSP_OK;
}


DSP_Status SetupLowpass(struct BQFilter *LP, float cutoff, float Q){

	float w0 = tanf(M_PI * cutoff / samplerate);
	float N = 1 / (w0 * w0 + w0 / Q + 1);

	LP->b0 = N * w0 * w0;
	LP->b1 = 2 * LP->b0;
	LP->b2 = LP->b0;
	LP->a1 = 2 * N * (w0 * w0 - 1);
	LP->a2 = N * (w0 * w0 - w0 / Q + 1);

	return DSP_OK;
}

DSP_Status SetupHighpass(struct BQFilter *HP, float cutoff, float Q){

	float w0 = tanf(M_PI * cutoff / samplerate);
	float N = 1 / (w0 * w0 + w0 / Q + 1);

	HP->b0 = N;
	HP->b1 = -2 * HP->b0;
	HP->b2 = HP->b0;
	HP->a1 = 2 * N * (w0 * w0 - 1);
	HP->a2 = N * (w0 * w0 - w0 / Q + 1);

	return DSP_OK;
}

DSP_Status SetupBandpass(struct BQFilter BP[2], float cutoff_LP, float cutoff_HP, float QLP, float QHP){

	//SetupLowpass (BP[0], cutoff_LP, QHP);
	//SetupHighpass(BP[1], cutoff_HP, QLP);

	return DSP_OK;
}

DSP_Status ProcessFilterTest(struct BQFilter *F,  float *data){

	float input = 0;
	float out = 0;

	input = *data;
	//out = input * F.b0 + F.z[0] * F.b1 + F.z[1] * F.b2 - F.z[2] * F.a1 - F.z[3] * F.a2;
	out = input * F->b0 + F->z[0] * F->b1 + F->z[1] * F->b2 - F->z[2] * F->a1 - F->z[3] * F->a2;
	F->z[3] = F->z[2];
	F->z[2] = out;
	F->z[1] = F->z[0];
	F->z[0] = input;
	*data = out;

	return DSP_OK;

}


DSP_Status ProcessFilter(struct BQFilter *F, float *data, uint16_t end){

	float out = 0;
	float input = 0;

	int z = 0;
	for(int i=0; i < 2*end; i++) {

		if(i==end) {
			z=0;
		}
		tempo[i] = data[z];
		z++;
		/*z = i;

		if(i >= end) z = i - end;

		tempo[i]=data[z];*/
	}

	//	F->z[0] = data[end-1];
	//	F->z[1] = data[end-2];
	//	F->z[2] = data[end-3];
	//	F->z[3] = data[end-4];

	for(int i=0; i < 2*end; i++) {

		input = tempo[i];
		//out = input * F.b0 + F.z[0] * F.b1 + F.z[1] * F.b2 - F.z[2] * F.a1 - F.z[3] * F.a2;
		out = input * F->b0 + F->z[0] * F->b1 + F->z[1] * F->b2 - F->z[2] * F->a1 - F->z[3] * F->a2;
		F->z[3] = F->z[2];
		F->z[2] = out;
		F->z[1] = F->z[0];
		F->z[0] = input;
		tempo[i] = out;

		if(i >= end) {
			data[i-end] = out;
		}

		//*(data+i) = out;
	}
	//}

	return DSP_OK;
}


DSP_Status ProcessBP(struct BQFilter BP[2], float data[], uint16_t end){

	//ProcessFilter(BP[0], data, end);
	//ProcessFilter(BP[1], data, end);

	return DSP_OK;
}

// DSP_Status AutoWah ()

