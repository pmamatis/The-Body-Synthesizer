#include "keyboard.h"

const uint16_t keyboard_note_adcval[] = {200, 400, 800, 1100, 1400, 1800, 2100, 2450, 2800, 3100, 3500, 3800, 4095};
/**
 * @brief Keyboaed Init funcrion
 * 
 * @param ADC_Handler 
 * @param TIM_Handler 
 */
void keyboard_init(ADC_HandleTypeDef *ADC_Handler,TIM_HandleTypeDef* TIM_Handler) {
	KEYBOARD_ADC = ADC_Handler;
	KEYBOARD_TIM = TIM_Handler;
	SetTimerSettings(TIM_Handler, KEYBOARD_SR);
	keyboard_pressed_counter = 0;
	for(int i = 0; i < MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++) {
		played_keyboard_note[i] = false;
		activate_processing[i] = false;
	}
	active_keyboard_notes = 0;
}

/**
 * @brief starts the keyboard reading process
 * @note the ADC is controlled by the Timer keyboard_TIM, so the ADC-Read Command is inside the Timer Interrupt
 */
HAL_StatusTypeDef keyboard_start_read(void) {

	HAL_StatusTypeDef retval;
	printf("start keyboard read....\r\n");
	retval = HAL_TIM_Base_Start_IT(KEYBOARD_TIM);
	HAL_ADC_Start_DMA(KEYBOARD_ADC, &Display.ADC1input, 1);
	return retval;
}

/**
 * @brief Stops teh Keyboard readout by stoping the timer-interrupt
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef keyboard_stop_read() {
	printf("end keyboard read....\r\n");
	return HAL_TIM_Base_Stop_IT(KEYBOARD_TIM);
}

/**
 * @brief This function handles the Data processing for the Keyboard ADC, depending on the given value a signal is generated and played untill the keyboard adsr end for this signal.  
 * @param adc_value raw data from the keyboard adc
 * @param signals 
 * @param Display 
 */
void OnePress_keyboard_process(uint32_t adc_value, struct signal_t* signals, struct display_variables* Display) {

	// Generate Signal
	for(uint8_t i=0; i<(NUMBER_OF_KEYBOARD_NOTES-1); i++) {

		if(adc_value > keyboard_note_adcval[i] && adc_value < keyboard_note_adcval[i+1]) {

			if(!played_keyboard_note[0] && activate_processing[0]){
				NewSignal(signals, RECT, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID);
				played_keyboard_note[0] = true;
				active_keyboard_notes++;
			}
			else if(!played_keyboard_note[1] && activate_processing[1]){
				NewSignal(signals, RECT, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+1);
				played_keyboard_note[1] = true;
				active_keyboard_notes++;
			}
			else if(!played_keyboard_note[2] && activate_processing[2]){
				NewSignal(signals, RECT, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+2);
				played_keyboard_note[2] = true;
				active_keyboard_notes++;
			}
			else if(!played_keyboard_note[3] && activate_processing[3]){
				NewSignal(signals, RECT, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+3);
				played_keyboard_note[3] = true;
				active_keyboard_notes++;
			}
			else if(!played_keyboard_note[4] && activate_processing[4]){
				NewSignal(signals, RECT, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+4);
				played_keyboard_note[4] = true;
				active_keyboard_notes++;
			}
		}
	}

	// Delete signal
	for (int i = 0; i < MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++){

		if (adsr_keyboard[i].adsr_done){
			int index = IDtoIndex(KEYBOARD_VOICE_ID+i);

			DeleteSignal(signals,index);
			adsr_keyboard[i].adsr_done = false;

			played_keyboard_note[i] = false;

			activate_processing[i] = false;

			active_keyboard_notes--;
		}
	}
}
