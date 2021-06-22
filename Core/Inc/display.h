/*
 * display.h
 *
 *  Created on: 21.01.2021
 *      Author: Marc Bielen
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include <stdbool.h>

typedef enum {
	DISPLAY_FAIL = -1,
	DISPLAY_OK = 1
} Display_Status;

struct display_variables {
	bool PatchSelected[3];	// arrays for 3 Modules for each patch
	bool ModuleState[3];
	bool ModuleStateSelected[3];
	bool ModuleParametersSelected[3];
	bool ModuleCompleted[3];
	uint8_t CurrentModule;

	// Keyboard Parameters
	bool KeyboardmodeSelected;
	bool Keyboardmode_ONOFF;
	uint8_t Keyboard_Octave;
	float Keyboard_AttackTime;
	float Keyboard_DecayTime;
	float Keyboard_SustainTime;
	float Keyboard_SustainLevel;
	float Keyboard_ReleaseTime;

	// Synthesizer Parameters
	uint8_t ActiveEffectsCounter;
	bool Voices_ONOFF[3];		// 3 Voices
	uint8_t Voices_Note[3];
	uint8_t Voices_Octave[3];
	bool ADSR_ONOFF;			// 1 ADSR
	float ADSR_Attack;
	float ADSR_Decay;
	float ADSR_Sustain;
	float ADSR_Release;
	uint8_t ADSR_EffectPosition;
	bool ADSR_EffectAdded;
	bool Distortion_ONOFF;
	bool Distortion_Type;
	float Distortion_Gain;
	uint8_t Distortion_EffectPosition;
	bool Distortion_EffectAdded;
	bool Tremolo_ONOFF;
	float Tremolo_Rate;
	float Tremolo_Depth;
	uint8_t Tremolo_EffectPosition;
	bool Tremolo_EffectAdded;
	bool Filter_ONOFF;
	float Filter_Cutoff;
	float Filter_Q;
	uint8_t Filter_EffectPosition;
	bool Filter_EffectAdded;
	//...Weitere Synth-Parameter

	uint16_t ADC1inputs[1];	// ADC input arrays
	uint16_t ADC2inputs[3];
	uint16_t ADC3inputs[2];
	uint16_t LowerLimit;
	uint16_t UpperLimit;
	uint16_t ADC_FullRange;

	// Joystick-variables
	uint16_t VRx;
	uint16_t VRy;
	uint8_t JoystickPatchPosition;
	uint8_t JoystickParameterPosition;

	// Potentiometer-variables
	uint16_t Poti_raw;
	float Poti_percent;
	int progress_bar;

	// EMG-Sensor-variables
	uint16_t EMG_DC;
	uint16_t EMG_AC;

	// Gyro-Sensor-variables
	uint16_t GyroX;
	uint16_t GyroY;
	uint16_t GyroZ;

	bool ENTER_Debounce_State;
	bool BACK_Debounce_State;
	bool SW_Debounce_State;
	bool ENTER;		// state variable of the ENTER-Button to go one step further in the display-menu
	bool BACK;		// state variable of the BACK-Button to go one step back in the display-menu
	bool SW;		// state variable of the SW-Button of the Joystick
};

struct display_variables Display;

Display_Status Display_Init(struct display_variables* Display);

#endif /* INC_DISPLAY_H_ */
