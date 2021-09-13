#include "adsr.h"

// Reference: The Audio Programming Book from Boulanger, Lazzarini and Mathews

ADSR_Status ADSR_Init(void) {

	SetupADSR(&envelope);

	return ADSR_OK;
}

// Reference: https://codingforspeed.com/using-faster-exponential-approximation/
inline float exp1(float x) {
	x = 1.0 + x / 256.0;
	x *= x; x *= x; x *= x; x *= x;
	x *= x; x *= x; x *= x; x *= x;
	return x;
}

ADSR_Status SetupADSR(struct adsr* envelope) {

	envelope->adsr_counter = 0;
	envelope->adsr_max_amp = 1.00;	// maximum value should be 1
	envelope->adsr_duration_time = 1.0 * LUT_SR;	// first number in seconds
	envelope->adsr_attack_time = 0.1 * LUT_SR;
	envelope->adsr_decay_time = 0.05 * LUT_SR;
	envelope->adsr_sustain_time = 0.15 * LUT_SR;
	envelope->adsr_sustain_amplitude = 0.5;
	envelope->adsr_release_time = 0.05 * LUT_SR;

	//	envelope->adsr_maximum_attack = (envelope->adsr_duration_time/4) / LUT_SR;	// in seconds; maximum 4.0 seconds (-> 4*LUT_SR), to display the value -> uint16_t
	//	envelope->adsr_maximum_decay = (envelope->adsr_duration_time/4) / LUT_SR;
	//	envelope->adsr_maximum_sustaintime = (envelope->adsr_duration_time/4) / LUT_SR;
	//	envelope->adsr_maximum_release = (envelope->adsr_duration_time/4) / LUT_SR;

	envelope->adsr_maximum_attack = 1.00;	// in seconds; maximum 4.0 seconds (-> 4*LUT_SR), to display the value -> uint16_t
	envelope->adsr_maximum_decay = 1.00;
	envelope->adsr_maximum_sustaintime = 2.00;
	envelope->adsr_maximum_release = 1.00;

	envelope->adsr_done = false;

	envelope->decay_counter = 0;
	envelope->release_counter = 0;

	return ADSR_OK;
}

void OnePress_ADSR_Linear_Process(struct adsr* envelope, float* calculate_value, bool flag) {

	if(flag == true) {

		float calc = 0;

		envelope->adsr_duration_time = envelope->adsr_attack_time + envelope->adsr_decay_time + envelope->adsr_sustain_time + envelope->adsr_release_time;

		if(envelope->adsr_counter < envelope->adsr_duration_time) { // if time < total duration

			// attack period
			if(envelope->adsr_counter <= envelope->adsr_attack_time) {
				// linear:
				calc = envelope->adsr_counter * (envelope->adsr_max_amp/envelope->adsr_attack_time);
				// exponential:
				//calc = 0.006737947 * exp1(envelope->adsr_counter/(envelope->adsr_attack_time/5));
				//calc = (envelope->adsr_max_amp/(exp1(5))) * exp1(envelope->adsr_counter/(envelope->adsr_attack_time/5));	// 5, because of 5*tau
			}

			// decay period
			else if(envelope->adsr_counter <= (envelope->adsr_attack_time + envelope->adsr_decay_time)) {
				// linear:
				calc = ((envelope->adsr_sustain_amplitude - envelope->adsr_max_amp)/envelope->adsr_decay_time) * (envelope->adsr_counter - envelope->adsr_attack_time) + envelope->adsr_max_amp;
				// exponential:
				//calc = (envelope->adsr_max_amp * (1/exp1(envelope->decay_counter/(envelope->adsr_decay_time/5)))/2)+0.5;
				//calc = (envelope->adsr_max_amp * (1/exp1(envelope->decay_counter/(envelope->adsr_decay_time/5))) * (envelope->adsr_sustain_amplitude/envelope->adsr_max_amp)) + (envelope->adsr_sustain_amplitude/envelope->adsr_max_amp);
				//calc = (envelope->adsr_max_amp * (1/exp1(envelope->decay_counter/(envelope->adsr_decay_time/5))) * (envelope->adsr_sustain_amplitude/envelope->adsr_max_amp)) + (envelope->adsr_sustain_amplitude/envelope->adsr_max_amp);
				//(envelope->decay_counter)++;
			}

			// sustain period
			else if(envelope->adsr_counter <= (envelope->adsr_duration_time - envelope->adsr_release_time))
				calc = envelope->adsr_sustain_amplitude;

			// release period
			else if(envelope->adsr_counter > (envelope->adsr_duration_time - envelope->adsr_release_time)) {
				// linear:
				calc = -(envelope->adsr_sustain_amplitude/envelope->adsr_release_time) * (envelope->adsr_counter - (envelope->adsr_duration_time - envelope->adsr_release_time)) + envelope->adsr_sustain_amplitude;
				// exponential:
				//calc = envelope->adsr_sustain_amplitude * (1/exp1(envelope->release_counter/(envelope->adsr_release_time/5)));
				(envelope->release_counter)++;
			}
		}

		else if(envelope->adsr_counter >= envelope->adsr_duration_time) {
			envelope->adsr_counter = 0;	// restart
			//envelope->decay_counter = 0;
			envelope->release_counter = 0;
			envelope->adsr_done = true;
		}

		// update time counter
		(envelope->adsr_counter)++;

		//*calculate_value = *calculate_value + 1;
		*calculate_value = *calculate_value * calc;
		//*calculate_value = *calculate_value - 1;
	}
}
