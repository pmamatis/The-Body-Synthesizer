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
	EQ_BAND1.Q = 0.707;
	EQ_BAND1.cutoff = 200;
	EQ_BAND1.dBGain = 0;
	EQ_BAND1.maximum_Q = 20.0;
	EQ_BAND1.maximum_cutoff = LUT_FMAX;
	EQ_BAND1.maximum_dBGain = 6;

	SetupLowShelf(&EQ_BAND1, EQ_BAND1.cutoff, EQ_BAND1.Q, EQ_BAND1.dBGain);


	// BAND 2: Peaking-EQ
	EQ_BAND2.Q = 0.707;
	EQ_BAND2.cutoff = 400;
	EQ_BAND2.dBGain = 0;
	EQ_BAND2.maximum_Q = 20.0;
	EQ_BAND2.maximum_cutoff = LUT_FMAX;
	EQ_BAND2.maximum_dBGain = 6;

	SetupPeakingEQ(&EQ_BAND2, EQ_BAND2.cutoff, EQ_BAND2.Q, EQ_BAND2.dBGain);


	// BAND 3: Peaking-EQ
	EQ_BAND3.Q = 0.707;
	EQ_BAND3.cutoff = 800;
	EQ_BAND3.dBGain = 0;
	EQ_BAND3.maximum_Q = 20.0;
	EQ_BAND3.maximum_cutoff = LUT_FMAX;
	EQ_BAND3.maximum_dBGain = 6;

	SetupPeakingEQ(&EQ_BAND3, EQ_BAND3.cutoff, EQ_BAND3.Q, EQ_BAND3.dBGain);


	// BAND 4: Peaking-EQ
	EQ_BAND4.Q = 0.707;
	EQ_BAND4.cutoff = 1600;
	EQ_BAND4.dBGain = 0;
	EQ_BAND4.maximum_Q = 20.0;
	EQ_BAND4.maximum_cutoff = LUT_FMAX;
	EQ_BAND4.maximum_dBGain = 6;

	SetupPeakingEQ(&EQ_BAND4, EQ_BAND4.cutoff, EQ_BAND4.Q, EQ_BAND4.dBGain);


	// BAND 5: High-Shelf filter
	EQ_BAND5.Q = 0.707;
	EQ_BAND5.cutoff = 3200;
	EQ_BAND5.dBGain = 0;
	EQ_BAND5.maximum_Q = 20.0;
	EQ_BAND5.maximum_cutoff = LUT_FMAX;
	EQ_BAND5.maximum_dBGain = 6;

	SetupHighShelf(&EQ_BAND5, EQ_BAND5.cutoff, EQ_BAND5.Q, EQ_BAND5.dBGain);


	// Drums Lowshelf
	LS_DRUMS.Q = 10;
	LS_DRUMS.cutoff = LUT_FMIN;
	LS_DRUMS.dBGain = -20;
	LS_DRUMS.maximum_Q = 20.0;
	LS_DRUMS.maximum_cutoff = LUT_FMAX;
	LS_DRUMS.maximum_dBGain = 1.0;

	SetupLowShelf(&LS_DRUMS, LS_DRUMS.cutoff, LS_DRUMS.Q, LS_DRUMS.dBGain);


	// AA-Notch
	//	SetupNotch(&LP_AA, 50, 0.707);


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
	//	SetupBandpassCPG(&EQ_BAND2_I,  10, 20);
	//  SetupBandpassCPG(&EQ_BAND2_II, 400, 20);
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






Filter_Status DrumFilters_Reinit_Gyro(float cutoff_d){


	if (cutoff_d > 10){
		//		SetupPeakingEQ(&EQ_BAND2_I,  cutoff , 20, 24);
		SetupLowShelf(&LS_DRUMS, cutoff_d, 10, -20);
		printf(" drum cutoff: %f\r\n",cutoff_d);
		return FILTER_OK;
	}
	else {
		//		SetupPeakingEQ(&EQ_BAND2_I,  10 , 20, 24);
		SetupLowShelf(&LS_DRUMS, 10, 10, -20);
		//		printf("cutoff: %f\r\n",cutoff);
		return FILTER_OK;
	}
}





Filter_Status Filters_Reinit_Gyro(float cutoff){



	if (cutoff > 10){
		//		SetupPeakingEQ(&EQ_BAND2_I,  cutoff , 20, 24);
		SetupBandpassCPG(&EQ_BAND2,  cutoff, 0.707);
		printf("cutoff: %f\r\n",cutoff);
		return FILTER_OK;
	}
	else {
		//		SetupPeakingEQ(&EQ_BAND2_I,  10 , 20, 24);
		SetupBandpassCPG(&EQ_BAND2,  10, 0.707);
		printf("cutoff: %f\r\n",cutoff);
		return FILTER_OK;
	}
}



Filter_Status Filters_Reinit_Poti(){

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


		SetupBandpassCPG(&EQ_BAND2,  cutoff, 20);
		//SetupBandpassCPG(&EQ_BAND2_II, cutoff, 20);
		//SetupHighpass   (&EQ_BAND1_I,  parameter, 0.707);
		//SetupHighpass   (&EQ_BAND1_II, parameter, 0.707);

		flag = 0;
	}
	return FILTER_OK;
}


Filter_Status Filters_Reset(void) {

	// BAND 1: Low-Shelf filter
	Display.Filter_ONOFF[0] = false;
	Display.Filter_Q[0] = EQ_BAND1.Q = 0.707;
	Display.Filter_Cutoff[0] = EQ_BAND1.cutoff = 200;
	Display.Filter_Gain[0] = EQ_BAND1.dBGain = 0;
	SetupLowShelf(&EQ_BAND1, EQ_BAND1.cutoff, EQ_BAND1.Q, EQ_BAND1.dBGain);


	// BAND 2: Peaking-EQ
	Display.Filter_ONOFF[1] = false;
	Display.Filter_Q[1] = EQ_BAND2.Q = 0.707;
	Display.Filter_Cutoff[1] = EQ_BAND2.cutoff = 400;
	Display.Filter_Gain[1] = EQ_BAND2.dBGain = 0;
	SetupPeakingEQ(&EQ_BAND2, EQ_BAND2.cutoff, EQ_BAND2.Q, EQ_BAND2.dBGain);


	// BAND 3: Peaking-EQ
	Display.Filter_ONOFF[2] = false;
	Display.Filter_Q[2] = EQ_BAND3.Q = 0.707;
	Display.Filter_Cutoff[2] = EQ_BAND3.cutoff = 800;
	Display.Filter_Gain[2] = EQ_BAND3.dBGain = 0;
	SetupPeakingEQ(&EQ_BAND3, EQ_BAND3.cutoff, EQ_BAND3.Q, EQ_BAND3.dBGain);


	// BAND 4: Peaking-EQ
	Display.Filter_ONOFF[3] = false;
	Display.Filter_Q[3] = EQ_BAND4.Q = 0.707;
	Display.Filter_Cutoff[3] = EQ_BAND4.cutoff = 1600;
	Display.Filter_Gain[3] = EQ_BAND4.dBGain = 0;
	SetupPeakingEQ(&EQ_BAND4, EQ_BAND4.cutoff, EQ_BAND4.Q, EQ_BAND4.dBGain);


	// BAND 5: High-Shelf filter
	Display.Filter_ONOFF[4] = false;
	Display.Filter_Q[4] = EQ_BAND5.Q = 0.707;
	Display.Filter_Cutoff[4] = EQ_BAND5.cutoff = 3200;
	Display.Filter_Gain[4] = EQ_BAND5.dBGain = 0;
	SetupHighShelf(&EQ_BAND5, EQ_BAND5.cutoff, EQ_BAND5.Q, EQ_BAND5.dBGain);


	//		// Drums Lowshelf
	//		LS_DRUMS.Q = 10;
	//		LS_DRUMS.cutoff = LUT_FMIN;
	//		LS_DRUMS.dBGain = -20;
	//		LS_DRUMS.maximum_Q = 20.0;
	//		LS_DRUMS.maximum_cutoff = LUT_FMAX;
	//		LS_DRUMS.maximum_dBGain = 1.0;
	//
	//		SetupLowShelf(&LS_DRUMS, LS_DRUMS.cutoff, LS_DRUMS.Q, LS_DRUMS.dBGain);

	for(int i=0; i<5; i++) {	// reset sources of all 5 filter bands
		Display.EQ_Q_factor_Sources[i] = POTI;
		Display.EQ_Cutoff_Sources[i] = POTI;
		Display.EQ_Gain_Sources[i] = POTI;
	}

	strcpy(Display.value_str_equalizer_overview[0], "OFF");
	strcpy(Display.value_str_equalizer_overview[1], "OFF");
	strcpy(Display.value_str_equalizer_overview[2], "OFF");
	strcpy(Display.value_str_equalizer_overview[3], "OFF");
	strcpy(Display.value_str_equalizer_overview[4], "OFF");

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
	if(Display.Filter_ONOFF[0] == true)
		ProcessFilter(&EQ_BAND1, data);
	// BAND 2
	if(Display.Filter_ONOFF[1] == true)
		ProcessFilter(&EQ_BAND2, data);
	// BAND 3
	if(Display.Filter_ONOFF[2] == true)
		ProcessFilter(&EQ_BAND3, data);
	// BAND 4
	if(Display.Filter_ONOFF[3] == true)
		ProcessFilter(&EQ_BAND4, data);
	// BAND 5
	if(Display.Filter_ONOFF[4] == true)
		ProcessFilter(&EQ_BAND5, data);

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
	float exp = (dBGain) / 40.0;
	float A = powf(10, exp);

	//float A = dBGain;
	float w = 2 * M_PI * cutoff / samplerate;

	float sin = sinf(w);
	float cos = cosf(w);

	float alpha = sin / (2 * Q);

	BP->b0 = 1 + alpha * A;
	BP->b1 = -2 * cos;
	BP->b2 = 1 - alpha * A;
	BP->a0 = 1 + alpha / A;
	BP->a1 = -2 * cos;
	BP->a2 = 1 - alpha / A;
	//	printf("cutoff: %f\r\n Gain: %f\r\n",cutoff,dBGain);
	return FILTER_OK;
}


// LowShelf Filter
Filter_Status SetupLowShelf(struct BQFilter *LS, float cutoff, float Q, float dBGain){

	float exp = (dBGain) / 40;
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

	float exp = (dBGain) / 40;
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
