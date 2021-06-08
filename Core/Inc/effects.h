#include "main.h"
#include <stdbool.h>

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
	DIST_S,		// Soft Clipping Distortion
	DIST_H,		// Hard Clipping Distortion
	EQ,			// Equalizer
	ADSR		// ADSR

}effects_t_enum;


/*********************************
 * @beief	Variables
 *********************************/

/** Array filled with the effects in process order
 */
effects_t_enum effect_order[MAX_EFFECTS];
float lfo_value;
//bool process_trem;

/*********************************
 * @brief	Functions
 *********************************/
void effects_init();
void effects_process(float* calculate_value);
void effects_add(effects_t_enum effect, uint8_t position);
void effects_delete(effects_t_enum effect, uint8_t position);

#endif /* __EFFECTS_H */
