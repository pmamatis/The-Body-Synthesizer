/*
 * input_interfaces.c
 *
 *  Created on: Aug 15, 2021
 *      Author: Marc Bielen
 */

#include "input_interfaces.h"

///** @brief Creates the Signals given throzgh the Display-Interput
// * retval: 0 Error
// * 		   1 Success
// */
//uint8_t II_Display_Voices(void){
//	for (uint8_t ii_i=0; ii_i < II_MAX_VOICES;ii_i++){
//
//		//create Signal and save its ID
//		if (Display.Voices_ONOFF[ii_i] == true && Display.Voices_Created[ii_i] == false){
//			NewSignal(&signals1, SIN, Display.Voices_Note[ii_i],Display.Voices_Octave[ii_i]);
//			ii_voice_IDs[ii_i] = signals1.ID[signals1.count];
////			printf("saved ID = %i\r\n", ii_voice_IDs[ii_i]);
//			Display.Voices_Created[ii_i] = true;
////			printf("Voice %i created\r\n", ii_i);
//		}
//		//Delete signal with its ID
//		else if (Display.Voices_ONOFF[ii_i]==false && Display.Voices_Created[ii_i] == true){
//			uint8_t find_ID_counter = 0;
//			while (ii_voice_IDs[ii_i] != signals1.ID[find_ID_counter]){
//				find_ID_counter ++;
////				printf("in while %i \r\n", find_ID_counter);
//				if (find_ID_counter > MAX_SIGNAL_KOMBINATION){
////					printf("Voice deletion error!\r\n");
//					return 0;
//				}
//			}
////			printf("deleted ID = %i\r\n", signals1.ID[find_ID_counter]);
//			DeleteSignal(&signals1, find_ID_counter);
////			printf("Voice %i deleted \r\n", ii_i);
//			Display.Voices_Created[ii_i] = false;
//
//
//			}
//		}
//
//	return 1;
//}

/** @brief Creates the Signals given throzgh the Display-Interput
 * retval: 0 Error
 * 		   1 Success
 */
uint8_t II_Display_Voices(void) {

	for(uint8_t ii_i=0; ii_i < II_MAX_VOICES; ii_i++) {

		//create Signal and save its ID
		if (Display.Voices_ONOFF[ii_i] == true && Display.Voices_Created[ii_i] == false) {
			NewSignal(&signals1, SIN, Display.Voices_Note[ii_i],Display.Voices_Octave[ii_i]);
			//outputBuffer_position = HALF_BLOCK;	// reset the buffer position
			ii_voice_IDs[ii_i] = signals1.ID[signals1.count];
			//printf("saved ID = %i\r\n", ii_voice_IDs[ii_i]);
			Display.Voices_Created[ii_i] = true;
			//printf("Voice %i created\r\n", ii_i);
			//printf("Note %c\r\n", Display.Voices_Note[ii_i]);
			//printf("Octave %c\r\n", Display.Voices_Octave[ii_i]);
		}
		//Delete signal with its ID
		else if (Display.Voices_ONOFF[ii_i]==false && Display.Voices_Created[ii_i] == true) {
			uint8_t find_ID_counter = 0;
			while (ii_voice_IDs[ii_i] != signals1.ID[find_ID_counter]) {
				find_ID_counter ++;
				//				printf("in while %i \r\n", find_ID_counter);
				if (find_ID_counter > MAX_SIGNAL_KOMBINATION){
					//					printf("Voice deletion error!\r\n");
					return 0;
				}
			}
			//printf("deleted ID = %i\r\n", signals1.ID[find_ID_counter]);
			DeleteSignal(&signals1, find_ID_counter);
			//printf("Voice %i deleted \r\n", ii_i);
			Display.Voices_Created[ii_i] = false;
		}


		// if note or octave is changed, the old signal should be exchanged with the new one
		else if (Display.Voices_ONOFF[ii_i] == true && Display.Voices_Created[ii_i] == true) {
			if( (Display.last_Voices_Note[ii_i] != Display.Voices_Note[ii_i]) || (Display.last_Voices_Octave[ii_i] != Display.Voices_Octave[ii_i]) ) {
				uint8_t find_ID_counter_2 = 0;
				while (ii_voice_IDs[ii_i] != signals1.ID[find_ID_counter_2]) {
					find_ID_counter_2++;
					if (find_ID_counter_2 > MAX_SIGNAL_KOMBINATION){
						return 0;
					}
				}
				//printf("deleted ID = %i\r\n", signals1.ID[find_ID_counter_2]);
				DeleteSignal(&signals1, find_ID_counter_2);
				//printf("Voice %i deleted \r\n", ii_i);
				NewSignal(&signals1, SIN, Display.Voices_Note[ii_i], Display.Voices_Octave[ii_i]);
				ii_voice_IDs[ii_i] = signals1.ID[signals1.count];
				//outputBuffer_position = HALF_BLOCK;	// reset the buffer position
				//printf("Voice %i created\r\n", ii_i);
				//printf("Note %c\r\n", Display.Voices_Note[ii_i]);
				//printf("Octave %c\r\n", Display.Voices_Octave[ii_i]);
				Display.last_Voices_Note[ii_i] = Display.Voices_Note[ii_i];
				Display.last_Voices_Octave[ii_i] = Display.Voices_Octave[ii_i];
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


	if (Display.currentBand > 0){

		if (Display.Filter_ONOFF[Display.currentBand] == true){
			effects_add(EQ, 2);

			//			if (Display.poti_moved == true){
			switch(Display.currentBand){

			case 1:
				// BAND 1: Low-Shelf filter
				SetupLowShelf(&EQ_BAND1_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
				break;

			case 2:
				// BAND 2: Peaking-EQ / Notch-Filter


				SetupPeakingEQ(&EQ_BAND2_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
				SetupNotch	(&EQ_BAND2_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand]);
				break;

			case 3:
				// BAND 3: Peaking-EQ / Notch-Filter
				SetupPeakingEQ(&EQ_BAND3_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
				SetupNotch	(&EQ_BAND3_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand]);
				break;

			case 4:
				// BAND 4: Peaking-EQ / Notch-Filter
				SetupPeakingEQ(&EQ_BAND4_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
				SetupNotch	(&EQ_BAND4_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand]);
				break;

			case 5:
				// BAND 5: High-Shelf filter
				SetupHighShelf(&EQ_BAND5_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
				break;

			}




			//		SetupLowShelf(EQ_BAND1_I, Display.Filter_Cutoff[], Q, dBGain)

			//		}
		}
		else if (Display.Filter_ONOFF == false){
			effects_delete(EQ, 2);

			//		SetupNotch(BP, cutoff, Q)
		}

	}


	return 1;

}

void II_processGyro(void){

	if (Display.Gyro_ON == true){

		switch(sensorData.tilt_detecded){
		case TILT_RIGHT:

			break;

		case TILT_LEFT:

			break;
		case TILT_FRONT:

			break;
		case TILT_BACK:

			break;
		case TILT_NONE:

			break;
		default:
			break;
		}
	}

}
