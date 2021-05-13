/**
 ******************************************************************************
 * @file    distortion.c
 * @author  Marc Bielen
 * @date 	 10 May 2020
 * @brief	 Distortion-Library
 */

#include "distortion.h"

/*********************************
 * @brief		Distortion functions
 * @parameter	Distortion
 *********************************/
Distortion_Status Distortion_Init(void) {

	SetupHardClippingDistortion(&HardClipping1);
	SetupAtanSoftClippingDistortion(&AtanSoftClipping1);

	return DISTORTION_OK;
}

Distortion_Status SetupHardClippingDistortion(struct effects_distortion* HardClipping) {

	//HardClipping->distortion_gain = 1.0;	// default -> no clipping
	HardClipping->distortion_gain = 3.0;

	return DISTORTION_OK;
}

Distortion_Status SetupAtanSoftClippingDistortion(struct effects_distortion* AtanSoftClipping) {

	AtanSoftClipping->last_distortion_gain = 0.0;	// MUSS ZU BEGINN VON distortion_gain ABWEICHEN!
	//AtanSoftClipping->distortion_gain = 1.0;
	AtanSoftClipping->distortion_gain = 10.0;
	AtanSoftClipping->min_distortion_calculatevector = 0.0;
	AtanSoftClipping->max_distortion_calculatevector = 0.0;
	AtanSoftClipping-> atan_softclipping_option = 1;	// 0=optionA; 1=optionB; 2=optionC

	// AtanSoftClipping Option A: 10 different distortion gain values, so the effect can be increased step-wise
	AtanSoftClipping->atan_softclipping_distortion_max[0] = 0.392650008;	// distortion_gain = 1.0
	AtanSoftClipping->atan_softclipping_distortion_max[1] = 0.553650022;	// distortion_gain = 2.0
	AtanSoftClipping->atan_softclipping_distortion_max[2] = 0.624499977;	// distortion_gain = 3.0
	AtanSoftClipping->atan_softclipping_distortion_max[3] = 0.662949979;	// distortion_gain = 4.0
	AtanSoftClipping->atan_softclipping_distortion_max[4] = 0.686699986;	// distortion_gain = 5.0
	AtanSoftClipping->atan_softclipping_distortion_max[5] = 0.702849984;	// distortion_gain = 6.0
	AtanSoftClipping->atan_softclipping_distortion_max[6] = 0.714450002;	// distortion_gain = 7.0
	AtanSoftClipping->atan_softclipping_distortion_max[7] = 0.723200023;	// distortion_gain = 8.0
	AtanSoftClipping->atan_softclipping_distortion_max[8] = 0.730050027;	// distortion_gain = 9.0
	AtanSoftClipping->atan_softclipping_distortion_max[9] = 0.735549986;	// distortion_gain = 10.0

	return DISTORTION_OK;
}

Distortion_Status ProcessHardClippingDistortion(struct effects_distortion* HardClipping, float* data) {

	float calc = *data;

	if( HardClipping->distortion_gain * calc <= -1 ) {
		calc = -1;
	}
	else if( (HardClipping->distortion_gain * calc > -1) && (HardClipping->distortion_gain * calc < 1) ) {
		calc = HardClipping->distortion_gain * calc;
	}
	else if( HardClipping->distortion_gain * calc >= 1 ) {
		calc = 1;
	}

	*data = calc;

	return DISTORTION_OK;
}

Distortion_Status ProcessAtanSoftClippingDistortion(struct effects_distortion* AtanSoftClipping, float* data) {

	float32_t calc = *data;

	if(AtanSoftClipping->atan_softclipping_option == 0) {	// optionA: use known values, which have been estimated (LUT-style)

		AtanSoftClipping->atan_parameter = (AtanSoftClipping->distortion_gain * calc) + 10;
		AtanSoftClipping->distortion_index = round(AtanSoftClipping->atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[AtanSoftClipping->distortion_index];	// scale down the amplitude

		if(AtanSoftClipping->distortion_gain == 1.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[0]);

		else if(AtanSoftClipping->distortion_gain == 2.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[1]);

		else if(AtanSoftClipping->distortion_gain == 3.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[2]);

		else if(AtanSoftClipping->distortion_gain == 4.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[3]);

		else if(AtanSoftClipping->distortion_gain == 5.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[4]);

		else if(AtanSoftClipping->distortion_gain == 6.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[5]);

		else if(AtanSoftClipping->distortion_gain == 7.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[6]);

		else if(AtanSoftClipping->distortion_gain == 8.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[7]);

		else if(AtanSoftClipping->distortion_gain == 9.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[8]);

		else if(AtanSoftClipping->distortion_gain == 10.0)
			calc = calc * (1.f/AtanSoftClipping->atan_softclipping_distortion_max[9]);
	}

	else if(AtanSoftClipping->atan_softclipping_option == 1) {	// optionB
		AtanSoftClipping->atan_parameter = (AtanSoftClipping->distortion_gain * calc) + 10;
		AtanSoftClipping->distortion_index = round(AtanSoftClipping->atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[AtanSoftClipping->distortion_index];	// scale down the amplitude
	}

	else if(AtanSoftClipping->atan_softclipping_option == 2) {	// optionC
		calc = tanh(AtanSoftClipping->distortion_gain * calc);
	}
	//float32_t arm_sin_f32 (float32_t x)
	//float32_t arm_cos_f32 (float32_t x)
	//calc = arm_sin_f32(calc) / arcm_cos_f32(calc);

	*data = calc;

	return DISTORTION_OK;
}
