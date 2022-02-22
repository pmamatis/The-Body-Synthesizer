/**
 * @file signal_synthesis.c
 * @author Marc Bielen & Max Lehmer & Paul Mamatis
 * @brief Signal Synthesis and related functions
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */



/**
 * @file signal_synthesis.c
 * @author paul mamatis
 * @version 3.2
 */

#include "signal_synthesis.h"

/** @brief maximal binary value which is used by the DAC, can be adjusted by AMPLITUDE in signal_sythesis.h and will be set in the Init function*/
double maxValueDAC;

/**@brief Init funtion for the signal_synthesis, must be used in order to use any other funtion of this .c
 * @param htim: timer-handler which controls the DAC, timer have to be connected with DAC
 * @param hdac: is the DAC handler
 *@return gives HAL-Status of started timer back
 */
HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac){

	// Sets the maximal digital value which the DAC converts into analog voltage
	maxValueDAC = (double)DAC_MAXVALUE_TO_AMPLITUDE_RATIO * (double)AMPLITUDE;
	outputBuffer_position = HALF_BLOCK;
	signals1.count = 0;
	signals1.max = 1;

	// Set Volumes for Master_Volume, Voices, Drumcomputer, Sequencer and Keyboard
	Master_Volume = 1.0;
	for(int i=0; i<4; i++) {
		volume[i] = 1;
	}

	for (int i=0; i>BLOCKSIZE/2; i++)
		*((uint32_t *)(&calculate_vector1[i] )) = (uint32_t)((i/(BLOCKSIZE/2)) * maxValueDAC/2); // TODO muss noch angepasst werden

	// Inits and starts timer connected with DAC
	SetTimerSettings(&htim, LUT_SR);

	return HAL_TIM_Base_Start(&htim);
}

/**
 * @brief resets the voice parameter which can be changed in the GUI 
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Voices_Reset(void) {

	// Clear screen content of voices overview
	Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);
	Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH , UNCOLORED);
	Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH , UNCOLORED);
	Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH , UNCOLORED);

	// Voices Reset
	for(int i=0; i<3; i++) {
		Display.Voices_ONOFF[i] = false;
		Display.Voices_Noteindex[i] = 0;
		Display.Voices_Note[i]   = (uint8_t)(keys[(uint8_t)Display.Voices_Noteindex[i] + Display.KeyNoteIndex]);
		Display.Voices_Octave[i] = 0;
		Display.Voice_Note_Sources[i] = POTI;
		Display.Voice_Octave_Sources[i] = POTI;
		strcpy(Display.value_str_voices_overview[i], "OFF");
		sprintf(Display.value_str_voices_settings[i][0], "%c", Display.Voices_Note[i]);
		sprintf(Display.value_str_voices_settings[i][1], "%d", Display.Voices_Octave[i]);
		strcpy(Display.value_str_voices_settings[i][2], Display.source_names[0]);
		strcpy(Display.value_str_voices_settings[i][3], Display.source_names[0]);
	}
	// Noise Reset
	Display.Noise_ONOFF = false;
	strcpy(Display.value_str_voices_overview[3], "OFF");
	Display.Noise_Volume = 1.0;

	return HAL_OK;
}


/**@brief Init funtion for the Timer which triggers the DAC, this function sets the timerperiode and presacaler
 * @param htim: timer-handler which controls the DAC, timer have to be connected with DAC
 * @param SR: Sample Rate
 */
void SetTimerSettings(TIM_HandleTypeDef* htim, uint32_t SR) {

	// Clock Sources of all 14 timers: 1 = APB1, 2 = APB2
	uint8_t APBTimerCases[] = {2,1,1,1,1,1,1,2,2,2,2,1,1,1};
	uint8_t Timer = 0;
	uint32_t Clock = 0;

	if(htim->Instance == TIM1) Timer = 1;
	else if(htim->Instance == TIM2) Timer = 2;
	else if(htim->Instance == TIM3) Timer = 3;
	else if(htim->Instance == TIM4) Timer = 4;
	else if(htim->Instance == TIM5) Timer = 5;
	else if(htim->Instance == TIM6) Timer = 6;
	else if(htim->Instance == TIM7) Timer = 7;
	else if(htim->Instance == TIM8) Timer = 8;
	else if(htim->Instance == TIM9) Timer = 9;
	else if(htim->Instance == TIM10) Timer = 10;
	else if(htim->Instance == TIM11) Timer = 11;
	else if(htim->Instance == TIM12) Timer = 12;
	else if(htim->Instance == TIM13) Timer = 13;
	else if(htim->Instance == TIM14) Timer = 14;

	if(APBTimerCases[Timer-1] == 1)
		Clock = 2 * HAL_RCC_GetPCLK1Freq();	// APB1 Timer Clock

	if(APBTimerCases[Timer-1] == 2)
		Clock = 2 * HAL_RCC_GetPCLK2Freq();	// APB2 Timer Clock

	uint32_t values_length = 65536;
	uint16_t prescaler;
	uint32_t timerperiod = 0;

	for(int i=1; i<values_length; i++) {

		prescaler = fmod(Clock, i);	// modulo-operation
		if(prescaler == 0) {// find possible prescaler Values
			prescaler = i;
			timerperiod = Clock/( prescaler * SR );//set timerperiod
			if (timerperiod < values_length){
				break;
			}
		}
	}//end for-loop

	__HAL_TIM_SET_AUTORELOAD(htim, timerperiod-1);	// update timer settings
	__HAL_TIM_SET_PRESCALER(htim, prescaler-1);
}

/** @brief Constructor for a signal, adds a signal into the signals1 struct
 *  @param kind: kind of the signal, use signal_kind_enum
 *  @param key:  is string which is a note key from C to b
 *  @param octave: defines in which octave the key is settled.
 *  @attention the combination of key and octave defines the frequency
 */
void LFO_SingleValueProcess(struct effects_lfo_t* lfo, uint8_t lfo_effect) {

	lfo->lfo_data = 0;

	// CASE 1: 0.125 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[0]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[0]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[0]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[0] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[0]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[0]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
	// CASE 2: 0.25 Hz
	else if(lfo->lfo_frequency == LFO_FREQUENCYS[1]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[1]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[1]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[1] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[1]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[1]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
	// CASE 3: 0.5 Hz
	else if(lfo->lfo_frequency == LFO_FREQUENCYS[2]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[2]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[2]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[2] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[2]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[2]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
	// CASE 4: 1 Hz
	else if(lfo->lfo_frequency == LFO_FREQUENCYS[3]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[3]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[3]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[3] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[3]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[3]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
	// CASE 5: 2 Hz
	else if(lfo->lfo_frequency == LFO_FREQUENCYS[4]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[4]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[4]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[4] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[4]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[4]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
	// CASE 6: 4 Hz
	else if(lfo->lfo_frequency == LFO_FREQUENCYS[5]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[5]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[5]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[5] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[5]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[5]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
	// CASE 7: 8 Hz
	else if(lfo->lfo_frequency == LFO_FREQUENCYS[6]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[6]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[6]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[6] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[6]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[6]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
	// CASE 8: 16 Hz
	else if(lfo->lfo_frequency == LFO_FREQUENCYS[7]) {

		switch(lfo->lfo_quarter) {
		case 0:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = LFO[LFO_STARTINDEX[7]  + lfo->lfo_index];
			break;
		case 1:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = 1;

				if(lfo_effect == TREMOLO_LFO) {
					Tremolo.lfo->lfo_depth = Display.Tremolo_Depth;	// tremolo depth has to be updated when the maximum amplitude is reached
					// tremolo effect has to be deleted, when the amplitude is 1 to avoid an abrupt change in the amplitude
					if(Display.Tremolo_ONOFF == false) {
						effects_delete(TREM);
						Display.last_Tremolo_ONOFF = false;
					}
				}
			}
			else
				lfo->lfo_data = LFO[LFO_ENDINDEX[7]    - lfo->lfo_index + 1];
			break;
		case 2:
			if(lfo->lfo_index == 0)
				lfo->lfo_data = 0;
			else
				lfo->lfo_data = -LFO[LFO_STARTINDEX[7] + lfo->lfo_index];
			break;
		case 3:
			if(lfo->lfo_index == 0) {
				lfo->lfo_data = -1;
			}
			else
				lfo->lfo_data = -LFO[LFO_ENDINDEX[7]   - lfo->lfo_index + 1];
			break;
		default:
			break;
		}
		lfo->lfo_index++;

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[7]) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter == 4) {
				lfo->lfo_quarter = 0;

				if(lfo_effect == TREMOLO_LFO) {
					// to make sure that the tremolo restarts only when the LFO period is done
					if(Display.Tremolo_Rate_Index != Display.last_Tremolo_Rate_Index) {

						Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
						Display.last_Tremolo_Rate_Index = Display.Tremolo_Rate_Index;
						lfo->lfo_done_flag = true;
						Tremolo.lfo->lfo_frequency = Display.Tremolo_Rate;
					}
				}
				else if(lfo_effect == WAHWAH_LFO) {
					// to make sure that the auto-wahwah restarts only when the LFO period is done
					if(Display.WahWah_LFOfreq_Index != Display.last_WahWah_LFOfreq_Index) {

						Display.WahWah_LFOfreq = LFO_FREQUENCYS[Display.WahWah_LFOfreq_Index];
						Display.last_WahWah_LFOfreq_Index = Display.WahWah_LFOfreq_Index;
						lfo->lfo_done_flag = true;
						WahWah.lfo->lfo_frequency = Display.WahWah_LFOfreq;
					}
				}
			}
		}
	}
}

/**
 * @brief generates a signal which is processed in the Signal_Synthesis() 
 * 
 * @note for more information see siganls struct description
 * 
 * @param signals 
 * @param kind 
 * @param key 
 * @param octave 
 * @param ID 
 */
void NewSignal(struct signal_t* signals, uint8_t kind, uint8_t key, uint8_t octave, uint8_t ID){

	if (signals -> count <= MAX_SIGNAL_KOMBINATION){
		signals -> count += 1;
		uint8_t index = (signals-> count)-1;
		signals -> ID[index]= ID;
		signals -> kind[index] = kind;

		switch(kind) {

		case SIN:
			signals -> freq[index] = Get_Note_Frequency(Get_Keyindex(key), octave);
			signals -> freqIndex[index] = Get_Note_Index(key,octave);
			signals -> current_LUT_Index[index] = LUT_STARTINDEX[signals -> freqIndex[index]];
			break;

		case RECT:
			signals -> freq[index] = Get_Note_Frequency(Get_Keyindex(key), octave);
			signals -> freqIndex[index] = Get_Note_Index(key,octave);
			signals -> current_LUT_Index[index] = 0;
			break;

		case TRIANGLE:
			signals -> freq[index] = Get_Note_Frequency(Get_Keyindex(key), octave);
			signals -> freqIndex[index] = Get_Note_Index(key,octave);
			signals -> current_LUT_Index[index] = 0;
			break;

		case NOISE:
			signals -> freq[index] = 0;
			signals -> freqIndex[index] = 0;
			signals -> current_LUT_Index[index] = 0;
			break;
		}
	}
	signals -> max = 1;
}

/** @brief deletes a signal inside the signals1 struct, and shifts all other signals behind the deleted signal to the left. The shift is for having no empty spaces inside the signals1 struct
 * @param: signal_index: index of the signals which should be seleted
 * @attention if you wnat to delete two signals in a row, beware that the index of the second signal could have changed, e.g. signals1 contains three signals, you want to delete signals1[0] and signals1[1]. After using DeleteSignal(0) you need to use DeleteSignal(0) again, because signals1[1] became signals1[0] after first use
 * @return None
 *  */
void DeleteSignal(struct signal_t* signals,int16_t signal_index) {

	if (signals->count > 0 && signal_index > -1){
		//shift signals too left
		for (int delete_counter=signal_index; delete_counter < signals->count; delete_counter++ ){
			signals -> current_LUT_Index[delete_counter] = signals -> current_LUT_Index[delete_counter+1] ;
			signals -> freq[delete_counter] = signals -> freq[delete_counter+1];
			signals -> freqIndex[delete_counter] = signals -> freqIndex[delete_counter+1];
			signals -> kind[delete_counter] = signals -> kind[delete_counter+1];
			signals -> ID[delete_counter] = signals -> ID[delete_counter+1];
		}
		signals -> count-=1;
		signals -> max = 1;
	}
	else {
		printf("delete ERROR\r\n");
	}
}
/**
 * @brief converts an signal ID into its Index
 * @param : ID of the wanted signal
 * @retval: Index of the signal with the given ID, or -1 when ID was not found
 */
int16_t IDtoIndex(int16_t id) {

	for(int i =0; i < MAX_SIGNAL_KOMBINATION;i++){
		if (signals1.ID[i] == id){
			return i;
		}
	}
	return -1;
}

/** @brief generates a digital signal in the calculate_vector, depending on the signals inside the struct signals1. To add signals use NewSignal and to delete signals use DeleteSignal
 *	@param signal: is a signal_t struct which contains the tones to be played
 *	@param  output_Channel: decides if the Array connected to the DAC Channel one is filled or the array connected with the DAC channel two is filled
 *  @note Channel 1 is connected to calculate_vector1 and Channel 2 connected to calculate_vector2
 *  @return None
 */

void Signal_Synthesis(struct signal_t* signals,uint8_t output_Channel){

	//Variables
	float addValue=0;
	uint8_t count = signals -> count;

	// decide if Channel 1 or Channel 2
	float* calculate_vector_tmp = 0; // working array

	if(output_Channel == 1) {
		calculate_vector_tmp = calculate_vector1;
	}
	else if(output_Channel == 2) {
		calculate_vector_tmp = calculate_vector2;
	}

	// decide if first half of BLOCKSIZE or second half
	uint16_t BLOOCKSIZE_startIndex = 0, BLOOCKSIZE_endIndex = 0;
	if (outputBuffer_position == HALF_BLOCK){
		BLOOCKSIZE_startIndex = 0;
		BLOOCKSIZE_endIndex = BLOCKSIZE/2;
	}
	else if(outputBuffer_position == FULL_BLOCK){
		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
		BLOOCKSIZE_endIndex  = BLOCKSIZE;
	}

	// Loop for signal synthesis
	for(int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex; BLOCKSIZE_counter++) {

		addValue = 0;

		calculate_keyboard[0] = 0;
		calculate_keyboard[1] = 0;
		calculate_keyboard[2] = 0;
		calculate_keyboard[3] = 0;
		calculate_keyboard[4] = 0;

		// Loop to reach all Signals
		for(int j=0; j<count; j++) {

			switch (signals->kind[j]) {

			case SIN:
				// adds all SIN values from the signals to addValue
				addValue = addValue + LUT[signals -> current_LUT_Index[j]];

				// get index for the next sin value
				signals->current_LUT_Index[j]++;

				if (signals->current_LUT_Index[j] > LUT_ENDINDEX[signals->freqIndex[j]]) {

					signals->current_LUT_Index[j] = LUT_STARTINDEX[signals->freqIndex[j]];

					// create voice signals (maximum 3) to avoid plop sound if note or octave is varied
					// this has to be done here to process the change immediately when the index is
					if(signals->ID[j] == VOICES_ID) {

						if(Display.last_Voices_Note[VOICES_ID] != Display.Voices_Note[VOICES_ID]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
							NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
							Display.last_Voices_Note[VOICES_ID] = Display.Voices_Note[VOICES_ID];
						}
						if(Display.last_Voices_Octave[VOICES_ID] != Display.Voices_Octave[VOICES_ID]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
							NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
							Display.last_Voices_Octave[VOICES_ID] = Display.Voices_Octave[VOICES_ID];
						}
					}
					else if(signals->ID[j] == VOICES_ID+1) {

						if(Display.last_Voices_Note[VOICES_ID+1] != Display.Voices_Note[VOICES_ID+1]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
							NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
							Display.last_Voices_Note[VOICES_ID+1] = Display.Voices_Note[VOICES_ID+1];
						}
						if(Display.last_Voices_Octave[VOICES_ID+1] != Display.Voices_Octave[VOICES_ID+1]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
							NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
							Display.last_Voices_Octave[VOICES_ID+1] = Display.Voices_Octave[VOICES_ID+1];
						}
					}
					else if(signals->ID[j] == VOICES_ID+2) {

						if(Display.last_Voices_Note[VOICES_ID+2] != Display.Voices_Note[VOICES_ID+2]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
							NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
							Display.last_Voices_Note[VOICES_ID+2] = Display.Voices_Note[VOICES_ID+2];
						}
						if(Display.last_Voices_Octave[VOICES_ID+2] != Display.Voices_Octave[VOICES_ID+2]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
							NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
							Display.last_Voices_Octave[VOICES_ID+2] = Display.Voices_Octave[VOICES_ID+2];
						}
					}
					// delete signal if voice off
					if(Display.Voices_ONOFF[VOICES_ID]==false && Display.Voices_Created[VOICES_ID] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
						Display.Voices_Created[VOICES_ID] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+1]==false && Display.Voices_Created[VOICES_ID+1] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
						Display.Voices_Created[VOICES_ID+1] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+2]==false && Display.Voices_Created[VOICES_ID+2] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
						Display.Voices_Created[VOICES_ID+2] = false;
					}
				}
				break;

			case RECT:
				// keyboard signals
				if(signals->ID[j] == KEYBOARD_VOICE_ID){
					calculate_keyboard[0] = CalcRectSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+1){
					calculate_keyboard[1] = CalcRectSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+2){
					calculate_keyboard[2] = CalcRectSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+3){
					calculate_keyboard[3] = CalcRectSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+4){
					calculate_keyboard[4] = CalcRectSample(signals, j);
				}
				else{
					// adds all RECT values from the signals to addValue
					addValue = addValue + CalcRectSample(signals, j);
				}

				// get index for the next rect value
				signals->current_LUT_Index[j]++;

				if (signals->current_LUT_Index[j] >= LUT_SUPPORTPOINTS[signals->freqIndex[j]]) {

					signals->current_LUT_Index[j] = 0;

					// create voice signals (maximum 3) to avoid plop sound if note or octave is varied
					// this has to be done here to process the change immediately when the index is
					if(signals->ID[j] == VOICES_ID) {

						if(Display.last_Voices_Note[VOICES_ID] != Display.Voices_Note[VOICES_ID]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
							NewSignal(&signals1, RECT, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
							Display.last_Voices_Note[VOICES_ID] = Display.Voices_Note[VOICES_ID];
						}
						if(Display.last_Voices_Octave[VOICES_ID] != Display.Voices_Octave[VOICES_ID]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
							NewSignal(&signals1, RECT, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
							Display.last_Voices_Octave[VOICES_ID] = Display.Voices_Octave[VOICES_ID];
						}
					}
					else if(signals->ID[j] == VOICES_ID+1) {

						if(Display.last_Voices_Note[VOICES_ID+1] != Display.Voices_Note[VOICES_ID+1]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
							NewSignal(&signals1, RECT, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
							Display.last_Voices_Note[VOICES_ID+1] = Display.Voices_Note[VOICES_ID+1];
						}
						if(Display.last_Voices_Octave[VOICES_ID+1] != Display.Voices_Octave[VOICES_ID+1]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
							NewSignal(&signals1, RECT, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
							Display.last_Voices_Octave[VOICES_ID+1] = Display.Voices_Octave[VOICES_ID+1];
						}
					}
					else if(signals->ID[j] == VOICES_ID+2) {

						if(Display.last_Voices_Note[VOICES_ID+2] != Display.Voices_Note[VOICES_ID+2]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
							NewSignal(&signals1, RECT, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
							Display.last_Voices_Note[VOICES_ID+2] = Display.Voices_Note[VOICES_ID+2];
						}
						if(Display.last_Voices_Octave[VOICES_ID+2] != Display.Voices_Octave[VOICES_ID+2]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
							NewSignal(&signals1, RECT, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
							Display.last_Voices_Octave[VOICES_ID+2] = Display.Voices_Octave[VOICES_ID+2];
						}
					}
					// delete signal if voice off
					if(Display.Voices_ONOFF[VOICES_ID]==false && Display.Voices_Created[VOICES_ID] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
						Display.Voices_Created[VOICES_ID] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+1]==false && Display.Voices_Created[VOICES_ID+1] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
						Display.Voices_Created[VOICES_ID+1] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+2]==false && Display.Voices_Created[VOICES_ID+2] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
						Display.Voices_Created[VOICES_ID+2] = false;
					}
				}
				break;

			case TRIANGLE:
				// keyboard signals
				if(signals->ID[j] == KEYBOARD_VOICE_ID){
					calculate_keyboard[0] = CalcTriangleSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+1){
					calculate_keyboard[1] = CalcTriangleSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+2){
					calculate_keyboard[2] = CalcTriangleSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+3){
					calculate_keyboard[3] = CalcTriangleSample(signals, j);
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+4){
					calculate_keyboard[4] = CalcTriangleSample(signals, j);
				}
				else{
					// adds all TRIANGLE values from the signals to addValue
					addValue = addValue + CalcTriangleSample(signals, j);
				}
				// get index for the next triangle value
				signals->current_LUT_Index[j]++;

				if (signals->current_LUT_Index[j] >= LUT_SUPPORTPOINTS[signals->freqIndex[j]]) {

					signals->current_LUT_Index[j] = 0;

					// create voice signals (maximum 3) to avoid plop sound if note or octave is varied
					// this has to be done here to process the change immediately when the index is
					if(signals->ID[j] == VOICES_ID) {

						if(Display.last_Voices_Note[VOICES_ID] != Display.Voices_Note[VOICES_ID]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
							NewSignal(&signals1, TRIANGLE, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
							Display.last_Voices_Note[VOICES_ID] = Display.Voices_Note[VOICES_ID];
						}
						if(Display.last_Voices_Octave[VOICES_ID] != Display.Voices_Octave[VOICES_ID]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
							NewSignal(&signals1, TRIANGLE, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
							Display.last_Voices_Octave[VOICES_ID] = Display.Voices_Octave[VOICES_ID];
						}
					}
					else if(signals->ID[j] == VOICES_ID+1) {

						if(Display.last_Voices_Note[VOICES_ID+1] != Display.Voices_Note[VOICES_ID+1]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
							NewSignal(&signals1, TRIANGLE, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
							Display.last_Voices_Note[VOICES_ID+1] = Display.Voices_Note[VOICES_ID+1];
						}
						if(Display.last_Voices_Octave[VOICES_ID+1] != Display.Voices_Octave[VOICES_ID+1]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
							NewSignal(&signals1, TRIANGLE, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
							Display.last_Voices_Octave[VOICES_ID+1] = Display.Voices_Octave[VOICES_ID+1];
						}
					}
					else if(signals->ID[j] == VOICES_ID+2) {

						if(Display.last_Voices_Note[VOICES_ID+2] != Display.Voices_Note[VOICES_ID+2]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
							NewSignal(&signals1, TRIANGLE, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
							Display.last_Voices_Note[VOICES_ID+2] = Display.Voices_Note[VOICES_ID+2];
						}
						if(Display.last_Voices_Octave[VOICES_ID+2] != Display.Voices_Octave[VOICES_ID+2]) {
							DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
							NewSignal(&signals1, TRIANGLE, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
							Display.last_Voices_Octave[VOICES_ID+2] = Display.Voices_Octave[VOICES_ID+2];
						}
					}
					// delete signal if voice off
					if(Display.Voices_ONOFF[VOICES_ID]==false && Display.Voices_Created[VOICES_ID] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
						Display.Voices_Created[VOICES_ID] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+1]==false && Display.Voices_Created[VOICES_ID+1] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
						Display.Voices_Created[VOICES_ID+1] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+2]==false && Display.Voices_Created[VOICES_ID+2] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
						Display.Voices_Created[VOICES_ID+2] = false;
					}
				}
				break;

			}//end witch Case

		}//End SIgnal for-Loop

		// NORM: Volume by signal count
		if(signals->count - active_keyboard_notes == 0) {}	// division by zero for addValue possible -> fuckup!
		else
			addValue = addValue / (signals->count - active_keyboard_notes);



		// write voices (including noise) into calculate vector
		calculate_vector_tmp[BLOCKSIZE_counter] = volume[0] * (addValue + Noise_Generator());



		// Drummachine
		if ((volume[1] > 0) || (volume[2] > 0)){
			Drum_Computer_Process();
			drums_filtered = drums;
			if(Display.Drumfilter_ONOFF)
				ProcessFilter(&LS_DRUMS, &drums_filtered);
		}
		else{
			drums = 0;
			sequencer = 0;
		}

		// Keyboard processing with effects
		if(Display.KeyboardFX_ONOFF == true) {
			keyboard_adsr_process();
			// summing up all played keyboard notes
			for (int k= 0; k < 5;k++)
				calculate_vector_tmp[BLOCKSIZE_counter] += volume[3] * calculate_keyboard[k];
		}
		// Keyboard processing without effects
		else if(Display.KeyboardFX_ONOFF == false) {
			keyboard_adsr_process();
			// summing up all played keyboard notes
			for (int k= 0; k < 5;k++)
				calculate_vector_tmp[BLOCKSIZE_counter] += volume[3] * calculate_keyboard[k];
		}



		// Play single sample
		if(play_single_sample_flag) {
			PlaySingleSample();
			calculate_vector_tmp[BLOCKSIZE_counter] += single_sample;
		}

		effects_process(&calculate_vector_tmp[BLOCKSIZE_counter]);

	

		// Add all values
		calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter] + volume[1] * drums_filtered + volume[2] * sequencer;

		// to make sure that the output is 0 when a new drumkit is loaded into the drum computer
		if(Display.LoadDrumkit == true)
			calculate_vector_tmp[BLOCKSIZE_counter] = 0;

		// Convert float to uint32 in order to make it readable for the DAC
		*((uint32_t *)(&calculate_vector_tmp[BLOCKSIZE_counter] )) = (uint32_t)((0.5 * Master_Volume * calculate_vector_tmp[BLOCKSIZE_counter]+1.65) * maxValueDAC); // +1.65 is the middle of 0-3V3
	}//End for-Loop



}



/** @brief wirtes a starting ramp into the DAC-Buffer to avoid speaker damage
 * @retval returns a bool which indicates if ramp is finished or still in process
 */
float ramp_counter = 0;

bool initRamp(void){
	bool retval = false;
	float* calculate_vector_tmp = calculate_vector1;

	// ramp Duration of 0.5 seconds
	float ramp_dur = 0.5*LUT_SR;
	// MAX Ramp Value in mV
	uint32_t maxRamp = (uint32_t)(1650 * DAC_MAXVALUE_TO_AMPLITUDE_RATIO );

	// Write into DAC-Buffer
	// decide if first half of BLOCKSIZE or second half
	uint16_t BLOOCKSIZE_startIndex = 0, BLOOCKSIZE_endIndex = 0;
	if (outputBuffer_position == HALF_BLOCK){
		BLOOCKSIZE_startIndex = 0;
		BLOOCKSIZE_endIndex = BLOCKSIZE/2;
	}
	else if(outputBuffer_position == FULL_BLOCK){
		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
		BLOOCKSIZE_endIndex  = BLOCKSIZE;
	}

	//Write into DAC
	for(int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex; BLOCKSIZE_counter++) {

		if (ramp_counter < ramp_dur){
			*((uint32_t *)(&calculate_vector_tmp[BLOCKSIZE_counter] )) = (uint32_t)((float)((ramp_counter/ramp_dur) * maxRamp));
			ramp_counter++;
		}
		else if(ramp_counter >= ramp_dur){
			*((uint32_t *)(&calculate_vector_tmp[BLOCKSIZE_counter] )) = (uint32_t)(maxRamp);
		}
	}
	if (ramp_counter >= ramp_dur)
		retval = true;

	return retval;
}


/**
 * @brief Rectangle wave based on struct signals
 * 
 * @param signals 
 * @param index 
 * @return float 
 */
float CalcRectSample(struct signal_t* signals, int index){

	float rect = 0;

	// Current Index:   signals->current_LUT_Index[index]
	// Period:			LUT_SUPPORTPOINTS[signals->freqIndex[index]]

	// IF: Length of period is even (e.g. 346)
	if(LUT_SUPPORTPOINTS[signals->freqIndex[index]] % 2 == 0){

		// IF: Current index < length of period of desired frequency (0:172 < 173)
		if(signals->current_LUT_Index[index] < (LUT_SUPPORTPOINTS[signals->freqIndex[index]] / 2)){

			rect = 0.2;
		}
		// IF: Current index >= length of period of desired frequency (173:345 >= 173)
		else if(signals->current_LUT_Index[index] >= (LUT_SUPPORTPOINTS[signals->freqIndex[index]] / 2)){

			rect = -0.2;
		}
	}
	// IF: Length of period is odd (e.g. 347)
	else if(LUT_SUPPORTPOINTS[signals->freqIndex[index]] % 2 == 1){

		// IF: Current index < length of period of desired frequency (0:173 < 174) due to (period-1)/2 + 1
		if(signals->current_LUT_Index[index] < (((LUT_SUPPORTPOINTS[signals->freqIndex[index]] - 1) / 2) + 1)){

			rect = 0.2;
		}
		// IF: Current index >= length of period of desired frequency (174:346 >= 174) due to (period-1)/2 + 1
		else if(signals->current_LUT_Index[index] >= (((LUT_SUPPORTPOINTS[signals->freqIndex[index]] - 1) / 2) + 1)){

			rect = -0.2;
		}
	}
	return rect;
}

/**
 * @brief Triangle wave samples based on struct signals
 * 
 * @param signals 
 * @param index 
 * @return triangle value
 */
float CalcTriangleSample(struct signal_t* signals, int index){

	float triangle      = 0;
	float current_index = (float)signals->current_LUT_Index[index];
	float period        = (float)LUT_SUPPORTPOINTS[signals->freqIndex[index]];

	/* FORMULA: 4*a/p * abs((((x - p/4) % p) + p) % p - p/2) - a
	 *
	 * a: Amplitude			>> 1
	 * x: Current index		>> signals->current_LUT_Index[index]
	 * p: Period			>> LUT_SUPPORTPOINTS[signals->freqIndex[index]]
	 *
	 * Source: https://en.wikipedia.org/wiki/Triangle_wave
	 *
	 */

	triangle = fmodf(current_index - period/4, period);
	triangle = triangle + period;
	triangle = fmodf(triangle, period) - period/2;
	triangle = abs(triangle);
	triangle = (4/period) * triangle - 1;;

	return triangle;
}

/**
 * @brief random number generator
 * 
 * @return float 
 */
float Noise_Generator(void) {

	float NoiseValue = 0;
	float Noise_Gain = 0.5;

	if(Display.Noise_ONOFF == true)
		NoiseValue = (Noise_Gain*Display.Noise_Volume*(float)rand()/ (powf(2, 8*sizeof(int))) )-(Noise_Gain*Display.Noise_Volume*0.25);	// Noise Gain = 8

	return NoiseValue;
}


/**
 * @brief Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1.
 * 
 * @return float 
 */
float AWGN_generator(void) {

	float temp1;
	float temp2;
	float result;
	int p;

	p = 1;

	while( p > 0 )
	{
		temp2 = ( rand() / ( (float)RAND_MAX ) ); /*  rand() function generates an
                                                       integer between 0 and  RAND_MAX,
                                                       which is defined in stdlib.h.
		 */

		if ( temp2 == 0 )
		{// temp2 is >= (RAND_MAX / 2)
			p = 1;
		}// end if
		else
		{// temp2 is < (RAND_MAX / 2)
			p = -1;
		}// end else

	}// end while()

	temp1 = cos( ( 2.0 * (float)PI ) * rand() / ( (float)RAND_MAX ) );
	result = sqrt( -2.0 * log( temp2 ) ) * temp1;

	return result;	// return the generated random sample to the caller

}// end AWGN_generator()
