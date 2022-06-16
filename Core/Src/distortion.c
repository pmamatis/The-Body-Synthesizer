/**
 * @file distortion.c
 * @author Marc Bielen
 * @brief Distortion effect
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "distortion.h"
#include "atanLUT.h"


/**
 * @brief	Distortion init functions
 *
 * @param	Distortion
 */
Distortion_Status Distortion_Init(void) {

	SetupHardClippingDistortion(&HardClipping);
	SetupSoftClippingDistortion(&SoftClipping);

	return DISTORTION_OK;
}

/**
 * @brief This function resets the distortion variables to its initial state
 * 
 * @return Distortion_Status 
 */
Distortion_Status Distortion_Reset(void) {

	Display.Distortion_ONOFF = false;

	Display.Distortion_Gain = SoftClipping.distortion_gain = 1.0;

	Display.Distortion_Sources = POTI;

	Display.Distortion_Type = 0;	// Soft Clipping

	strcpy(Display.value_str_distortion[1], "Soft");

	strcpy(Display.value_str_distortion[0], "OFF");

	return DISTORTION_OK;
}
/**
 * @brief 
 * 
 * @param HardClipping 
 * @return Distortion_Status 
 */
Distortion_Status SetupHardClippingDistortion(struct effects_distortion* HardClipping) {

	HardClipping->distortion_gain = 1.0;
	HardClipping->distortion_maximum_gain = 9;

	return DISTORTION_OK;
}

/**
 * @brief 
 * 
 * @param SoftClipping 
 * @return Distortion_Status 
 */
Distortion_Status SetupSoftClippingDistortion(struct effects_distortion* SoftClipping) {

	SoftClipping->distortion_gain = 1.0;

	// 10 different distortion gain values, so the effect can be increased step-wise
	SoftClipping->atan_softclipping_distortion_max[0] = 0.392650;	// distortion_gain = 1.0
	SoftClipping->atan_softclipping_distortion_max[1] = 0.553650;	// distortion_gain = 2.0
	SoftClipping->atan_softclipping_distortion_max[2] = 0.624500;	// distortion_gain = 3.0
	SoftClipping->atan_softclipping_distortion_max[3] = 0.662950;	// distortion_gain = 4.0
	SoftClipping->atan_softclipping_distortion_max[4] = 0.686700;	// distortion_gain = 5.0
	SoftClipping->atan_softclipping_distortion_max[5] = 0.702850;	// distortion_gain = 6.0
	SoftClipping->atan_softclipping_distortion_max[6] = 0.714450;	// distortion_gain = 7.0
	SoftClipping->atan_softclipping_distortion_max[7] = 0.723200;	// distortion_gain = 8.0
	SoftClipping->atan_softclipping_distortion_max[8] = 0.730050;	// distortion_gain = 9.0
	SoftClipping->atan_softclipping_distortion_max[9] = 0.735550;	// distortion_gain = 10.0

	SoftClipping->distortion_maximum_gain = 10.0;

	return DISTORTION_OK;
}

/**
 * @brief 
 * 
 * @param data 
 * @return Distortion_Status 
 */
Distortion_Status ProcessHardClippingDistortion(float* data) {

	float calc = *data;

	if( HardClipping.distortion_gain * calc <= -1 ) {
		calc = -1;
	}
	else if( (HardClipping.distortion_gain * calc > -1) && (HardClipping.distortion_gain * calc < 1) ) {
		calc = HardClipping.distortion_gain * calc;
	}
	else if( HardClipping.distortion_gain * calc >= 1 ) {
		calc = 1;
	}

	*data = calc;

	return DISTORTION_OK;
}

/**
 * @brief 
 * 
 * @param data 
 * @return Distortion_Status 
 */
Distortion_Status ProcessSoftClippingDistortion(float* data) {

	float calc = *data;


	// Sinnvoller Gain: 1 - 10
	// Use known Arcustangens values, which have been estimated (LUT-style)

	SoftClipping.atan_parameter = (SoftClipping.distortion_gain * calc) + 10;	// SoftClipping.distortion_maximum_gain = 10
	SoftClipping.distortion_index = round(SoftClipping.atan_parameter/aquidistance);
	calc = 0.5*atan_LUT_y[SoftClipping.distortion_index];

	// scale down the amplitude
	if(0.0 <= SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 1.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[0]);

	else if(1.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 2.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[1]);

	else if(2.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 3.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[2]);

	else if(3.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 4.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[3]);

	else if(4.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 5.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[4]);

	else if(5.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 6.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[5]);

	else if(6.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 7.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[6]);

	else if(7.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 8.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[7]);

	else if(8.0 < SoftClipping.distortion_gain && SoftClipping.distortion_gain <= 9.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[8]);

	else if(SoftClipping.distortion_gain > 9.0)
		calc = calc * (1.f/SoftClipping.atan_softclipping_distortion_max[9]);

	*data = calc;

	return DISTORTION_OK;
}
