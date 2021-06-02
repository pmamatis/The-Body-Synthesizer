#include "effects.h"

void effects_init(){
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
void effects_process(float* calculate_value){

	for (int i = 0; i < MAX_EFFECTS; i++) {

		switch (effect_order[i]) {

		case TREM:
			/* code */
			break;

		case EQ:
			ProcessEQ(calculate_value);
			break;

		case DIST:
			/* code */
			break;

		case ADSR:
			/*calculate_value = calculate_value + 1;	// necessary for ADSR processing
			calculate_value = calculate_value * ADSR_Linear_Process(&envelope);
			calculate_value = calculate_value - 1;*/

		default:
			break;

		}
	}
}

/**
 * Inserts an entry in the effect_order[position], and shifts the other entrys to the right
 * @param effect: wanted effect listed in the effects_t_enum
 * @param position:
 */
void effects_add(effects_t_enum effect, uint8_t position){

	if (position < MAX_EFFECTS){

		effects_t_enum tmp = effect_order[position];
		effects_t_enum tmp2;
		effect_order[position] = effect;
		for (int i = position+1; i < MAX_EFFECTS;i++){
			tmp2 = effect_order[i];
			effect_order[i] = tmp;
			tmp = tmp2;



		}
	}
	else {
		//error @TODO
	}

}

/**
 * Deletes an effect inside the effect_order[position]
 */
void effects_delete(effects_t_enum effect, uint8_t position){

	if (position < MAX_EFFECTS){
		if (effect == effect_order[position]){
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
