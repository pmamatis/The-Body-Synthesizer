/*
 * drum_computer.c
 *
 *  Created on: 05.08.2021
 *      Author: Marc Bielen & Max Lehmer
 */

#include "drum_computer.h"


HAL_StatusTypeDef Drum_Computer_Init(UART_HandleTypeDef *huart){

	// Tempo
	BPM = 130;	// at SR of 96000 Hz and sample length of 40000 -> 144 BPM Maximum
	MasterClock = LUT_SR;
	counter_master = 0;

	// Sound bins
	kick = 0;
	hihat = 0;
	clap = 0;
	rimshot = 0;
	drums = 0;

	// Index
	drum_index = 0;

	for(int i = 0; i < FourFour; i++){

		// Flag
		flag_kick[i] = 0;
		flag_hihat[i] = 0;
		flag_clap[i] = 0;
		flag_rimshot[i] = 0;

		// Counter
		counter_kick [i] = 0;
		counter_hihat[i] = 0;
		counter_clap [i] = 0;
		counter_rimshot [i] = 0;

		// Timing positions
		timing_kick [i] = 0;
		timing_hihat[i] = 0;
		timing_clap [i] = 0;
		timing_rimshot [i] = 0;
		timing_position_in_samples[i] = 4 * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
	}

	// LUT Init
	sd_card_mount(huart);
	sd_card_free_space(huart);
	//	sd_card_read("909_Rimshot.txt", &rimshot_LUT, huart);
	//	sd_card_unmount(huart);

	//	sd_card_mount(huart);
	//	sd_card_free_space(huart);
	//	sd_card_read("909_Kick.txt", &kick_LUT, huart);
	//	sd_card_unmount(huart);

	//	sd_card_mount(huart);
	//	sd_card_free_space(huart);
	//	sd_card_read("909_Clap.txt", &clap_LUT, huart);
	//	sd_card_unmount(huart);

	//	sd_card_mount(huart);
	//	sd_card_free_space(huart);
	//	sd_card_read("909_OpenHihat.txt", &open_hh_LUT, huart);
	//	sd_card_unmount(huart);


	// Timing Init
	timing_kick[0]  = 1;
	timing_kick[4]  = 1;
	timing_kick[8]  = 1;
	timing_kick[12] = 1;

	timing_hihat[2]  = 1;
	timing_hihat[6]  = 1;
	timing_hihat[10] = 1;
	timing_hihat[14] = 1;

	timing_clap[4] = 1;
	timing_clap[12] = 1;

	timing_rimshot[2] = 1;
	timing_rimshot[6] = 1;
	timing_rimshot[10] = 1;
	timing_rimshot[14] = 1;

	return HAL_OK;
}

HAL_StatusTypeDef Drum_Computer_Process() {

	kick = 0;
	clap = 0;
	hihat = 0;
	rimshot = 0;

	//uint32_t avg_counter = 0;

	if(timing_kick[drum_index] == 1){

		flag_kick[drum_index] = 1;

	}
	if(timing_hihat[drum_index] == 1){

		flag_hihat[drum_index] = 1;

	}
	if(timing_clap[drum_index] == 1){

		flag_clap[drum_index] = 1;

	}
	if(timing_rimshot[drum_index] == 1){

		flag_rimshot[drum_index] = 1;

	}

	//	sd_card_mount(huart);
	//	sd_card_free_space(huart);
	//	sd_card_read("909_OpenHihat.txt", &open_hh_LUT, huart);
	//	sd_card_unmount(huart);
	Drum_Computer_CalcSampleFromSD();

	if(counter_master > timing_position_in_samples[drum_index]){

		drum_index++;
	}

	counter_master++;

	if(counter_master > timing_position_in_samples[FourFour - 1] - 1){

		drum_index = 0;
		counter_master = 0;
	}

	return HAL_OK;
}

//HAL_StatusTypeDef Drum_Computer_CalcSample() {
//
//	for(int i=0; i<FourFour; i++) {
//
//		if(flag_kick[i] == 1) {
//
//			kick = kick + kick_LUT[counter_kick[i]];
//			counter_kick[i]++;
//
//			if(counter_kick[i] == sample_length - 1){
//
//				counter_kick[i] = 0;
//				flag_kick[i] = 0;
//			}
//		}
//		if(flag_hihat[i] == 1) {
//
//			hihat = hihat + open_hh_LUT[counter_hihat[i]];
//			counter_hihat[i]++;
//
//			if(counter_hihat[i] == sample_length - 1){
//
//				counter_hihat[i] = 0;
//				flag_hihat[i] = 0;
//			}
//		}
////		if(flag_clap[i] == 1) {
////
////			clap = clap + clap_LUT[counter_clap[i]];
////			counter_clap[i]++;
////
////			if(counter_clap[i] == sample_length - 1){
////
////				counter_clap[i] = 0;
////				flag_clap[i] = 0;
////			}
////		}
//		//		if(flag_rimshot[i] == 1) {
//			//
//			//			rimshot = rimshot + rimshot_LUT[counter_rimshot[i]];
//		//			counter_rimshot[i]++;
//		//
//		//			if(counter_rimshot[i] == sample_length - 1){
//		//
//		//				counter_rimshot[i] = 0;
//		//				flag_rimshot[i] = 0;
//		//			}
////	}
//}
//drums = kick + hihat + clap + rimshot;
//
//return HAL_OK;
//}

HAL_StatusTypeDef Drum_Computer_CalcSampleFromSD() {

	for(int i=0; i<FourFour; i++) {

//		if(flag_kick[i] == 1) {
//
//			kick = kick + sd_card_read_sample("909_Kick.txt");
//			counter_kick[i]++;
//
//			if(counter_kick[i] == sample_length - 1){
//
//				counter_kick[i] = 0;
//				flag_kick[i] = 0;
//			}
//		}
		if(flag_hihat[i] == 1) {

			hihat = hihat + sd_card_read_sample("909_OpenHihat.txt");
			counter_hihat[i]++;

			if(counter_hihat[i] == sample_length - 1){

				counter_hihat[i] = 0;
				flag_hihat[i] = 0;
			}
		}
		//		if(flag_clap[i] == 1) {
		//
		//			clap = clap + clap_LUT[counter_clap[i]];
		//			counter_clap[i]++;
		//
		//			if(counter_clap[i] == sample_length - 1){
		//
		//				counter_clap[i] = 0;
		//				flag_clap[i] = 0;
		//			}
		//		}
		//		if(flag_rimshot[i] == 1) {
		//
		//			rimshot = rimshot + rimshot_LUT[counter_rimshot[i]];
		//			counter_rimshot[i]++;
		//
		//			if(counter_rimshot[i] == sample_length - 1){
		//
		//				counter_rimshot[i] = 0;
		//				flag_rimshot[i] = 0;
		//			}
		//	}
	}
	drums = kick + hihat + clap + rimshot;

	return HAL_OK;
}






//		uint32_t drum_index_pre[3];
//
//		for(int i = 0; i < 3; i++){
//
//			if(drum_index - (i + 1) < 0){
//
//				drum_index_pre[i] = drum_index - (i + 1) + FourFour;
//			}
//			else{
//
//				drum_index_pre[i] = drum_index - (i + 1);
//			}
//			if(timing_kick[drum_index_pre[i]]){
//
//				kick = kick + kick_LUT[counter_kick[drum_index_pre[i]]];
//				counter_kick[drum_index_pre[i]]++;
//				//avg_counter++;
//
//				if(counter_kick[drum_index_pre[i]] > sample_length - 1){
//
//					counter_kick[drum_index_pre[i]] = 0;
//				}
//			}
//		}

//		kick = kick_LUT[counter_kick[drum_index]];  // avg_counter;
//		counter_kick[drum_index]++;
//
//		if(counter_kick[drum_index] == sample_length - 1){
//
//			counter_kick[drum_index] = 0;
//		}
//
//		drums = kick;//+ hihat + clap;
