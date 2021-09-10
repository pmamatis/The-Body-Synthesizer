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


// Reinit variables
uint32_t ADC_value = 50;
uint32_t ADC_value_deb = 50;
uint32_t ADC_value_thresh = 50;
uint32_t flag = 0;

float parameter = 0;
float cutoff = 0;


// Processing variables
float band1, band2, band3, band4, band5 = 0;

Filter_Status Filters_Init(){

	/*****************************
	 * Default EQ consisting of Low-/Highshelfs and Peaking-EQ-/Notch-Filter
	 *
	 * @brief	Band 1: LS   ,  200 Hz, Versatile Gain
	 * @brief   Band 3: PEQ/N,  400 Hz,	PEQ: up to 6dB gain, Notch: up to ??dB Att.
	 * @brief	Band 4: PEQ/N,  800 Hz,	PEQ: up to 6dB gain, Notch: up to ??dB Att.
	 * @brief	Band 5: PEQ/N, 1600 Hz,	PEQ: up to 6dB gain, Notch: up to ??dB Att.
	 * @brief	Band 6: HS	 , 3200 Hz,	Versatile Gain
	 ******************************/

	// BAND 1: Low-Shelf filter
//	SetupLowShelf(&EQ_BAND1_I,      266, 0.707, -20);

//	// BAND 2: Peaking-EQ / Notch-Filter
//	SetupPeakingEQ(&EQ_BAND2_I,   400, 0.707, 20);
//	SetupNotch	(&EQ_BAND2_I,  	400, 0.707	 );
//
//	// BAND 3: Peaking-EQ / Notch-Filter
//	SetupPeakingEQ(&EQ_BAND3_I,   800, 0.707, 0);
//	SetupNotch	(&EQ_BAND3_I,  	800, 0.707	 );
//
//	// BAND 4: Peaking-EQ / Notch-Filter
//	SetupPeakingEQ(&EQ_BAND4_I,  1600, 0.707, 0);
//	SetupNotch	(&EQ_BAND4_I,  1600, 0.707	 );
//
//	// BAND 5: High-Shelf filter
//	SetupHighShelf(&EQ_BAND5_I,    3200, 0.707, 0);



	/*****************************
	 * Alternative EQ with several stages (high CPU consumption)
	 *
	 * Default corner / center frequencies
	 *
	 * @brief	Band 1: LP,  200 Hz, 	80 dB / Dec. (2 Stages)
	 * @brief   Band 3: BP,  400 Hz,	12 dB / Oct. (4 Stages)
	 * @brief	Band 4: BP,  800 Hz,	12 dB / Oct. (4 Stages)
	 * @brief	Band 5: BP, 1600 Hz,	12 dB / Oct. (4 Stages)
	 * @brief	Band 6: HP, 3200 Hz,	80 dB / Dec. (2 Stages)
	 ******************************/

	//	// BAND 1: LP 4th order
	//	SetupLowpass (&EQ_BAND1_I,  200, 0.707);
	//	SetupLowpass (&EQ_BAND1_II, 200, 0.707);
	//
	//	// BAND 2: BP 8th order
	SetupBandpassCPG(&EQ_BAND2_I,  400, 20);
	//SetupBandpassCPG(&EQ_BAND2_II, 400, 20);
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


Filter_Status Filters_Reinit(){

	// GND debouncing
	if(ADC_value < ADC_value_thresh) ADC_value = ADC_value_thresh;

	// General debouncing
	if(ADC_value_deb + ADC_value_thresh <= ADC_value || ADC_value_deb - ADC_value_thresh >= ADC_value)
	{
		ADC_value_deb = ADC_value;
		flag = 1;
	}
	// IF: Value changed
	if(flag)
	{
		/*****************************
		 * @brief	HS / LS Gain: -18dB to 6dB
		 * @brief	Scaling 4095 (ADC_value) to a range of 24dB by dividing with 170.625
		 * @brief   Center around 0dB by subtracting (4095/(2*170.625))
		 * @brief	Subtract 6dB for final adjust
		 ******************************/
		//parameter = ((float)ADC_value / 170.625)-(4095/(2*170.625))-6;


		/*****************************
		 * @brief	PEQ Gain: 0 to 6dB
		 ******************************/
		//parameter = ((float)ADC_value / (2*341.25));


		/*****************************
		 * @brief	Frequency: Cutoff / Center / Midshelf
		 * @brief	Ranging from 0 to 4000Hz
		 ******************************/
		//parameter = (float)ADC_value * 4000 / 4095;
		cutoff = (float)ADC_value/8;

		// REINIT:
		//SetupLowShelf (&EQ_BAND1_I, cutoff, 20, -20);
//		SetupHighShelf(&EQ_BAND1_I, parameter, 0.707, -20);
//		SetupPeakingEQ(&EQ_BAND2_I, cutoff, 	     10, 20);
//		SetupNotch(&EQ_BAND2_I, parameter, 0.707);


		SetupBandpassCPG(&EQ_BAND2_I,  cutoff, 20);
		//SetupBandpassCPG(&EQ_BAND2_II, cutoff, 20);
		//SetupHighpass   (&EQ_BAND1_I,  parameter, 0.707);
		//SetupHighpass   (&EQ_BAND1_II, parameter, 0.707);

		flag = 0;
	}
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

	// BAND 1
//	band1 = *data;
//	ProcessFilter(&EQ_BAND1_I,  &band1);
	//ProcessFilter(&EQ_BAND1_II, &band1);

//	// BAND 2
	band2 = *data;
	ProcessFilter(&EQ_BAND2_I,  &band2);
	//ProcessFilter(&EQ_BAND2_II, &band2);
//	//  ProcessFilter(&EQ_BAND2_II, &band2);
//	//	ProcessFilter(&EQ_BAND2_III,&band2);
//	//	ProcessFilter(&EQ_BAND2_IV, &band2);
//
//
//	// BAND 3
//	band3 = *data;
//	ProcessFilter(&EQ_BAND3_I,  &band3);
//	//	ProcessFilter(&EQ_BAND3_II, &band3);
//	//	ProcessFilter(&EQ_BAND3_III,&band3);
//	//	ProcessFilter(&EQ_BAND3_IV, &band3);
//
//	// BAND 4
//	band4 = *data;
//	ProcessFilter(&EQ_BAND4_I,  &band4);
//	//	ProcessFilter(&EQ_BAND4_II, &band4);
//	//	ProcessFilter(&EQ_BAND4_III,&band4);
//	//	ProcessFilter(&EQ_BAND4_IV, &band4);
//
//	// BAND 5
//	band5 = *data;
//	ProcessFilter(&EQ_BAND5_I,  &band5);
//	//	ProcessFilter(&EQ_BAND5_II, &band5);

	// Write OUT
	*data = band2;// + band2 + band3 + band4 + band5;

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

	//for dBGain in function() head use:
	float exp = (2*dBGain) / 40.0;
	float A = powf(10, exp);

	//float A = dBGain;
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	BP->b0 = 1 + alpha * A;
	BP->b1 = -2 * cos;
	BP->b2 = 1 - alpha * A;
	BP->a0 = 1 + alpha * A;
	BP->a1 = -2 * cos;
	BP->a2 = 1 - alpha / A;

	return FILTER_OK;
}


// LowShelf Filter
Filter_Status SetupLowShelf(struct BQFilter *LS, float cutoff, float Q, float dBGain){

	float exp = (2*dBGain) / 40;
	float A = powf(10, exp);
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

	float exp = (2*dBGain) / 40;
	float A = powf(10, exp);
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


