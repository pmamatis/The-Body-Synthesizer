#include "main.h"

#ifndef INC_EFFECTS_H_
#define INC_EFFECTS_H_

/*********************************
 * @brief		Defines
 *********************************/
#define MAX_EFFECTS 10

/***************************
 * @brief		Enumeration for DSP Effects
 ***************************/
typedef enum effects_t_enum {
	TREM = 1,	// Tremolo
	DIST,		// Distortion
	EQ,			// Equalizer
	ADSR		// ADSR

}effects_t_enum;


/*********************************
 * @beief	Variables
 *********************************/

/** Array filled with the effects in process order
 */
effects_t_enum effect_order[MAX_EFFECTS];

/*********************************
 * @brief	Functions
 *********************************/
void effects_init();
void effects_process(float* calculate_value);
void effects_add(effects_t_enum effect, uint8_t position);
void effects_delete(effects_t_enum effect, uint8_t position);

#endif /* __EFFECTS_H */
