/*
 * input_interfaces.c
 *
 *  Created on: Aug 15, 2021
 *      Author: Marc Bielen
 */


#include "input_interfaces.h"
/** @brief Creates the Signals given throzgh the Display-Interput
 * retval: 0 Error
 * 		   1 Success
 */
uint8_t II_Display_Voices(void){
	for (uint8_t ii_i=0; ii_i < II_MAX_VOICES;ii_i++){

		//create Signal and save its ID
		if (Display.Voices_ONOFF[ii_i] == true && signals1.count < II_MAX_VOICES){
			NewSignal(&signals1, SIN, Display.Voices_Note[ii_i],Display.Voices_Octave[ii_i]);
			ii_voice_IDs[ii_i] = signals1.ID[signals1.count];
		}
		//Delete signal with its ID
		else if (Display.Voices_ONOFF[ii_i]==false &&  signals1.count > 0){
			uint8_t find_ID_counter = 0;
			while (ii_voice_IDs != signals1.ID[find_ID_counter]){
				find_ID_counter ++;
				if (find_ID_counter > MAX_SIGNAL_KOMBINATION){
					printf("Voice deletion error!\r\n");
					return 0;
				}
			DeleteSignal(&signals1, find_ID_counter);
			}
		}
	}
	return 1;
}


/**@brief parses the information from the Display-input to the strcuts of the effects
 * retval: 0 Error
 * 		   1 Success
 */
uint8_t II_Display_Effects(void){

	// Distortion
	if (Display.Distortion_ONOFF == true){
		effects_add(DIST_H, 0);
		HardClipping.distortion_gain = Display.Distortion_Gain;
	}
	else if (Display.Distortion_ONOFF == false){
		effects_delete(DIST_H, 0);
	}

	//Tremolo
	if (Display.Tremolo_ONOFF == true){
		effects_add(TREM, 1);
		Tremolo.lfo_data->lfo_depth = Display.Tremolo_Depth;
		Tremolo.lfo_data->lfo_frequency = Display.Tremolo_Rate;

	}
	else if (Display.Distortion_ONOFF == false){
		effects_delete(TREM, 1);
	}

	//Filter
	if (Display.Filter_ONOFF == true){
		effects_add(EQ, 3);

//		SetupLowShelf(EQ_BAND1_I, Display.Filter_Cutoff[], Q, dBGain)

	}
	else if (Display.Filter_ONOFF == false){
		effects_delete(TREM, 1);
		Display.Filter_Cutoff;
		Display.Filter_Q;

//		SetupNotch(BP, cutoff, Q)
	}




	return 1;

}


