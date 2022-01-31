/**
 * @file adsr.c
 * @author Marc Bielen
 * @brief Source code for the adsr effect
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "adsr.h"


// Reference: The Audio Programming Book from Boulanger, Lazzarini and Mathews
/** TODO
 * @brief 
 * 
 * @return ADSR_Status 
 */
ADSR_Status ADSR_Init(void) {

	SetupADSR(&envelope);
	for(uint8_t i=0; i<MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++)
		SetupADSR(&adsr_keyboard[i]);

	return ADSR_OK;
}

ADSR_Status SetupADSR(struct adsr* envelope) {

	envelope->adsr_counter = 0;
	envelope->adsr_max_amp = 1.00;	// maximum value should be 1
	envelope->adsr_attack_time = 0.1 * LUT_SR;
	envelope->adsr_decay_time = 0.05 * LUT_SR;
	envelope->adsr_sustain_time = 0.15 * LUT_SR;
	envelope->adsr_sustain_amplitude = 0.5;
	envelope->adsr_release_time = 0.05 * LUT_SR;

	envelope->adsr_maximum_attack = 1.00;	// in seconds; maximum 4.0 seconds (-> 4*LUT_SR), to display the value -> uint16_t
	envelope->adsr_maximum_decay = 1.00;
	envelope->adsr_maximum_sustaintime = 2.00;
	envelope->adsr_maximum_release = 1.00;

	envelope->adsr_done = false;

	return ADSR_OK;
}

/**
 * @brief 
 * 
 * @param envelope 
 * @return ADSR_Status 
 */
ADSR_Status ADSR_Reset(struct adsr* envelope) {

	envelope->adsr_counter = 0;
	envelope->adsr_max_amp = 1.00;	// maximum value should be 1
	envelope->adsr_attack_time = 0.1 * LUT_SR;
	envelope->adsr_decay_time = 0.05 * LUT_SR;
	envelope->adsr_sustain_time = 0.15 * LUT_SR;
	envelope->adsr_sustain_amplitude = 0.5;
	envelope->adsr_release_time = 0.05 * LUT_SR;

	envelope->adsr_done = false;

	Display.ADSR_Attacktime = envelope->adsr_attack_time/LUT_SR;
	Display.ADSR_Decaytime = envelope->adsr_decay_time/LUT_SR;
	Display.ADSR_Sustaintime = envelope->adsr_sustain_time/LUT_SR;
	Display.ADSR_Sustainlevel = envelope->adsr_sustain_amplitude/LUT_SR;
	Display.ADSR_Releasetime = envelope->adsr_release_time/LUT_SR;

	Display.ADSR_Sources[0] = POTI;
	Display.ADSR_Sources[1] = POTI;
	Display.ADSR_Sources[2] = POTI;
	Display.ADSR_Sources[3] = POTI;
	Display.ADSR_Sources[4] = POTI;

	strcpy(Display.value_str_adsr_settings[0], Display.source_names[Display.ADSR_Sources[0]]);
	strcpy(Display.value_str_adsr_settings[1], Display.source_names[Display.ADSR_Sources[1]]);
	strcpy(Display.value_str_adsr_settings[2], Display.source_names[Display.ADSR_Sources[2]]);
	strcpy(Display.value_str_adsr_settings[3], Display.source_names[Display.ADSR_Sources[3]]);
	strcpy(Display.value_str_adsr_settings[4], Display.source_names[Display.ADSR_Sources[4]]);

	return ADSR_OK;
}

/**
 * @brief 
 * 
 * @param envelope 
 * @param calculate_value 
 * @param flag 
 */
void OnePress_ADSR_Linear_Process(struct adsr* envelope, float* calculate_value, bool flag) {

	if(flag == true) {

		float calc = 0;

		envelope->adsr_duration_time = envelope->adsr_attack_time + envelope->adsr_decay_time + envelope->adsr_sustain_time + envelope->adsr_release_time;

		if(envelope->adsr_counter < envelope->adsr_duration_time) { // if time < total duration

			// attack period
			if(envelope->adsr_counter < envelope->adsr_attack_time)
				calc = envelope->adsr_counter * (envelope->adsr_max_amp/envelope->adsr_attack_time);

			// decay period
			else if(envelope->adsr_counter < (envelope->adsr_attack_time + envelope->adsr_decay_time))
				calc = ((envelope->adsr_sustain_amplitude - envelope->adsr_max_amp)/envelope->adsr_decay_time) * (envelope->adsr_counter - envelope->adsr_attack_time) + envelope->adsr_max_amp;

			// sustain period
			else if(envelope->adsr_counter < (envelope->adsr_duration_time - envelope->adsr_release_time))
				calc = envelope->adsr_sustain_amplitude;

			// release period
			else if(envelope->adsr_counter >= (envelope->adsr_duration_time - envelope->adsr_release_time))
				calc = -(envelope->adsr_sustain_amplitude/envelope->adsr_release_time) * (envelope->adsr_counter - (envelope->adsr_duration_time - envelope->adsr_release_time)) + envelope->adsr_sustain_amplitude;

			*calculate_value = *calculate_value * calc;
		}

		// update adsr counter
		envelope->adsr_counter++;

		if(envelope->adsr_counter >= envelope->adsr_duration_time) {
			envelope->adsr_counter = 0;	// restart
			envelope->adsr_done = true;
		}
	}
}
/** TODO
 * @brief 
 * 
 * @param envelope 
 * @param calculate_value 
 * @param flag 
 */
void OnePress_ADSR_Sequencer_Process(struct adsr* envelope, float* calculate_value, bool flag) {

	if(flag == true) {

		float calc;

		envelope->adsr_duration_time = envelope->adsr_attack_time + envelope->adsr_decay_time + envelope->adsr_sustain_time + envelope->adsr_release_time;

		if(envelope->adsr_counter < envelope->adsr_duration_time) { // if time < total duration time

			// attack period
			if(envelope->adsr_counter < envelope->adsr_attack_time)
				calc = envelope->adsr_counter * (envelope->adsr_max_amp/envelope->adsr_attack_time);

			// decay period
			else if(envelope->adsr_counter < (envelope->adsr_attack_time + envelope->adsr_decay_time))
				calc = ((envelope->adsr_sustain_amplitude - envelope->adsr_max_amp)/envelope->adsr_decay_time) * (envelope->adsr_counter - envelope->adsr_attack_time) + envelope->adsr_max_amp;

			// sustain period
			else if(envelope->adsr_counter < (envelope->adsr_duration_time - envelope->adsr_release_time))
				calc = envelope->adsr_sustain_amplitude;

			// release period
			else if(envelope->adsr_counter >= (envelope->adsr_duration_time - envelope->adsr_release_time))
				calc = -(envelope->adsr_sustain_amplitude/envelope->adsr_release_time) * (envelope->adsr_counter - (envelope->adsr_duration_time - envelope->adsr_release_time)) + envelope->adsr_sustain_amplitude;

			*calculate_value = *calculate_value * calc;
		}

		// update adsr counter
		envelope->adsr_counter++;

		if(envelope->adsr_counter >= envelope->adsr_duration_time) {

			envelope->adsr_counter = 0;	// restart
			envelope->adsr_done = true;
		}
	}
}
