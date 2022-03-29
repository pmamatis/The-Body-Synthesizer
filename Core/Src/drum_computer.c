/**
 * @file drum_computer.c
 * @author Max Lehmer & Marc Bielen
 * @brief Drumcomputer functions
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "drum_computer.h"

/**
 * @brief Initializes the variables of the sequencer ADSR
 * 
 * @param env: Struct of each ADSR of each sequencer note
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Sequencer_ADSR_Init(struct adsr* env){

	// INIT: ADSR structs
	env->adsr_counter = 0;
	env->adsr_max_amp = 1.00;					// maximum value should be 1

	env->adsr_attack_time = 0.01 * LUT_SR;
	env->adsr_decay_time = 0.05 * LUT_SR;
	env->adsr_sustain_time = 0.05 * LUT_SR;
	env->adsr_sustain_amplitude = 0.3;
	env->adsr_release_time = 0.01 * LUT_SR;

	env->adsr_done = false;

	return HAL_OK;
}

/**
 * @brief This function calculates actual samples of the drumcomputer depending on via display set timings
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Drum_Computer_CalcSample(void) {

	for(int i = 0; i < FourFour; i++) {

		if(Display.Drumcomputer_ONOFF == true) {

			// Drumsample 1
			if(flag_DS1[i] == 1) {

				DS1s = DS1s + DS1[counter_DS1[i]];
				counter_DS1[i]++;

				if(counter_DS1[i] == DS_L - 1){

					counter_DS1[i] = 0;
					flag_DS1[i]    = 0;
				}
			}
			// Drumsample 2
			if(flag_DS2[i] == 1) {

				DS2s = DS2s + DS2[counter_DS2[i]];
				counter_DS2[i]++;

				if(counter_DS2[i] == DS_L - 1){

					counter_DS2[i] = 0;
					flag_DS2[i]    = 0;
				}
			}
			// Drumsample 3
			if(flag_DS3[i] == 1) {

				DS3s = DS3s + DS3[counter_DS3[i]];
				counter_DS3[i]++;

				if(counter_DS3[i] == DS_L - 1){

					counter_DS3[i] = 0;
					flag_DS3[i]    = 0;
				}
			}
			// Drumsample 4
			if(flag_DS4[i] == 1) {

				DS4s = DS4s + DS4[counter_DS4[i]];
				counter_DS4[i]++;

				if(counter_DS4[i] == DS_L - 1){

					counter_DS4[i] = 0;
					flag_DS4[i]    = 0;
				}
			}
		}

		if(Display.Sequencer_ONOFF == true) {
			// Sequencer Note 1
			if(timing_SN1[i] == 1){

				if(adsr_SN1[i].adsr_done == false){


					SN1_temp = LUT[current_LUT_index_SN1[i]];

					OnePress_ADSR_Sequencer_Process(&adsr_SN1[i], &SN1_temp, timing_SN1[i]);

					SN1 += SN1_temp;
					current_LUT_index_SN1[i]++;
				}
				else if(adsr_SN1[i].adsr_done == true){

					SN1 += 0;
				}
				if (current_LUT_index_SN1[i] > LUT_ENDINDEX[freq_index_SN1])
				{
					current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
				}
			}
			// Sequencer Note 2
			if(timing_SN2[i] == 1){

				if(adsr_SN2[i].adsr_done == false){

					SN2_temp = LUT[current_LUT_index_SN2[i]];

					OnePress_ADSR_Sequencer_Process(&adsr_SN2[i], &SN2_temp, timing_SN2[i]);

					SN2 += SN2_temp;
					current_LUT_index_SN2[i]++;
				}
				else if(adsr_SN2[i].adsr_done == true){

					SN2 += 0;
				}
				if (current_LUT_index_SN2[i] > LUT_ENDINDEX[freq_index_SN2])
				{
					current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
				}
			}
			// Sequencer Note 3
			if(timing_SN3[i] == 1){

				if(adsr_SN3[i].adsr_done == false){

					SN3_temp = LUT[current_LUT_index_SN3[i]];

					OnePress_ADSR_Sequencer_Process(&adsr_SN3[i], &SN3_temp, timing_SN3[i]);

					SN3 += SN3_temp;
					current_LUT_index_SN3[i]++;
				}
				else if(adsr_SN3[i].adsr_done == true){

					SN3 += 0;
				}
				if (current_LUT_index_SN3[i] > LUT_ENDINDEX[freq_index_SN3])
				{
					current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
				}
			}
			// Sequencer Note 4
			if(timing_SN4[i] == 1){

				if(adsr_SN4[i].adsr_done == false){

					SN4_temp = LUT[current_LUT_index_SN4[i]];

					OnePress_ADSR_Sequencer_Process(&adsr_SN4[i], &SN4_temp, timing_SN4[i]);

					SN4 += SN4_temp;
					current_LUT_index_SN4[i]++;
				}
				else if(adsr_SN4[i].adsr_done == true){

					SN4 += 0;
				}

				if (current_LUT_index_SN4[i] > LUT_ENDINDEX[freq_index_SN4])
				{
					current_LUT_index_SN4[i] = LUT_STARTINDEX[freq_index_SN4];
				}
			}
		}
	}

	drums =  DS1s + DS2s + DS3s + DS4s;
	sequencer = SN1 + SN2 + SN3 + SN4;

	return HAL_OK;
}

/**
 * @brief This function resets the drumcomputer to its initial state
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Drum_Computer_Reset(void) {

	Display.Drumcomputer_ONOFF = false;

	for(int i=0; i<MAX_NUMBER_OF_SAMPLES; i++) {
		for(int j=0; j<NUMBER_OF_DRUMSTEPS; j++) {
			Display.DrumMatrix[i][j] = false;
		}
	}

	// INIT: Tempo, SR, Counter
	BPM = 120;
	last_BPM = BPM;
	BPM_MAX = 160;
	MasterClock = LUT_SR;
	counter_master = 0;

	// INIT: Sound bins
	DS1s = 0;
	DS2s = 0;
	DS3s = 0;
	DS4s = 0;
	drums = 0;

	// Drums: Index
	drum_index = 0;

	// FOR: all steps in drums
	for(int i=0; i<FourFour; i++) {

		// INIT: Flag
		flag_DS1[i] = 0;
		flag_DS2[i] = 0;
		flag_DS3[i] = 0;
		flag_DS4[i] = 0;

		// INIT: Counter
		counter_DS1[i] = 0;
		counter_DS2[i] = 0;
		counter_DS3[i] = 0;
		counter_DS4[i] = 0;

		// INIT: Timing positions
		timing_DS1[i] = 0;
		timing_DS2[i] = 0;
		timing_DS3[i] = 0;
		timing_DS4[i] = 0;

		// INIT: Array of timing positions
		timing_position_in_samples[i] = (FourFour / 4 ) * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
	}

	Display.Drumcomputer_BPMbyECG_ONOFF = false;
	strcpy(Display.value_str_drumcomputer[6], "OFF");

	return HAL_OK;
}

/**
 * @brief This function resets the sequencer to its initial state
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Sequencer_Reset(void) {

	Display.Sequencer_ONOFF = false;

	for(int i=0; i<MAX_NUMBER_OF_NOTES; i++) {
		for(int j=0; j<NUMBER_OF_SEQUENCERSTEPS; j++) {
			Display.SequencerMatrix[i][j] = false;
		}
		Display.Sequencer_Note[i] = 'C';
		Display.Sequencer_Noteindex[i] = 0;
		Display.Sequencer_Octave[i] = 0;
	}

	// FOR: all steps in sequencer
	for(int i=0; i<FourFour; i++) {

		// INIT: Sequencer timing positions
		timing_SN1[i] = 0;
		timing_SN2[i] = 0;
		timing_SN3[i] = 0;
		timing_SN4[i] = 0;

		// INIT: Sequencer start index
		current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
		current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
		current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
		current_LUT_index_SN4[i] = LUT_STARTINDEX[freq_index_SN4];

		// INIT: ADSR structs
		Sequencer_ADSR_Init(&adsr_SN1[i]);
		Sequencer_ADSR_Init(&adsr_SN2[i]);
		Sequencer_ADSR_Init(&adsr_SN3[i]);
		Sequencer_ADSR_Init(&adsr_SN4[i]);
	}

	strcpy(Display.value_str_sequencer[0], "OFF");
	sprintf(Display.value_str_sequencer[1], "%c", Display.Sequencer_Note[0]);
	sprintf(Display.value_str_sequencer[2], "%d", Display.Sequencer_Octave[0]);
	sprintf(Display.value_str_sequencer[3], "%c", Display.Sequencer_Note[1]);
	sprintf(Display.value_str_sequencer[4], "%d", Display.Sequencer_Octave[1]);
	sprintf(Display.value_str_sequencer[5], "%c", Display.Sequencer_Note[2]);
	sprintf(Display.value_str_sequencer[6], "%d", Display.Sequencer_Octave[2]);

	return HAL_OK;
}

/** 
 * @brief Init function for the drumcomputer  
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Drum_Computer_Init(void) {


	// INIT: Tempo, SR, Counter
	BPM = 120;
	last_BPM = BPM;
	BPM_MAX = 160;
	MasterClock = LUT_SR;
	counter_master = 0;

	// INIT: Sound bins
	DS1s = 0;
	DS2s = 0;
	DS3s = 0;
	DS4s = 0;
	drums = 0;

	// INIT: Play Single Sample Sound bin and flags
	PSSs = 0;
	counter_single_sample = 0;
	play_single_sample_flag = false;

	// Drums: Index
	drum_index = 0;

	// FOR: all steps in drums / sequencer
	for(int i=0; i<FourFour; i++) {

		// INIT: Flag
		flag_DS1[i] = 0;
		flag_DS2[i] = 0;
		flag_DS3[i] = 0;
		flag_DS4[i] = 0;

		// INIT: Counter
		counter_DS1[i] = 0;
		counter_DS2[i] = 0;
		counter_DS3[i] = 0;
		counter_DS4[i] = 0;

		// INIT: Timing positions
		timing_DS1[i] = 0;
		timing_DS2[i] = 0;
		timing_DS3[i] = 0;
		timing_DS4[i] = 0;

		// INIT: Sequencer timing positions
		timing_SN1[i] = 0;
		timing_SN2[i] = 0;
		timing_SN3[i] = 0;
		timing_SN4[i] = 0;

		// INIT: Sequencer start index
		current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
		current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
		current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
		current_LUT_index_SN4[i] = LUT_STARTINDEX[freq_index_SN4];

		// INIT: ADSR structs
		Sequencer_ADSR_Init(&adsr_SN1[i]);
		Sequencer_ADSR_Init(&adsr_SN2[i]);
		Sequencer_ADSR_Init(&adsr_SN3[i]);
		Sequencer_ADSR_Init(&adsr_SN4[i]);

		// INIT: Array of timing positions
		timing_position_in_samples[i] = (FourFour / 4 ) * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
	}
	// INIT: 909 LUTs
	// POSSIBLE: Kick, ClosedHihat, OpenHihat, Clap, Rimshot, LowTom, MidTom, HiTom
	__disable_irq();
	sd_card_mount();
	sd_card_read("909_Kick.txt", &DS1);
	sd_card_read("909_OpenHihat.txt", &DS2);
	sd_card_read("909_Clap.txt", &DS3);
	sd_card_read("909_LowTom.txt", &DS4);
	sd_card_unmount();
	__enable_irq();

	strcpy(Display.sample1, "Kick");	// Init drumcomputer display content, has to be similar to the drumkit above!
	strcpy(Display.sample2, "Op.HH");
	strcpy(Display.sample3, "Clap");
	strcpy(Display.sample4, "L.Tom");

	return HAL_OK;
}

/**
 * @brief Process-function of drumcomputer as well as sequencer
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Drum_Computer_Process(void) {

	// RESET: Drum sound bins
	DS1s = 0;
	DS2s = 0;
	DS3s = 0;
	DS4s = 0;

	drums = 0;

	// RESET: Sequencer sound bins
	SN1 = 0;
	SN2 = 0;
	SN3 = 0;
	SN4 = 0;

	SN1_temp = 0;
	SN2_temp = 0;
	SN3_temp = 0;
	SN4_temp = 0;

	sequencer = 0;

	// SET: Drum flags if there is a timing available
	if(timing_DS1[drum_index] == 1){

		flag_DS1[drum_index] = 1;
	}
	if(timing_DS2[drum_index] == 1){

		flag_DS2[drum_index] = 1;
	}
	if(timing_DS3[drum_index] == 1){

		flag_DS3[drum_index] = 1;
	}
	if(timing_DS4[drum_index] == 1){

		flag_DS4[drum_index] = 1;
	}

	// CALC: each drumsample
	Drum_Computer_CalcSample();

	// INCREMENT: master counter
	counter_master++;

	// SET: drum index
	if(counter_master == timing_position_in_samples[drum_index]){

		drum_index++;

		if(drum_index == FourFour){

			drum_index = 0;
			counter_master = 0;

			if(abs(last_BPM - BPM) > 3) {

				for(int i=0; i<FourFour; i++) {

					// INIT: Counter
					counter_DS1[i] = 0;
					counter_DS2[i] = 0;
					counter_DS3[i] = 0;
					counter_DS4[i] = 0;

					drum_index = 0;
					counter_master = 0;

					// RESET: Drum sound bins
					DS1s = 0;
					DS2s = 0;
					DS3s = 0;
					DS4s = 0;

					drums = 0;

					timing_position_in_samples[i] = (FourFour / 4 ) * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
				}
			}
		}

		// RESET: ADSR for being ready in next cycle
		adsr_SN1[drum_index].adsr_done = false;
		adsr_SN2[drum_index].adsr_done = false;
		adsr_SN3[drum_index].adsr_done = false;
		adsr_SN4[drum_index].adsr_done = false;
	}

	return HAL_OK;
}

/** 
 * @brief Function to play a chosen sample each time it is triggerd by EMG / ECG, must be called inside Signal_Synthesis()
 * 
 */
void PlaySingleSample(void) {

	single_sample = PSS[counter_single_sample];
	counter_single_sample++;

	if(counter_single_sample == DS_L - 1) {
		counter_single_sample = 0;
		play_single_sample_flag = false;
	}
}

/** TODO
 * @brief Plays actual drumsamples in reverse mode (not completely finished yet and therefore not in use)
 * 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef Drum_Computer_CalcSample_Reverse(void) {

	for(int i = 0; i < FourFour; i++) {

		// Drumsample 1
		if(flag_DS1[i] == 1) {

			DS1s = DS1s + DS1[10000-counter_DS1[i]];
			counter_DS1[i]++;

			if(counter_DS1[i] == DS_L - 1){

				counter_DS1[i] = 0;
				flag_DS1[i]    = 0;
			}
		}
		// Drumsample 2
		if(flag_DS2[i] == 1) {

			DS2s = DS2s + DS2[10000-counter_DS2[i]];
			counter_DS2[i]++;

			if(counter_DS2[i] == DS_L - 1){

				counter_DS2[i] = 0;
				flag_DS2[i]    = 0;
			}
		}
		// Drumsample 3
		if(flag_DS3[i] == 1) {

			DS3s = DS3s + DS3[10000-counter_DS3[i]];
			counter_DS3[i]++;

			if(counter_DS3[i] == DS_L - 1){

				counter_DS3[i] = 0;
				flag_DS3[i]    = 0;
			}
		}
		// Drumsample 4
		if(flag_DS4[i] == 1) {

			DS4s = DS4s + DS4[10000-counter_DS4[i]];
			counter_DS4[i]++;

			if(counter_DS4[i] == DS_L - 1){

				counter_DS4[i] = 0;
				flag_DS4[i]    = 0;
			}
		}
	}
	drums = DS1s + DS2s + DS3s + DS4s;

	return HAL_OK;
}
