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


	//if(effect_order[0] == EQ)
	ProcessEQ(calculate_value);
	lfo_value = LFO_SingleValueProcess(&lfo);
	ProcessTremolo(&Tremolo, calculate_value, &lfo_value);
	//ProcessHardClippingDistortion(&HardClipping, calculate_value);
	//ProcessAtanSoftClippingDistortion(&SoftClipping, calculate_value);


	//	if(Display.mode == BODYSYNTH) {
	//		for(int i=0; i<MAX_EFFECTS; i++) {
	//			switch(effect_order[i]) {
	////			case TREM:
	////				lfo_value = LFO_SingleValueProcess(&lfo);
	////				ProcessTremolo(&Tremolo, calculate_value, &lfo_value);
	////				break;
	//			case EQ:
	//				ProcessEQ(calculate_value);
	//				break;
	////			case DIST_H:
	////				ProcessHardClippingDistortion(&HardClipping, calculate_value);
	//////				break;
	////			case DIST_S:
	////				ProcessAtanSoftClippingDistortion(&SoftClipping, calculate_value);
	////				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//	else if(Display.mode == KEYBOARD) {
	////		OnePress_ADSR_Linear_Process(&envelope, calculate_value);
	//	}
}


/**
 * Inserts an entry in the effect_order[position]
 * @param effect: wanted effect listed in the effects_t_enum
 * @param position: position in the effect chain
 */
void effects_add(effects_t_enum effect, uint8_t position) {

	if(position < MAX_EFFECTS) {
		effect_order[position] = effect;

		/*
		effects_t_enum tmp = effect_order[position];
		effects_t_enum tmp2;

		for(int i=position+1; i<MAX_EFFECTS; i++) {
			tmp2 = effect_order[i];
			effect_order[i] = tmp;
			tmp = tmp2;
		}
		 */
	}
	else {
		//error @TODO
	}
}


/**
 * Deletes an effect inside the effect_order[position]
 */
void effects_delete(effects_t_enum effect, uint8_t position) {

	if(position < MAX_EFFECTS) {
		if(effect == effect_order[position]) {
			effect_order[position] = 0;
		}
		else{
			//print LCD( "diffrent Effect, really want to delete?" )
		}
	}
	else {
		//error @TODO
	}
}
