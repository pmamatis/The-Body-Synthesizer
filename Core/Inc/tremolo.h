/** TODO
 * @file tremolo.h
 * @author marc bielen
 * @brief tremolo effect
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INC_TREMOLO_H_
#define INC_TREMOLO_H_
/**
 * @defgroup tremolo Tremolo effect
 * @ingroup Effects
 * @brief another effect TODO
 * 
 * @{
 */

#include "main.h"
#include <stdbool.h>
/*********************************
 * @brief		Enums
 *********************************/
/***************************
 * @brief Enumeration for Tremolo Debugging
 ***************************/
typedef enum {
	TREMOLO_FAIL = -1,
	TREMOLO_OK = 1
} Tremolo_Status;

/*********************************
 * @brief		Structs
 *********************************/

/*********************************
 * @brief		Tremolo struct
 * @parameter	Tremolo
 *********************************/
struct Tremolo_t{

	struct effects_lfo_t *lfo;
	float tremolo_maximum_rate;
	float tremolo_maximum_depth;
};

/*********************************
 * @brief		Variables
 *********************************/
struct Tremolo_t Tremolo;

Tremolo_Status Tremolo_Init(struct Tremolo_t* Tremolo);
Tremolo_Status Tremolo_Reset(void);
Tremolo_Status ProcessTremolo(struct Tremolo_t* Tremolo, float* data);
/** @} */
#endif /* INC_TREMOLO_H_ */
