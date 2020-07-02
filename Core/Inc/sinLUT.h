#ifndef INC_SINLUT_H_
#define INC_SINLUT_H_
//includes 
#include "main.h"
 
 
//defines 
#define LUT_SR 48000
#define LUT_FMAX 4186.009
#define LUT_FMIN 65.4064
#define LUT_OCTAVES 6
//defines 
#define LFO_FMAX 32
#define LFO_FMIN 0.5
#define LFO_OCTAVES 7
 
 
//variables
const float  LUT[12880];
const uint32_t LUT_ENDINDEX[73];
const uint32_t LUT_STARTINDEX[73];
const uint32_t LUT_SUPPORTPOINTS[73];
const float LUT_FREQUENCYS[73];
const float LFO[190500];
const uint32_t LFO_ENDINDEX[7];
const uint32_t LFO_STARTINDEX[7];
const uint32_t LFO_SUPPORTPOINTS[7];
const float LFO_FREQUENCYS[7];
#endif
