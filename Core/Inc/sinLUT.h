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
const float  LUT[6439];
const uint32_t LUT_ENDINDEX[73];
const uint32_t LUT_STARTINDEX[73];
const uint32_t LUT_SUPPORTPOINTS[73];
const float LUT_FREQUENCYS[73];
const float LFO[95625];
const uint32_t LFO_ENDINDEX[8];
const uint32_t LFO_STARTINDEX[8];
const uint32_t LFO_SUPPORTPOINTS[8];
const float LFO_FREQUENCYS[8];
#endif
