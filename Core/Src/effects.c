#include "effects.h"
#include "display.h"

void effects_init(void) {

	for (int i = 0; i < MAX_EFFECTS; i++){
		effect_order[i] = 0;
	}
}

/** @brief reads the effect_order[] and activates the processing functions for the effects
 * 	@param single sample value, where the effects should be applied
 */
void effects_process(float* calculate_value){

	if(effect_order[0] == EQ) {
		ProcessEQ(calculate_value);
	}

	if(effect_order[1] == TREM) {
		ProcessTremolo(&Tremolo, calculate_value);
	}


	if(effect_order[2] == DIST) {
		if(Display.Distortion_Type == 0)
			ProcessSoftClippingDistortion(calculate_value);
		else if(Display.Distortion_Type == 1)
			ProcessHardClippingDistortion(calculate_value);
	}

	if(effect_order[3] == WAHWAH) {
		if(Display.WahWah_Mode == 0)
			ProcessWahWah(&WahWah, calculate_value);
		else if(Display.WahWah_Mode == 1)
			ProcessAutoWahWah(&WahWah, calculate_value);
	}
}


/** @brief function for the keyboard adsr processing*/
void keyboard_adsr_process(void){
	OnePress_ADSR_Linear_Process(&adsr_keyboard[0], &calculate_keyboard[0], activate_processing[0]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[1], &calculate_keyboard[1], activate_processing[1]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[2], &calculate_keyboard[2], activate_processing[2]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[3], &calculate_keyboard[3], activate_processing[3]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[4], &calculate_keyboard[4], activate_processing[4]);
}

/**
 * @brief Inserts an entry in the effect_order[position]
 * @param effect: wanted effect listed in the effects_t_enum
 */
void effects_add(effects_t_enum effect) {

	switch(effect) {
	case EQ:
		effect_order[0] = EQ;
		break;
	case TREM:
		effect_order[1] = TREM;
		break;

	case DIST:
		effect_order[2] = DIST;
		break;
	case WAHWAH:
		effect_order[3] = WAHWAH;
	default:
		break;
	}
}

/** @brief Deletes a certain effect inside the effect_order[position]
 */
void effects_delete(effects_t_enum effect) {


	switch(effect) {
	case EQ:
		effect_order[0] = 0;
		break;
	case TREM:
		effect_order[1] = 0;
		break;

	case DIST:
		effect_order[2] = 0;
		break;
	case WAHWAH:
		effect_order[3] = 0;
	default:
		break;
	}
}
