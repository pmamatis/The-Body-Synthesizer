/*
 * keyboard.c
 *
 *  Created on: Jun 18, 2021
 *      Author: Marc Bielen
 */

#include "keyboard.h"

void keyboard_init(ADC_HandleTypeDef *ADC_Handler,TIM_HandleTypeDef* TIM_Handler) {
	KEYBOARD_ADC = ADC_Handler;
	KEYBOARD_TIM = TIM_Handler;
	SetTimerSettings(TIM_Handler, KEYBOARD_SR);
	keyboard_octave = 1;
	keyboard_pressed_flag = false;
	start_release_flag = false;
	keyboard_counter = 0;
}

/** starts the keyboard reading process
 * @note the ADC is controlled by the Timer keyboard_TIM, so the ADC-Read Command is inside the Timer Interrupt
 */
HAL_StatusTypeDef keyboard_start_read() {
	HAL_StatusTypeDef retval;
	printf("start keyboard read....\r\n");
	retval = HAL_TIM_Base_Start_IT(KEYBOARD_TIM);
	//retval = HAL_TIM_Base_Start(KEYBOARD_TIM);
	//retval = HAL_ADC_Start_DMA(KEYBOARD_ADC, &keyboard_adc_value, 1);
	return retval;
}

HAL_StatusTypeDef keyboard_stop_read() {
	printf("end keyboard read....\r\n");
	return HAL_TIM_Base_Stop_IT(KEYBOARD_TIM);

	//	return HAL_ADC_Stop_DMA(KEYBOARD_ADC);
}

void OnePress_keyboard_process(uint32_t adc_value, struct signal_t* signals, struct adsr* envelope, struct display_variables* Display) {

	if (adc_value > AIS_NOTE_ADC_VALUE){
		printf("H\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'H', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > A_NOTE_ADC_VALUE) {
		printf("B\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'B', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > GIS_NOTE_ADC_VALUE) {
		printf("A\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'A', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > G_NOTE_ADC_VALUE) {
		printf("GIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'g', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > FIS_NOTE_ADC_VALUE) {
		printf("G\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'G', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > F_NOTE_ADC_VALUE) {
		printf("FIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'f', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > E_NOTE_ADC_VALUE) {
		printf("F\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'F', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > DIS_NOTE_ADC_VALUE) {
		printf("E\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'E', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > D_NOTE_ADC_VALUE) {
		printf("DIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'd', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > CIS_NOTE_ADC_VALUE) {
		printf("D\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'D', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > C_NOTE_ADC_VALUE) {
		printf("CIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'c', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > NO_KEY_ADC_VALUE) {
		printf("C\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'C', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else {
		printf("No Key\n\r");
		if(envelope->adsr_done == true) {
			keyboard_counter = 0;
			//find signal with the right ID
			while(signals->ID[keyboard_counter]!=keyboard_ID)
				keyboard_counter++;
			DeleteSignal(signals, keyboard_counter);
			keyboard_pressed_flag = false;
			envelope->adsr_done = false;
		}
	}
}

/*void OnePress_keyboard_process(uint32_t adc_value, struct signal_t* signals, struct adsr* envelope, struct display_variables* Display) {

	if (adc_value > AIS_NOTE_ADC_VALUE){
		printf("H\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'H', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > A_NOTE_ADC_VALUE) {
		printf("B\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'B', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > GIS_NOTE_ADC_VALUE) {
		printf("A\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'A', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > G_NOTE_ADC_VALUE) {
		printf("GIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'g', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > FIS_NOTE_ADC_VALUE) {
		printf("G\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'G', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > F_NOTE_ADC_VALUE) {
		printf("FIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'f', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > E_NOTE_ADC_VALUE) {
		printf("F\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'F', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > DIS_NOTE_ADC_VALUE) {
		printf("E\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'E', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > D_NOTE_ADC_VALUE) {
		printf("DIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'd', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > CIS_NOTE_ADC_VALUE) {
		printf("D\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'D', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > C_NOTE_ADC_VALUE) {
		printf("CIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'c', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > NO_KEY_ADC_VALUE) {
		printf("C\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'C', Display->Keyboard_Octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else {
		printf("No Key\n\r");
		if(envelope->adsr_done == true) {
			keyboard_counter = 0;
			//find signal with the right ID
			while(signals->ID[keyboard_counter]!=keyboard_ID)
				keyboard_counter++;
			DeleteSignal(signals, keyboard_counter);
			keyboard_pressed_flag = false;
			envelope->adsr_done = false;
		}
	}
}*/

/*void keyboard_process(uint16_t adc_value, struct signal_t* signals, struct adsr* envelope) {

	if (adc_value > AIS_NOTE_ADC_VALUE){
		printf("H\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'H', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > A_NOTE_ADC_VALUE) {
		printf("B\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'B', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > GIS_NOTE_ADC_VALUE) {
		printf("A\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'A', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > G_NOTE_ADC_VALUE) {
		printf("GIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'g', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > FIS_NOTE_ADC_VALUE) {
		printf("G\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'G', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > F_NOTE_ADC_VALUE) {
		printf("FIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'f', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > E_NOTE_ADC_VALUE) {
		printf("F\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'F', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > DIS_NOTE_ADC_VALUE) {
		printf("E\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'E', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > D_NOTE_ADC_VALUE) {
		printf("DIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'd', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > CIS_NOTE_ADC_VALUE) {
		printf("D\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'D', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > C_NOTE_ADC_VALUE) {
		printf("CIS\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'c', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else if (adc_value > NO_KEY_ADC_VALUE) {
		printf("C\n\r");
		if (keyboard_pressed_flag == false){
			NewSignal(signals, SIN, 'C', keyboard_octave);
			keyboard_ID = signals->ID[(signals->count)-1];
			keyboard_pressed_flag = true;
		}
	}
	else {
		printf("No Key\n\r");

		if(keyboard_pressed_flag == true) {
			keyboard_pressed_flag = false;
			start_release_flag = true;
		}
	}
}*/
