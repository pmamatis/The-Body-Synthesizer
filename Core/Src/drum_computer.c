/*
 * drum_computer.c
 *
 *  Created on: 05.08.2021
 *      Author: Marc Bielen & Max Lehmer
 */

#include "drum_computer.h"


HAL_StatusTypeDef Sequencer_ADSR_Init(struct adsr* envelope){

	// INIT: ADSR structs
	envelope->adsr_counter = 0;
	envelope->adsr_max_amp = 1.00;					// maximum value should be 1
	envelope->adsr_duration_time = 1.0 * LUT_SR;	// first number in seconds

	envelope->adsr_attack_time = 0.15 * LUT_SR;
	envelope->adsr_decay_time = 0.15 * LUT_SR;
	envelope->adsr_sustain_time = 0.15 * LUT_SR;
	envelope->adsr_sustain_amplitude = 0.5;
	envelope->adsr_release_time = 0.15 * LUT_SR;

	envelope->adsr_done = false;

	envelope->decay_counter = 0;
	envelope->release_counter = 0;

	return HAL_OK;
}


HAL_StatusTypeDef Drum_Computer_Init(UART_HandleTypeDef *huart){

	// INIT: Sequencer state
	sequencer_state = true;

	// INIT: Tempo, SR, Counter
	BPM = 120;
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

	// Sequencer: Get freq index
	freq_index_SN1 = Get_Note_Index('E',2);
	freq_index_SN2 = Get_Note_Index('C',2);
	freq_index_SN3 = Get_Note_Index('H',1);
	freq_index_SN4 = Get_Note_Index('E',2);

	// FOR: all steps in drums / sequencer
	for(int i = 0; i < FourFour; i++){

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
	sd_card_mount(huart);
	sd_card_read("909_Kick.txt", &DS1, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("909_OpenHihat.txt", &DS2, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("909_Clap.txt", &DS3, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("909_LowTom.txt", &DS4, huart);
	sd_card_unmount(huart);


	/*
	// INIT: Rock Loud LUTs
	// POSSIBLE: Kick, Hihat, Snare, Ride
	sd_card_mount(huart);
	sd_card_read("Rock_loud_Kick.txt", &DS1, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("Rock_loud_Hihat.txt", &DS2, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("Rock_loud_Snare.txt", &DS3, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("Rock_loud_Ride.txt", &DS4, huart);
	sd_card_unmount(huart);


	// INIT: Rock LUTs
	// POSSIBLE: Kick, Hihat, Snare, Ride
	sd_card_mount(huart);
	sd_card_read("Rock_Kick.txt", &DS1, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("Rock_Hihat.txt", &DS2, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("Rock_Snare.txt", &DS3, huart);
	sd_card_unmount(huart);

	sd_card_mount(huart);
	sd_card_read("Rock_Ride.txt", &DS4, huart);
	sd_card_unmount(huart);
	 */

	//	// INIT: Timing
	//	// Kick
	timing_DS1[0]  = 0;
	timing_DS1[1]  = 0;
	timing_DS1[2]  = 0;
	timing_DS1[3]  = 0;
	timing_DS1[4]  = 0;
	timing_DS1[5]  = 0;
	timing_DS1[6]  = 0;
	timing_DS1[7]  = 0;
	//	timing_DS1[8]  = 1;
	//	timing_DS1[9]  = 0;
	//	timing_DS1[10] = 0;
	//	timing_DS1[11] = 0;
	//	timing_DS1[12] = 0;
	//	timing_DS1[13] = 0;
	//	timing_DS1[14] = 0;
	//	timing_DS1[15] = 0;
	//
	//	// Hihat
	//	timing_DS2[0]  = 1;
	//	timing_DS2[1]  = 0;
	//	timing_DS2[2]  = 1;
	//	timing_DS2[3]  = 0;
	//	timing_DS2[4]  = 1;
	//	timing_DS2[5]  = 0;
	//	timing_DS2[6]  = 1;
	//	timing_DS2[7]  = 0;
	//	timing_DS2[8]  = 0;
	//	timing_DS2[9]  = 0;
	//	timing_DS2[10] = 1;
	//	timing_DS2[11] = 0;
	//	timing_DS2[12] = 1;
	//	timing_DS2[13] = 0;
	//	timing_DS2[14] = 1;
	//	timing_DS2[15] = 1;
	//
	//	// Clap
	//	timing_DS3[0]  = 0;
	//	timing_DS3[1]  = 0;
	//	timing_DS3[2]  = 0;
	//	timing_DS3[3]  = 0;
	//	timing_DS3[4]  = 1;
	//	timing_DS3[5]  = 0;
	//	timing_DS3[6]  = 0;
	//	timing_DS3[7]  = 1;
	//	timing_DS3[8]  = 0;
	//	timing_DS3[9]  = 0;
	//	timing_DS3[10] = 0;
	//	timing_DS3[11] = 0;
	//	timing_DS3[12] = 1;
	//	timing_DS3[13] = 0;
	//	timing_DS3[14] = 0;
	//	timing_DS3[15] = 1;
	//
	//	// LowTom
	//	timing_DS4[0]  = 0;
	//	timing_DS4[1]  = 0;
	//	timing_DS4[2]  = 1;
	//	timing_DS4[3]  = 1;
	//	timing_DS4[4]  = 0;
	//	timing_DS4[5]  = 0;
	//	timing_DS4[6]  = 0;
	//	timing_DS4[7]  = 1;
	//	timing_DS4[8]  = 0;
	//	timing_DS4[9]  = 0;
	//	timing_DS4[10] = 1;
	//	timing_DS4[11] = 1;
	//	timing_DS4[12] = 0;
	//	timing_DS4[13] = 0;
	//	timing_DS4[14] = 0;
	//	timing_DS4[15] = 1;

	//
	// Sequencer Note 1
	timing_SN1[0]  = 1;
	timing_SN1[1]  = 0;
	timing_SN1[2]  = 1;
	timing_SN1[3]  = 0;
	timing_SN1[4]  = 1;
	timing_SN1[5]  = 0;
	timing_SN1[6]  = 1;
	timing_SN1[7]  = 0;
	//	timing_SN1[8]  = 1;
	//	timing_SN1[9]  = 0;
	//	timing_SN1[10] = 0;
	//	timing_SN1[11] = 1;
	//	timing_SN1[12] = 0;
	//	timing_SN1[13] = 1;
	//	timing_SN1[14] = 0;
	//	timing_SN1[15] = 1;

	// Sequencer Note 2
//	timing_SN2[0]  = 1;
//	timing_SN2[1]  = 1;
//	timing_SN2[2]  = 1;
//	timing_SN2[3]  = 1;
//	timing_SN2[4]  = 1;
//	timing_SN2[5]  = 1;
//	timing_SN2[6]  = 1;
//	timing_SN2[7]  = 1;
	//	timing_SN2[8]  = 0;
	//	timing_SN2[9]  = 0;
	//	timing_SN2[10] = 1;
	//	timing_SN2[11] = 0;
	//	timing_SN2[12] = 0;
	//	timing_SN2[13] = 0;
	//	timing_SN2[14] = 0;
	//	timing_SN2[15] = 1;

	// Sequencer Note 3
	//	timing_SN3[0]  = 1;
	//	timing_SN3[1]  = 1;
	//	timing_SN3[2]  = 1;
	//	timing_SN3[3]  = 1;
	//	timing_SN3[4]  = 1;
	//	timing_SN3[5]  = 1;
	//	timing_SN3[6]  = 1;
	//	timing_SN3[7]  = 1;
	//	timing_SN3[8]  = 0;
	//	timing_SN3[9]  = 0;
	//	timing_SN3[10] = 0;
	//	timing_SN3[11] = 0;
	//	timing_SN3[12] = 1;
	//	timing_SN3[13] = 0;
	//	timing_SN3[14] = 0;
	//	timing_SN3[15] = 1;

	// Sequencer Note 4
	//	timing_SN4[0]  = 1;
	//	timing_SN4[1]  = 1;
	//	timing_SN4[2]  = 1;
	//	timing_SN4[3]  = 1;
	//	timing_SN4[4]  = 1;
	//	timing_SN4[5]  = 1;
	//	timing_SN4[6]  = 1;
	//	timing_SN4[7]  = 1;
	//	timing_SN4[8]  = 0;
	//	timing_SN4[9]  = 0;
	//	timing_SN4[10] = 0;
	//	timing_SN4[11] = 0;
	//	timing_SN4[12] = 0;
	//	timing_SN4[13] = 0;
	//	timing_SN4[14] = 0;
	//	timing_SN4[15] = 1;

	return HAL_OK;
}


HAL_StatusTypeDef Drum_Computer_Process() {

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

		// RESET: ADSR for being ready in next cycle
		adsr_SN1[drum_index].adsr_done = false;
		adsr_SN2[drum_index].adsr_done = false;
		adsr_SN3[drum_index].adsr_done = false;
		adsr_SN4[drum_index].adsr_done = false;
	}



	// RESET: drum index & master counter
	if(counter_master == timing_position_in_samples[FourFour - 1] - 1){

		drum_index = 0;
		counter_master = 0;

		// RESET: ADSR for being ready in next cycle
		adsr_SN1[drum_index].adsr_done = false;
		adsr_SN2[drum_index].adsr_done = false;
		adsr_SN3[drum_index].adsr_done = false;
		adsr_SN4[drum_index].adsr_done = false;
	}

	return HAL_OK;
}

HAL_StatusTypeDef Drum_Computer_CalcSample() {

	for(int i = 0; i < FourFour; i++) {

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
		// Sequencer Note 1
		if(timing_SN1[i] == 1){

			if(adsr_SN1[i].adsr_done == false){

				SN1_temp += LUT[current_LUT_index_SN1[i]];

				OnePress_ADSR_Linear_Process(&adsr_SN1[i], &SN1_temp, timing_SN1[i]);

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

				SN2_temp += LUT[current_LUT_index_SN2[i]];

				OnePress_ADSR_Linear_Process(&adsr_SN2[i], &SN2_temp, timing_SN2[i]);

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

				SN3_temp += LUT[current_LUT_index_SN3[i]];

				OnePress_ADSR_Linear_Process(&adsr_SN3[i], &SN3_temp, timing_SN3[i]);

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

				SN4_temp += LUT[current_LUT_index_SN4[i]];

				OnePress_ADSR_Linear_Process(&adsr_SN4[i], &SN4_temp, timing_SN4[i]);

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

	drums = 1.5 * DS1s + DS2s + DS3s + DS4s;
	sequencer = SN1 + SN2 + SN3 + SN4;

	return HAL_OK;
}

HAL_StatusTypeDef Drum_Computer_CalcSample_Reverse() {

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
	drums = 1.5 * DS1s + DS2s + DS3s + DS4s;

	return HAL_OK;
}


/* Techno Beat
 * // Kick
	timing_DS1[0] = 1;
	timing_DS1[1] = 0;
	timing_DS1[2] = 0;
	timing_DS1[3] = 0;
	timing_DS1[4] = 1;
	timing_DS1[5] = 0;
	timing_DS1[6] = 0;
	timing_DS1[7] = 0;

	// Hihat
	timing_DS2[0] = 0;
	timing_DS2[1] = 0;
	timing_DS2[2] = 1;
	timing_DS2[3] = 0;
	timing_DS2[4] = 0;
	timing_DS2[5] = 0;
	timing_DS2[6] = 1;
	timing_DS2[7] = 0;

	// Clap
	timing_DS3[0] = 0;
	timing_DS3[1] = 0;
	timing_DS3[2] = 0;
	timing_DS3[3] = 0;
	timing_DS3[4] = 1;
	timing_DS3[5] = 0;
	timing_DS3[6] = 0;
	timing_DS3[7] = 0;

//	// LowTom
	timing_DS4[0] = 0;
	timing_DS4[1] = 0;
	timing_DS4[2] = 1;
	timing_DS4[3] = 1;
	timing_DS4[4] = 0;
	timing_DS4[5] = 0;
	timing_DS4[6] = 0;
	timing_DS4[7] = 1;
 *
 */

/*
 *
 * // INIT: Timing
	// Kick
	timing_DS1[0] = 1;
	timing_DS1[1] = 0;
	timing_DS1[2] = 0;
	timing_DS1[3] = 0;
	timing_DS1[4] = 1;
	timing_DS1[5] = 0;
	timing_DS1[6] = 0;
	timing_DS1[7] = 0;

	// Hihat
	timing_DS2[0] = 0;
	timing_DS2[1] = 0;
	timing_DS2[2] = 1;
	timing_DS2[3] = 0;
	timing_DS2[4] = 0;
	timing_DS2[5] = 0;
	timing_DS2[6] = 1;
	timing_DS2[7] = 0;

	// Clap
	timing_DS3[0] = 0;
	timing_DS3[1] = 0;
	timing_DS3[2] = 0;
	timing_DS3[3] = 0;
	timing_DS3[4] = 1;
	timing_DS3[5] = 0;
	timing_DS3[6] = 0;
	timing_DS3[7] = 1;

	// LowTom
	timing_DS4[0] = 0;
	timing_DS4[1] = 0;
	timing_DS4[2] = 1;
	timing_DS4[3] = 1;
	timing_DS4[4] = 0;
	timing_DS4[5] = 0;
	timing_DS4[6] = 0;
	timing_DS4[7] = 1;
 */


/* Advanced Techno Beat
 *
	// Kick
	timing_DS1[0] = 1;
	timing_DS1[1] = 0;
	timing_DS1[2] = 1;
	timing_DS1[3] = 0;
	timing_DS1[4] = 1;
	timing_DS1[5] = 0;
	timing_DS1[6] = 0;
	timing_DS1[7] = 0;

	// Hihat
	timing_DS2[0] = 0;
	timing_DS2[1] = 0;
	timing_DS2[2] = 1;
	timing_DS2[3] = 0;
	timing_DS2[4] = 0;
	timing_DS2[5] = 0;
	timing_DS2[6] = 1;
	timing_DS2[7] = 0;

	// Clap
	timing_DS3[0] = 0;
	timing_DS3[1] = 0;
	timing_DS3[2] = 0;
	timing_DS3[3] = 0;
	timing_DS3[4] = 1;
	timing_DS3[5] = 0;
	timing_DS3[6] = 0;
	timing_DS3[7] = 1;

	// LowTom
	timing_DS4[0] = 0;
	timing_DS4[1] = 0;
	timing_DS4[2] = 1;
	timing_DS4[3] = 1;
	timing_DS4[4] = 0;
	timing_DS4[5] = 0;
	timing_DS4[6] = 0;
	timing_DS4[7] = 1;

 */


/*
 * 	// Sequencer Note 1
	timing_SN1[0]  = 1;
	timing_SN1[1]  = 0;
	timing_SN1[2]  = 0;
	timing_SN1[3]  = 0;
	timing_SN1[4]  = 0;
	timing_SN1[5]  = 0;
	timing_SN1[6]  = 1;
	timing_SN1[7]  = 1;
//	timing_SN1[8]  = 1;
//	timing_SN1[9]  = 0;
//	timing_SN1[10] = 0;
//	timing_SN1[11] = 1;
//	timing_SN1[12] = 0;
//	timing_SN1[13] = 1;
//	timing_SN1[14] = 0;
//	timing_SN1[15] = 1;

	// Sequencer Note 2
	timing_SN2[0]  = 0;
	timing_SN2[1]  = 0;
	timing_SN2[2]  = 1;
	timing_SN2[3]  = 0;
	timing_SN2[4]  = 0;
	timing_SN2[5]  = 0;
	timing_SN2[6]  = 0;
	timing_SN2[7]  = 0;
//	timing_SN2[8]  = 0;
//	timing_SN2[9]  = 0;
//	timing_SN2[10] = 1;
//	timing_SN2[11] = 0;
//	timing_SN2[12] = 0;
//	timing_SN2[13] = 0;
//	timing_SN2[14] = 0;
//	timing_SN2[15] = 1;

	// Sequencer Note 3
	timing_SN3[0]  = 0;
	timing_SN3[1]  = 0;
	timing_SN3[2]  = 0;
	timing_SN3[3]  = 0;
	timing_SN3[4]  = 1;
	timing_SN3[5]  = 0;
	timing_SN3[6]  = 0;
	timing_SN3[7]  = 0;
//	timing_SN3[8]  = 0;
//	timing_SN3[9]  = 0;
//	timing_SN3[10] = 0;
//	timing_SN3[11] = 0;
//	timing_SN3[12] = 1;
//	timing_SN3[13] = 0;
//	timing_SN3[14] = 0;
//	timing_SN3[15] = 1;

	// Sequencer Note 4
	timing_SN4[0]  = 1;
	timing_SN4[1]  = 0;
	timing_SN4[2]  = 0;
	timing_SN4[3]  = 1;
	timing_SN4[4]  = 0;
	timing_SN4[5]  = 0;
	timing_SN4[6]  = 1;
	timing_SN4[7]  = 1;
//	timing_SN4[8]  = 0;
//	timing_SN4[9]  = 0;
//	timing_SN4[10] = 0;
//	timing_SN4[11] = 0;
//	timing_SN4[12] = 0;
//	timing_SN4[13] = 0;
//	timing_SN4[14] = 0;
//	timing_SN4[15] = 1;
 * */
