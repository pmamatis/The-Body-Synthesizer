/**
 ******************************************************************************
 * @file    wahwah.c
 * @author  Max Lehmer
 * @date 	11 Sep 2021
 * @brief	WahWah-Library
 */
//
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
//	return WAHWAH_OK;
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
