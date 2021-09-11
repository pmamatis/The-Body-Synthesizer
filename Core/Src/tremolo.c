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
Tremolo_Status Tremolo_Init(void) {

	Tremolo.lfo_data = &lfo;
	SetupTremolo(&Tremolo);

	return TREMOLO_OK;
}

Tremolo_Status SetupTremolo(struct Tremolo_t* Tremolo) {

	Tremolo->lfo_data->lfo_index = 0;
	Tremolo->lfo_data->lfo_frequency = 4.00;
	//Tremolo->lfo_frequency = 4.00;
	Tremolo->lfo_data->lfo_quarter = 0;
	Tremolo->lfo_data->lfo_blocksizecounter = 0;
	Tremolo->tremolo_blocksizecounter = 0;
	//Tremolo->lfo_depth = 0.00;
	Tremolo->lfo_data->lfo_depth = 0.50;
	Tremolo->recalc_lfo = false;
	Tremolo->tremolo_maximum_rate = 9;
	Tremolo->tremolo_maximum_depth = 1.00;

	return TREMOLO_OK;
}

/*Tremolo_Status ProcessTremolo(struct effects_LFO* Tremolo, float* data) {	// ORIGINAL!!!

	float calc = *data;

	Signal_Synthesis_LFO(Tremolo);
	//Signal_Synthesis_LFO(&Tremolo);	// calculates new LFO value and saves it into effects_LFO
	float tremolo_mod = (1 + Tremolo->lfo_depth * effect_LFO[Tremolo->lfo_blocksizecounter]);
	//calculate_vector1[BLOCKSIZE_counter] = (tremolo_mod * calculate_vector1[BLOCKSIZE_counter]) / (1+LFO_Depth);
	calc = (tremolo_mod * calc) / (1+Tremolo->lfo_depth);
	Tremolo->lfo_blocksizecounter++;

 *data = calc;

	return TREMOLO_OK;
}*/

/*Tremolo_Status ProcessTremolo(struct effects_LFO* Tremolo, float* data, float* lfo_data) {

	float calc = *data;
	float lfo = *lfo_data;

	float tremolo_mod = (1 + Tremolo->lfo_depth * lfo);
	calc = (tremolo_mod * calc) / (1+Tremolo->lfo_depth);
	//Tremolo->lfo_blocksizecounter++;

	*data = calc;

	return TREMOLO_OK;
}*/

/** @brief Processed current tremolo sample
 * @param Tremolo: struct for tremolo information
 * @param data: current sample
 * @param lfo_value: current lfo value
 */
Tremolo_Status ProcessTremolo(struct Tremolo_t* Tremolo, float* data, float* lfo_value) {

	float tremolo_mod = (1 + Tremolo->lfo_data->lfo_depth * *lfo_value);
	*data = (tremolo_mod * *data) / (1+Tremolo->lfo_data->lfo_depth);

	return TREMOLO_OK;
}
