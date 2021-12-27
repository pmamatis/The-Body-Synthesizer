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
	WahWah->lfo->lfo_frequency = 1;	// [0.125, 0.25, 0.5, 1, 2, 4, 8, 16]

	WahWah->range        = 600;
	WahWah->mid_freq     = 350;
	WahWah->mid_freq_mod = 0;

	WahWah->max_range = 500;
	WahWah->max_mid_freq = 2000;	// can be adjusted in the display to values 1000, 2000, 3000 and 4000
	WahWah->max_Q = 20;

	WahWah->reinit_counter = 0;
	WahWah->bandpass->Q = 1;

	SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq, WahWah->bandpass->Q);

	return WAHWAH_OK;
}

WahWah_Status WahWah_Reset(struct WahWah_t *WahWah) {

	Display.WahWah_ONOFF = false;

	WahWah->lfo->lfo_index     = 0;
	WahWah->lfo->lfo_quarter   = 0;
	Display.WahWah_LFOfreq = WahWah->lfo->lfo_frequency = 1;	// [0.125, 0.25, 0.5, 1, 2, 4, 8, 16]
	Display.WahWah_LFOfreq_Index = Display.last_WahWah_LFOfreq_Index = 3;	// 1 Hz

	Display.WahWah_Range = WahWah->range        = 600;
	Display.WahWah_MidFreq = WahWah->mid_freq     = 350;
	WahWah->mid_freq_mod = 0;

	WahWah->reinit_counter = 0;
	Display.WahWah_Q = WahWah->bandpass->Q = 1;

	Display.WahWah_Sources[0] = POTI;
	Display.WahWah_Sources[1] = POTI;
	Display.WahWah_Sources[2] = POTI;
	Display.WahWah_Sources[3] = POTI;

	strcpy(Display.value_str_wahwah[0], "OFF");

	SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq, WahWah->bandpass->Q);

	return WAHWAH_OK;
}

/** @brief Processed current tremolo sample
 * @param Tremolo: struct for tremolo information
 * @param data: current sample
 * @param lfo_value: current lfo value
 */
WahWah_Status ProcessWahWah(struct WahWah_t *WahWah, float *data){

	// SET: mid frequency to at least 50 Hz due to filter response
	if(WahWah->mid_freq < 50)
		WahWah->mid_freq = 50;	// 50 Hz Offset;

	// RESET: Filter after 100 samples (with SR = 24k Hz >> 240 times a second)
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
	LFO_SingleValueProcess(WahWah->lfo, WAHWAH_LFO);

	if(WahWah->mid_freq < 50)
		WahWah->mid_freq = 50;	// 50 Hz Offset;

	WahWah->mid_freq_mod = WahWah->mid_freq + (WahWah->range / 2) * WahWah->lfo->lfo_data;

	// RESET: Filter after 100 samples (with SR = 24k Hz >> 240 times a second)
	if(WahWah->reinit_counter == 100){

		SetupBandpassCPG(WahWah->bandpass, WahWah->mid_freq_mod, WahWah->bandpass->Q);
		WahWah->reinit_counter = 0;
	}

	WahWah->reinit_counter++;

	ProcessFilter(WahWah->bandpass, data);

	return WAHWAH_OK;
}
