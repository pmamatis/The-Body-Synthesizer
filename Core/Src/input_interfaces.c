/*
 * input_interfaces.c
 *
 *  Created on: Aug 15, 2021
 *      Author: Marc Bielen
 */

#include "input_interfaces.h"

void II_init(){
	log_mapping_F = log(LUT_FMAX);
	filter_step_counter = 10;
}

/** starts the Interface Timer Interrupt
 *
 */
void II_startInterface(TIM_HandleTypeDef* htim){
	SetTimerSettings(htim, II_SR);
	HAL_TIM_Base_Start_IT(htim);
	//printf("starting Interface Controll\r\n");
}

/** @brief Creates the Signals given through the Display-Interput
 * retval: 0 Error
 * 		   1 Success
 */
uint8_t II_Display_Voices(void) {

	for(uint8_t ii_i=0; ii_i < II_MAX_VOICES; ii_i++) {

		if (Display.Voices_ONOFF[ii_i] == true ) {
			//			//printf("is true\r\n");
			//create Signal
			if (Display.Voices_Created[ii_i] == false){
				NewSignal(&signals1, SIN, Display.Voices_Note[ii_i],Display.Voices_Octave[ii_i],ii_i);
				//				ii_voice_IDs[ii_i] = signals1.ID[signals1.count];
				Display.Voices_Created[ii_i] = true;
			}
			switch (Display.Voice_Note_Sources[ii_i]) {
			case EKG:
				if (emg_peak == 1){
					//					//printf("raise note\r\n");
					II_raiseNote(ii_i);
					emg_peak = 0;
				}
				break;
			case GYRO_FB:
				if ( toggleCounter > toggleThreshold && sensorData.tilt_detected != TILT_NONE) {

					if (sensorData.tilt_detected == TILT_BACK){
						II_decreaseNote(ii_i);
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT){
						II_raiseNote(ii_i);
						sensorData.tilt_detected = TILT_NONE;
					}
					toggleCounter = 0;
				}
				else
					toggleCounter++;
				break;
			case GYRO_LR:

				if ( toggleCounter > toggleThreshold && sensorData.tilt_detected != TILT_NONE) {
					if (sensorData.tilt_detected == TILT_RIGHT){
						II_decreaseNote(ii_i);
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_LEFT){
						II_raiseNote(ii_i);
						sensorData.tilt_detected = TILT_NONE;

					}

					toggleCounter = 0;
				}
				else
					toggleCounter++;
				break;
			default:
				break;
			}
		}
		//Delete signal with its ID
		else if (Display.Voices_ONOFF[ii_i]==false && Display.Voices_Created[ii_i] == true) {
			//get signal index
			uint8_t signal_index = IDtoIndex(ii_voice_IDs[ii_i]);
			//delete signal
			DeleteSignal(&signals1, signal_index);
			Display.Voices_Created[ii_i] = false;
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
		effects_add(DIST_H);
		HardClipping.distortion_gain = Display.Distortion_Gain;
		if (Display.Distortion_Sources > 0){
			switch (Display.Distortion_Sources ) {
			case GYRO_FB:

				if (sensorData.tilt_detected == TILT_BACK){
					if (Display.Distortion_Gain >= 1) {
						Display.Distortion_Gain --;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_FRONT){
					if (Display.Distortion_Gain < 10) {
						Display.Distortion_Gain ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				break;
			case GYRO_LR:
				if (sensorData.tilt_detected == TILT_LEFT){
					if (Display.Distortion_Gain > 1) {
						Display.Distortion_Gain --;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_RIGHT){
					if (Display.Distortion_Gain < 10) {
						Display.Distortion_Gain ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				break;
			default:
				break;
			}
		}
	}
	else if (Display.Distortion_ONOFF == false){
		effects_delete(DIST_H, 2);
	}

	//Tremolo
	if (Display.Tremolo_ONOFF == true){
		effects_add(TREM);
		if (Display.Distortion_Sources > 0){
			switch (Display.Tremolo_Sources[0]) {//RATE
			case GYRO_FB:

				if (sensorData.tilt_detected == TILT_BACK){
					if (Display.Tremolo_Rate > 0) {
						//printf("decrease Trem Rate\r\n");
						Display.Tremolo_Rate --;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_FRONT){
					if (Display.Distortion_Gain < Tremolo.tremolo_maximum_rate) {
						//printf("raise Trem Rate\r\n");
						Display.Tremolo_Rate ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				break;
			case GYRO_LR:

				if (sensorData.tilt_detected == TILT_LEFT ){
					if (Display.Tremolo_Rate > 0) {
						//printf("decrease Trem Rate\r\n");
						Display.Tremolo_Rate --;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_RIGHT){
					if (Display.Distortion_Gain < Tremolo.tremolo_maximum_rate) {
						//printf("raise Trem Rate\r\n");
						Display.Tremolo_Rate ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				break;
			default:
				break;
			}
		}
		if (Display.Tremolo_Sources[1] > 0){
			switch (Display.Tremolo_Sources[1]) {//DEPTH
			case GYRO_FB:

				if (sensorData.tilt_detected == TILT_BACK ){
					if (Display.Tremolo_Depth > 0) {
						//printf("decrease Trem Depth\r\n");
						//reduce depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
						Display.Tremolo_Depth = Display.Tremolo_Depth - Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_FRONT){
					if (Display.Tremolo_Depth < Tremolo.tremolo_maximum_depth) {
						//increase depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
						//printf("raise Trem Depth\r\n");
						Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
			case GYRO_LR:

				if (sensorData.tilt_detected == TILT_LEFT){
					if (Display.Tremolo_Depth > 0) {
						//printf("decrease Trem Depth\r\n");
						//reduce depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
						Display.Tremolo_Depth = Display.Tremolo_Depth - Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_RIGHT){
					if (Display.Tremolo_Depth < Tremolo.tremolo_maximum_depth) {
						//increase depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
						//printf("raise Trem Depth\r\n");
						Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				break;
			default:
				break;
			}
		}
		Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;
		Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
	}
	else if (Display.Distortion_ONOFF == false){
		effects_delete(TREM, 1);
	}

	//Filter
	//	if (Display.currentBand > 0){
	//	Display.Filter_ONOFF[0] = true;
	if (Display.Filter_ONOFF[Display.currentBand] == true){
		//		if (Display.Filter_ONOFF[0] == true){
		effects_add(EQ);
		if (Display.EQ_Cutoff_Sources[0] != POTI){

			switch (Display.EQ_Cutoff_Sources[0]) {
			case GYRO_FB:

				if (sensorData.tilt_detected == TILT_BACK){
					if (Display.Filter_Cutoff > 0 ) {
						////printf("decrease cuttoff Rate\r\n");
						Display.Filter_Cutoff[0]= Display.Filter_Cutoff[0] - LUT_FMAX/ II_FILTER_CUTTOFF_STEP_SIZE;
						Filters_Reinit_Gyro(Display.Filter_Cutoff[0]);
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_FRONT){
					if (Display.Filter_Cutoff[0] <  II_FILTER_CUTTOFF_STEP_SIZE) {
						////printf("increase cuttoff Rate\r\n");
						Display.Filter_Cutoff[0]= Display.Filter_Cutoff[0] + LUT_FMAX/ II_FILTER_CUTTOFF_STEP_SIZE;
						Filters_Reinit_Gyro(Display.Filter_Cutoff[0]);
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				break;
			case GYRO_LR:

				if (sensorData.tilt_detected == TILT_LEFT ){
					if (Display.Filter_Cutoff[0] > (float)(LUT_FMAX / II_FILTER_CUTTOFF_STEP_SIZE) ) {
						printf("decrease cuttoff Rate\r\n");
						filter_step_counter--;
						Display.Filter_Cutoff[0]=  exp(((float)filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
						Filters_Reinit_Gyro(Display.Filter_Cutoff[0]);
					}
					sensorData.tilt_detected = TILT_NONE;
				}

				else if (sensorData.tilt_detected == TILT_RIGHT){
					if (Display.Filter_Cutoff[0] <  LUT_FMAX-(LUT_FMAX/ II_FILTER_CUTTOFF_STEP_SIZE)) {
						printf("increase cuttoff Rate\r\n");
						filter_step_counter++;
						Display.Filter_Cutoff[0]=  exp(((float)filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
						//								Display.Filter_Cutoff[0]= Display.Filter_Cutoff[0] + LUT_FMAX/ II_FILTER_CUTTOFF_STEP_SIZE;
						Filters_Reinit_Gyro(Display.Filter_Cutoff[0]);
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				break;
			default:
				break;
			}
		}
	}
	else if (Display.Filter_ONOFF == false){
		effects_delete(EQ, 0);
	}

	// WahWah
	if(Display.WahWah_ONOFF == true) {
		effects_add(WAHWAH);
	}
	else {
		effects_delete(WAHWAH, 4);
	}

	//	}

	return 1;
}

//			//			if (Display.poti_moved == true){
//			switch(Display.currentBand){
//
//			case 1:
//				// BAND 1: Low-Shelf filter
//				SetupLowShelf(&EQ_BAND1_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
//				break;
//
//			case 2:
//				// BAND 2: Peaking-EQ / Notch-Filter
//
//
//				SetupPeakingEQ(&EQ_BAND2_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
//				SetupNotch	(&EQ_BAND2_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand]);
//				break;
//
//			case 3:
//				// BAND 3: Peaking-EQ / Notch-Filter
//				SetupPeakingEQ(&EQ_BAND3_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
//				SetupNotch	(&EQ_BAND3_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand]);
//				break;
//
//			case 4:
//				// BAND 4: Peaking-EQ / Notch-Filter
//				SetupPeakingEQ(&EQ_BAND4_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
//				SetupNotch	(&EQ_BAND4_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand]);
//				break;
//
//			case 5:
//				// BAND 5: High-Shelf filter
//				SetupHighShelf(&EQ_BAND5_I, Display.Filter_Cutoff[Display.currentBand], Display.Filter_Q[Display.currentBand], Display.Filter_Gain[Display.currentBand]);
//				break;
//
//			}

//		SetupLowShelf(EQ_BAND1_I, Display.Filter_Cutoff[], Q, dBGain)
//		}

//		SetupNotch(BP, cutoff, Q)

void II_processGyro(void){

	if (Display.Gyro_ON == true){

		switch(sensorData.tilt_detected){
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

//void II_processEMG(){
////	if (emg_peak_== 1){
//
//	}
//}
//

/** raises the key of an existing signal, by deleting the signal and creating a new signal
 * @param ID: signal ID

 */
void II_raiseNote(uint8_t ID){
	uint8_t index= IDtoIndex(ID);
	char oldKey = Display.Voices_Note[ID];

	uint8_t key_counter = 0;
	//gets index of old key..
	while (keys[key_counter] != oldKey){
		key_counter++;
	}
	//gets key of the next note
	char newKey = keys[key_counter+1];

	if (oldKey == 'H'){
		//raise octave if changing from H to C
		if (Display.Voices_Octave[ID] < LUT_OCTAVES-1)
			Display.Voices_Octave[ID]++;

		else if (Display.Voices_Octave[ID] == LUT_OCTAVES-1) {
			//reaches end of playable notes
			newKey = 'H';
		}
	}
	Display.Voices_Note[ID] = newKey;
	if(index >= 0){
		//printf("old: %c new: %c octave: %i \r\n",oldKey,(char)newKey,Display.Voices_Octave[ID]);
		DeleteSignal(&signals1, index);
		NewSignal(&signals1, SIN, newKey, Display.Voices_Octave[ID],ID);
	}
	//	else
	//printf("Signal ID not found\r\n");
}

/** raises the key of an existing signal, by deleting the signal and creating a new signal
 * @param ID: signal ID

 */
void II_decreaseNote(uint8_t ID){
	uint8_t index= IDtoIndex(ID);
	char oldKey = Display.Voices_Note[ID];
	char newKey;
	uint8_t key_counter = 0;
	//gets index of old key..
	while (keys[key_counter] != oldKey){
		key_counter++;
	}
	key_counter+= 12;

	//gets key of the note before
	newKey = keys[key_counter-1];

	if (oldKey == 'C'){
		//decrease octave if changing from C to H
		if (Display.Voices_Octave[ID] > 0){
			Display.Voices_Octave[ID]--;
		}
		else if (Display.Voices_Octave[ID] == 0) {
			//reaches end of playable notes
			newKey = 'C';
		}
	}
	Display.Voices_Note[ID] = newKey;
	if(index >= 0){
		//printf("old: %c new: %c octave: %i \r\n",oldKey,(char)newKey,Display.Voices_Octave[ID]);
		DeleteSignal(&signals1, index);
		NewSignal(&signals1, SIN, newKey, Display.Voices_Octave[ID],ID);
	}
	//	else
	//printf("Signal ID not found\r\n");

}

/**Play Voice triggerd by EMG
 *
 */
void II_pVwECG(void){
	if (emg_peak == 1){

		NewSignal(&signals1, SIN, Display.Voices_Note[0], Display.Voices_Octave[0], 0);
		emg_triggerd_flag = true;
	}
	else {
		if(envelope.adsr_done == true) {

			DeleteSignal(&signals1, IDtoIndex(0));
			emg_triggerd_flag = false;
			envelope.adsr_done = false;
		}
	}
}
