/**
 ******************************************************************************
 * @file    wahwah.c
 * @author  Max Lehmer
 * @date 	11 Sep 2021
 * @brief	WahWah-Library
 */

//#include "wahwah.h"
//
///*********************************
// * @brief		WahWah functions
// * @parameter	WahWah
// *********************************/
//WahWah_Status WahWah_Init(struct WahWah_t *WahWah) {
//
//	Tremolo.lfo_data = &lfo;
//	SetupTremolo(&Tremolo);
//
//	return TREMOLO_OK;
//}
//
//Tremolo_Status SetupTremolo(struct Tremolo_t* Tremolo) {
//
//
//	Tremolo->lfo_data->lfo_index = 0;
//	Tremolo->lfo_data->lfo_frequency = 8.00;	// was 4
//	//Tremolo->lfo_frequency = 4.00;
//	Tremolo->lfo_data->lfo_quarter = 0;
//	Tremolo->lfo_data->lfo_blocksizecounter = 0;
//	Tremolo->tremolo_blocksizecounter = 0;
//	//Tremolo->lfo_depth = 0.00;
//	Tremolo->lfo_data->lfo_depth = 1.0;	// was 0.5
//	Tremolo->recalc_lfo = false;
//	Tremolo->tremolo_maximum_rate = 9;
//	Tremolo->tremolo_maximum_depth = 1.00;
//
//	return TREMOLO_OK;
//}
//
//
///** @brief Processed current tremolo sample
// * @param Tremolo: struct for tremolo information
// * @param data: current sample
// * @param lfo_value: current lfo value
// */
//Tremolo_Status ProcessTremolo(struct Tremolo_t* Tremolo, float* data, float* lfo_value) {
//
//	float tremolo_mod = (1 + Tremolo->lfo_data->lfo_depth * *lfo_value);
//	*data = (tremolo_mod * *data) / (1+Tremolo->lfo_data->lfo_depth);
//
//	return TREMOLO_OK;
//}
