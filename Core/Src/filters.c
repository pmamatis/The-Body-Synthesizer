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

Filter_Status Filters_Init(){

	// BAND 1
	SetupLowpass (&EQ_BAND1,    224, 0.707);

	// BAND 2: center frequency = 224
	SetupLowpass (&EQ_BAND2_LP, 448, 0.707);
	SetupHighpass(&EQ_BAND2_HP, 112, 0.707);

	// BAND 3
	//SetupLowpass (&EQ_BAND3_LP, 224, 0.707);
	//SetupHighpass(&EQ_BAND3_HP, 224, 0.707);

	// BAND 4
	//SetupLowpass (&EQ_BAND4_LP, 224, 0.707);
	//SetupHighpass(&EQ_BAND4_HP, 224, 0.707);

	// BAND 5
	SetupHighpass(&EQ_BAND5, 224, 0.707);

	return FILTER_OK;
}


Filter_Status SetupLowpass(struct BQFilter *LP, float cutoff, float Q){

	float w0 = tanf(M_PI * cutoff / samplerate);
	float N = 1 / (w0 * w0 + w0 / Q + 1);

	LP->b0 = N * w0 * w0;
	LP->b1 = 2 * LP->b0;
	LP->b2 = LP->b0;
	LP->a1 = 2 * N * (w0 * w0 - 1);
	LP->a2 = N * (w0 * w0 - w0 / Q + 1);

	return FILTER_OK;
}

Filter_Status SetupHighpass(struct BQFilter *HP, float cutoff, float Q){

	float w0 = tanf(M_PI * cutoff / samplerate);
	float N = 1 / (w0 * w0 + w0 / Q + 1);

	HP->b0 = N;
	HP->b1 = -2 * HP->b0;
	HP->b2 = HP->b0;
	HP->a1 = 2 * N * (w0 * w0 - 1);
	HP->a2 = N * (w0 * w0 - w0 / Q + 1);

	return FILTER_OK;
}

Filter_Status ProcessFilter(struct BQFilter *F,  float *data){

	float input = 0;
	float out = 0;

	input = *data;
	out = input * F->b0 + F->z[0] * F->b1 + F->z[1] * F->b2 - F->z[2] * F->a1 - F->z[3] * F->a2;
	F->z[3] = F->z[2];
	F->z[2] = out;
	F->z[1] = F->z[0];
	F->z[0] = input;
	*data = out;

	return FILTER_OK;

}

Filter_Status ProcessEQ(float *data){

	float band1, band2, band3, band4, band5 = 0;

	// BAND 1
	//band1 = *data;
	//ProcessFilter(&EQ_BAND1,    &band1);

	// BAND 2
	band2 = *data;
	ProcessFilter(&EQ_BAND2_LP, &band2);
	ProcessFilter(&EQ_BAND2_HP, &band2);

	// BAND 3
	//band3 = *data;
	//ProcessFilter(&EQ_BAND3_LP, &band3);
	//ProcessFilter(&EQ_BAND3_HP, &band3);

	// BAND 4
	//band4 = *data;
	//ProcessFilter(&EQ_BAND4_LP, &band4);
	//ProcessFilter(&EQ_BAND4_HP, &band4);

	// BAND 5
	//band5 = *data;
	//ProcessFilter(&EQ_BAND5,    &band5);

	// Write OUT
	*data = band1 + band2 + band3 + band4 + band5;

	return FILTER_OK;

}

