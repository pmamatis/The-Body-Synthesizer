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
	EQ,			// Equalizer
	ADSR,		// ADSR
	VOICES,		// Voices
	WAHWAH		// WahWah
} effects_t_enum;

/** Array filled with the effects in process order
 */
effects_t_enum effect_order[MAX_EFFECTS];

/*********************************
 * @brief	Functions
 *********************************/
void effects_init(void);
void effects_add(effects_t_enum effect);
void effects_process(float* calculate_value);
void effects_delete(effects_t_enum effect) ;
void keyboard_adsr_process(void);

#endif /* __EFFECTS_H */
