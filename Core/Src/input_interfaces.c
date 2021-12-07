/*
 * input_interfaces.c
 *
 *  Created on: Aug 15, 2021
 *      Author: Paul Mamatis
 */

#include "input_interfaces.h"


/** @brief init function*/
void II_init(void) {

	log_mapping_F = log(LUT_FMAX);

	for (int i = 0;i<5 ;i++)
		filter_step_counter[i] = II_MINIMUM_STEPCOUNTER;

	drum_filter_step_counter = II_MINIMUM_STEPCOUNTER;

	// Play Single Sample
	play_single_sample_flag = false;
	counter_single_sample = 0;

	for(uint8_t i=0; i<(sizeof(gyro_delay_counter)/sizeof(gyro_delay_counter[0])); i++)
		gyro_delay_counter[i] = 0;

	gyrochanged = false;
}

/** @brief starts the interface timer Interrupt*/
void II_startInterface(TIM_HandleTypeDef* htim) {

	SetTimerSettings(htim, II_SR);
	HAL_TIM_Base_Start_IT(htim);
}

/** @brief Creates the Signals given through the Display-Interput
 * retval: 0 Error
 * 		   1 Success
 */
uint32_t gyro_toggleCounter = 0;
uint32_t gyro_toggleThreshold = 10;

uint8_t II_Display_Voices(void) {

	for(uint8_t ii_i=0; ii_i < II_MAX_VOICES; ii_i++) {

		if(Display.Voices_ONOFF[ii_i] == true ) {

			// signal has to be created once, because otherwise the count for-loop in signal synthesis function can not be entered (count > 0)
			if(Display.Voices_Created[ii_i] == false) {
				NewSignal(&signals1, Display.Voices_Kind[ii_i], Display.Voices_Note[ii_i], Display.Voices_Octave[ii_i], ii_i);
				Display.Voices_Created[ii_i] = true;
			}

			switch (Display.Voice_Note_Sources[ii_i]) {

			case GYRO_FB:
				if ( gyro_toggleCounter > gyro_toggleThreshold && sensorData.tilt_detected != TILT_NONE) {

					if (sensorData.tilt_detected == TILT_BACK || sensorData.tilt_detected == TILT_BACK_S){

						// Noteindex decreased the same way for all Scale Modes (Freestyle, Major and Minor)
						if(Display.Voices_Noteindex[ii_i] > 0)
							Display.Voices_Noteindex[ii_i]--;

						// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
						if(Display.ScaleMode == FREESTYLE)
							Display.Voices_Note[ii_i] = (uint8_t)(keys[(uint8_t)Display.Voices_Noteindex[ii_i]]);

						else if(Display.ScaleMode == MAJOR)
							Display.Voices_Note[ii_i] = (uint8_t)(keys[major_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);

						else if(Display.ScaleMode == MINOR)
							Display.Voices_Note[ii_i] = (uint8_t)(keys[minor_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);

						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT || sensorData.tilt_detected == TILT_FRONT_S){

						if(Display.ScaleMode == FREESTYLE){
							if(Display.Voices_Noteindex[ii_i] < 12)	// 12 keys per octave + deep C
								Display.Voices_Noteindex[ii_i]++;
							// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
							Display.Voices_Note[ii_i] = (uint8_t)(keys[(uint8_t)Display.Voices_Noteindex[ii_i]]);
						}
						else if(Display.ScaleMode == MAJOR){
							if(Display.Voices_Noteindex[ii_i] < 7)	// 7 keys per octave + deep root
								Display.Voices_Noteindex[ii_i]++;
							// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
							Display.Voices_Note[ii_i] = (uint8_t)(keys[major_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);
						}
						else if(Display.ScaleMode == MINOR){
							if(Display.Voices_Noteindex[ii_i] < 7)	// 7 keys per octave + deep root
								Display.Voices_Noteindex[ii_i]++;
							// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
							Display.Voices_Note[ii_i] = (uint8_t)(keys[minor_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);
						}


						sensorData.tilt_detected = TILT_NONE;
					}
					gyro_toggleCounter = 0;
				}
				else
					gyro_toggleCounter++;
				break;
			case GYRO_LR:

				if ( gyro_toggleCounter > gyro_toggleThreshold && sensorData.tilt_detected != TILT_NONE) {
					if (sensorData.tilt_detected == TILT_RIGHT || sensorData.tilt_detected == TILT_RIGHT_S){

						if(Display.ScaleMode == FREESTYLE){
							if(Display.Voices_Noteindex[ii_i] < 12)	// 12 keys per octave + deep C
								Display.Voices_Noteindex[ii_i]++;
							// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
							Display.Voices_Note[ii_i] = (uint8_t)(keys[(uint8_t)Display.Voices_Noteindex[ii_i]]);
						}
						else if(Display.ScaleMode == MAJOR){
							if(Display.Voices_Noteindex[ii_i] < 7)	// 7 keys per octave + deep root
								Display.Voices_Noteindex[ii_i]++;
							// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
							Display.Voices_Note[ii_i] = (uint8_t)(keys[major_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);
						}
						else if(Display.ScaleMode == MINOR){
							if(Display.Voices_Noteindex[ii_i] < 7)	// 7 keys per octave + deep root
								Display.Voices_Noteindex[ii_i]++;
							// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
							Display.Voices_Note[ii_i] = (uint8_t)(keys[minor_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);
						}


						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_LEFT || sensorData.tilt_detected == TILT_LEFT_S){

						// Noteindex decreased the same way for all Scale Modes (Freestyle, Major and Minor)
						if(Display.Voices_Noteindex[ii_i] > 0)
							Display.Voices_Noteindex[ii_i]--;

						// Decide which mode is used (Freestyle, Major, Minor) and set respective Voices_Note with major/minor mapping indices of root note + desired note
						if(Display.ScaleMode == FREESTYLE)
							Display.Voices_Note[ii_i] = (uint8_t)(keys[(uint8_t)Display.Voices_Noteindex[ii_i]]);

						else if(Display.ScaleMode == MAJOR)
							Display.Voices_Note[ii_i] = (uint8_t)(keys[major_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);

						else if(Display.ScaleMode == MINOR)
							Display.Voices_Note[ii_i] = (uint8_t)(keys[minor_scale[(uint8_t)Display.Voices_Noteindex[ii_i]] + Display.KeyNoteIndex]);


						sensorData.tilt_detected = TILT_NONE;
					}

					gyro_toggleCounter = 0;
				}
				else
					gyro_toggleCounter++;
				break;
			default:
				break;
			}

			switch (Display.Voice_Octave_Sources[ii_i]) {
			case GYRO_FB:
				if ( gyro_toggleCounter > gyro_toggleThreshold && sensorData.tilt_detected != TILT_NONE) {

					if (sensorData.tilt_detected == TILT_BACK || sensorData.tilt_detected == TILT_BACK_S){

						if(Display.Voices_Octave[ii_i] > 0)
							Display.Voices_Octave[ii_i]--;

						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT || sensorData.tilt_detected == TILT_FRONT_S){

						if(Display.Voices_Octave[ii_i] < 5)	// maximum 6 octaves
							Display.Voices_Octave[ii_i]++;

						sensorData.tilt_detected = TILT_NONE;
					}
					gyro_toggleCounter = 0;
				}
				else
					gyro_toggleCounter++;
				break;
			case GYRO_LR:

				if ( gyro_toggleCounter > gyro_toggleThreshold && sensorData.tilt_detected != TILT_NONE) {
					if (sensorData.tilt_detected == TILT_RIGHT || sensorData.tilt_detected == TILT_RIGHT_S){

						if(Display.Voices_Octave[ii_i] < 5)	// maximum 6 octaves
							Display.Voices_Octave[ii_i]++;

						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_LEFT || sensorData.tilt_detected == TILT_LEFT_S){

						if(Display.Voices_Octave[ii_i] > 0)
							Display.Voices_Octave[ii_i]--;

						sensorData.tilt_detected = TILT_NONE;

					}

					gyro_toggleCounter = 0;
				}
				else
					gyro_toggleCounter++;
				break;
			default:
				break;
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
	if(Display.Distortion_ONOFF == true) {

		effects_add(DIST);

		if(Display.Distortion_Type == 0)
			SoftClipping.distortion_gain = Display.Distortion_Gain;
		else if(Display.Distortion_Type == 1)
			HardClipping.distortion_gain = Display.Distortion_Gain;

		if(Display.Distortion_Sources > POTI) {	// POTI = 0

			switch (Display.Distortion_Sources ) {
			case GYRO_FB:

				if (sensorData.tilt_detected == TILT_BACK){
					if (Display.Distortion_Gain >= 1) {
						Display.Distortion_Gain --;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_FRONT){
					if (Display.Distortion_Gain < HardClipping.distortion_maximum_gain) {
						Display.Distortion_Gain ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_FRONT_S){
					if (Display.Distortion_Gain < HardClipping.distortion_maximum_gain) {
						Display.Distortion_Gain ++;
						Display.Distortion_Gain ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if(sensorData.tilt_detected == TILT_BACK_S){
					if (Display.Distortion_Gain >= 1) {
						Display.Distortion_Gain --;
						Display.Distortion_Gain --;
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
					if (Display.Distortion_Gain < HardClipping.distortion_maximum_gain) {
						Display.Distortion_Gain ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_RIGHT_S){
					if (Display.Distortion_Gain < HardClipping.distortion_maximum_gain) {
						Display.Distortion_Gain ++;
						Display.Distortion_Gain ++;
					}
					sensorData.tilt_detected = TILT_NONE;
				}
				else if (sensorData.tilt_detected == TILT_LEFT_S){
					if (Display.Distortion_Gain > 1) {
						Display.Distortion_Gain --;
						Display.Distortion_Gain --;
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
		effects_delete(DIST);
	}

	//Tremolo
	if(Display.Tremolo_ONOFF == true) {

		if(Display.last_Tremolo_ONOFF == false) {
			effects_add(TREM);
			Tremolo.lfo->lfo_quarter = 1;
			Tremolo.lfo->lfo_index = 0;
			Display.last_Tremolo_ONOFF = true;
		}

		if (Display.Tremolo_Sources[0] > POTI){	// POTI = 0

			if(gyro_delay_counter[0] == 0 ) {

				switch (Display.Tremolo_Sources[0]) {	// TREMOLO RATE
				case GYRO_FB:

					// THE TREMOLO RATE SHOULD NOT BE ADJUSTED WITH --/++ THE RATE BUT THE INDEX, LIKE:
					// Display.Tremolo_Rate_Index = LFO_FREQUENCYS[Display.Tremolo_Rate_Index_Index];

					if (sensorData.tilt_detected == TILT_BACK){
						if (Display.Tremolo_Rate_Index > 0) {
							Display.Tremolo_Rate_Index --;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_BACK_S){
						if (Display.Tremolo_Rate_Index > 0) {
							Display.Tremolo_Rate_Index--;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT){
						if (Display.Tremolo_Rate_Index < 7) {	//((sizeof(LFO_FREQUENCYS[8])/sizeof(float))-1)
							Display.Tremolo_Rate_Index ++;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT_S){
						if (Display.Tremolo_Rate_Index < 7) {
							Display.Tremolo_Rate_Index ++;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					break;

				case GYRO_LR:
					if (sensorData.tilt_detected == TILT_LEFT ){
						if (Display.Tremolo_Rate_Index > 0) {
							Display.Tremolo_Rate_Index --;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_LEFT_S ){
						if (Display.Tremolo_Rate_Index > 0) {
							Display.Tremolo_Rate_Index --;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_RIGHT){
						if (Display.Tremolo_Rate_Index < 7) {
							Display.Tremolo_Rate_Index ++;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_RIGHT_S){
						if (Display.Tremolo_Rate_Index < 7) {
							Display.Tremolo_Rate_Index ++;
							printf("rateidx = %u\r\n", Display.Tremolo_Rate_Index);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					break;
				default:
					break;
				}
			}

			gyro_delay_counter[0]++;
			if (gyro_delay_counter[0] >= II_TREM_RATE_DELAY) // >= necessary, because II_TREM_RATE_DELAY is a floating number
				gyro_delay_counter[0] = 0;

		}
		if (Display.Tremolo_Sources[1] > POTI){	// POTI = 0

			if(gyro_delay_counter[0] == 0 ) {

				switch (Display.Tremolo_Sources[1]) {	// TREMOLO DEPTH

				case GYRO_FB:
					if (sensorData.tilt_detected == TILT_BACK ){
						if (Display.Tremolo_Depth > 0) {
							//reduce depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
							Display.Tremolo_Depth = Display.Tremolo_Depth - Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_BACK_S ){
						if (Display.Tremolo_Depth > 0) {
							//reduce depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
							Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT){
						if (Display.Tremolo_Depth < Tremolo.tremolo_maximum_depth) {
							//increase depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
							Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT_S){
						if (Display.Tremolo_Depth < Tremolo.tremolo_maximum_depth) {
							//increase depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
							Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
				case GYRO_LR:
					if (sensorData.tilt_detected == TILT_LEFT){
						if (Display.Tremolo_Depth > 0) {
							Display.Tremolo_Depth = Display.Tremolo_Depth - Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					if (sensorData.tilt_detected == TILT_LEFT_S){
						if (Display.Tremolo_Depth > 0) {
							//reduce depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
							Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_RIGHT){
						if (Display.Tremolo_Depth < Tremolo.tremolo_maximum_depth) {
							//increase depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
							Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_RIGHT_S){
						if (Display.Tremolo_Depth < Tremolo.tremolo_maximum_depth) {
							//increase depth by 1/II_TREM_DEPTH_STEP_SIZE of Max value => II_TREM_DEPTH_STEP_SIZE steps
							Display.Tremolo_Depth = Display.Tremolo_Depth + Tremolo.tremolo_maximum_depth/II_TREM_DEPTH_STEP_SIZE;
							printf("depth = %f\r\n", Display.Tremolo_Depth);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					break;
				default:
					break;
				}
			}

			gyro_delay_counter[1]++;
			if (gyro_delay_counter[1] >= II_TREM_DEPTH_DELAY) // >= necessary, because II_TREM_DEPTH_DELAY is a floating number
				gyro_delay_counter[1] = 0;
		}

	}

	//Filters
	if(Display.currentBand > 0) {	// guard to make sure that array boundaries of next if clause are not exceeded [-1]

		// create Equalizer effect when at least one filter band is on
		if(Display.Filter_ONOFF[0] || Display.Filter_ONOFF[1] || Display.Filter_ONOFF[2] || Display.Filter_ONOFF[3] || Display.Filter_ONOFF[4]) {

			effects_add(EQ);

			if(Display.EQ_Cutoff_Sources[Display.currentBand-1] > POTI) {	// POTI = 0

				switch (Display.EQ_Cutoff_Sources[Display.currentBand-1]) {
				case GYRO_FB:

					if (sensorData.tilt_detected == TILT_BACK){
						if (Display.Filter_Cutoff[Display.currentBand-1] > LUT_FMIN ) {
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							Display.Filter_Cutoff[Display.currentBand-1] =  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_BACK_S){
						if (Display.Filter_Cutoff[Display.currentBand-1] > LUT_FMIN ) {
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							Display.Filter_Cutoff[Display.currentBand-1]=  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT){
						if (Display.Filter_Cutoff[Display.currentBand-1] <  LUT_FMAX) {
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							Display.Filter_Cutoff[Display.currentBand-1]=  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_FRONT_S){
						if (Display.Filter_Cutoff[Display.currentBand-1] <  LUT_FMAX) {
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							Display.Filter_Cutoff[Display.currentBand-1]=  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					break;
				case GYRO_LR:

					if (sensorData.tilt_detected == TILT_LEFT ){
						if (Display.Filter_Cutoff[Display.currentBand-1] > (float)(LUT_FMAX / II_FILTER_CUTTOFF_STEP_SIZE) ) {
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							Display.Filter_Cutoff[Display.currentBand-1]=  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_LEFT_S ){
						if (Display.Filter_Cutoff[Display.currentBand-1] > (float)(LUT_FMAX / II_FILTER_CUTTOFF_STEP_SIZE) ) {
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							filter_step_counter[Display.currentBand-1]--;
							Display.Filter_Cutoff[Display.currentBand-1]=  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}

					else if (sensorData.tilt_detected == TILT_RIGHT){
						if (Display.Filter_Cutoff[Display.currentBand-1] <  LUT_FMAX-(LUT_FMAX/ II_FILTER_CUTTOFF_STEP_SIZE)) {
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							Display.Filter_Cutoff[Display.currentBand-1]=  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					else if (sensorData.tilt_detected == TILT_RIGHT_S){
						if (Display.Filter_Cutoff[Display.currentBand-1] <  LUT_FMAX-(LUT_FMAX/ II_FILTER_CUTTOFF_STEP_SIZE)) {
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							filter_step_counter[Display.currentBand-1]++;
							Display.Filter_Cutoff[Display.currentBand-1]=  exp(((float)filter_step_counter[Display.currentBand-1]/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
							Filters_Reinit_Gyro(Display.Filter_Cutoff[Display.currentBand-1]);
						}
						sensorData.tilt_detected = TILT_NONE;
					}
					break;
				default:
					break;
				}
			}
		}
		// delete Equalizer effect when every filter band is off
		else if( (Display.Filter_ONOFF[0] && Display.Filter_ONOFF[1] && Display.Filter_ONOFF[2] && Display.Filter_ONOFF[3] && Display.Filter_ONOFF[4]) == false ) {

			effects_delete(EQ);
		}
	}


	//Drum Filter
	if(Display.Drumfilter_ONOFF == true) {
		switch (Display.Drumfilter_Cutoff_Source) {
		case GYRO_FB:

			if (sensorData.tilt_detected == TILT_BACK){
				if (Display.Drumfilter_Cutoff > II_FILTER_CUTOFF_MIN) {
					drum_filter_step_counter--;
					if(drum_filter_step_counter < II_MINIMUM_STEPCOUNTER)
						drum_filter_step_counter = II_MINIMUM_STEPCOUNTER;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}
			else if (sensorData.tilt_detected == TILT_BACK_S){
				if (Display.Drumfilter_Cutoff > II_FILTER_CUTOFF_MIN) {
					drum_filter_step_counter--;
					drum_filter_step_counter--;
					if(drum_filter_step_counter < II_MINIMUM_STEPCOUNTER)
						drum_filter_step_counter = II_MINIMUM_STEPCOUNTER;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}
			else if (sensorData.tilt_detected == TILT_FRONT){
				if (Display.Drumfilter_Cutoff <  LUT_FMAX) {
					drum_filter_step_counter++;
					if(drum_filter_step_counter > II_FILTER_CUTTOFF_STEP_SIZE)
						drum_filter_step_counter = II_FILTER_CUTTOFF_STEP_SIZE;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}
			else if (sensorData.tilt_detected == TILT_FRONT_S){
				if (Display.Drumfilter_Cutoff <  LUT_FMAX) {
					drum_filter_step_counter++;
					drum_filter_step_counter++;
					if(drum_filter_step_counter > II_FILTER_CUTTOFF_STEP_SIZE)
						drum_filter_step_counter = II_FILTER_CUTTOFF_STEP_SIZE;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}
			break;
		case GYRO_LR:

			if (sensorData.tilt_detected == TILT_LEFT){
				if (Display.Drumfilter_Cutoff > II_FILTER_CUTOFF_MIN) {
					drum_filter_step_counter--;
					if(drum_filter_step_counter < II_MINIMUM_STEPCOUNTER)
						drum_filter_step_counter = II_MINIMUM_STEPCOUNTER;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}
			else if (sensorData.tilt_detected == TILT_LEFT_S){
				if (Display.Drumfilter_Cutoff > II_FILTER_CUTOFF_MIN) {
					drum_filter_step_counter--;
					drum_filter_step_counter--;
					if(drum_filter_step_counter < II_MINIMUM_STEPCOUNTER)
						drum_filter_step_counter = II_MINIMUM_STEPCOUNTER;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}
			else if (sensorData.tilt_detected == TILT_RIGHT){
				if (Display.Drumfilter_Cutoff <  LUT_FMAX) {
					drum_filter_step_counter++;
					if(drum_filter_step_counter > II_FILTER_CUTTOFF_STEP_SIZE)
						drum_filter_step_counter = II_FILTER_CUTTOFF_STEP_SIZE;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}
			else if (sensorData.tilt_detected == TILT_RIGHT_S){
				if (Display.Drumfilter_Cutoff <  LUT_FMAX) {
					drum_filter_step_counter++;
					drum_filter_step_counter++;
					if(drum_filter_step_counter > II_FILTER_CUTTOFF_STEP_SIZE)
						drum_filter_step_counter = II_FILTER_CUTTOFF_STEP_SIZE;
					Display.Drumfilter_Cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
					DrumFilters_Reinit_Gyro(Display.Drumfilter_Cutoff, Display.Drumfilter_Q, Display.Drumfilter_Gain);

					gyrochanged = true;
				}
				sensorData.tilt_detected = TILT_NONE;
			}

		default:
			break;
		}
	}

	// WahWah
	if(Display.WahWah_ONOFF == true) {
		effects_add(WAHWAH);
	}
	else {
		effects_delete(WAHWAH);
	}

	return 1;
}

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
	if(index >= 0){	// only done if ID is existing
		DeleteSignal(&signals1, index);
		NewSignal(&signals1, SIN, newKey, Display.Voices_Octave[ID],ID);
	}
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
		DeleteSignal(&signals1, index);
		NewSignal(&signals1, SIN, newKey, Display.Voices_Octave[ID],ID);
	}

}

/**Play Voice triggerd by EMG
 *
 */
void II_pVwEMG(void) {	// TODO: braucht eigenes adsr struct für emg
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

/** Play Sample with EMG */
void II_pSwEMG(void) {

	if(emg_peak == 1) {

		play_single_sample_flag = true;
		emg_peak = 0;
	}
}
