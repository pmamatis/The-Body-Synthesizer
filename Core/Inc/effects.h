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
typedef enum effects_t_enum{
	TREM = 1,	// Tremolo
	DIST,		// Distortion
//	DIST_S,		// Soft Clipping Distortion
//	DIST_H,		// Hard Clipping Distortion
	EQ,			// Equalizer
	ADSR,		// ADSR
	VOICES,
	WAHWAH
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
void effects_init(void);
void effects_process(float* calculate_value);
void effects_add(effects_t_enum effect);
void effects_process_fast(float* calculate_value);
void keyboard_adsr_process(void);
void effects_delete(effects_t_enum effect) ;

#endif /* __EFFECTS_H */
