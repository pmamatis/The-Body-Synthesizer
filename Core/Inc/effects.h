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
typedef enum effects_t_enum{
    TREM = 1,     // Tremolo
    DIST,         // Distortion 
    EQ_BA1,       // LP
    EQ_BA2,       // BP1
    EQ_BA3,       // BP2
    EQ_BA4,       // BP3
    EQ_BA5        // HP

}effects_t_enum;


/*********************************
 * @parameter	Variables
 *********************************/
uint8_t effect_order[MAX_EFFECTS];



/*********************************
 * @parameter	Functions
 *********************************/
void effects_init();
void effects(float calculate_value);
void effects_addEffect(effects_t_enum effect, uint8_t position);

#endif /* __EFFECTS_H */
