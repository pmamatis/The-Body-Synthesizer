#include "effects.h"
#include "display.h"

void effects_init(void) {

	for (int i = 0; i < MAX_EFFECTS; i++){
		effect_order[i] = 0;
	}
}

/**
 * processes all effects in the given order, order is determined through effect_order[i]
 * @note access order throgh the functions:  effects_add(effects_t_enum effect, uint8_t position) to add effects
 * 											 effects_delete(effects_t_enum effect, uint8_t position) to delete effects
 * @param calculate_value:adress of a signle sample which should be effected
 */
void effects_process(float* calculate_value) {

	if(Display.mode == BODYSYNTH) {
		for(int i=0; i<MAX_EFFECTS; i++) {
			switch(effect_order[i]) {
			case TREM:
				ProcessTremolo(&Tremolo, calculate_value);
				break;
			case EQ:
				ProcessEQ(calculate_value);
				break;
			case DIST_H:
				ProcessHardClippingDistortion(&HardClipping, calculate_value);
				break;
			case DIST_S:
				ProcessAtanSoftClippingDistortion(&SoftClipping, calculate_value);
				break;
			default:
				break;
			}
		}
	}
	//	else if(Display.mode == KEYBOARD) {
	//		OnePress_ADSR_Linear_Process(&envelope, calculate_value);
	//	}
	//	 if(emg_triggerd_flag || keyboard_pressed_flag) {
	//		OnePress_ADSR_Linear_Process(&envelope, calculate_value);
	//	}
}



void effects_process_fast(float* calculate_value){

	if(effect_order[0] == EQ){
		ProcessEQ(calculate_value);
	}

	if(effect_order[1] == TREM){
		ProcessTremolo(&Tremolo, calculate_value);
	}

	if(effect_order[2] == DIST_H){
		ProcessHardClippingDistortion(&HardClipping, calculate_value);

	}

	if(effect_order[3] == DIST_S){
		ProcessAtanSoftClippingDistortion(&SoftClipping, calculate_value);
	}

	if(effect_order[4] == WAHWAH) {
		if(Display.WahWah_Mode == 0)
			ProcessWahWah(&WahWah, calculate_value);
		else if(Display.WahWah_Mode == 1)
			ProcessAutoWahWah(&WahWah, calculate_value);
	}
}


/** function for the keyboard adsr processing */
void keyboard_adsr_process(void){
	//	if(emg_triggerd_flag || keyboard_pressed_flag) {
	OnePress_ADSR_Linear_Process(&adsr_keyboard[0], &calculate_keyboard[0], activate_processing[0]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[1], &calculate_keyboard[1], activate_processing[1]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[2], &calculate_keyboard[2], activate_processing[2]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[3], &calculate_keyboard[3], activate_processing[3]);
	OnePress_ADSR_Linear_Process(&adsr_keyboard[4], &calculate_keyboard[4], activate_processing[4]);
}

/**
 * Inserts an entry in the effect_order[position]
 * @param effect: wanted effect listed in the effects_t_enum
 * @param position: position in the effect chain,EQ = 0 Trem = 1, Dist_h = 2, Dist_s = 3
 */
void effects_add(effects_t_enum effect) {

	switch(effect) {
	case EQ:
		effect_order[0] = EQ;
		break;
	case TREM:
		effect_order[1] = TREM;
		break;
	case DIST_H:
		effect_order[2] = DIST_H;
		break;
	case DIST_S:
		effect_order[3] = DIST_S;
		break;
	case WAHWAH:
		effect_order[4] = WAHWAH;
	default:
		break;
	}
	//
	//	if(position < MAX_EFFECTS) {
	//		effect_order[position] = effect;
	//
	//		/*
	//		effects_t_enum tmp = effect_order[position];
	//		effects_t_enum tmp2;
	//
	//		for(int i=position+1; i<MAX_EFFECTS; i++) {
	//			tmp2 = effect_order[i];
	//			effect_order[i] = tmp;
	//			tmp = tmp2;
	//		}
	//		*/
	//	}
	//	else {
	//		//error @TODO
	//	}
}


/**
 * Deletes an effect inside the effect_order[position]
 */
void effects_delete(effects_t_enum effect) {


	switch(effect) {
	case EQ:
		effect_order[0] = 0;
		break;
	case TREM:
		effect_order[1] = 0;
		break;
	case DIST_H:
		effect_order[2] = 0;
		break;
	case DIST_S:
		effect_order[3] = 0;
		break;
	case WAHWAH:
		effect_order[4] = 0;
	default:
		break;
	}

}
