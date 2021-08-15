/**
 ******************************************************************************
 * @file    tremolo.h
 * @author  Marc Bielen
 * @date 	 10 May 2020
 * @brief	 Tremolo-Library
 */

#ifndef INC_TREMOLO_H_
#define INC_TREMOLO_H_

#include "main.h"
#include <stdbool.h>

/***************************
 * @brief Enumeration for Tremolo Debugging
 ***************************/
typedef enum {
	TREMOLO_FAIL = -1,
	TREMOLO_OK = 1
} Tremolo_Status;

/*********************************
 * @brief		Tremolo struct
 * @parameter	Tremolo
 *********************************/
struct effects_LFO{
	uint8_t name;
	uint32_t index;
	uint8_t quarter;
	float lfo_frequency;
	uint32_t lfo_blocksizecounter;
	uint32_t tremolo_blocksizecounter;
	float lfo_depth;
	bool recalc_lfo;
	float tremolo_maximum_rate;
	float tremolo_maximum_depth;
};

struct effects_lfo_t Tremolo;

Tremolo_Status Tremolo_Init(void);
Tremolo_Status SetupTremolo(struct effects_LFO* Tremolo);
//Tremolo_Status ProcessTremolo(struct effects_LFO* Tremolo, float* data);
Tremolo_Status ProcessTremolo(struct effects_LFO* Tremolo, float* data, float* lfo_data);

#endif /* INC_TREMOLO_H_ */
