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

float band1, band2, band3, band4, band5 = 0;

Filter_Status Filters_Init(){

	/*****************************
	 * Default corner / center frequencies
	 *
	 * @brief	Band 1: LP,  100 Hz, 	80 dB / Dec.
	 * @brief	Band 2: BP,  200 Hz,	12 dB / Oct.
	 * @brief   Band 3: BP,  400 Hz,	12 dB / Oct.
	 * @brief	Band 4: BP,  800 Hz,	12 dB / Oct.
	 * @brief	Band 5: BP, 1600 Hz,	12 dB / Oct.
	 * @brief	Band 6: HP, 3200 Hz,	80 dB / Dec.
	 ******************************/

	// BAND 1: High-shelf filter
	SetupHighShelf(&EQ_BAND1_I,   106, 0.707, 0);
	SetupHighShelf(&EQ_BAND1_II,  106, 0.707, 0);

	// BAND 2: Peaking-EQ filter
	SetupPeakingEQ(&EQ_BAND2_I,   400, 0.707, 0);
	SetupPeakingEQ(&EQ_BAND2_II,  400, 0.707, 0);

	// BAND 3: Peaking-EQ filter
	SetupPeakingEQ(&EQ_BAND3_I,   800, 0.707, 0);
	SetupPeakingEQ(&EQ_BAND3_II,  800, 0.707, 0);

	// BAND 4: Peaking-EQ filter
	SetupPeakingEQ(&EQ_BAND4_I,  1600, 0.707, 0);
	SetupPeakingEQ(&EQ_BAND4_II, 1600, 0.707, 0);

	// BAND 5: Low-Shelf filter
	SetupLowShelf(&EQ_BAND5_I,    3200, 0.707, 0);
	SetupLowShelf(&EQ_BAND5_II,   3200, 0.707, 0);



	//	// BAND 1: LP 4th order
	//	SetupLowpass (&EQ_BAND1_I,  200, 0.707);
	//	SetupLowpass (&EQ_BAND1_II, 200, 0.707);
	//
	//	// BAND 2: BP 8th order
	//	SetupBandpassCPG(&EQ_BAND2_I,  400, 0.707);
	//	SetupBandpassCPG(&EQ_BAND2_II, 400, 0.707);
	//	SetupBandpassCPG(&EQ_BAND2_III,400, 0.707);
	//	SetupBandpassCPG(&EQ_BAND2_IV, 400, 0.707);
	//
	//	// BAND 3: BP 8th order
	//	SetupBandpassCPG(&EQ_BAND3_I,  800, 0.707);
	//	SetupBandpassCPG(&EQ_BAND3_II, 800, 0.707);
	//	SetupBandpassCPG(&EQ_BAND3_III,800, 0.707);
	//	SetupBandpassCPG(&EQ_BAND3_IV, 800, 0.707);
	//
	//	// BAND 4: BP 8th order
	//	SetupBandpassCPG(&EQ_BAND4_I,  1600, 0.707);
	//	SetupBandpassCPG(&EQ_BAND4_II, 1600, 0.707);
	//	SetupBandpassCPG(&EQ_BAND4_III,1600, 0.707);
	//	SetupBandpassCPG(&EQ_BAND4_IV, 1600, 0.707);
	//
	//	// BAND 5
	//	SetupHighpass(&EQ_BAND5_I,  3200, 0.707);
	//	SetupHighpass(&EQ_BAND5_II, 3200, 0.707);

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


Filter_Status ProcessEQ(float *data){

	/*****************************
	 * Processing EQ
	 *
	 * @brief	LP / HP: 	40 dB / Dec. per ProcessFilter() call
	 * @brief	BP: 		 3 dB / Oct. per ProcessFilter() call
	 *
	 * @brief	Partly commented due to too low processor speed that causes glitches
	 ******************************/

	// (*

	float gain = 10*(float)testcutoff / 4095;

	// BAND 1
	band1 = *data;
	//SetupHighShelf(&EQ_BAND1_I, 106, 0.707, gain);
	ProcessFilter(&EQ_BAND1_I,  &band1);
	//	ProcessFilter(&EQ_BAND1_II, &band1);

	// BAND 2
	band2 = *data;
	//	ProcessFilter(&EQ_BAND2_I,  &band2);
	//	ProcessFilter(&EQ_BAND2_II, &band2);
	//	ProcessFilter(&EQ_BAND2_III,&band2);
	//	ProcessFilter(&EQ_BAND2_IV, &band2);

	// BAND 3
	band3 = *data;
	//	ProcessFilter(&EQ_BAND3_I,  &band3);
	//	ProcessFilter(&EQ_BAND3_II, &band3);
	//	ProcessFilter(&EQ_BAND3_III,&band3);
	//	ProcessFilter(&EQ_BAND3_IV, &band3);

	// BAND 4
	band4 = *data;
	//	ProcessFilter(&EQ_BAND4_I,  &band4);
	//	ProcessFilter(&EQ_BAND4_II, &band4);
	//	ProcessFilter(&EQ_BAND4_III,&band4);
	//	ProcessFilter(&EQ_BAND4_IV, &band4);

	// BAND 5
	band5 = *data;
	//	ProcessFilter(&EQ_BAND5_I,  &band5);
	//	ProcessFilter(&EQ_BAND5_II, &band5);

	// Write OUT
	*data = band1;// + band2 + band3 + band4 + band5;

	return FILTER_OK;
}


// Lowpass Filter
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


// Highpass Filter
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


// Constant Peak Gain Bandpass Filter
Filter_Status SetupBandpassCPG(struct BQFilter *BP, float cutoff, float Q){

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


// Constant Skirt Gain Bandpass Filter
Filter_Status SetupBandpassCSG(struct BQFilter *BP, float cutoff, float Q){

	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	BP->b0 = Q*alpha;
	BP->b1 = 0;
	BP->b2 = -Q*alpha;
	BP->a0 = 1 + alpha;
	BP->a1 = -2 * cos;
	BP->a2 = 1 - alpha;

	return FILTER_OK;
}


// Notch Filter
Filter_Status SetupNotch(struct BQFilter *BP, float cutoff, float Q){

	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	BP->b0 = 1;
	BP->b1 = -2 * cos;
	BP->b2 = 1;
	BP->a0 = 1 + alpha;
	BP->a1 = -2 * cos;
	BP->a2 = 1 - alpha;

	return FILTER_OK;
}


// Peaking EQ Filter
Filter_Status SetupPeakingEQ(struct BQFilter *BP, float cutoff, float Q, float dBGain){

	float A = powf(10, dBGain / 40);
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	BP->b0 = 1 + alpha * A;
	BP->b1 = -2 * cos;
	BP->b2 = 1 + alpha * A;
	BP->a0 = 1 + alpha * A;
	BP->a1 = -2 * cos;
	BP->a2 = 1 - alpha / A;

	return FILTER_OK;
}


// LowShelf Filter
Filter_Status SetupLowShelf(struct BQFilter *LS, float cutoff, float Q, float dBGain){

	float A = powf(10, dBGain / 40);
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float beta  = sqrtf(A)/Q;

	LS->b0 =     A * ((A + 1) - (A - 1) * cos + beta * sin);
	LS->b1 = 2 * A * ((A - 1) - (A + 1) * cos);
	LS->b2 =     A * ((A + 1) - (A - 1) * cos - beta * sin);
	LS->a0 =          (A + 1) + (A - 1) * cos + beta * sin;
	LS->a1 =    -2 * ((A - 1) + (A + 1) * cos);
	LS->a2 =          (A + 1) + (A - 1) * cos - beta * sin;

	return FILTER_OK;
}


// HighShelf Filter
Filter_Status SetupHighShelf(struct BQFilter *HS, float cutoff, float Q, float dBGain){

	float A = powf(10, dBGain / 40);
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float beta  = sqrtf(A)/Q;

	HS->b0 =      A * ((A + 1) + (A - 1) * cos + beta * sin);
	HS->b1 = -2 * A * ((A - 1) + (A + 1) * cos);
	HS->b2 =      A * ((A + 1) + (A - 1) * cos - beta * sin);
	HS->a0 =           (A + 1) - (A - 1) * cos + beta * sin;
	HS->a1 =      2 * ((A - 1) - (A + 1) * cos);
	HS->a2 =           (A + 1) - (A - 1) * cos - beta * sin;

	return FILTER_OK;
}


