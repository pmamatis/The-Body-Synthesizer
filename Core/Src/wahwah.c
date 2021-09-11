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

	WahWah->lfo->lfo_index     = 0;
	WahWah->lfo->lfo_quarter   = 0;
	WahWah->lfo->lfo_depth     = 0.8;	// [0, 1]
	WahWah->lfo->lfo_frequency = 8;	// [0.125, 0.25, 0.5, 1, 2, 4, 8]

	WahWah->range        = 200;
	WahWah->mid_freq     = 200;
	WahWah->mid_freq_mod = 0;

	SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq, 10);

	return WAHWAH_OK;
}


/** @brief Processed current tremolo sample
 * @param Tremolo: struct for tremolo information
 * @param data: current sample
 * @param lfo_value: current lfo value
 */

WahWah_Status ProcessWahWah(struct WahWah_t *WahWah, float* data){

	LFO_SingleValueProcess(WahWah->lfo);

//	WahWah->mid_freq_mod = WahWah->mid_freq + (WahWah->range / 2) * WahWah->lfo->lfo_data;
//
//	SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq_mod, 10);
//
//	ProcessFilter(WahWah->bandpass, data);

	float wahwah_mod = (1 + WahWah->lfo->lfo_depth * WahWah->lfo->lfo_data);
	*data = (wahwah_mod * *data) / (1 + WahWah->lfo->lfo_depth);


	return WAHWAH_OK;
}
