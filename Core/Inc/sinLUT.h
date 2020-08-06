#ifndef INC_SINLUT_H_
#define INC_SINLUT_H_
//includes 
#include "main.h"
 
 
//defines 
#define LUT_SR 96000
#define LUT_START_OCTAVE 4186.009
#define LUT_FMAX 4186.009
#define LUT_FMIN 65.4064
#define LUT_OCTAVES 6
//defines LFO
#define LFO_FMAX 8
#define LFO_FMIN 0.5
 
 
//variables
const float  LUT[25767];
const uint32_t LUT_ENDINDEX[73];
const uint32_t LUT_STARTINDEX[73];
const uint32_t LUT_SUPPORTPOINTS[73];
const float LUT_FREQUENCYS[73];
const uint32_t LFO_ENDINDEX[5];
const uint32_t LFO_STARTINDEX[5];
const uint32_t LFO_SUPPORTPOINTS[5];
const float LFO_FREQUENCYS[5];
#endif
