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

/*********************************
 * @brief		Biquad Filter struct
 * @parameter	BQFilter
 *********************************/
struct BQFilter{
	float Q;
	float cutoff;
	float dBGain;
	float a0, a1, a2, b0, b1, b2;
	float z[4];
};

uint32_t ADC_value;
uint32_t ADC_value_deb;
uint32_t flag;

float parameter;


// Equalizer
struct BQFilter EQ_BAND1_I;

struct BQFilter EQ_BAND2_I;
struct BQFilter EQ_BAND2_II;

struct BQFilter EQ_BAND3_I;
struct BQFilter EQ_BAND3_II;

struct BQFilter EQ_BAND4_I;
struct BQFilter EQ_BAND4_II;

struct BQFilter EQ_BAND5_I;

struct BQFilter LP_WAH;
struct BQFilter HP_WAH;

struct BQFilter LP_REVERB;
struct BQFilter LP_DELAY;

struct BQFilter LP_AA;



/***************************
 * @brief		Enumeration for DSP Debugging
 ***************************/
/*typedef enum DSP_Status{
	DSP_FAIL = -1,
	DSP_OK = 1
} DSP_Status;*/

/***************************
 * @brief Enumeration for Filter Debugging
 ***************************/
typedef enum {
	FILTER_FAIL = -1,
	FILTER_OK = 1
} Filter_Status;



/*********************************
 * @parameter	Functions
 *********************************/

Filter_Status Filters_Init();
Filter_Status Filters_Reinit(float cutoff);

Filter_Status SetupLowpass    (struct BQFilter *LP, float cutoff, float Q);
Filter_Status SetupHighpass   (struct BQFilter *HP, float cutoff, float Q);
Filter_Status SetupBandpassCPG(struct BQFilter *BP, float cutoff, float Q);
Filter_Status SetupBandpassCSG(struct BQFilter *BP, float cutoff, float Q);
Filter_Status SetupNotch 	  (struct BQFilter *BP, float cutoff, float Q);
Filter_Status SetupPeakingEQ  (struct BQFilter *BP, float cutoff, float Q, float dBGain);
Filter_Status SetupLowShelf   (struct BQFilter *LS, float cutoff, float Q, float dBGain);
Filter_Status SetupHighShelf  (struct BQFilter *HS, float cutoff, float Q, float dBGain);

Filter_Status ProcessFilter(struct BQFilter *F,  float *data);
Filter_Status ProcessEQ    (float *data);



#endif /* INC_MUSIC_NOTES_H_ */
