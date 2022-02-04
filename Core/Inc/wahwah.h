/**
 * @file wahwah.h
 * @author Max Lehmer, Marc Bielen
 * @brief wahwah effect
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INC_WAHWAH_H_
#define INC_WAHWAH_H_

/**
 * @defgroup wahwah Wahwah Effect
 * @ingroup Effects
 * @brief another effect TODO
 * @{
 */

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
	float max_Q;
	float max_lfo_depth;
	uint32_t reinit_counter;
};

/*********************************
 * @brief		Variables
 *********************************/
struct WahWah_t WahWah;


/*********************************
 * @brief		Functions
 *********************************/
WahWah_Status WahWah_Init(struct WahWah_t *WahWah);
WahWah_Status WahWah_Reset(struct WahWah_t *WahWah);
WahWah_Status ProcessWahWah(struct WahWah_t *WahWah, float* data);
WahWah_Status ProcessAutoWahWah(struct WahWah_t *WahWah, float* data);
/** @} */
#endif /* INC_WAHWAH_H_ */
