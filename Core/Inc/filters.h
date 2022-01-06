#ifndef INC_FILTERS_H_
#define INC_FILTERS_H_

#include "main.h"

/*********************************
 * @brief		Biquad Filter struct
 * @parameter	BQFilter
 *********************************/
struct BQFilter {

	float Q;
	float cutoff;
	float dBGain;
	float a0, a1, a2, b0, b1, b2;
	float z[4];

	float maximum_Q;
	float maximum_cutoff;
	float maximum_dBGain;
};

uint32_t ADC_value;
uint32_t ADC_value_deb;
uint32_t flag;

// Equalizer
struct BQFilter EQ_BAND1;
struct BQFilter EQ_BAND2;
struct BQFilter EQ_BAND3;
struct BQFilter EQ_BAND4;
struct BQFilter EQ_BAND5;

// WahWah
struct BQFilter BP_WAHWAH;

// Drums
struct BQFilter LS_DRUMS;

// Anti-Aliasing
struct BQFilter LP_AA;

/***************************
 * @brief Enumeration for Filter Debugging
 ***************************/
typedef enum {
	FILTER_FAIL = -1,
	FILTER_OK = 1
} Filter_Status;

/*********************************
 * @brief	Functions
 *********************************/
Filter_Status Filters_Init(void);
Filter_Status Filters_Reinit_Poti(void);
Filter_Status Filters_Reinit_Gyro(float cutoff);
Filter_Status DrumFilters_Reinit_Gyro(float cutoff_d, float Qfactor_d, float gain_d);
Filter_Status Equalizer_Reset(void);
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
