/**
 ******************************************************************************
 * @file    adsr.h
 * @author  Marc Bielen
 * @date 	28 May 2020
 * @brief	ADSR-Library
 */

#ifndef ADSR_H
#define ADSR_H

#include "main.h"

/***************************
 * @brief Enumeration for ADSR Debugging
 ***************************/
typedef enum {
	ADSR_FAIL = -1,
	ADSR_OK = 1
} ADSR_Status;

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

	uint32_t decay_counter;
	uint32_t release_counter;
};

struct adsr envelope;

// ADSR for sequencer notes
// Length 16 is max. time steps: 1/16, 1/8, 1/4
struct adsr adsr_SN1[16];
struct adsr adsr_SN2[16];
struct adsr adsr_SN3[16];
struct adsr adsr_SN4[16];

//bool envelope_done;	// flag for keyboard to delete signal

ADSR_Status ADSR_Init(void);
ADSR_Status SetupADSR(struct adsr* envelope);
//void ADSR_Linear_Process(struct adsr* envelope, float* calculate_value, struct signal_t* signals);
void OnePress_ADSR_Linear_Process(struct adsr* envelope, float* calculate_value, bool flag);
extern inline float exp1(float x);

#endif
