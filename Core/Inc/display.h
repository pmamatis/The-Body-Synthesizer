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

#include "epd1in54.h"
#include "epdif.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED      0
#define UNCOLORED    1


typedef enum {
	CASE1 = 30,
	CASE2 = 50,
	CASE3 =	70,
	CASE4 =	90,
	CASE5 =	110,
	CASE6 =	130,
	CASE7 =	150,
	CASE8 =	170,
	CASE9 =	190,
}y_row_value;

typedef enum {
	DISPLAY_FAIL = -1,
	DISPLAY_OK = 1
} Display_Status;


typedef enum {
	NONE = -1,
	KEYBOARD = 0,
	BODYSYNTH = 1
}synth_mode_t;

struct display_variables {
	bool PatchSelected[3];	// arrays for 3 Modules for each patch
	bool ModuleState[3];
	bool ModuleStateSelected[3];
	bool ModuleParametersSelected[3];
	bool ModuleCompleted[3];
	uint8_t CurrentModule;

	//MODE
	synth_mode_t mode;

	// Keyboard Parameters
	bool KeyboardmodeSelected;
	bool Keyboardmode_ONOFF;
	uint8_t last_Keyboard_Octave;
	uint8_t Keyboard_Octave;
	float last_Keyboard_AttackTime;
	float Keyboard_AttackTime;
	float last_Keyboard_DecayTime;
	float Keyboard_DecayTime;
	float last_Keyboard_SustainTime;
	float Keyboard_SustainTime;
	float last_Keyboard_SustainLevel;
	float Keyboard_SustainLevel;
	float last_Keyboard_ReleaseTime;
	float Keyboard_ReleaseTime;

	// Synthesizer Parameters
	uint8_t ActiveEffectsCounter;
	bool Voices_ONOFF[3];		// 3 Voices
	bool last_Voices_ONOFF[3];
	char Voices_Note[3];
	char Voices_Octave[3];
	float noteindex;

	//ADSR
	bool ADSR_ONOFF;			// 1 ADSR
	float ADSR_Attack;
	float ADSR_Decay;
	float ADSR_Sustain;
	float ADSR_Release;
	uint8_t ADSR_EffectPosition;
	bool ADSR_EffectAdded;

	//Distortion
	bool Distortion_ONOFF;
	bool last_Distortion_ONOFF;
	bool last_Distortion_Type;
	bool Distortion_Type;
	//float Distortion_Gain;
	uint8_t Distortion_Gain;
	uint8_t Distortion_EffectPosition;
	bool Distortion_EffectAdded;

	//Tremolo
	bool Tremolo_ONOFF;
	//float Tremolo_Rate;
	uint8_t Tremolo_Rate;
	float Tremolo_Depth;
	uint8_t Tremolo_EffectPosition;
	bool Tremolo_EffectAdded;
	bool Filter_ONOFF[5];
	float Filter_Cutoff[5];
	float Filter_Q[5];
	float Filter_Gain[5];
	uint8_t currentBand;
	uint8_t Filter_EffectPosition;
	bool Filter_EffectAdded;
	uint16_t lastState;
	//...Weitere Synthesizer-Parameter

	uint8_t last_note;
	uint8_t note;
	char last_octave;
	char octave;
	uint16_t last_rate;
	uint16_t rate;
	uint16_t last_depth;
	uint16_t depth;
	uint32_t last_cutoff;
	uint32_t cutoff;
	uint16_t last_Q;
	uint16_t Q;
	uint16_t last_distortion_gain;
	uint16_t distortion_gain;
	uint16_t last_attack;
	uint16_t attack;
	uint16_t last_decay;
	uint16_t decay;
	uint16_t last_sustain;
	uint16_t sustain;
	uint16_t last_release;
	uint16_t release;

	// ADC input arrays
	uint32_t ADC1input;
	uint16_t ADC2inputs[3];
	uint16_t ADC3inputs[2];

	// Joystick-variables
	uint16_t LowerLimit;
	uint16_t UpperLimit;
	uint16_t ADC_FullRange;
	uint16_t VRx;
	uint16_t VRy;
	uint8_t JoystickPatchPosition;
	uint8_t JoystickModePosition;
	uint8_t last_JoystickModePosition;
	uint8_t JoystickParameterPosition;
	uint8_t last_JoystickParameterPosition;
	uint16_t last_joystick_x;
	uint16_t last_joystick_y;
	uint16_t UpdateThreshold;

	//Draw Parameters
	bool arrow_flag;
	uint8_t arrow_start_x_position;
	uint8_t arrow_end_x_position;
	uint8_t value_start_x_position;
	uint8_t value_end_x_position;
	uint8_t row_start_x_position;
	uint8_t row_end_x_position;

	//Page parameter
	int8_t pagePosition;
	uint8_t page_max;
	uint8_t page_min;
	// Potentiometer-variables
	uint16_t Poti_raw;
	float Poti_percent;
	int progress_bar;
	uint16_t last_Poti;
	uint16_t Poti_Threshold;

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
EPD epd;
Paint paint;
unsigned char* frame_buffer;

Display_Status Display_Init(struct display_variables* Display);
Display_Status Display_Start(EPD* epd, Paint* paint, unsigned char* frame_buffer);
Display_Status PatchSelectionMenu(struct display_variables* Display, Paint paint, EPD epd, unsigned char* frame_buffer);
//void SetParameters(struct display_variables* Display, struct signal_t* signals, struct BQFilter* Filter, struct adsr* envelope, struct effects_distortion* SoftClipping, struct effects_distortion* HardClipping, struct effects_LFO* Tremolo, Paint paint, EPD epd, unsigned char* frame_buffer);


//Display draw functions
void DISPLAY_ArrowDown(uint8_t *JoystickParameterPosition);
void DISPLAY_ArrowUp(uint8_t *JoystickParameterPosition);
void DISPLAY_SwitchPageLeft(void);
void DISPLAY_SwitchPageRight(void);
void DISPLAY_Update(void);
void DISPLAY_DrawArrow(uint8_t JoystickParameterPosition);

//Page functions
void DISPLAY_processing(void);
Display_Status p_StartingMenu(unsigned char* frame_buffer);
void p_Voices(void);
void p_Distortion(struct effects_distortion* HardClipping);
void p_Tremolo(struct Tremolo_t* Tremolo);
void p_Equalizer_Settings();
void p_KeyboardSetParameters(struct adsr* envelope);
void p_Dummy(void);
void p_Equalizer_overview();

#endif /* INC_DISPLAY_H_ */
