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
struct Tremolo_t{
	struct effects_lfo_t* lfo_data;
	uint32_t tremolo_blocksizecounter;
	bool recalc_lfo;
	float tremolo_maximum_rate;
	float tremolo_maximum_depth;
};

struct Tremolo_t Tremolo;

Tremolo_Status Tremolo_Init(void);
Tremolo_Status SetupTremolo(struct Tremolo_t* Tremolo);
//Tremolo_Status ProcessTremolo(struct effects_LFO* Tremolo, float* data);
Tremolo_Status ProcessTremolo(struct Tremolo_t* Tremolo, float* data, float* lfo_value);

#endif /* INC_TREMOLO_H_ */
