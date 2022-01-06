/**
 ******************************************************************************
 * @file    distortion.c
 * @author  Marc Bielen
 * @date 	 10 May 2020
 * @brief	 Distortion-Library
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

/** TODO
 * @brief 
 * 
 * @return Distortion_Status 
 */
Distortion_Status Distortion_Reset(void) {

	Display.Distortion_ONOFF = false;

	//	Display.Distortion_Gain = SoftClipping.distortion_gain = 0.0;
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
	SoftClipping->softclipping_option = 0;	// 0=option A; 1=option B; 2=option C

	// SoftClipping Option A: 10 different distortion gain values, so the effect can be increased step-wise
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

	SoftClipping->softclipping_distortion_max[0] = 0.999990;	// distortion gain of 0.0
	SoftClipping->softclipping_distortion_max[1] = 0.966691;	// distortion gain of 0.1
	SoftClipping->softclipping_distortion_max[2] = 0.933392;	// distortion gain of 0.2
	SoftClipping->softclipping_distortion_max[3] = 0.900093;	// distortion gain of 0.3
	SoftClipping->softclipping_distortion_max[4] = 0.866794;	// distortion gain of 0.4
	SoftClipping->softclipping_distortion_max[5] = 0.833495;	// distortion gain of 0.5
	SoftClipping->softclipping_distortion_max[6] = 0.800196;	// distortion gain of 0.6
	SoftClipping->softclipping_distortion_max[7] = 0.766897;	// distortion gain of 0.7
	SoftClipping->softclipping_distortion_max[8] = 0.733598;	// distortion gain of 0.8
	SoftClipping->softclipping_distortion_max[9] = 0.700299;	// distortion gain of 0.9
	SoftClipping->softclipping_distortion_max[10] = 0.667000;	// distortion gain of 1.0

	//	SoftClipping->distortion_maximum_gain = 1.0;
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
	if(SoftClipping.softclipping_option == 0) {	// option A: use known Arcustangens values, which have been estimated (LUT-style)

		SoftClipping.atan_parameter = (SoftClipping.distortion_gain * calc) + 10;
		SoftClipping.distortion_index = round(SoftClipping.atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[SoftClipping.distortion_index];	// scale down the amplitude

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
	}

	else if(SoftClipping.softclipping_option == 1) {	// option B

		SoftClipping.atan_parameter = (SoftClipping.distortion_gain * calc) + 10;	// 10 -> because distortion_max = 10
		SoftClipping.distortion_index = round(SoftClipping.atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[SoftClipping.distortion_index];	// scale down the amplitude
	}

	else if(SoftClipping.softclipping_option == 2) {	// option C: Soft clipping based on exponential function

		float in = SoftClipping.distortion_gain * calc;

		if(in > 0 && SoftClipping.distortion_gain > 1)
			calc = 1.0f - expf(-in);
		else if(in <= 0 && SoftClipping.distortion_gain > 1)
			calc = -1.0f + expf(in);
	}

	*data = calc;

	return DISTORTION_OK;
}
