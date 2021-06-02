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

	SetupTremolo(&Tremolo1);

	return TREMOLO_OK;
}

Tremolo_Status SetupTremolo(struct effects_lfo_t* Tremolo) {
	Tremolo->lfo_index = 0;
	Tremolo->lfo_frequency = 1;
	Tremolo->lfo_quarter = 0;
	Tremolo->lfo_blocksizecounter = 0;
	Tremolo->depth = 1.00;

	return TREMOLO_OK;
}

Tremolo_Status ProcessTremolo(struct effects_lfo_t* Tremolo, float* data) {

	float calc = *data;

	Signal_Synthesis_LFO(Tremolo);
	float tremolo_mod = (1 + Tremolo->depth * effect_LFO[Tremolo->lfo_blocksizecounter]);
	calc = (tremolo_mod * calc) / (1+Tremolo->depth);
	Tremolo->lfo_blocksizecounter++;

	*data = calc;

	return TREMOLO_OK;
}
