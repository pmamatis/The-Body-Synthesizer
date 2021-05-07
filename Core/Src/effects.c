#include "effects.h"



void effects_init(){
    for (int i = 0; i < MAX_EFFECTS; i++){
    	effect_order[i] = 0;
    }
}


void effects(float calculate_value){



    for (int i = 0; i < MAX_EFFECTS; i++)
    {
        switch (effect_order[i])
        {
        case TREM:
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

void effects_addEffect(effects_t_enum effect, uint8_t position){

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
