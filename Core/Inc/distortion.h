/** TODO
 * @file distortion.h
 * @author marc bielen
 * @brief distortion effect
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
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
	float atan_softclipping_distortion_max[10];	// 10 different distortion gain values, so the effect can be increased step-wise
	uint8_t distortion_maximum_gain;
};

/*********************************
 * @beief	Variables
 *********************************/
struct effects_distortion HardClipping;
struct effects_distortion SoftClipping;

extern const float aquidistance;
extern const float atan_LUT_y[8192];	// blocksize = 8192

/*********************************
 * @brief	Functions
 *********************************/
Distortion_Status Distortion_Init(void);
Distortion_Status Distortion_Reset(void);
Distortion_Status SetupHardClippingDistortion(struct effects_distortion* HardClipping);
Distortion_Status SetupSoftClippingDistortion(struct effects_distortion* SoftClipping);
Distortion_Status ProcessHardClippingDistortion(float* data);
Distortion_Status ProcessSoftClippingDistortion(float* data);

#endif /* INC_DISTORTION_H_ */
