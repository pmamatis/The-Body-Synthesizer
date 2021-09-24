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
	WahWah->lfo->lfo_depth     = 1;	// [0, 1]
	WahWah->lfo->lfo_frequency = 2;	// [0.125, 0.25, 0.5, 1, 2, 4, 8, 16]

	WahWah->range        = 200;
	WahWah->mid_freq     = 350;
	WahWah->mid_freq_mod = 0;

	WahWah->reinit_counter = 0;
	WahWah->bandpass->Q = 20;

	SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq, WahWah->bandpass->Q);

	return WAHWAH_OK;
}


/** @brief Processed current tremolo sample
 * @param Tremolo: struct for tremolo information
 * @param data: current sample
 * @param lfo_value: current lfo value
 */

WahWah_Status ProcessWahWah(struct WahWah_t *WahWah, float *data){

	// FETCH: actual LFO value
	LFO_SingleValueProcess(WahWah->lfo);

	// MODULATE: mid frequency of bandpass with light sensor
	WahWah->mid_freq = (float)ADC_value / 4;

	// MODULATE: mid frequency of bandpass with poti
	//WahWah->mid_freq = (((float)ADC_value / 4095) * 2000) + WahWah->range / 2;

	// MODULATE: mid frequency of bandpass with a certain range and lfo amplitude
	WahWah->mid_freq_mod = WahWah->mid_freq + (WahWah->range / 2) * WahWah->lfo->lfo_data;

	// MODULATE: mid frequncy of bandpass with light sensor
	//WahWah->mid_freq_mod = (float)ADC_value / 4;

	// FETCH: Q from ADC
	//WahWah->bandpass->Q = (((float)ADC_value / 4095) * 10) + 0.01;

	// RESET: Filter after 1000 samples (with SR = 24k Hz >> 24 times a second)
	if(WahWah->reinit_counter == 100){

		SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq_mod, WahWah->bandpass->Q);
		WahWah->reinit_counter = 0;
	}

	WahWah->reinit_counter++;

	ProcessFilter(WahWah->bandpass, data);

	return WAHWAH_OK;
}
