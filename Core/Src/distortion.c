/**
 ******************************************************************************
 * @file    distortion.c
 * @author  Marc Bielen
 * @date 	 10 May 2020
 * @brief	 Distortion-Library
 */

#include "distortion.h"
#include "atanLUT.h"

/*********************************
 * @brief		Distortion functions
 * @parameter	Distortion
 *********************************/
Distortion_Status Distortion_Init(void) {

	SetupHardClippingDistortion(&HardClipping);
	SetupAtanSoftClippingDistortion(&SoftClipping);

	return DISTORTION_OK;
}

Distortion_Status SetupHardClippingDistortion(struct effects_distortion* HardClipping) {

	HardClipping->distortion_gain = 9.0;	// default -> no clipping
	HardClipping->distortion_maximum_gain = 9;

	return DISTORTION_OK;
}

Distortion_Status SetupSoftClippingDistortion(struct effects_distortion* SoftClipping) {

	//SoftClipping->last_distortion_gain = 0.0;	// MUSS ZU BEGINN VON distortion_gain ABWEICHEN!
	//SoftClipping->distortion_gain = 1.0;
	SoftClipping->distortion_gain = 9.0;
	SoftClipping->min_distortion_calculatevector = 0.0;
	SoftClipping->max_distortion_calculatevector = 0.0;
	SoftClipping->softclipping_option = 2;	// 0=optionA; 1=optionB; 2=optionC

	// SoftClipping Option A: 10 different distortion gain values, so the effect can be increased step-wise
	SoftClipping->atan_softclipping_distortion_max[0] = 0.392650008;	// distortion_gain = 1.0
	SoftClipping->atan_softclipping_distortion_max[1] = 0.553650022;	// distortion_gain = 2.0
	SoftClipping->atan_softclipping_distortion_max[2] = 0.624499977;	// distortion_gain = 3.0
	SoftClipping->atan_softclipping_distortion_max[3] = 0.662949979;	// distortion_gain = 4.0
	SoftClipping->atan_softclipping_distortion_max[4] = 0.686699986;	// distortion_gain = 5.0
	SoftClipping->atan_softclipping_distortion_max[5] = 0.702849984;	// distortion_gain = 6.0
	SoftClipping->atan_softclipping_distortion_max[6] = 0.714450002;	// distortion_gain = 7.0
	SoftClipping->atan_softclipping_distortion_max[7] = 0.723200023;	// distortion_gain = 8.0
	SoftClipping->atan_softclipping_distortion_max[8] = 0.730050027;	// distortion_gain = 9.0
	SoftClipping->atan_softclipping_distortion_max[9] = 0.735549986;	// distortion_gain = 10.0

	SoftClipping->distortion_maximum_gain = 9.0;

	return DISTORTION_OK;
}

Distortion_Status SetupAtanSoftClippingDistortion(struct effects_distortion* SoftClipping) {
	//SoftClipping->last_distortion_gain = 0.0;	// MUSS ZU BEGINN VON distortion_gain ABWEICHEN!
	SoftClipping->distortion_gain = 5.0;
	SoftClipping->min_distortion_calculatevector = 0.0;
	SoftClipping->max_distortion_calculatevector = 0.0;
	SoftClipping-> atan_softclipping_option = 0;	// 0=optionA; 1=optionB

	// AtanSoftClipping Option A: 10 different distortion gain values, so the effect can be increased step-wise
	SoftClipping->atan_softclipping_distortion_max[0] = 0.392650008;	// distortion_gain = 1.0
	SoftClipping->atan_softclipping_distortion_max[1] = 0.553650022;	// distortion_gain = 2.0
	SoftClipping->atan_softclipping_distortion_max[2] = 0.624499977;	// distortion_gain = 3.0
	SoftClipping->atan_softclipping_distortion_max[3] = 0.662949979;	// distortion_gain = 4.0
	SoftClipping->atan_softclipping_distortion_max[4] = 0.686699986;	// distortion_gain = 5.0
	SoftClipping->atan_softclipping_distortion_max[5] = 0.702849984;	// distortion_gain = 6.0
	SoftClipping->atan_softclipping_distortion_max[6] = 0.714450002;	// distortion_gain = 7.0
	SoftClipping->atan_softclipping_distortion_max[7] = 0.723200023;	// distortion_gain = 8.0
	SoftClipping->atan_softclipping_distortion_max[8] = 0.730050027;	// distortion_gain = 9.0
	SoftClipping->atan_softclipping_distortion_max[9] = 0.735549986;	// distortion_gain = 10.0

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

Distortion_Status ProcessSoftClippingDistortion(struct effects_distortion* SoftClipping, float* data) {

	float calc = *data;
	float in = SoftClipping->distortion_gain * calc;

	// Sinnvoller Gain: 1 - 10
	if(SoftClipping->softclipping_option == 0) {	// optionA: use known Arcustangens values, which have been estimated (LUT-style)

		SoftClipping->atan_parameter = (SoftClipping->distortion_gain * calc) + 10;
		SoftClipping->distortion_index = round(SoftClipping->atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[SoftClipping->distortion_index];	// scale down the amplitude

		if(SoftClipping->distortion_gain == 1.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[0]);

		else if(SoftClipping->distortion_gain == 2.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[1]);

		else if(SoftClipping->distortion_gain == 3.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[2]);

		else if(SoftClipping->distortion_gain == 4.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[3]);

		else if(SoftClipping->distortion_gain == 5.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[4]);

		else if(SoftClipping->distortion_gain == 6.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[5]);

		else if(SoftClipping->distortion_gain == 7.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[6]);

		else if(SoftClipping->distortion_gain == 8.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[7]);

		else if(SoftClipping->distortion_gain == 9.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[8]);

		else if(SoftClipping->distortion_gain == 10.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[9]);
	}

	else if(SoftClipping->softclipping_option == 1) {	// optionB
		SoftClipping->atan_parameter = (SoftClipping->distortion_gain * calc) + 10;	// 10 -> because distortion_max = 10
		SoftClipping->distortion_index = round(SoftClipping->atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[SoftClipping->distortion_index];	// scale down the amplitude
	}

	// sinnvoller Gain: 1 - 10, ab 10 wird das Signal schon rel. stark rechteckförmig
	else if(SoftClipping->softclipping_option == 2) {	// optionC: Soft clipping based on exponential function

		if(in > 0 && SoftClipping->distortion_gain > 1)
			calc = 1.0f - expf(-in);
		else if(in <= 0 && SoftClipping->distortion_gain > 1)
			calc = -1.0f + expf(in);
	}

	*data = calc;

	return DISTORTION_OK;
}

Distortion_Status ProcessAtanSoftClippingDistortion(struct effects_distortion* SoftClipping, float* data) {

	float calc = *data;

	if(SoftClipping->atan_softclipping_option == 0) {	// optionA: use known values, which have been estimated (LUT-style)

		SoftClipping->atan_parameter = (SoftClipping->distortion_gain * calc) + 10;
		SoftClipping->distortion_index = round(SoftClipping->atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[SoftClipping->distortion_index];	// scale down the amplitude

		if(SoftClipping->distortion_gain == 1.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[0]);

		else if(SoftClipping->distortion_gain == 2.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[1]);

		else if(SoftClipping->distortion_gain == 3.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[2]);

		else if(SoftClipping->distortion_gain == 4.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[3]);

		else if(SoftClipping->distortion_gain == 5.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[4]);

		else if(SoftClipping->distortion_gain == 6.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[5]);

		else if(SoftClipping->distortion_gain == 7.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[6]);

		else if(SoftClipping->distortion_gain == 8.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[7]);

		else if(SoftClipping->distortion_gain == 9.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[8]);

		else if(SoftClipping->distortion_gain == 10.0)
			calc = calc * (1.f/SoftClipping->atan_softclipping_distortion_max[9]);
	}

	else if(SoftClipping->atan_softclipping_option == 1) {	// optionB
		SoftClipping->atan_parameter = (SoftClipping->distortion_gain * calc) + 10;
		SoftClipping->distortion_index = round(SoftClipping->atan_parameter/aquidistance);
		calc = 0.5*atan_LUT_y[SoftClipping->distortion_index];	// scale down the amplitude
	}


	*data = calc;

	return DISTORTION_OK;
}
