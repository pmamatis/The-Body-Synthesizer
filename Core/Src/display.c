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
	// Weitere Synthesizer-Parameter...

	Display->last_rate = 0;
	Display->rate = 0;
	Display->last_depth = 0;
	Display->depth = 0;
	Display->last_cutoff = 0;
	Display->cutoff = 0;
	Display->last_Q = 0;
	Display->Q = 0;
	Display->last_distortion_gain = 0;
	Display->distortion_gain = 0;
	Display->last_attack = 0;
	Display->attack = 0;
	Display->last_decay = 0;
	Display->decay = 0;
	Display->last_sustain = 0;
	Display->sustain = 0;
	Display->last_release = 0;
	Display->release = 0;

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

Display_Status Display_Start(void) {
	// you have to edit the startup_stm32fxxx.s file and set a big enough heap size
	frame_buffer = (unsigned char*)malloc(EPD_WIDTH * EPD_HEIGHT / 8);

	// Display Init
	//	EPD epd;
	//EPD_Reset(&epd);

	if (EPD_Init(&epd, lut_full_update) != 0) {
		printf("e-Paper init failed\n");
		//return -1;
	}

	//	Paint paint;
	Paint_Init(&paint, frame_buffer, epd.width, epd.height);
	Paint_Clear(&paint, UNCOLORED);

	if (EPD_Init(&epd, lut_partial_update) != 0) {
		printf("e-Paper init failed\n");
		//return -1;
	}

	//	there are 2 memory areas embedded in the e-paper display
	//	and once the display is refreshed, the memory area will be auto-toggled,
	//	i.e. the next action of SetFrameMemory will set the other memory area
	//	therefore you have to set the frame memory and refresh the display twice.

	for(int i=0; i<EPD_WIDTH*EPD_HEIGHT; i++) {	// fill the BLACKSCREEN-array with values to show a black screen in the beginning
		BLACKSCREEN[i] = 0X00;
	}
	EPD_SetFrameMemory(&epd, BLACKSCREEN, 0, 0, epd.width, epd.height);
	EPD_DisplayFrame(&epd);
	EPD_SetFrameMemory(&epd, BLACKSCREEN, 0, 0, epd.width, epd.height);
	EPD_DisplayFrame(&epd);
	//	EPD_DelayMs(&epd, 300);
	//	HAL_Delay(1000);

	Paint_Clear(&paint, UNCOLORED);
	EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
	EPD_DisplayFrame(&epd);

	Paint_SetRotate(&paint, ROTATE_270);

	return DISPLAY_OK;
}

Display_Status PatchSelectionMenu(struct display_variables* Display, Paint paint, EPD epd, unsigned char* frame_buffer) {

	Paint_DrawStringAt(&paint, 1, 10, "THE BODYSYNTH", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, 30, "Choose a Patch you wanna use", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, 60, "Patch 1", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, 80, "Patch 2", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, 100, "Patch 3", &Font16, COLORED);

	while((Display->PatchSelected[0]==false) && (Display->PatchSelected[1]==false) && (Display->PatchSelected[2]==false)) {

		Display->VRy = Display->ADC2inputs[1];

		if( (Display->JoystickPatchPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
			Paint_DrawStringAt(&paint, 100, 60, "<---", &Font16, COLORED);	// draw arrow on Patch 1
		}
		else if( (Display->JoystickPatchPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
			Paint_DrawFilledRectangle(&paint, 100, 60, 200, 70, UNCOLORED);	// leave Patch 1 and draw arrow on Patch 2
			Paint_DrawStringAt(&paint, 100, 80, "<---", &Font16, COLORED);
			Display->JoystickPatchPosition = 2;
		}
		else if( (Display->JoystickPatchPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
			Paint_DrawFilledRectangle(&paint, 100, 80, 200, 90, UNCOLORED);	// leave Patch 2 and draw arrow on Patch 1
			Paint_DrawStringAt(&paint, 100, 60, "<---", &Font16, COLORED);
			Display->JoystickPatchPosition = 1;
		}
		else if( (Display->JoystickPatchPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
			Paint_DrawFilledRectangle(&paint, 100, 80, 200, 90, UNCOLORED);	// leave Patch 2 and draw arrow on Patch 3
			Paint_DrawStringAt(&paint, 100, 100, "<---", &Font16, COLORED);
			Display->JoystickPatchPosition = 3;
		}
		else if( (Display->JoystickPatchPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
			Paint_DrawStringAt(&paint, 100, 80, "<---", &Font16, COLORED);	// draw arrow on Patch 2
		}
		else if( (Display->JoystickPatchPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
			Paint_DrawFilledRectangle(&paint, 100, 100, 200, 110, UNCOLORED);	// leave Patch 3 and draw arrow on Patch 2
			Paint_DrawStringAt(&paint, 100, 80, "<---", &Font16, COLORED);
			Display->JoystickPatchPosition = 2;
		}
		else if( (Display->JoystickPatchPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
			Paint_DrawStringAt(&paint, 100, 100, "<---", &Font16, COLORED);	// draw arrow on Patch 3
		}

		// check which patch is chosen
		if( (Display->JoystickPatchPosition == 1) && (Display->ENTER == true) ) {
			Display->PatchSelected[0] = true;
			Display->PatchSelected[1] = false;	// NECESSARY?
			Display->PatchSelected[2] = false;	// NECESSARY?
			Paint_Clear(&paint, UNCOLORED);
			Paint_DrawStringAt(&paint, 10, 10, "Patch 1 picked", &Font16, COLORED);
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);
			HAL_Delay(1000);	// NECESSARY?
			Paint_Clear(&paint, UNCOLORED);	// clear display
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);
		}
		else if( (Display->JoystickPatchPosition == 2) && (Display->ENTER == true) ) {
			Display->PatchSelected[0] = false;	// NECESSARY?
			Display->PatchSelected[1] = true;
			Display->PatchSelected[2] = false;	// NECESSARY?
			Paint_Clear(&paint, UNCOLORED);
			Paint_DrawStringAt(&paint, 10, 10, "Patch 2 picked", &Font16, COLORED);
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);
			HAL_Delay(1000);	// NECESSARY?
			Paint_Clear(&paint, UNCOLORED);	// clear display
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);
		}
		else if( (Display->JoystickPatchPosition == 3) && (Display->ENTER == true) ) {
			Display->PatchSelected[0] = false;	// NECESSARY?
			Display->PatchSelected[1] = false;	// NECESSARY?
			Display->PatchSelected[2] = true;
			Paint_Clear(&paint, UNCOLORED);
			Paint_DrawStringAt(&paint, 10, 10, "Patch 3 picked", &Font16, COLORED);
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);
			HAL_Delay(1000);	// NECESSARY?
			Paint_Clear(&paint, UNCOLORED);	// clear display
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);
		}

		// Display the frame_buffer
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
		EPD_DisplayFrame(&epd);

		// reset BACK-switch
		//if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_SET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
		if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {
			Display->BACK = false;
		}
		// reset ENTER-switch
		if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
			Display->ENTER = false;
		}
	}

	return DISPLAY_OK;
}

Display_Status SelectKeyboardmode(struct display_variables* Display, Paint paint, EPD epd, unsigned char* frame_buffer) {

	while(Display->KeyboardmodeSelected == false) {

		Paint_DrawStringAt(&paint, 1, 10, "THE BODYSYNTH", &Font16, COLORED);
		Paint_DrawStringAt(&paint, 1, 30, "Keyboardmode ON/OFF", &Font12, COLORED);

		Display->VRx = Display->ADC2inputs[0];		// read joystick-x-value
		Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

		if(Display->Poti_raw < Display->ADC_FullRange/2) {
			Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
			Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
			Display->Keyboardmode_ONOFF = false;
		}
		else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
			Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
			Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
			Display->Keyboardmode_ONOFF = true;
		}

		if(Display->VRx < Display->LowerLimit) {
			Display->KeyboardmodeSelected = true;
			Paint_Clear(&paint, UNCOLORED);	// clear display
		}

		// Display the frame_buffer
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
		EPD_DisplayFrame(&epd);
	}

	return DISPLAY_OK;
}

void SetParameters(struct display_variables* Display, struct signal_t* signals, struct BQFilter* Filter, struct adsr* envelope, struct effects_distortion* SoftClipping, struct effects_distortion* HardClipping, struct effects_LFO* Tremolo, Paint paint, EPD epd, unsigned char* frame_buffer) {

	while(Display->KeyboardmodeSelected == true) {

		// KEYBOARDMODE
		if(Display->Keyboardmode_ONOFF == true) {

			Paint_DrawStringAt(&paint, 1, 10, "KEYBOARDMODE", &Font16, COLORED);
			Paint_DrawStringAt(&paint, 1, 30, "Octave", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 50, "Attack Time", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 70, "Decay Time", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 90, "Sustain Time", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 110, "Sustain Level", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 130, "Release Time", &Font12, COLORED);

			Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
			Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
			Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

			char octave;
			char attacktime_string[9], decaytime_string[9], sustaintime_string[9], sustainlevel_string[9], releasetime_string[9];

			if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Octave
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Octave to Attack Time
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Attack Time to Octave
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 1;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Attack Time to Decay Time
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Attack Time
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Decay Time to Attack Time
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Decay Time to Sustain Time
				Paint_DrawStringAt(&paint, 110, 90, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 4;
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Decay Time
			}
			else if( (Display->JoystickParameterPosition == 4) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 90, 150, 100, UNCOLORED);// switch from Sustain Time to Decay Time
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 4) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 90, 150, 100, UNCOLORED);// switch from Sustain Time to Sustain Level
				Paint_DrawStringAt(&paint, 110, 110, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 5;
			}
			else if( (Display->JoystickParameterPosition == 4) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 90, "<---", &Font12, COLORED);	// arrow to Sustain Time
			}
			else if( (Display->JoystickParameterPosition == 5) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 110, 150, 120, UNCOLORED);// switch from Sustain Level to Sustain Time
				Paint_DrawStringAt(&paint, 110, 90, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 4;
			}
			else if( (Display->JoystickParameterPosition == 5) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 110, 150, 120, UNCOLORED);// switch from Sustain Level to Release Time
				Paint_DrawStringAt(&paint, 110, 130, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 6;
			}
			else if( (Display->JoystickParameterPosition == 5) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 110, "<---", &Font12, COLORED);	// arrow to Sustain Level
			}
			else if( (Display->JoystickParameterPosition == 6) && (Display->VRy > Display->UpperLimit)  ) {
				Paint_DrawFilledRectangle(&paint, 110, 130, 150, 140, UNCOLORED);// switch from Release Time to Sustain Level
				Paint_DrawStringAt(&paint, 110, 110, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 5;
			}
			else if( (Display->JoystickParameterPosition == 6) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 130, "<---", &Font12, COLORED);	// arrow to Release Time
			}

			// check state of the potentiometer and assign parameter value
			// Octave
			if(Display->JoystickParameterPosition == 1) {
				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
				octave = (char) (((float)Display->Poti_raw/4096) * 6);	// 5 0ctaves
				Display->Keyboard_Octave = (uint8_t)octave;	// assign Octave
				Paint_DrawCharAt(&paint, 150, 30, octave+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen (ASCII)
			}
			// Attack Time
			else if(Display->JoystickParameterPosition == 2) {
				Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
				Display->Keyboard_AttackTime = (((float)Display->Poti_raw/4096) * envelope->adsr_maximum_attack) + 0.05;
				sprintf(attacktime_string, "%f", Display->Keyboard_AttackTime);
				Paint_DrawStringAt(&paint, 150, 50, attacktime_string, &Font12, COLORED);

				envelope->adsr_attack_time = Display->Keyboard_AttackTime * LUT_SR;
			}
			// Decay Time
			else if(Display->JoystickParameterPosition == 3) {
				Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
				Display->Keyboard_DecayTime = (((float)Display->Poti_raw/4096) * envelope->adsr_maximum_decay);
				sprintf(decaytime_string, "%f", Display->Keyboard_DecayTime);
				Paint_DrawStringAt(&paint, 150, 70, decaytime_string, &Font12, COLORED);

				envelope->adsr_decay_time = Display->Keyboard_DecayTime * LUT_SR;
			}
			// Sustain Time
			else if(Display->JoystickParameterPosition == 4) {
				Paint_DrawFilledRectangle(&paint, 150, 90, 200, 110, UNCOLORED);
				Display->Keyboard_SustainTime = (((float)Display->Poti_raw/4096) * envelope->adsr_maximum_sustaintime);
				sprintf(sustaintime_string, "%f", Display->Keyboard_SustainTime);
				Paint_DrawStringAt(&paint, 150, 90, sustaintime_string, &Font12, COLORED);

				envelope->adsr_sustain_time = Display->Keyboard_SustainTime * LUT_SR;
				//envelope->adsr_duration_time = (Display->Keyboard_AttackTime + Display->Keyboard_DecayTime + Display->Keyboard_SustainTime + Display->Keyboard_ReleaseTime) * LUT_SR;
				//envelope->adsr_duration_time = Display->Keyboard_SustainTime * LUT_SR;
			}
			// Sustain Level
			else if(Display->JoystickParameterPosition == 5) {
				Paint_DrawFilledRectangle(&paint, 150, 110, 200, 130, UNCOLORED);
				Display->Keyboard_SustainLevel = (((float)Display->Poti_raw/4096) * envelope->adsr_max_amp);
				sprintf(sustainlevel_string, "%f", Display->Keyboard_SustainLevel);
				Paint_DrawStringAt(&paint, 150, 110, sustainlevel_string, &Font12, COLORED);

				envelope->adsr_sustain_amplitude = Display->Keyboard_SustainLevel;
			}
			// Release Time
			else if(Display->JoystickParameterPosition == 6) {
				Paint_DrawFilledRectangle(&paint, 150, 130, 200, 150, UNCOLORED);
				Display->Keyboard_ReleaseTime = (((float)Display->Poti_raw/4096) * envelope->adsr_maximum_release);
				sprintf(releasetime_string, "%f", Display->Keyboard_ReleaseTime);
				Paint_DrawStringAt(&paint, 150, 130, releasetime_string, &Font12, COLORED);

				envelope->adsr_release_time = Display->Keyboard_ReleaseTime * LUT_SR;
			}

			// Display the frame_buffer
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);

			//OnePress_keyboard_process(Display->ADC1inputs[0], signals, envelope);
			//OnePress_ADSR_Linear_Process(envelope, float* calculate_value);
		}

		// SYNTHESIZERMODE
		else if(Display->Keyboardmode_ONOFF == false) {
			// effect order for patch 1
			Display->Distortion_EffectPosition = 0;
			Display->Tremolo_EffectPosition = 1;
			Display->Filter_EffectPosition = 2;

			// #############################################
			// ########### BEGIN VOICES SUBMENU ############
			// #############################################
			while(Display->CurrentModule == 0) {

				Paint_DrawStringAt(&paint, 1, 10, "Voices", &Font16, COLORED);
				Paint_DrawStringAt(&paint, 1, 30, "Voice1 ON/OFF", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 50, "Voice1 Note", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 70, "Voice1 Octave", &Font12, COLORED);

				Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
				Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
				Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

				uint8_t note, last_note;
				char octave, last_octave;

				if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Voice1 ON/OFF
				}
				else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Voice1 ON/OFF to Voice1 Note
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Voice1 Note to Voice1 ON/OFF
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 1;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Voice1 Note to Voice1 Octave
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 3;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Voice1 Note
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Note1 Octave to Voice1 Note
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Voice1 Octave
				}

				// check state of the potentiometer and assign parameter value
				// Voice1 ON/OFF
				if( (Display->JoystickParameterPosition == 1) && (Display->Poti_raw < Display->ADC_FullRange/2) ) {
					Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
					Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
					Display->Voices_ONOFF[0] = false;
				}
				else if( (Display->JoystickParameterPosition == 1) && (Display->Poti_raw >= Display->ADC_FullRange/2) ) {
					Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
					Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
					Display->Voices_ONOFF[0] = true;
				}

				// Voice1 Note
				else if(Display->JoystickParameterPosition == 2) {
					Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
					float noteindex = ((float)Display->Poti_raw/4096) * (sizeof(keys)/sizeof(keys[0]));
					note = keys[(uint8_t)noteindex];
					Display->Voices_Note[0] = note;	// assign Voice1 Note
				}

				// Voice1 Octave
				else if(Display->JoystickParameterPosition == 3) {
					Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
					octave = (char) (((float)Display->Poti_raw/4096) * 6);	// 5 0ctaves
					Display->Voices_Octave[0] = (uint8_t)octave;	// assign Voice1 Octave
				}

				if(Display->Voices_ONOFF[0] == true) {	// if Voice1 ON

					if( (last_note != note) || (last_octave != octave) ) {	// if voice parameters changed

						if(signals1.count == 1)		// Delete the last generated signal
							DeleteSignal(&signals1, 1);

						NewSignal(&signals1, SIN, Display->Voices_Note[0], Display->Voices_Octave[0]);	// create signal and assign selected parameters
						outputBuffer_position = HALF_BLOCK;
					}
				}
				else if(Display->Voices_ONOFF[0] == false) {	// if Voice1 OFF
					if(signals1.count == 1)
						DeleteSignal(&signals1, 1);
				}
				last_note = note;
				last_octave = octave;

				Paint_DrawCharAt(&paint, 150, 50, note, &Font12, COLORED);
				Paint_DrawCharAt(&paint, 150, 70, octave+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);

				//			// reset BACK-switch
				//			if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
				//				Display->BACK = false;
				//			}
				//			// reset ENTER-switch
				//			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
				//				Display->ENTER = false;
				//			}

				if(Display->VRx < Display->LowerLimit) {
					Display->CurrentModule = 1;	// forward to Distortion
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
				}
			}
			// #############################################
			// ############ END VOICES SUBMENU #############
			// #############################################


			// #############################################
			// ########## BEGIN DISTORTION SUBMENU #########
			// #############################################
			while(Display->CurrentModule == 1) {

				Paint_DrawStringAt(&paint, 1, 10, "Distortion", &Font16, COLORED);
				Paint_DrawStringAt(&paint, 1, 30, "Dist. ON/OFF", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 50, "Type", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 70, "Gain", &Font12, COLORED);

				Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
				Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
				Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

				char distortion_gain_string[9];
				sprintf(distortion_gain_string, "%f", Display->Distortion_Gain);

				if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Distortion ON/OFF
				}
				else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Distortion ON/OFF to Type
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Type to Distortion ON/OFF
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 1;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Type to Gain
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 3;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Type
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Gain to Type
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Gain
				}

				// check state of the potentiometer and assign parameter value
				// Distortion ON/OFF
				if(Display->JoystickParameterPosition == 1) {

					Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);

					if(Display->Poti_raw < Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
						Display->Distortion_ONOFF = false;
					}
					else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
						Display->Distortion_ONOFF = true;
					}
				}

				// Distortion Type
				else if(Display->JoystickParameterPosition == 2) {	// SOFT CLIPPING DIDNT WORK!!!

					Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);

					if(Display->Poti_raw < Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 50, "Soft", &Font12, COLORED);
						Display->Distortion_Type = 0;
						process_dist_soft = true;
						process_dist_hard = false;
					}
					else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 50, "Hard", &Font12, COLORED);
						Display->Distortion_Type = 1;
						process_dist_soft = false;
						process_dist_hard = true;
					}
				}

				// Distortion Gain
				else if(Display->JoystickParameterPosition == 3) {

					Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
					Display->Distortion_Gain = (((float)Display->Poti_raw/4096) * HardClipping->distortion_maximum_gain) + 1;	// +1 to prevent 0
					sprintf(distortion_gain_string, "%f", Display->Distortion_Gain);
					Display->distortion_gain = (uint16_t)(Display->Distortion_Gain * 1000);
				}

				if(Display->Distortion_ONOFF == true) {	// if Distortion ON

					if( abs(Display->last_distortion_gain-Display->distortion_gain)>1000 ) {

						if(Display->Distortion_Type == 0)
							SoftClipping->distortion_gain = Display->Distortion_Gain;
						else if(Display->Distortion_Type == 1)
							HardClipping->distortion_gain = Display->Distortion_Gain;

						//						HardClipping->distortion_gain = Display->Distortion_Gain;
						//						process_dist_hard = true;

						//					if(Display->Distortion_EffectAdded == false) {	// if no distortion effect added yet
						//
						//						effects_add(DIST_H, Display->Distortion_EffectPosition);
						//						Display->Distortion_EffectAdded = true;
						//					}
					}
				}
				else if(Display->Distortion_ONOFF == false) {	// if Distortion OFF

					process_dist_hard = false;
					process_dist_soft = false;

					//				if(Display->Distortion_EffectAdded == true) {
					//
					//					effects_delete(DIST_H, Display->Distortion_EffectPosition);
					//					Display->Distortion_EffectAdded = false;
					//				}
				}
				Display->last_distortion_gain = Display->distortion_gain;

				Paint_DrawStringAt(&paint, 150, 70, distortion_gain_string, &Font12, COLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);

				//			// reset BACK-switch
				//			if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
				//				Display->BACK = false;
				//			}
				//			// reset ENTER-switch
				//			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
				//				Display->ENTER = false;
				//			}

				if(Display->VRx > Display->UpperLimit) {
					Display->CurrentModule = 0;	// back to Voices
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
				}
				else if(Display->VRx < Display->LowerLimit) {
					Display->CurrentModule = 2;	// forward to Tremolo
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
				}
			}
			// #############################################
			// ########## END DISTORTION SUBMENU ###########
			// #############################################


			// #############################################
			// ########### BEGIN TREMOLO SUBMENU ###########
			// #############################################
			while(Display->CurrentModule == 2) {

				Paint_DrawStringAt(&paint, 1, 10, "Tremolo", &Font16, COLORED);
				Paint_DrawStringAt(&paint, 1, 30, "Tremolo ON/OFF", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 50, "Rate", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 70, "Depth", &Font12, COLORED);

				Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
				Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
				Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

				//uint16_t last_rate, rate, last_depth, depth;
				char tremolo_rate_string[9];
				//sprintf(tremolo_rate_string, "%f", Display->Tremolo_Rate);
				char tremolo_depth_string[9];
				//sprintf(tremolo_depth_string, "%f", Display->Tremolo_Depth);

				if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Tremolo ON/OFF
				}
				else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Tremolo ON/OFF to Rate
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Rate to Tremolo ON/OFF
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 1;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Rate to Depth
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 3;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Rate
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Depth to Rate
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Depth
				}

				// check state of the potentiometer and assign parameter value
				// Tremolo ON/OFF
				if(Display->JoystickParameterPosition == 1) {

					Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);

					if(Display->Poti_raw < Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
						Display->Tremolo_ONOFF = false;
					}
					else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
						Display->Tremolo_ONOFF = true;
					}
				}

				// Tremolo Rate
				else if(Display->JoystickParameterPosition == 2) {

					Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
					Display->Tremolo_Rate = round( (((float)Display->Poti_raw/4096) * Tremolo->tremolo_maximum_rate) + 1);	// +1 to prevent 0
					sprintf(tremolo_rate_string, "%f", Display->Tremolo_Rate);
					Display->rate = (uint16_t)(Display->Tremolo_Rate * 1000);
				}

				// Tremolo Depth
				else if(Display->JoystickParameterPosition == 3) {

					Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
					Display->Tremolo_Depth = ((float)Display->Poti_raw/4096) * Tremolo->tremolo_maximum_depth;
					sprintf(tremolo_depth_string, "%f", Display->Tremolo_Depth);
					Display->depth = (uint16_t)(Display->Tremolo_Depth * 1000);
				}

				if(Display->Tremolo_ONOFF == true) {	// if Tremolo ON

					Tremolo->lfo_frequency = Display->Tremolo_Rate;
					Tremolo->lfo_depth = Display->Tremolo_Depth;

					if( abs(Display->last_rate-Display->rate)>=1000 || abs(Display->last_depth-Display->depth)>=100 ) {

						process_trem = true;

						//					if(Display->Tremolo_EffectAdded == false) {	// if no tremolo effect added yet
						//
						//						effects_add(TREM, Display->Tremolo_EffectPosition);
						//						Display->Tremolo_EffectAdded = true;
						//					}
					}
				}
				else if(Display->Tremolo_ONOFF == false) {	// if Tremolo OFF

					process_trem = false;

					//				if(Display->Tremolo_EffectAdded == true) {
					//
					//					effects_delete(TREM, Display->Tremolo_EffectPosition);
					//					Display->Tremolo_EffectAdded = false;
					//				}
				}
				Display->last_rate = Display->rate;
				Display->last_depth = Display->depth;

				Paint_DrawStringAt(&paint, 150, 50, tremolo_rate_string, &Font12, COLORED);
				Paint_DrawStringAt(&paint, 150, 70, tremolo_depth_string, &Font12, COLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);

				//			// reset BACK-switch
				//			if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
				//				Display->BACK = false;
				//			}
				//			// reset ENTER-switch
				//			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
				//				Display->ENTER = false;
				//			}

				if(Display->VRx > Display->UpperLimit) {
					Display->CurrentModule = 1;	// back to Distortion
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
				}
				else if(Display->VRx < Display->LowerLimit) {
					Display->CurrentModule = 3;	// forward to Equalizer
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
				}
			}
			// #############################################
			// ########### END TREMOLO SUBMENU #############
			// #############################################


			// #############################################
			// ########## BEGIN EQUALIZER SUBMENU ##########
			// #############################################
			while(Display->CurrentModule == 3) {

				//			Paint_DrawStringAt(&paint, 1, 10, "Equalizer", &Font16, COLORED);
				//			Paint_DrawStringAt(&paint, 1, 30, "Band1 ON/OFF", &Font12, COLORED);
				//			Paint_DrawStringAt(&paint, 1, 50, "Band1 Q", &Font12, COLORED);
				//			Paint_DrawStringAt(&paint, 1, 70, "Band1 Gain", &Font12, COLORED);
				//			Paint_DrawStringAt(&paint, 1, 90, "Band1 Cutoff", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 10, "Tiefpassfilter", &Font16, COLORED);
				Paint_DrawStringAt(&paint, 1, 30, "Filter ON/OFF", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 50, "Cutoff", &Font12, COLORED);
				Paint_DrawStringAt(&paint, 1, 70, "Güte", &Font12, COLORED);

				Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
				Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
				Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

				char filter_cutoff_string[9];
				//sprintf(filter_cutoff_string, "%f", Display->Filter_Cutoff);
				char filter_Q_string[9];
				//sprintf(filter_Q_string, "%f", Display->Filter_Q);

				if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Filter ON/OFF
				}
				else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Filter ON/OFF to Cutoff
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Cutoff to Filter ON/OFF
					Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 1;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Cutoff to Q
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 3;
				}
				else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Cutoff
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
					Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Q to Cutoff
					Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
					Display->JoystickParameterPosition = 2;
				}
				else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
					Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Q
				}

				// check state of the potentiometer and assign parameter value
				// Filter ON/OFF
				if(Display->JoystickParameterPosition == 1) {

					Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);

					if(Display->Poti_raw < Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
						Display->Filter_ONOFF = false;
					}
					else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
						Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
						Display->Filter_ONOFF = true;
					}
				}

				// Filter Cutoff
				else if(Display->JoystickParameterPosition == 2) {

					Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
					Display->Filter_Cutoff = round( (((float)Display->Poti_raw/4096) * 4000) + 1);	// +1 to prevent 0; 4000 Hz maximum cutoff
					sprintf(filter_cutoff_string, "%f", Display->Filter_Cutoff);
					Display->cutoff = (uint16_t)(Display->Filter_Cutoff * 1000);
				}

				// Filter Q
				else if(Display->JoystickParameterPosition == 3) {

					Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
					Display->Filter_Q = (float)Display->Poti_raw/4096;	// maximum Q of 1
					sprintf(filter_Q_string, "%f", Display->Filter_Q);
					Display->Q = (uint16_t)(Display->Filter_Q * 1000);
				}

				if(Display->Filter_ONOFF == true) {	// if Filter ON

					if( abs(Display->last_cutoff-Display->cutoff)>=1000 || abs(Display->last_Q-Display->Q)>=100 ) {

						SetupLowpass(&EQ_BAND1_I, Display->Filter_Cutoff, Display->Filter_Q);

						process_filter = true;

						//					if(Display->Filter_EffectAdded == false) {	// if no filter effect added yet
						//
						//						effects_add(EQ, Display->Filter_EffectPosition);
						//						Display->Filter_EffectAdded = true;
						//					}
					}
				}
				else if(Display->Filter_ONOFF == false) {	// if Filter OFF

					process_filter = false;

					//				if(Display->Filter_EffectAdded == true) {
					//					effects_delete(EQ, Display->Filter_EffectPosition);
					//					Display->Filter_EffectAdded = false;
					//				}
				}
				Display->last_cutoff = Display->cutoff;
				Display->last_Q = Display->Q;

				Paint_DrawStringAt(&paint, 150, 50, filter_cutoff_string, &Font12, COLORED);
				Paint_DrawStringAt(&paint, 150, 70, filter_Q_string, &Font12, COLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);

				if(Display->VRx > Display->UpperLimit) {
					Display->CurrentModule = 2;	// back to Tremolo
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
				}
			}
			// #############################################
			// ########## END EQUALIZER SUBMENU ############
			// #############################################
		}
	}
}
