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
/** Difference of starting point and end point for Value-row
 */
#define VALUE_ROW_LENGTH 10

//#define NUMBER_OF_SOURCES 5	// as big as the number of sources in source_t enum
#define NUMBER_OF_SOURCES 3

// Voices
#define NUMBER_OF_VOICES 3

// Drumcomputer
#define MAX_NUMBER_OF_SAMPLES 4
#define NUMBER_OF_DRUMSTEPS 8

// Sequencer
#define MAX_NUMBER_OF_NOTES 3
#define NUMBER_OF_SEQUENCERSTEPS 8


typedef enum {	// Waveshare 2.9 inch ePD
	CASE0 = 10,
	CASE1 = 20,
	CASE2 = 30,
	CASE3 =	40,
	CASE4 =	50,
	CASE5 =	60,
	CASE6 =	70,
	CASE7 =	80,
	CASE8 =	90,
	CASE9 =	100,
}y_row_value;

//typedef enum {	// Waveshare 1.54 inch ePD
//	CASE0 = 10,
//	CASE1 = 30,
//	CASE2 = 50,
//	CASE3 =	70,
//	CASE4 =	90,
//	CASE5 =	110,
//	CASE6 =	130,
//	CASE7 =	150,
//	CASE8 =	170,
//	CASE9 =	190,
//}y_row_value;

typedef enum {
	STEP1 = 40,
	STEP2 = 60,
	STEP3 = 80,
	STEP4 = 100,
	STEP5 = 120,
	STEP6 = 140,
	STEP7 = 160,
	STEP8 = 180
} drumcomputer_step_coordinate;

typedef enum {
	DISPLAY_FAIL = -1,
	DISPLAY_OK = 1
} Display_Status;

typedef enum {
	NONE = -1,
	KEYBOARD = 0,
	BODYSYNTH = 1,
}synth_mode_t;

typedef enum {
	POTI = 0,
	GYRO_LR = 1,
	GYRO_FB,
	EMG,
	EKG,
	DISTANCE
}source_t;

//static const char * const source_names[] = {
//		[GYRO_LEFT] = "Gyro L",
//		[GYRO_RIGHT] = "Gyro R",
//		[GYRO_FRONT] = "Gyro F",
//		[GYRO_BACK] = "Gyro B",
//		[EMG] = "EMG",
//		[EKG] = "EKG",
//		[POTI] = "POTI"
//};

struct display_variables {

	char source_names[NUMBER_OF_SOURCES][10];	// assumption: maximum length of 10 characters for a each source name

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
	// Voices
	uint8_t ActiveEffectsCounter;
	bool Voices_ONOFF[NUMBER_OF_VOICES];
	char Voices_Note[NUMBER_OF_VOICES];
	char last_Voices_Note[NUMBER_OF_VOICES];
	char Voices_Octave[NUMBER_OF_VOICES];
	char last_Voices_Octave[NUMBER_OF_VOICES];
	float noteindex;
	bool Voices_Created[NUMBER_OF_VOICES];
	uint8_t currentVoice;
	uint8_t Voices_Noteindex[NUMBER_OF_VOICES];
	uint8_t last_Voices_Noteindex[NUMBER_OF_VOICES];
//	float Voices_Volume;
	uint8_t Voices_Kind[NUMBER_OF_VOICES];

	// Noise
	bool Noise_ONOFF;
	float Noise_Volume;

	//ADSR
	float ADSR_Attacktime;
	float ADSR_Decaytime;
	float ADSR_Sustaintime;
	float ADSR_Sustainlevel;
	float ADSR_Releasetime;
	uint8_t ADSR_EffectPosition;
	bool ADSR_EffectAdded;
	uint8_t currentADSR;

	//Distortion
	bool Distortion_ONOFF;
	bool last_Distortion_ONOFF;
	bool last_Distortion_Type;
	bool Distortion_Type;
	float Distortion_Gain;
	uint8_t Distortion_EffectPosition;
	bool Distortion_EffectAdded;
	uint8_t currentDistortion;

	//Tremolo
	bool Tremolo_ONOFF;
	bool last_Tremolo_ONOFF;
	float Tremolo_Rate;
	float Tremolo_Depth;
	uint8_t Tremolo_EffectPosition;
	bool Tremolo_EffectAdded;
	uint8_t currentTremolo;
	uint16_t Tremolo_Rate_Index;
	uint16_t last_Tremolo_Rate_Index;

	//Filter/EQ
	bool Filter_ONOFF[5];
	float Filter_Cutoff[5];
	float Filter_Q[5];
	float Filter_Gain[5];
	uint8_t currentBand;
	uint8_t Filter_EffectPosition;
	bool Filter_EffectAdded;
	uint16_t lastState;

	// WahWah
	bool WahWah_ONOFF;
	float WahWah_LFOdepth;
	float WahWah_LFOfreq;
	float WahWah_Range;
	float WahWah_MidFreq;
	float WahWah_Q;
	uint8_t currentWahWah;
	uint16_t WahWah_LFOfreq_Index;
	uint16_t last_WahWah_LFOfreq_Index;

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
	uint16_t ADC2inputs[4];
	uint16_t ADC3inputs[2];

	// Joystick-variables
	uint16_t JoystickMiddle;
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
	int8_t page_min;
	uint8_t max_parameter;

	// Potentiometer-variables
	uint16_t Poti_raw;
	float Poti_percent;
	int progress_bar;
	uint16_t last_Poti;
	uint16_t Poti_Threshold;
	bool poti_moved;
	uint16_t PotiMean_tmp;
	uint16_t PotiMean;
	uint16_t PotiMean_counter;

	// EMG-Sensor-variables
	uint16_t EMG_DC;
	uint16_t EMG_AC;

	// Gyro-Sensor-variables
	uint16_t GyroX;
	uint16_t GyroY;
	uint16_t GyroZ;
	uint8_t Gyro_select;
	bool Gyro_ON;
	bool ENTER_Debounce_State;
	bool BACK_Debounce_State;
	bool SW_Debounce_State;
	bool ENTER;		// state variable of the ENTER-Button to go one step further in the display-menu
	bool BACK;		// state variable of the BACK-Button to go one step back in the display-menu
	bool SW;		// state variable of the SW-Button of the Joystick
	bool button_pressed_flag;

	// SOURCES
	source_t Voice_Note_Sources[3];				// sources for note of Voice 1,2 and 3
	source_t Voice_Octave_Sources[3];			// sources for octave of Voice 1,2 and 3
	source_t ADSR_Sources[5];					// sources for attack time, decay time, sustain time, sustain level, release time
	source_t EQ_Q_factor_Sources[5];			// sources for q-factor of 5 frequency bands
	source_t EQ_Cutoff_Sources[5];				// sources for cutoff of 5 frequency bands
	source_t EQ_Gain_Sources[5];				// sources for gain of 5 frequency bands
	source_t WahWah_Sources[4];					// sources for wahwah parameters
	source_t Distortion_Sources;				// sources for gain
	source_t Tremolo_Sources[2];				// sources for rate and depth
	source_t Drumfilter_Cutoff_Source;			// source for drumfilter cuttoff
	// page value strings
	char value_str_dummy[9][10];	// 9 rows and maximum 10 characters
	char value_str_voices_overview[6][10];
	char value_str_voices_settings[4][9][10];
	char value_str_adsr_overview[6][10];
	char value_str_adsr_settings[5][10];
	char value_str_equalizer_overview[6][10];
	char value_str_equalizer_settings[5][6][10];
	char value_str_wahwah[15][10];
	char value_str_distortion[5][10];
	char value_str_tremolo[6][10];
	char value_str_volume[4][10];
	char value_str_presets[2][10];
	char value_str_keyboardmode[9][10];
	char value_str_drumcomputer[11][10];
	char value_str_sequencer[9][10];
	char value_str_emg[3][10];

	// Drumcomputer
	uint8_t lastCurrentSampleRow;
	uint8_t CurrentSampleRow;
	uint8_t lastCurrentDrumstep;
	uint8_t CurrentDrumstep;
	bool DrumMatrix[MAX_NUMBER_OF_SAMPLES][NUMBER_OF_DRUMSTEPS];
	bool UpdateDisplay;
	bool Drumcomputer_ONOFF;
	bool EditDrums;
	uint8_t currentDrumcomputer;
	char sample1[10], sample2[10], sample3[10], sample4[10];
	bool LoadDrumkit;
	float Drumfilter_Cutoff;
	float Drumfilter_Q;
	float Drumfilter_Gain;
	bool realtimeBPM_ONOFF; // heartbeat from EMG-Board as bpm for Drumcomputer
	// Sequencer
	uint8_t CurrentNoteRow;
	uint8_t CurrentSequencestep;
	bool Sequencer_ONOFF;
	char Sequencer_Note[4];
	char Sequencer_Octave[4];
	char last_Sequencer_Octave[4];
	bool SequencerMatrix[MAX_NUMBER_OF_NOTES][NUMBER_OF_SEQUENCERSTEPS];
	bool EditSteps;
	uint8_t currentSequencer;
	uint8_t Sequencer_Noteindex[3];
	uint8_t last_Sequencer_Noteindex[3];

	// WahWah
	uint8_t WahWah_Mode;

	// Play Single Sample
	bool PlaySingleSample_ONOFF;

	// Drumfilter_ONOFF
	bool Drumfilter_ONOFF;

	// Preset
	bool GyroResetPreset[2];

	// Reset
	bool Reset;
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
void DISPLAY_PrintCurrentPage(void);
void DISPLAY_ArrowDown(uint8_t *JoystickParameterPosition);
void DISPLAY_ArrowUp(uint8_t *JoystickParameterPosition);
void DISPLAY_SwitchPageLeft(void);
void DISPLAY_SwitchPageRight(void);
void DISPLAY_Update(void);
void DISPLAY_DrawArrow(uint8_t JoystickParameterPosition);


// Display Drum Computer
Display_Status Display_DrawDrumcomputerIcons(char* S1, char* S2, char* S3, char* S4);
Display_Status Display_LoadDrumKits(uint8_t Drumkit);
Display_Status DISPLAY_DrawDrumcomputerPatternFrame(uint8_t Drumsteps);
Display_Status DISPLAY_DrawDrumcomputerPattern(void);
Display_Status DISPLAY_SetDrumcomputerStep(void);
Display_Status DISPLAY_DeleteDrumcomputerStep(void);
Display_Status DISPLAY_SetDrumcomputerStepCursor(void);
Display_Status DISPLAY_DeleteDrumcomputerStepCursor(void);


// Display Sequencer
Display_Status Display_DrawSequencerIcons(void);
Display_Status DISPLAY_DrawSequencerPatternFrame(uint8_t Drumsteps);
Display_Status DISPLAY_DrawSequencerPattern(void);
Display_Status DISPLAY_SetSequencerStep(void);
Display_Status DISPLAY_DeleteSequencerStep(void);
Display_Status DISPLAY_SetSequencerStepCursor(void);
Display_Status DISPLAY_DeleteSequencerStepCursor(void);


//Page functions
void DISPLAY_processing(void);
Display_Status p_StartingMenu(unsigned char* frame_buffer);
void p_Voices_overview(void);
void p_Voices_Settings(void);
//void p_ADSR_overview(struct adsr* envelope);
void p_ADSR_overview(void);

void p_ADSR_Settings(void);
void p_Equalizer_overview(void);
void p_Equalizer_Settings(void);
void p_WahWah_overview(void);
void p_WahWah_Settings(struct WahWah_t *WahWah);
//void p_WahWah(struct WahWah_t *WahWah);
void p_Distortion(struct effects_distortion* HardClipping);
void p_Tremolo(struct Tremolo_t* Tremolo);
void p_EMG(void);
void p_Volume(void);
void p_Presets(void);
void p_KeyboardSetParameters(struct adsr* envelope);
Display_Status p_Drumcomputer_overview(void);
Display_Status p_Drumcomputer_Settings(void);
Display_Status p_Sequencer_overview(void);
Display_Status p_Sequencer_Settings(void);

void p_Dummy(void);

#endif /* INC_DISPLAY_H_ */
