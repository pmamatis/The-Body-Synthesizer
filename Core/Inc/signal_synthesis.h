/**
 * @file signal_synthesis.h
 * @author max lehmer & marc bielen & paul mamatis
 * @brief sound synthesis, (Signals + Effects) -> DAC
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INC_SIGNAL_SYNTHESIS_H_
#define INC_SIGNAL_SYNTHESIS_H_

#include <math.h>
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "display.h"

/*********************************
 * @brief		Defines
 *********************************/

/** @brief maximal amplitude of output voltage in millivolts*/
#define AMPLITUDE 	1000
/** @brief digital DAC value for maximal output voltage (3,3V) */
#define DAC_MAX 	4095
/** @brief digital value for 1.65 V */
#define OFFSET 2047
/** @brief 4096/3300 */
#define DAC_MAXVALUE_TO_AMPLITUDE_RATIO  1.24121212121212

/**@brief Maximum of SIgnals which can be played at the same time */
#define MAX_SIGNAL_KOMBINATION 30

/*********************************
 * @brief		Structs
 *********************************/

/**
 * @brief struct to store signals
 * @param count: amount of signals
 * @param max: global Maximum of all added Signals, set to zero when construct or destruct a Signal
 * @param kind: kind of the signal, e.g. sinus, triangle, noise etc.
 * @param freq: frequency
 * @param freqIndex: starting index of the LUT for the gicen frequency, all LUT's for all predefiend frequencys are in the same array
 * @param current_LUT_Index: last used LUT index, neccessary to write the signal in arrays which are smaller or bigger than the LUT samples
 * @param ID: indicates the Signal where it comes from. 0-2 Synthesizer Voices. 3-5 Keyboard notes,
 * */
struct signal_t{
	uint8_t count;
	float max;
	//part of a Signal Object
	unsigned int kind[MAX_SIGNAL_KOMBINATION];
	double freq[MAX_SIGNAL_KOMBINATION];
	uint8_t freqIndex[MAX_SIGNAL_KOMBINATION];
	uint32_t current_LUT_Index[MAX_SIGNAL_KOMBINATION];
	//ID's 0-2 Synthesizer Voices. 3-5 Keyboard notes, 5 < open
	uint8_t ID[MAX_SIGNAL_KOMBINATION];
};



//Effects
struct effects_lfo_t{

	uint32_t lfo_index;
	uint8_t lfo_quarter;
	float lfo_frequency;
	float lfo_data;
	float lfo_depth;
	bool lfo_done_flag;
};


/*********************************
 * @brief		Enums
 *********************************/
/**@brief Signal kinds*/
enum signal_kind_enum{
	SIN = 1,
	RECT,
	TRIANGLE,
	NOISE
};

enum lfo_effect{
	TREMOLO_LFO = 0,
	WAHWAH_LFO
};


/*********************************
 * @brief	Variables	
 *********************************/
struct signal_t signals1;
struct effects_lfo_t lfo_tremolo;
struct effects_lfo_t lfo_wahwah;

/** defines volume of the Voices, Drummachine and Sequencer
 * 0 -> Voices
 * 1 -> Drums
 * 2 -> Sequencer
 * */
float volume[4];
/** Volume applied at the end, to prevent clipping */
float Master_Volume;

float calculate_keyboard[5];

/** @brief Position of the DMA Output Buffer, can be HALF_BLOCK or FULL_BLOCK */
uint8_t outputBuffer_position;

/*********************************
 * @brief		Functions
 *********************************/
HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac);
HAL_StatusTypeDef Voices_Reset(void);
void SetTimerSettings(TIM_HandleTypeDef* htim, uint32_t SR);
void Signal_Synthesis(struct signal_t* signals,uint8_t output_Channel);
void DeleteSignal(struct signal_t* signals,int16_t signal_index);
void NewSignal(struct signal_t* signals, uint8_t kind, uint8_t key, uint8_t octave, uint8_t ID);
void LFO_SingleValueProcess(struct effects_lfo_t* lfo, uint8_t lfo_effect);
float CalcRectSample(struct signal_t* signals, int index);
float CalcTriangleSample(struct signal_t* signals, int index);
float Noise_Generator(void);
int16_t IDtoIndex(int16_t id);
bool initRamp(void);

#endif /* INC_SIGNAL_SYNTHESIS_H_ */
