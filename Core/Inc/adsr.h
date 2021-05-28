#ifndef ADSR_H
#define ADSR_H

#include "main.h"

struct adsr {
	uint32_t adsr_counter;
	//int adsr_counter;
	float adsr_max_amp;
	float adsr_duration_time;
	float adsr_attack_time;
	float adsr_decay_time;
	float adsr_sustain_amplitude;
	float adsr_release_time;
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
void adsr_linear_init(struct adsr* envelope);
float adsr_linear_process(struct adsr* envelope);
void adsr_log_init(struct adsr* envelope);
float adsr_log_process(struct adsr* envelope);

#endif
