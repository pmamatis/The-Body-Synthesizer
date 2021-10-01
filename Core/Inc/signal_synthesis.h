/**
 ******************************************************************************
 * @file    signal_sythesis.c
 * @author  Paul Mamatis
 * @date 	27 Apr 2020
 * @brief	Signal sythesis for HAL-Libary on Nucleo-144 F4.....
 *
 *@todo implement 	SAWTOOTH, TRIANGLE, PWM in signal_sythesis function
 */

#ifndef INC_SIGNAL_SYNTHESIS_H_
#define INC_SIGNAL_SYNTHESIS_H_

#include <math.h>
#include "main.h"
#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include "display.h"

/**@brief maximal amplitude of output voltage in millivolts*/
#define AMPLITUDE 	2000
/**@brief digital DAC value for maximal output voltage (3,3V) */
#define DAC_MAX 	4095
/** @brief digital value for 100mV */
//#define OFFSET 		145
#define OFFSET 2047
/**@brief 4096/3300 */
#define DAC_MAXVALUE_TO_AMPLITUDE_RATIO  1.24121212121212

/**@brief Maximum of SIgnals which can be played at the same time */
#define MAX_SIGNAL_KOMBINATION 30

/**@brief struct to store signals
 * @param count: amount of signals
 * @param max: global Maximum of all added Signals, set to zero when construct or destruct a Signal
 * @param kind:
 * @param freq:
 * @param freqIndex:
 * @param
 * @param ID: indicates the Signal where it comes from. 0-2 Synthesizer Voices. 3-5 Keyboard notes,
 * */
struct signal_t{
	//globals
	uint8_t count;
	float max;

	//part of a Signal Object
	unsigned int kind[MAX_SIGNAL_KOMBINATION];
	double freq[MAX_SIGNAL_KOMBINATION];
	uint8_t freqIndex[MAX_SIGNAL_KOMBINATION];
	uint32_t current_LUT_Index[MAX_SIGNAL_KOMBINATION];
	//ID's 0-2 Synthesizer Voices. 3-5 Keyboard notes, 5 < open
	uint8_t ID[MAX_SIGNAL_KOMBINATION];
	uint8_t channel[MAX_SIGNAL_KOMBINATION];
};
/**@brief Array to monitor which ID's are taken, taken = 1; free = 0 */
uint8_t ID_array[MAX_SIGNAL_KOMBINATION];


/** defines volume of the Voices, Drummachine and Sequencer
 * 0 -> Voices
 * 1 -> Drums
 * 2 -> Sequencer
 * */
float volume[3];

float calculate_keyboard[3];
/** should avoid Plop sound after finishing the Keyboard sound */
uint32_t noPlopOffset;

//Effects//Effects
enum effects_using_LFO{
	TREMOLLO = 0,
};
//Effects
struct effects_lfo_t{

	uint32_t lfo_index;
	uint8_t lfo_quarter;
	uint32_t lfo_blocksizecounter;
	float lfo_frequency;
	float lfo_data;
	float lfo_depth;
};

struct effects_lfo_t lfo_tremolo;
struct effects_lfo_t lfo_wahwah;

enum singnal_synthesis_enum{
	note_key = 0,
	mixed
};

/**@brief Signal kinds*/
enum signal_kind_enum{
	SIN = 1,
	SAWTOOTH,
	TRIANGLE,
	PWM,
	NOISE
};

//Variables
float lfo_value;

uint8_t output_Channel;
/** @brief Position of the DMA Output Buffer, can be HALF_BLOCK or FULL_BLOCK */
uint8_t outputBuffer_position;

struct signal_t signals1;
struct signal_t signals2;

///** defines volume of the Voices, Drummachine and Sequencer
// * 0 -> Voices
// * 1 -> Drums
// * 2 -> Sequencer
// * */
//float volume[3];

//functions
HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac);
void SetTimerSettings(TIM_HandleTypeDef* htim, uint32_t SR);
void Signal_Synthesis(struct signal_t* signals,uint8_t output_Channel);
void DeleteSignal(struct signal_t* signals,uint8_t signal_index);
//void NewSignal(struct signal_t* signals, uint8_t kind, uint8_t key, uint8_t octave);
void NewSignal(struct signal_t* signals, uint8_t kind, uint8_t key, uint8_t octave, uint8_t ID);
void Signal_Synthesis_LFO(struct effects_lfo_t* effect);
void LFO_SingleValueProcess(struct effects_lfo_t* lfo) ;
float AWGN_generator(void);
uint8_t IDtoIndex(uint8_t ID);

#endif /* INC_SIGNAL_SYNTHESIS_H_ */
