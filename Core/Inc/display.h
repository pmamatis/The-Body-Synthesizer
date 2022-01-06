#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include <stdbool.h>

#include "epd1in54.h"
#include "epdif.h"
#include "epdpaint.h"
#include "imagedata.h"

/*********************************
 * @brief		Defines
 *********************************/

#define COLORED      0
#define UNCOLORED    1

#define VALUE_ROW_LENGTH 10	// Difference of starting point and end point for Value-row

#define NUMBER_OF_SOURCES 3	// As big as the number of sources in source_t enum

// Voices
#define NUMBER_OF_VOICES 3

// Drumcomputer
#define MAX_NUMBER_OF_SAMPLES 4
#define NUMBER_OF_DRUMSTEPS 8

// Sequencer
#define MAX_NUMBER_OF_NOTES 3
#define NUMBER_OF_SEQUENCERSTEPS 8

/***************************
 * @brief		Enumeration
 ***************************/

//typedef enum {	// Waveshare 2.9 inch ePD
//	CASE0 = 10,
//	CASE1 = 20,
//	CASE2 = 30,
//	CASE3 =	40,
//	CASE4 =	50,
//	CASE5 =	60,
//	CASE6 =	70,
//	CASE7 =	80,
//	CASE8 =	90,
//	CASE9 =	100,
//	CASE10 = 110
//}y_row_value;



typedef enum {	// Waveshare 1.54 inch ePD
	CASE0 = 10,
	CASE1 = 30,
	CASE2 = 50,
	CASE3 =	70,
	CASE4 =	90,
	CASE5 =	110,
	CASE6 =	130,
	CASE7 =	150,
	CASE8 =	170,
	CASE9 =	190,
	CASE10 = 210
} y_row_value;

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
	POTI = 0,
	GYRO_LR = 1,
	GYRO_FB = 2
} source_t;

typedef enum {
	FREESTYLE = 0,
	MAJOR = 1,
	MINOR = 2
} keyandmode_t;

/***************************
 * @brief		Structs
 ***************************/

/**
 * @brief struct for all variables related to the display, 
 * 
 */
struct display_variables {

	char source_names[NUMBER_OF_SOURCES][10];	// assumption: maximum length of 10 characters for a each source name

	// Keyboard Parameters
	uint8_t Keyboard_Octave;

	// Synthesizer Parameters
	// Voices
	bool Voices_ONOFF[NUMBER_OF_VOICES];
	char Voices_Note[NUMBER_OF_VOICES];
	char last_Voices_Note[NUMBER_OF_VOICES];
	char Voices_Octave[NUMBER_OF_VOICES];
	char last_Voices_Octave[NUMBER_OF_VOICES];
	bool Voices_Created[NUMBER_OF_VOICES];
	uint8_t currentVoice;
	uint8_t Voices_Noteindex[NUMBER_OF_VOICES];
	uint8_t last_Voices_Noteindex[NUMBER_OF_VOICES];
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
	uint8_t currentADSR;
	bool KeyboardFX_ONOFF;

	//Distortion
	bool Distortion_ONOFF;
	bool Distortion_Type;
	float Distortion_Gain;
	uint8_t currentDistortion;

	//Tremolo
	bool Tremolo_ONOFF;
	bool last_Tremolo_ONOFF;
	float Tremolo_Rate;
	float Tremolo_Depth;
	uint8_t currentTremolo;
	uint16_t Tremolo_Rate_Index;
	uint16_t last_Tremolo_Rate_Index;

	//Filter/EQ
	bool Filter_ONOFF[5];
	float Filter_Cutoff[5];
	float Filter_Q[5];
	float Filter_Gain[5];
	uint8_t currentBand;

	// WahWah
	bool WahWah_ONOFF;
	float WahWah_LFOfreq;
	float WahWah_Range;
	float WahWah_MidFreq;
	float WahWah_Q;
	uint8_t currentWahWah;
	uint16_t WahWah_LFOfreq_Index;
	uint16_t last_WahWah_LFOfreq_Index;

	// ADC input arrays
	uint32_t ADC1input;
	uint16_t ADC2inputs[4];

	// Joystick-variables
	uint16_t JoystickMiddle;
	uint16_t LowerLimit;
	uint16_t UpperLimit;
	uint16_t ADC_FullRange;
	uint16_t VRx;
	uint16_t VRy;
	uint8_t JoystickParameterPosition;

	// Draw Parameters
	bool arrow_flag;
	uint8_t arrow_start_x_position;
	uint8_t arrow_end_x_position;
	uint8_t value_start_x_position;
	uint8_t value_end_x_position;
	uint8_t row_start_x_position;

	// Page parameters
	int8_t pagePosition;
	uint8_t page_max;
	int8_t page_min;
	uint8_t max_parameter;

	// Potentiometer-variables
	uint16_t last_Poti;
	uint16_t Poti_Threshold;
	bool poti_moved;
	uint16_t PotiMean_tmp;
	uint16_t PotiMean;
	uint16_t PotiMean_counter;

	bool ENTER_Debounce_State;
	bool BACK_Debounce_State;
	bool ENTER;		// state variable of the ENTER-Button to go one step further in the display-menu
	bool BACK;		// state variable of the BACK-Button to go one step back in the display-menu
	bool button_pressed_flag;

	// SOURCES
	source_t Voice_Note_Sources[3];				// sources for note of Voice 1,2 and 3
	source_t Voice_Octave_Sources[3];			// sources for octave of Voice 1,2 and 3
	source_t ADSR_Sources[5];					// sources for attack time, decay time, sustain time, sustain level, release time
	source_t EQ_Q_factor_Sources[5];			// sources for q-factor of 5 frequency bands
	source_t EQ_Cutoff_Sources[5];				// sources for cutoff of 5 frequency bands
	source_t EQ_Gain_Sources[5];				// sources for gain of 5 frequency bands
	source_t WahWah_Sources[6];					// sources for wahwah parameters
	source_t Distortion_Sources;				// sources for gain
	source_t Tremolo_Sources[2];				// sources for rate and depth
	source_t Drumfilter_Cutoff_Source;			// source for drumfilter cuttoff

	// Page value strings
	char value_str_voices_overview[6][10];
	char value_str_voices_settings[4][9][10];
	char value_str_adsr_overview[7][10];
	char value_str_adsr_settings[5][10];
	char value_str_equalizer_overview[6][10];
	char value_str_equalizer_settings[5][6][10];
	char value_str_wahwah[15][10];
	char value_str_distortion[5][10];
	char value_str_tremolo[6][10];
	char value_str_volume[4][10];
	char value_str_presets[9][10];
	char value_str_keyboardmode[9][10];
	char value_str_drumcomputer[12][10];
	char value_str_sequencer[9][10];
	char value_str_emg[5][10];
	char value_str_ecg[2][10];
	char value_str_keyandmode[2][10];

	// Drumcomputer
	uint8_t CurrentSampleRow;
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
	bool Drumcomputer_BPMbyECG_ONOFF; // heartbeat from EMG/ECG-Board as bpm for Drumcomputer
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

	// EMG / ECG
	float EMG_detectionThreshold;
	float EMG_toggleThreshold;
	float ECG_detectionThreshold;
	float ECG_toggleThreshold;

	// Key and Mode
	char KeyNote;
	uint8_t KeyNoteIndex;
	keyandmode_t ScaleMode;

	// Play Single Sample
	bool PlaySingleSample_ONOFF;
	uint8_t SingleSampleKit;
	uint8_t SingleSample;

	// Drumfilter
	bool Drumfilter_ONOFF;

	// Preset
	bool GyroResetPreset[2];

	// Reset
	bool Reset;

	// SetPreset
	bool SetPreset;
};

struct display_variables Display;
EPD epd;
Paint paint;
unsigned char* frame_buffer;

Display_Status Display_Init(struct display_variables* Display);

Display_Status Display_Start(EPD* epd, Paint* paint, unsigned char* frame_buffer);

// Display draw functions
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


// Page functions
void DISPLAY_processing(void);
Display_Status p_StartingMenu(unsigned char* frame_buffer);
void p_Voices_overview(void);
void p_Voices_Settings(void);
void p_ADSR_overview(void);
void p_ADSR_Settings(void);
void p_Equalizer_overview(void);
void p_Equalizer_Settings(void);
void p_WahWah_overview(void);
void p_WahWah_Settings(struct WahWah_t *WahWah);
void p_Distortion(struct effects_distortion* HardClipping);
void p_Tremolo(struct Tremolo_t* Tremolo);
void p_EMG(void);
void p_KeyAndMode(void);
Display_Status Display_LoadSingleSample(uint8_t SampleNUM, uint8_t KitNUM);
void p_Volume(void);
void Full_Reset(void);
void p_Presets(void);
Display_Status p_Drumcomputer_overview(void);
Display_Status p_Drumcomputer_Settings(void);
Display_Status p_Sequencer_overview(void);
Display_Status p_Sequencer_Settings(void);

#endif /* INC_DISPLAY_H_ */
