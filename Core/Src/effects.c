/*
 * effects.c
 *
 *  Created on: 12.08.2020
 *      Author: Marc Bielen
 */

#include "effects.h"

float Tremolo(struct effects_LFO* effect, float LFO_Depth, float calculate_vector) {
	Signal_Synthesis_LFO(&tremollo);	// calculates new LFO value and saves it into effects_LFO
	float tremolo_mod = (1 + LFO_Depth * effect_LFO[tremollo.lfo_blocksizecounter]);
	//calculate_vector1[BLOCKSIZE_counter] = (tremolo_mod * calculate_vector1[BLOCKSIZE_counter]) / (1+LFO_Depth);
	calculate_vector = (tremolo_mod * calculate_vector) / (1+LFO_Depth);
	tremollo.lfo_blocksizecounter++;

	return calculate_vector;
}
/*float Tremolo(struct effects_LFO* effect, float calculate_vector) {
	Signal_Synthesis_LFO(&tremollo);	// calculates new LFO value and saves it into effects_LFO
	float tremolo_mod = (1 + tremollo.lfo_depth * effect_LFO[tremollo.lfo_blocksizecounter]);
	//calculate_vector1[BLOCKSIZE_counter] = (tremolo_mod * calculate_vector1[BLOCKSIZE_counter]) / (1+LFO_Depth);
	calculate_vector = (tremolo_mod * calculate_vector) / (1+tremollo.lfo_depth);
	tremollo.lfo_blocksizecounter++;

	return calculate_vector;
}*/

float HardClippingDistortion(struct effects_distortion* effect, float Distortion_Gain, float calculate_vector) {
	if( Distortion_Gain * calculate_vector <= -1 ) {
		calculate_vector = -1;
	}
	else if( (Distortion_Gain * calculate_vector > -1) && (Distortion_Gain * calculate_vector < 1) ) {
		calculate_vector = Distortion_Gain * calculate_vector;
	}
	else if( Distortion_Gain * calculate_vector >= 1 ) {
		calculate_vector = 1;
	}

	return calculate_vector;
}

float atanSoftClippingDistortion(struct effects_distortion* effect, float calculate_vector) {
	//atan_parameter = distortion.distortion_gain * calculate_vector1[BLOCKSIZE_counter]+(10-aquidistance);
	distortion.atan_parameter = (distortion.distortion_gain * calculate_vector) + 10;
	distortion.distortion_index = round(distortion.atan_parameter/aquidistance);
	calculate_vector = 0.5*atan_LUT_y[distortion.distortion_index];	// scale down the amplitude
}
