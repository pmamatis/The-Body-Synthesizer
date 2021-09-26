/**
 ******************************************************************************
 * @file    wahwah.h
 * @author  Max Lehmer
 * @date 	11 Sep 2021
 * @brief	WahWah-Library
 */

#ifndef INC_WAHWAH_H_
#define INC_WAHWAH_H_

#include "main.h"
#include <stdbool.h>

/***************************
 * @brief Enumeration for Tremolo Debugging
 ***************************/
typedef enum {
	WAHWAH_FAIL = -1,
	WAHWAH_OK = 1
} WahWah_Status;

/*********************************
 * @brief		WahWah struct
 * @parameter	WahWah
 *********************************/
struct WahWah_t{

	struct effects_lfo_t* lfo;
	struct BQFilter* bandpass;

	float mid_freq;
	float mid_freq_mod;
	float range;
	float gain;

	float max_mid_freq;
	float max_range;

	uint32_t reinit_counter;
};

struct WahWah_t WahWah;

WahWah_Status WahWah_Init(struct WahWah_t *WahWah);
WahWah_Status ProcessWahWah(struct WahWah_t *WahWah, float* data);
WahWah_Status ProcessAutoWahWah(struct WahWah_t *WahWah, float* data);

#endif /* INC_WAHWAH_H_ */
