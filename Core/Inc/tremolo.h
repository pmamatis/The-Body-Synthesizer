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

struct effects_lfo_t Tremolo1;

Tremolo_Status Tremolo_Init(void);
Tremolo_Status SetupTremolo(struct effects_lfo_t* Tremolo);
Tremolo_Status ProcessTremolo(struct effects_lfo_t* Tremolo, float* data);

#endif /* INC_TREMOLO_H_ */
