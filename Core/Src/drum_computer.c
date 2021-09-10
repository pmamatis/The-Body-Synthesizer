/*
 * drum_computer.c
 *
 *  Created on: 05.08.2021
 *      Author: Marc Bielen & Max Lehmer
 */

#include "drum_computer.h"


HAL_StatusTypeDef Drum_Computer_Init(UART_HandleTypeDef *huart){

	// INIT: Tempo, SR, Counter
	BPM = 130;						// at SR of 96000 Hz and sample length of 40000 -> 144 BPM Maximum
	MasterClock = LUT_SR;
	counter_master = 0;

	// INIT: Sound bins
	DS1s = 0;
	DS2s = 0;
	DS3s = 0;
	DS4s = 0;
	drums = 0;

	// Index
	drum_index = 0;

	for(int i = 0; i < FourFour; i++){

		// INIT: Flag
		flag_DS1[i] = 0;
		flag_DS2[i] = 0;
		flag_DS3[i] = 0;
		flag_DS4[i] = 0;

		// INIT: Oversampling counter
		OS_DS1[i] = 0;
		OS_DS2[i] = 0;
		OS_DS3[i] = 0;
		OS_DS4[i] = 0;

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

		timing_position_in_samples[i] = (FourFour / 4 ) * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
	}

	// INIT: LUTs
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


	// INIT: Timing
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
	timing_DS3[7] = 0;
//
//	// LowTom
	timing_DS4[0] = 0;
	timing_DS4[1] = 0;
	timing_DS4[2] = 1;
	timing_DS4[3] = 1;
	timing_DS4[4] = 0;
	timing_DS4[5] = 0;
	timing_DS4[6] = 0;
	timing_DS4[7] = 1;

	return HAL_OK;
}


HAL_StatusTypeDef Drum_Computer_Process() {

	// RESET: Sound bins
	DS1s = 0;
	DS2s = 0;
	DS3s = 0;
	DS4s = 0;

	drums = 0;

	// SET: Flags if there is a timing available
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


	// SET: drum index
	if(counter_master > timing_position_in_samples[drum_index]){

		drum_index++;
	}

	// INCREMENT: master counter
	counter_master++;

	// RESET: drum index & master counter
	if(counter_master > timing_position_in_samples[FourFour - 1] - 1){

		drum_index = 0;
		counter_master = 0;
	}

	return HAL_OK;
}

HAL_StatusTypeDef Drum_Computer_CalcSample() {

	for(int i = 0; i < FourFour; i++) {

		// Drumsample 1
		if(flag_DS1[i] == 1) {

			DS1s = DS1s + DS1[counter_DS1[i]];
			OS_DS1[i]++;

			if(OS_DS1[i] == 4){

				counter_DS1[i]++;
				OS_DS1[i] = 0;
			}

			if(counter_DS1[i] == D909_S1_L - 1){

				counter_DS1[i] = 0;
				flag_DS1[i]    = 0;
			}
		}
		// Drumsample 2
		if(flag_DS2[i] == 1) {

			DS2s = DS2s + DS2[counter_DS2[i]];
			OS_DS2[i]++;

			if(OS_DS2[i] == 4){

				counter_DS2[i]++;
				OS_DS2[i] = 0;
			}

			if(counter_DS2[i] == D909_S2_L - 1){

				counter_DS2[i] = 0;
				flag_DS2[i]    = 0;
			}
		}
		// Drumsample 3
		if(flag_DS3[i] == 1) {

			DS3s = DS3s + DS3[counter_DS3[i]];
			OS_DS3[i]++;

			if(OS_DS3[i] == 4){

				counter_DS3[i]++;
				OS_DS3[i] = 0;
			}

			if(counter_DS3[i] == D909_S3_L - 1){

				counter_DS3[i] = 0;
				flag_DS3[i]    = 0;
			}
		}
		// Drumsample 4
		if(flag_DS4[i] == 1) {

			DS4s = DS4s + DS4[counter_DS4[i]];
			OS_DS4[i]++;

			if(OS_DS4[i] == 4){

				counter_DS4[i]++;
				OS_DS4[i] = 0;
			}

			if(counter_DS4[i] == D909_S4_L - 1){

				counter_DS4[i] = 0;
				flag_DS4[i]    = 0;
			}
		}
	}
	drums = 1.5 * DS1s + DS2s + DS3s + DS4s;

	//ProcessFilter(&EQ_BAND1_I,  &drums);

	return HAL_OK;
}


