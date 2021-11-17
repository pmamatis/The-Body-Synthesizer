/**
 ******************************************************************************
 * @file    distortion.h
 * @author  Marc Bielen
 * @date 	 10 May 2020
 * @brief	 Distortion-Library
 */

#ifndef INC_DISTORTION_H_
#define INC_DISTORTION_H_

#include "main.h"

/***************************
 * @brief Enumeration for Distortion Debugging
 ***************************/
typedef enum {
	DISTORTION_FAIL = -1,
	DISTORTION_OK = 1
} Distortion_Status;

/*********************************
 * @brief		Distortion struct
 * @parameter	Distortion
 *********************************/
struct effects_distortion{

	float distortion_gain;
	float atan_parameter;
	unsigned int distortion_index;
	uint8_t softclipping_option;
	float distortion_threshold;

	bool atan_softclipping_option;

	// distortion_gain = 1.0 -> +-0.392650008
	// distortion_gain = 2.0 -> +-0.553650022
	// distortion_gain = 3.0 -> +-0.624499977
	// distortion_gain = 4.0 -> +-0.662949979
	// distortion_gain = 5.0 -> +-0.686699986
	// distortion_gain = 6.0 -> +-0.702849984
	// distortion_gain = 7.0 -> +-0.714450002
	// distortion_gain = 8.0 -> +-0.723200023
	// distortion_gain = 9.0 -> +-0.730050027
	// distortion_gain = 10.0 -> +-0.735549986
	float atan_softclipping_distortion_max[10];	// 10 different distortion gain values, so the effect can be increased step-wise
	float softclipping_distortion_max[11];	// LUT for softclipping to normalize the values to -1 to +1 amplitude

	//float distortion_maximum_gain;
	uint8_t distortion_maximum_gain;
};

/*% softclipping-atan lookup-table generation in MATLAB
	blocksize = 8192;
	max_distortion_gain = 10;
	values = linspace(-max_distortion_gain, max_distortion_gain, blocksize);
	aquidistance = (2*max_distortion_gain) / (blocksize-1);
	atan_LUT = atan(values);
	atan_LUT_rounded = round(atan_LUT,4);  % runden und transponieren
	tt = 1:blocksize;
	figure(4)
	plot(tt, atan_LUT_rounded); grid on
	csvwrite('atan_LUT_y.txt',atan_LUT_rounded)
	csvwrite('atan_LUT_x.txt',values)
	dlmwrite('aquidistance.txt', aquidistance, 'delimiter', ',', 'precision', 15);*/
extern const float aquidistance;
extern const float atan_LUT_y[8192];	// blocksize = 8192

struct effects_distortion HardClipping;
struct effects_distortion SoftClipping;

Distortion_Status Distortion_Init(void);
Distortion_Status Distortion_Reset(void);
Distortion_Status SetupHardClippingDistortion(struct effects_distortion* HardClipping);
Distortion_Status SetupSoftClippingDistortion(struct effects_distortion* SoftClipping);
Distortion_Status ProcessHardClippingDistortion(float* data);
Distortion_Status ProcessSoftClippingDistortion(float* data);

#endif /* INC_DISTORTION_H_ */
