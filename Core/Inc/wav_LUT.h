/**
 * @file wav_LUT.h
 * @author max lehmer & marc bielen
 * @brief memory saver for the drumcomputer wav-samples
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INC_WAV_LUT_H_
#define INC_WAV_LUT_H_

// Length of the Drumcomputer/PlaySingleSample arrays
# define DS_L 10000

// Sample bins
float DS1[DS_L];
float DS2[DS_L];
float DS3[DS_L];
float DS4[DS_L];
float PSS[DS_L];

#endif
