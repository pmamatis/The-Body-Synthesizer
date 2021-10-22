/**
 ******************************************************************************
 * @file    wahwah.c
 * @author  Max Lehmer
 * @date 	11 Sep 2021
 * @brief	WahWah-Library
 */

#include "wahwah.h"

/*********************************
 * @brief		WahWah functions
 * @parameter	WahWah
 *********************************/
WahWah_Status WahWah_Init(struct WahWah_t *WahWah) {

	WahWah->lfo = &lfo_wahwah;
	WahWah->bandpass = &BP_WAHWAH;

	WahWah->lfo->lfo_index     = 0;
	WahWah->lfo->lfo_quarter   = 0;
//	WahWah->lfo->lfo_depth     = 1;	// [0, 1]
	WahWah->lfo->lfo_frequency = 1;	// [0.125, 0.25, 0.5, 1, 2, 4, 8, 16]

	WahWah->range        = 600;
	WahWah->mid_freq     = 350;
	WahWah->mid_freq_mod = 0;

	WahWah->max_range = 500;
	WahWah->max_mid_freq = 2000;	// can be adjusted in the display to values 1000, 2000, 3000 and 4000
	WahWah->max_Q = 20;
//	WahWah->max_lfo_depth = 1;

	WahWah->reinit_counter = 0;
	WahWah->bandpass->Q = 1;

	SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq, WahWah->bandpass->Q);

	return WAHWAH_OK;
}


/** @brief Processed current tremolo sample
 * @param Tremolo: struct for tremolo information
 * @param data: current sample
 * @param lfo_value: current lfo value
 */
WahWah_Status ProcessWahWah(struct WahWah_t *WahWah, float *data){

	// MODULATE: mid frequency of bandpass with light sensor or potentiometer either linear or logarithmical
//	WahWah->mid_freq = exp1(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * log_mapping_F);	// log_mapping_F=log(LUT_FMAX) has to be updated in the display regarding the adjusted value for max_mid_freq
//	WahWah->mid_freq = ((float)Display.ADC2inputs[2] / Display.ADC_FullRange) * WahWah->max_mid_freq;	// DISPLAY!!!

	// SET: mid frequency to at least 50 Hz due to filter response
	if(WahWah->mid_freq < 50)
		WahWah->mid_freq = 50;	// 50 Hz Offset;

	// FETCH: Q from ADC
//	WahWah->bandpass->Q = (((float)Display.ADC2inputs[3] / Display.ADC_FullRange) * 10) + 0.5;W	// DISPLAY!!!

	// RESET: Filter after 1000 samples (with SR = 24k Hz >> 24 times a second)
	if(WahWah->reinit_counter == 100){

		SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq, WahWah->bandpass->Q);
		WahWah->reinit_counter = 0;
	}

	WahWah->reinit_counter++;

	ProcessFilter(WahWah->bandpass, data);

	return WAHWAH_OK;
}

WahWah_Status ProcessAutoWahWah(struct WahWah_t *WahWah, float *data){

	// mid_freq and range have to be set in the display function

	// FETCH: actual LFO value
	LFO_SingleValueProcess(WahWah->lfo);

//	WahWah->mid_freq = (float)Display.ADC2inputs[2] / 4;	// DISPLAY!!!
	if(WahWah->mid_freq < 50)
		WahWah->mid_freq = 50;	// 50 Hz Offset;

//	WahWah->max_range = (WahWah->mid_freq - 50) * 2;	// max range calculated in DISPLAY depending on the current mid_freq value

//	WahWah->range = WahWah->max_range/4;	// DISPLAY!!!

	WahWah->mid_freq_mod = WahWah->mid_freq + (WahWah->range / 2) * WahWah->lfo->lfo_data;

	// RESET: Filter after 1000 samples (with SR = 24k Hz >> 24 times a second)
	if(WahWah->reinit_counter == 100){

		SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq_mod, WahWah->bandpass->Q);
		WahWah->reinit_counter = 0;
	}

	WahWah->reinit_counter++;

	ProcessFilter(WahWah->bandpass, data);

	return WAHWAH_OK;
}
