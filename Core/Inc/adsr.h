#ifndef ADSR_H
#define ADSR_H

#include "main.h"

/***************************
 * @brief Enumeration for Tremolo Debugging
 ***************************/
typedef enum {
	ADSR_FAIL = -1,
	ADSR_OK = 1
} ADSR_Status;

struct adsr {
	uint32_t adsr_counter;
	//int adsr_counter;
	float adsr_max_amp;
	float adsr_duration_time;
	float adsr_attack_time;
	float adsr_decay_time;
	float adsr_sustain_amplitude;
	float adsr_release_time;

	float adsr_maximum_attack;
	float adsr_maximum_decay;
};

struct adsr envelope;

/* adsr envelope.
maxamp: maximum amplitude
dur: total duration (s)
at: attack time (s)
dt: decay time (s)
sus: sustain amplitude
rt: release time (s)
cnt: time index
cr: control rate
returns: output control sample*/

ADSR_Status ADSR_Init(void);
ADSR_Status SetupADSR(struct adsr* envelope);
float ADSR_Linear_Process(struct adsr* envelope);

#endif
