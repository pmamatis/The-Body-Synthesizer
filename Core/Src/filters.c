/*****************************
 * @file    filters.c
 * @author  Max Lehmer
 * @date 	07 May 2020
 * @brief	Filter-Library
 * @brief	Based on Audio-EQ cookbook
 * @brief   https://github.com/libaudioverse/libaudioverse/blob/master/audio%20eq%20cookbook.txt
 ******************************/
#include "filters.h"

/* ------------------------------------------------------------------
 * Global variables for FIR LPF Example
 * ------------------------------------------------------------------- */
uint32_t samplerate = LUT_SR;


Filter_Status Filters_Init(){

	/*****************************
	 * Default corner frequencies
	 *
	 * @brief	Band 1: LP, to 200 Hz
	 * @brief	Band 2: BP, 200 Hz to 800 Hz
	 * @brief   Band 3: BP, 800 Hz to 2 kHz
	 * @brief	Band 4: BP, 2 kHz to 4 kHz
	 * @brief	Band 5: HP, from 4 kHz
	 ******************************/


	// BAND 1 (200)
	SetupLowpass (&EQ_BAND1_I,  448, 0.707);
	SetupLowpass (&EQ_BAND1_II, 448, 0.707);

	// BAND 2: 800 / 200
	SetupLowpass (&EQ_BAND2_LP_I,  10000, 0.707);
	SetupLowpass (&EQ_BAND2_LP_II, 10000, 0.707);
	SetupHighpass(&EQ_BAND2_HP_I,  10000, 0.707);
	SetupHighpass(&EQ_BAND2_HP_II, 10000, 0.707);

	// BAND 3
	SetupLowpass (&EQ_BAND3_LP_I,  2000, 0.707);
	SetupLowpass (&EQ_BAND3_LP_II, 2000, 0.707);
	SetupHighpass(&EQ_BAND3_HP_I,  800, 0.707);
	SetupHighpass(&EQ_BAND3_HP_II, 800, 0.707);

	// BAND 4
	SetupLowpass (&EQ_BAND4_LP_I,  4000, 0.707);
	SetupLowpass (&EQ_BAND4_LP_II, 4000, 0.707);
	SetupHighpass(&EQ_BAND4_HP_I,  2000, 0.707);
	SetupHighpass(&EQ_BAND4_HP_II, 2000, 0.707);

	// BAND 5
	SetupHighpass(&EQ_BAND5_I,  4000, 0.707);
	SetupHighpass(&EQ_BAND5_II, 4000, 0.707);

	return FILTER_OK;
}

Filter_Status SetupLowpass(struct BQFilter *LP, float cutoff, float Q){

	//float A = 1;
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	LP->b0 = (1 - cos) / 2;
	LP->b1 = 1 - cos;
	LP->b2 = LP->b0;
	LP->a0 = 1 + alpha;
	LP->a1 = -2 * cos;
	LP->a2 = 1 - alpha;

	return FILTER_OK;
}

//
//Filter_Status SetupLowpass(struct BQFilter *LP, float cutoff, float Q){
//
//	float w0 = tanf(M_PI * cutoff / samplerate);
//	float N = 1 / (w0 * w0 + w0 / Q + 1);
//
//	LP->b0 = N * w0 * w0;
//	LP->b1 = 2 * LP->b0;
//	LP->b2 = LP->b0;
//	LP->a1 = 2 * N * (w0 * w0 - 1);
//	LP->a2 = N * (w0 * w0 - w0 / Q + 1);
//
//	return FILTER_OK;
//}

Filter_Status SetupHighpass(struct BQFilter *HP, float cutoff, float Q){

	//float A = 1;
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	HP->b0 = (1 + cos) / 2;
	HP->b1 = -(1 + cos);
	HP->b2 = HP->b0;
	HP->a0 = 1 + alpha;
	HP->a1 = -2 * cos;
	HP->a2 = 1 - alpha;

	return FILTER_OK;
}


//Filter_Status SetupHighpass(struct BQFilter *HP, float cutoff, float Q){
//
//	float w0 = tanf(M_PI * cutoff / samplerate);
//	float N = 1 / (w0 * w0 + w0 / Q + 1);
//
//	HP->b0 = N;
//	HP->b1 = -2 * HP->b0;
//	HP->b2 = HP->b0;
//	HP->a1 = 2 * N * (w0 * w0 - 1);
//	HP->a2 = N * (w0 * w0 - w0 / Q + 1);
//
//	return FILTER_OK;
//}


Filter_Status SetupBandpass(struct BQFilter *BP, float cutoff, float Q){

	//float A = 1;
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	BP->b0 = alpha;
	BP->b1 = 0;
	BP->b2 = -alpha;
	BP->a0 = 1 + alpha;
	BP->a1 = -2 * cos;
	BP->a2 = 1 - alpha;

	return FILTER_OK;
}


Filter_Status ProcessFilter(struct BQFilter *F,  float *data){

	float input = 0;
	float out = 0;

	input = *data;
	out = (F->b0 / F->a0) * input + (F->b1 / F->a0) * F->z[0] + (F->b2 / F->a0) * F->z[1] - (F->a1 / F->a0) * F->z[2] - (F->a2 / F->a0) * F->z[3];
	F->z[3] = F->z[2];
	F->z[2] = out;
	F->z[1] = F->z[0];
	F->z[0] = input;
	*data = out;

	return FILTER_OK;
}

//Filter_Status ProcessFilter(struct BQFilter *F,  float *data){
//
//	float input = 0;
//	float out = 0;
//
//	input = *data;
//	out = input * F->b0 + F->z[0] * F->b1 + F->z[1] * F->b2 - F->z[2] * F->a1 - F->z[3] * F->a2;
//	F->z[3] = F->z[2];
//	F->z[2] = out;
//	F->z[1] = F->z[0];
//	F->z[0] = input;
//	*data = out;
//
//	return FILTER_OK;
//
//}

Filter_Status ProcessEQ(float *data){

	float band1, band2, band3, band4, band5 = 0;

	// BAND 1
	band1 = *data;
	ProcessFilter(&EQ_BAND1_I,  &band1);
	ProcessFilter(&EQ_BAND1_II, &band1);


	//	// BAND 2
	band2 = *data;
	ProcessFilter(&EQ_BAND2_LP_I,  &band2);
	ProcessFilter(&EQ_BAND2_HP_I,  &band2);
	ProcessFilter(&EQ_BAND2_LP_II, &band2);
	ProcessFilter(&EQ_BAND2_HP_II, &band2);


	//	// BAND 3
	//	band3 = *data;
	//	ProcessFilter(&EQ_BAND3_LP, &band3);
	//	ProcessFilter(&EQ_BAND3_LP, &band3);
	//	ProcessFilter(&EQ_BAND3_HP, &band3);
	//	ProcessFilter(&EQ_BAND3_HP, &band3);
	//
	//	// BAND 4
	//	band4 = *data;
	//	ProcessFilter(&EQ_BAND4_LP, &band4);
	//	ProcessFilter(&EQ_BAND4_LP, &band4);
	//	ProcessFilter(&EQ_BAND4_HP, &band4);
	//	ProcessFilter(&EQ_BAND4_HP, &band4);
	//
	// BAND 5
	//	band5 = *data;
	//	ProcessFilter(&EQ_BAND5,    &band5);
	//	ProcessFilter(&EQ_BAND5,    &band5);
	//	ProcessFilter(&EQ_BAND5,    &band5);
	//	ProcessFilter(&EQ_BAND5,    &band5);

	// Write OUT
	//	*data = band1 + band2 + band3 + band4 + band5;
	*data = band2;

	return FILTER_OK;

}

