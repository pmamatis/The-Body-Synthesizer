#include "effects.h"



void effects_init(){
    for (int i = 0; i < MAX_EFFECTS; i++){
    	effect_order[i] = 0;
    }
}


void effects_process(float* calculate_value){



    for (int i = 0; i < MAX_EFFECTS; i++)
    {
        switch (effect_order[i])
        {
        case TREM:
            /* code */
            break;
        
        case EQ:
        	/* code */
            break;
        case DIST:
            /* code */
            break;
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
