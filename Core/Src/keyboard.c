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
	keyboard_pressed_flag = false;
	initial_press_flag = false;
	for (int i =0;i < MAX_SIMULTANEOUS_KEYBOARD_NOTES;i++)
		play_keyboard_note[i] = false;

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

	if (adsr_keyboard[0].adsr_counter >0){
		//Key release sensing
		if(adc_value <= NO_KEY_ADC_VALUE) {

			if(keyboard_pressed_counter%2==0)
				keyboard_pressed_counter++;

		}
		//Key Press Sensing
		else if (adc_value > NO_KEY_ADC_VALUE){

			if(keyboard_pressed_counter%2==1)
				keyboard_pressed_counter++;

		}
	}
		printf("%i\r\n", keyboard_pressed_counter);
	//activate processing
	if (keyboard_pressed_counter >= 4)
		play_keyboard_note[1] = true;
	if(keyboard_pressed_counter >= 6)
		play_keyboard_note[2] = true;



	//generate Signal
	if(keyboard_pressed_counter % 2 == 0) {
		for(uint8_t i=0; i<(NUMBER_OF_KEYBOARD_NOTES-1); i++) {
			if(adc_value > keyboard_note_adcval[i] && adc_value < keyboard_note_adcval[i+1]) {
				NewSignal(signals, SIN, keys[i], Display->Keyboard_Octave, KEYBOARD_VOICE_ID+ID);
				keyboard_pressed_flag = true;
			}
		}
	}


	//ADSR info
	if(adc_value < NO_KEY_ADC_VALUE && envelope->adsr_done == true) {
		keyboard_pressed_flag = false;
	}

	//Delete signal
	if(envelope->adsr_done == true) {
		DeleteSignal(signals,IDtoIndex(KEYBOARD_VOICE_ID+ID));
		envelope->adsr_done = false;
		play_keyboard_note[ID] = false;
		printf("delete\r\n");
	}
	//reset counter
	if (keyboard_pressed_counter >=6)
		keyboard_pressed_counter = 1;
}
