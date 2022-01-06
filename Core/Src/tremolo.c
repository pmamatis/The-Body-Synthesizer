#include "tremolo.h"

/*********************************
 * @brief		Tremolo functions
 * @parameter	Tremolo
 *********************************/

/** 
 * @brief Tremolo Init function 
 * 
 * @param Tremolo 
 * @return Tremolo_Status 
 */
Tremolo_Status Tremolo_Init(struct Tremolo_t* Tremolo) {

	Tremolo->lfo = &lfo_tremolo;

	Tremolo->lfo->lfo_index = 0;
	Tremolo->lfo->lfo_frequency = 1;
	Tremolo->lfo->lfo_quarter = 0;
	Tremolo->lfo->lfo_depth = 0.5;
	Tremolo->lfo->lfo_done_flag = false;

	Tremolo->tremolo_maximum_rate = 16;
	Tremolo->tremolo_maximum_depth = 1.00;

	return TREMOLO_OK;
}

/**
 * @brief resets all tremelo parameters
 * 
 * @return Tremolo_Status 
 */
Tremolo_Status Tremolo_Reset(void) {

	Display.Tremolo_ONOFF = false;

	Tremolo.lfo->lfo_index = 0;
	Display.Tremolo_Rate = Tremolo.lfo->lfo_frequency = 1;
	Display.Tremolo_Rate_Index = Display.last_Tremolo_Rate_Index  = 3;	// 1 Hz
	Tremolo.lfo->lfo_quarter = 0;
	Display.Tremolo_Depth = Tremolo.lfo->lfo_depth = 0.5;
	Tremolo.lfo->lfo_done_flag = false;

	Display.Tremolo_Sources[0] = POTI;
	Display.Tremolo_Sources[1] = POTI;

	strcpy(Display.value_str_tremolo[0], "OFF");

	return TREMOLO_OK;
}

/** @brief Processed current tremolo sample
 * @param Tremolo: struct for tremolo information
 * @param data: current sample
 * @param lfo_value: current lfo value
 */
Tremolo_Status ProcessTremolo(struct Tremolo_t* Tremolo, float* data) {

	LFO_SingleValueProcess(Tremolo->lfo, TREMOLO_LFO);

	float tremolo_mod = (1 + Tremolo->lfo->lfo_depth * Tremolo->lfo->lfo_data);
	*data = (tremolo_mod * *data) / (1+Tremolo->lfo->lfo_depth);

	return TREMOLO_OK;
}
