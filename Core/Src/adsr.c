#include "adsr.h"
//#include "math.h"

// Reference: The Audio Programming Book from Boulanger, Lazzarini and Mathews

ADSR_Status ADSR_Init(void) {

	SetupADSR(&envelope);

	return ADSR_OK;
}

ADSR_Status SetupADSR(struct adsr* envelope) {

	envelope->adsr_counter = 0;
	envelope->adsr_max_amp = 0.75;	// maximum value should be 1
	envelope->adsr_duration_time = 1.0 * LUT_SR;	// first number in seconds
	envelope->adsr_attack_time = 0.15 * LUT_SR;
	envelope->adsr_decay_time = 0.3 * LUT_SR;
	envelope->adsr_sustain_amplitude = 0.5;
	envelope->adsr_release_time = 0.25 * LUT_SR;

	envelope->adsr_maximum_attack = 0.25;	// in seconds; maximum 4.0 seconds, to display the value -> uint8_t
	envelope->adsr_maximum_decay = 0.4;

	return ADSR_OK;
}

float ADSR_Linear_Process(struct adsr* envelope) {

	float calc;

	if(envelope->adsr_counter < envelope->adsr_duration_time) { // if time < total duration

		// attack period
		if(envelope->adsr_counter <= envelope->adsr_attack_time)
			calc = envelope->adsr_counter * (envelope->adsr_max_amp/envelope->adsr_attack_time);

		// decay period
		else if(envelope->adsr_counter <= (envelope->adsr_attack_time + envelope->adsr_decay_time))
			calc = ((envelope->adsr_sustain_amplitude - envelope->adsr_max_amp)/envelope->adsr_decay_time) * (envelope->adsr_counter - envelope->adsr_attack_time) + envelope->adsr_max_amp;

		// sustain period
		else if(envelope->adsr_counter <= (envelope->adsr_duration_time - envelope->adsr_release_time))
			calc = envelope->adsr_sustain_amplitude;

		// release period
		else if(envelope->adsr_counter > (envelope->adsr_duration_time - envelope->adsr_release_time))
			calc = -(envelope->adsr_sustain_amplitude/envelope->adsr_release_time) * (envelope->adsr_counter - (envelope->adsr_duration_time - envelope->adsr_release_time)) + envelope->adsr_sustain_amplitude;

	}
	else
		calc = 0.f;

	// update time counter
	(envelope->adsr_counter)++;

	if(envelope->adsr_counter == envelope->adsr_duration_time)
		envelope->adsr_counter = 0;	// restart

	return calc;
}
