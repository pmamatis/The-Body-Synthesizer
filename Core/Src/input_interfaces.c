/*
 * input_interfaces.c
 *
 *  Created on: Aug 15, 2021
 *      Author: Marc Bielen
 */


#include "input_interfaces.h"
//
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

uint8_t II_Display_Effects(void){
	if (Display.Distortion_ONOFF == true){

	}
}


