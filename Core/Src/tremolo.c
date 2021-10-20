/**
 ******************************************************************************
 * @file    tremolo.c
 * @author  Marc Bielen
 * @date 	 10 May 2020
 * @brief	 Tremolo-Library
 */

#include "tremolo.h"

/*********************************
 * @brief		Tremolo functions
 * @parameter	Tremolo
 *********************************/

Tremolo_Status Tremolo_Init(struct Tremolo_t* Tremolo) {

	Tremolo->lfo = &lfo_tremolo;

	Tremolo->lfo->lfo_index = 0;
	Tremolo->lfo->lfo_frequency = 0.125;
	Tremolo->lfo->lfo_quarter = 0;
	Tremolo->lfo->lfo_depth = 0.5;
	Tremolo->lfo->lfo_done_flag = false;

	Tremolo->tremolo_maximum_rate = 16;
	Tremolo->tremolo_maximum_depth = 1.00;

	return TREMOLO_OK;
}

/** @brief Processed current tremolo sample
 * @param Tremolo: struct for tremolo information
 * @param data: current sample
 * @param lfo_value: current lfo value
 */
Tremolo_Status ProcessTremolo(struct Tremolo_t* Tremolo, float* data) {

	LFO_SingleValueProcess(Tremolo->lfo);

	float tremolo_mod = (1 + Tremolo->lfo->lfo_depth * Tremolo->lfo->lfo_data);
	*data = (tremolo_mod * *data) / (1+Tremolo->lfo->lfo_depth);

	return TREMOLO_OK;
}
