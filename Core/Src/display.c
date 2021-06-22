/*
 * display.c
 *
 *  Created on: 21.01.2021
 *      Author: Marc Bielen
 */

#include "display.h"

Display_Status Display_Init(struct display_variables* Display) {

	Display->PatchSelected[0] = false;				// PatchSelected
	Display->PatchSelected[1] = false;
	Display->PatchSelected[2] = false;

	Display->ModuleStateSelected[0] = false;		// ModuleStateSelected
	Display->ModuleStateSelected[1] = false;
	Display->ModuleStateSelected[2] = false;

	Display->ModuleParametersSelected[0] = false;	// ModuleParametersSelected
	Display->ModuleParametersSelected[1] = false;
	Display->ModuleParametersSelected[2] = false;

	Display->ModuleCompleted[0] = false;			// ModuleCompleted
	Display->ModuleCompleted[1] = false;
	Display->ModuleCompleted[2] = false;

	Display->CurrentModule = 0;						// CurrentModule

	Display->KeyboardmodeSelected = false;			// KeyboardmodeSelected

	Display->Keyboardmode_ONOFF = false;			// Keyboardmode_ONOFF

	Display->ActiveEffectsCounter = 0;				// ActiveEffectsCounter

	Display->Voices_ONOFF[0] = false;				// Voices_ONOFF
	Display->Voices_ONOFF[1] = false;
	Display->Voices_ONOFF[2] = false;

	Display->ADSR_ONOFF = false;					// ADSR_ONOFF
	Display->ADSR_Attack = 0.0;						// ADSR_Attack
	Display->ADSR_Decay = 0.0;						// ADSR_Decay
	Display->ADSR_Sustain = 1.0;					// ADSR_Sustain
	Display->ADSR_Release = 0.0;					// ADSR_Release
	Display->ADSR_EffectPosition = 0;				// ADSR_EffectPosition
	Display->ADSR_EffectAdded = false;				// ADSR_EffectAdded

	Display->Distortion_ONOFF = false;				// Distortion_ONOFF
	Display->Distortion_Type = false;				// Distortion_Type
	Display->Distortion_Gain = 1.0;					// Distortion_Gain
	Display->Distortion_EffectPosition = 0;			// Distortion_EffectPosition
	Display->Distortion_EffectAdded = false;		// Distortion_EffectAdded

	Display->Tremolo_ONOFF = false;					// Tremolo_ONOFF
	Display->Tremolo_Rate = 0.0;					// Tremolo_Rate
	Display->Tremolo_Depth = 0.0;					// Tremolo_Depth
	Display->Tremolo_EffectPosition = 0;			// Tremolo_EffectPosition
	Display->Tremolo_EffectAdded = false;			// Tremolo_EffectAdded

	Display->Filter_ONOFF = false;					// Filter_ONOFF
	Display->Filter_Cutoff = 1.0;					// Filter_Cutoff
	Display->Filter_Q = 1.0;						// Filter_Q
	Display->Filter_EffectPosition = 0;				// Filter_EffectPosition
	Display->Filter_EffectAdded = false;			// Filter_EffectAdded
	// Weitere Synth-Parameter...

	Display->LowerLimit = 95;						// LowerLimit
	Display->UpperLimit = 4000;						// UpperLimit
	Display->ADC_FullRange = 4095;					// ADC_FullRange

	Display->JoystickPatchPosition = 1;				// JoystickPatchPosition
	Display->JoystickParameterPosition = 1;			// JoystickParameterPosition

	Display->ENTER_Debounce_State = true;			// ENTER_Debounce_State
	Display->BACK_Debounce_State = true;			// BACK_Debounce_State
	Display->SW_Debounce_State = true;				// SW_Debounce_State
	Display->ENTER = false;							// ENTER
	Display->BACK = false;							// BACK
	Display->SW = false;							// SW

	return DISPLAY_OK;
}
