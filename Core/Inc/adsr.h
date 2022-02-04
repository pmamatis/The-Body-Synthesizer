/**
 * @file adsr.h
 * @author Marc Bielen
 * @brief adsr effect header
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ADSR_H
#define ADSR_H

#include "main.h"
/**
 * @defgroup ADSR ADSR Effect
 * @ingroup Effects
 * @brief Attack-Decay-Sustain-Release
 * @{
 */

/***************************
 * @brief Enumeration for ADSR Debugging
 ***************************/
typedef enum {
	ADSR_FAIL = -1,
	ADSR_OK = 1
} ADSR_Status;

/*********************************
 * @brief	Structs
 *********************************/
/**
 * @brief stores the state of the ADSR values for keyboardand sequencer structs as well as the configuration
 * 
 */
struct adsr {
	uint32_t adsr_counter;
	float adsr_max_amp;
	float adsr_duration_time;
	float adsr_attack_time;
	float adsr_decay_time;
	float adsr_sustain_time;
	float adsr_sustain_amplitude;
	float adsr_release_time;

	float adsr_maximum_attack;
	float adsr_maximum_decay;
	float adsr_maximum_sustaintime;
	float adsr_maximum_release;

	bool adsr_done;
};



/*********************************
 * @brief	Variables
 *********************************/

/**
 * @brief ADSR for the Voice notes 
 */
struct adsr envelope;

/** 
 * @defgroup ADSR Sequencer ADSR
 * @brief ADSR storage for sequencer notes
 * @note  Length 16 is max. time steps: 1/16, 1/8, 1/4
 * @{
 */
struct adsr adsr_SN1[16];
struct adsr adsr_SN2[16];
struct adsr adsr_SN3[16];
struct adsr adsr_SN4[16];
/** @} */

/**
 * @brief  ADSR storage for the keyboard
 * 
 */
struct adsr adsr_keyboard[5];	// maximum 5 keys processed simultaneously


/*********************************
 * @brief	Functions
 *********************************/
ADSR_Status ADSR_Init(void);
ADSR_Status SetupADSR(struct adsr* envelope);
ADSR_Status ADSR_Reset(struct adsr* envelope);
void OnePress_ADSR_Linear_Process(struct adsr* envelope, float* calculate_value, bool flag);
void OnePress_ADSR_Sequencer_Process(struct adsr* envelope, float* calculate_value, bool flag);

/** @}*/
#endif
