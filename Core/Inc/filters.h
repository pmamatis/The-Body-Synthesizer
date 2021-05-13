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

	float a1, a2, b0, b1, b2;
	float z[4];
};


struct BQFilter EQ_BAND1;
struct BQFilter EQ_BAND2;
struct BQFilter EQ_BAND3;
struct BQFilter EQ_BAND4;
struct BQFilter EQ_BAND5;

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

Filter_Status SetupLowpass (struct BQFilter *LP, float cutoff, float Q);
Filter_Status SetupHighpass(struct BQFilter *HP, float cutoff, float Q);
Filter_Status SetupBandpass(struct BQFilter BP[2], float cutoff_LP, float cutoff_HP, float QLP, float QHP);

Filter_Status ProcessFilter(struct BQFilter *F,  float *data);
Filter_Status ProcessBP    (struct BQFilter BP[2], float data[], uint16_t end);


#endif /* INC_MUSIC_NOTES_H_ */
