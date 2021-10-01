/*
 * keyboard.c
 *
 *  Created on: Jun 18, 2021
 *      Author: Marc Bielen
 */

#include "keyboard.h"

const uint16_t keyboard_note_adcval[] = {200, 400, 800, 1100, 1400, 1800, 2100, 2450, 2800, 3100, 3500, 3800, 4095};

void keyboard_init(ADC_HandleTypeDef *ADC_Handler,TIM_HandleTypeDef* TIM_Handler) {
	KEYBOARD_ADC = ADC_Handler;
	KEYBOARD_TIM = TIM_Handler;
	SetTimerSettings(TIM_Handler, KEYBOARD_SR);
	keyboard_octave = 1;
	start_release_flag = false;
	keyboard_pressed_counter = 0;
	initial_press_flag = false;
	for (int i =0;i < MAX_SIMULTANEOUS_KEYBOARD_NOTES;i++){
		played_keyboard_note[i] = false;
		activate_processing[i] =false;
	}
}

/** starts the keyboard reading process
 * @note the ADC is controlled by the Timer keyboard_TIM, so the ADC-Read Command is inside the Timer Interrupt
 */
HAL_StatusTypeDef keyboard_start_read() {
	HAL_StatusTypeDef retval;
	printf("start keyboard read....\r\n");
	retval = HAL_TIM_Base_Start_IT(KEYBOARD_TIM);
	HAL_ADC_Start_DMA(KEYBOARD_ADC, &Display.ADC1input, 1);
	//retval = HAL_TIM_Base_Start(KEYBOARD_TIM);
	//retval = HAL_ADC_Start_DMA(KEYBOARD_ADC, &keyboard_adc_value, 1);
	return retval;
}

HAL_StatusTypeDef keyboard_stop_read() {
	printf("end keyboard read....\r\n");
	return HAL_TIM_Base_Stop_IT(KEYBOARD_TIM);

	//	return HAL_ADC_Stop_DMA(KEYBOARD_ADC);
}

void OnePress_keyboard_process(uint32_t adc_value, struct signal_t* signals, struct adsr* envelope, struct display_variables* Display,uint8_t ID) {

	//	for(uint8_t i=0; i<MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++) {
	//		if(adc_value < NO_KEY_ADC_VALUE && adsr_keyboard[i].adsr_done == true) {
	//			keyboard_pressed_flag[i] = false;
	//		}
	//
	//		if(adsr_keyboard[i].adsr_done == true) {
	//			DeleteSignal(signals,IDtoIndex(KEYBOARD_VOICE_ID+i));
	//			adsr_keyboard[i].adsr_done = false;
	//		}
	//
	//		if(keyboard_pressed_flag[i] == false) {
	//			for(uint8_t j=0; j<(NUMBER_OF_KEYBOARD_NOTES-1); j++) {
	//				if(adc_value > keyboard_note_adcval[j] && adc_value < keyboard_note_adcval[j+1]) {
	//					NewSignal(signals, SIN, keys[j], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+i);
	//					keyboard_pressed_flag[i] = true;
	//				}
	//			}
	//		}
	//	}

	//	if (adsr_keyboard[0].adsr_counter >0){

	//	}


//	printf("%i\r\n", keyboard_pressed_counter);
//	printf("ID: %i\r\n",ID);
	//	printf("count: %i\r\n",signals->count);


	// Generate Signal
	if(!(keyboard_pressed_counter % 2) ) {
		for(uint8_t i=0; i<(NUMBER_OF_KEYBOARD_NOTES-1); i++) {
			if(adc_value > keyboard_note_adcval[i] && adc_value < keyboard_note_adcval[i+1]) {

				if(!played_keyboard_note[0] && activate_processing[0]){
					NewSignal(signals, SIN, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID);
					played_keyboard_note[0] = true;
//					activate_processing[0] = true;
				}
				else if(!played_keyboard_note[1] && activate_processing[1]){
//					activate_processing[1] = true;
					NewSignal(signals, SIN, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+1);
					played_keyboard_note[1] = true;
				}

				else if(!played_keyboard_note[2] && activate_processing[2]){
//					activate_processing[2] = true;
					NewSignal(signals, SIN, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+2);
					played_keyboard_note[2] = true;
				}
			}
		}
	}

	// Delete signal
	for (int i = 0; i < 3;i++){
		if (adsr_keyboard[i].adsr_done){
			DeleteSignal(signals,IDtoIndex(KEYBOARD_VOICE_ID+i));
			adsr_keyboard[i].adsr_done = false;
			if (keyboard_pressed_counter % 2)
				played_keyboard_note[i] = false;
			activate_processing[i] = false;
		}
	}

}
