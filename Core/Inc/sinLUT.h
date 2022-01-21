/**
 * @file sinLUT.h
 * @author paul mamatis
 * @brief contains a certain amount of frequencys which can be accsed 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 * @attention SIN LUT Data are only valid SIN's with given samplerate (LUT_SR)
 */


#ifndef INC_SINLUT_H_
#define INC_SINLUT_H_

/** 
 * @defgroup SINLUT Sinus LUT
 * @ingroup LUT
 * @brief Sinus LUT for the Signal Synthesis
 * @note the containing LUT's are genearated by an own MATLAB skript 
 * @attention SIN LUT Data are only valid SIN's with given samplerate (LUT_SR)
 *  @{
 * */

// Includes
#include "main.h"
 
 
/*********************************
 * @brief Defines
 *********************************/
#define LUT_SR 24000
#define LUT_START_OCTAVE 4186.009
#define LUT_FMAX 4186.009
#define LUT_FMIN 65.4064
#define LUT_OCTAVES 6
#define LFO_FMAX 16
#define LFO_FMIN 0.125
 
/*********************************
 * @brief		Variables
 *********************************/
/** @brief SIN-LUT, contains all values of 1/4-Sin's for the frequency from LUT_FMIN to LUT_FMAX  */
const float  LUT[6439];
/** @brief contains all endindizies of the frequencies in the SIN-LUT */
const uint32_t LUT_ENDINDEX[73];
/** @brief contains all startindizies of the frequencies in the SIN-LUT */
const uint32_t LUT_STARTINDEX[73];
/** @brief contains the support points for each frequncy*/
const uint32_t LUT_SUPPORTPOINTS[73];
/** @brief gives the the frquncy value */
const float LUT_FREQUENCYS[73];

/** @brief containing the LFO values */
const float LFO[95625];
/** @brief contains all startindizies of the frequencies in the LFO-LUT */
const uint32_t LFO_ENDINDEX[8];
/** @brief contains all startindizies of the frequencies in the LFO-LUT */
const uint32_t LFO_STARTINDEX[8];
/** @brief contains the support points for each LFO-frequncy*/
const uint32_t LFO_SUPPORTPOINTS[8];
/** @brief gives the the LFO-frquency value */
const float LFO_FREQUENCYS[8];

/** @} */
#endif
