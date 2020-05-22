/**
  ******************************************************************************
  * @file    filters.h
  * @author  Max Lehmer
  * @date 	 07 May 2020
  * @brief	 Filter-Library
*/

#ifndef INC_FILTERS_H_
#define INC_FILTERS_H_

#include "main.h"

/*********************************
 * @brief		Defines
 *********************************/
#define BUFFERSIZE	65536
#define CLOCK		108000000
#define TIMPERIOD	1125
#define SAMPLERATE	96000

/***************************
 * @brief		Enumeration for DSP Debugging
 ***************************/
typedef enum{
	DSP_FAIL = -1,
	DSP_OK = 1
} DSP_Status;

/*********************************
 * @brief		Biquad Filter struct
 * @parameter	BQFilter
 *********************************/
struct BQFilter{

	float a1, a2, b0, b1, b2;
	float z[4];
};


/*********************************
 * @parameter	Functions
 *********************************/
DSP_Status SetupLowpass (struct BQFilter LP, float cutoff, float Q);
DSP_Status SetupHighpass(struct BQFilter HP, float cutoff, float Q);
DSP_Status SetupBandpass(struct BQFilter LP, struct BQFilter HP, float cutoff_LP, float cutoff_HP, float QLP, float QHP);

DSP_Status ProcessFilter(struct BQFilter F,  float data[], uint16_t end);
DSP_Status ProcessBP    (struct BQFilter F1, struct BQFilter F2, float data[], uint16_t end);


#endif /* INC_MUSIC_NOTES_H_ */
