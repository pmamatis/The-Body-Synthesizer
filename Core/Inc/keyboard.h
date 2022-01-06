#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "main.h"

/*********************************
 * @brief		Defines
 *********************************/
#define KEYBOARD_SR 500 // in Hz
#define KEYBOARD_VOICE_ID 4	// as big as NUMBER_OF_VOICES+1
#define VOICES_ID 0

// Define Notes (has to be calibrated for every keyboard)
//#define H_NOTE_ADC_VALUE 	4095
//#define AIS_NOTE_ADC_VALUE 	3800
//#define A_NOTE_ADC_VALUE 	3500
//#define GIS_NOTE_ADC_VALUE 	3100
//#define G_NOTE_ADC_VALUE 	2800
//#define FIS_NOTE_ADC_VALUE 	2450
//#define F_NOTE_ADC_VALUE 	2100
//#define E_NOTE_ADC_VALUE 	1800
//#define DIS_NOTE_ADC_VALUE 	1400
//#define D_NOTE_ADC_VALUE 	1100
//#define CIS_NOTE_ADC_VALUE 	800
//#define C_NOTE_ADC_VALUE 	400
#define NO_KEY_ADC_VALUE 	200

#define NUMBER_OF_KEYBOARD_NOTES 13
#define MAX_SIMULTANEOUS_KEYBOARD_NOTES 5

/** reserved position in the signal struct array.
 * 	(NewSignal from last pressed key)
 */
#define KEYBOARD_SP MAX_SIGNAL_KOMBINATION




/*********************************
 * @brief		Variables
 *********************************/
const uint16_t keyboard_note_adcval[NUMBER_OF_KEYBOARD_NOTES];

ADC_HandleTypeDef* KEYBOARD_ADC;

/** Timer which triggers the keyboard ADC */
TIM_HandleTypeDef* KEYBOARD_TIM;

uint32_t keyboard_pressed_counter;

bool played_keyboard_note[MAX_SIMULTANEOUS_KEYBOARD_NOTES];
bool activate_processing[MAX_SIMULTANEOUS_KEYBOARD_NOTES];

uint8_t active_keyboard_notes;

/*********************************
 * @brief		Functions
 *********************************/
void keyboard_init(ADC_HandleTypeDef *ADC_Handler,TIM_HandleTypeDef* TIM_Handler);
HAL_StatusTypeDef keyboard_start_read(void);
HAL_StatusTypeDef keyboard_stop_read(void);
void OnePress_keyboard_process(uint32_t adc_value, struct signal_t* signals, struct display_variables* Display);

#endif /* INC_KEYBOARD_H_ */
