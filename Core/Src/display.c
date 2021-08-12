/*
 * display.c
 *
 *  Created on: 21.01.2021
 *      Author: Marc Bielen
 */

#include "display.h"

Display_Status Display_Init(struct display_variables* Display ) {

	Display->PatchSelected[0] = false;
	Display->PatchSelected[1] = false;
	Display->PatchSelected[2] = false;

	Display->ModuleStateSelected[0] = false;
	Display->ModuleStateSelected[1] = false;
	Display->ModuleStateSelected[2] = false;

	Display->ModuleParametersSelected[0] = false;
	Display->ModuleParametersSelected[1] = false;
	Display->ModuleParametersSelected[2] = false;

	Display->ModuleCompleted[0] = false;
	Display->ModuleCompleted[1] = false;
	Display->ModuleCompleted[2] = false;

	Display->CurrentModule = 0;

	//Mode
	Display->mode = NONE;


	Display->KeyboardmodeSelected = false;

	Display->Keyboardmode_ONOFF = false;

	Display->ActiveEffectsCounter = 0;

	Display->Voices_ONOFF[0] = false;
	Display->Voices_ONOFF[1] = false;
	Display->Voices_ONOFF[2] = false;
	Display->last_Voices_ONOFF[0] = true;
	Display->last_Voices_ONOFF[1] = true;
	Display->last_Voices_ONOFF[2] = true;

	Display->ADSR_ONOFF = false;
	Display->ADSR_Attack = 0.0;
	Display->ADSR_Decay = 0.0;
	Display->ADSR_Sustain = 1.0;
	Display->ADSR_Release = 0.0;
	Display->ADSR_EffectPosition = 0;
	Display->ADSR_EffectAdded = false;

	Display->Distortion_ONOFF = false;
	Display->last_Distortion_ONOFF = true;
	Display->last_Distortion_Type = true;
	Display->Distortion_Type = false;
	Display->Distortion_Gain = 1.0;
	Display->Distortion_EffectPosition = 0;
	Display->Distortion_EffectAdded = false;

	Display->Tremolo_ONOFF = false;
	Display->Tremolo_Rate = 0.0;
	Display->Tremolo_Depth = 0.0;
	Display->Tremolo_EffectPosition = 0;
	Display->Tremolo_EffectAdded = false;

	Display->Filter_ONOFF = false;
	Display->Filter_Cutoff = 1.0;
	Display->Filter_Q = 1.0;
	Display->Filter_EffectPosition = 0;
	Display->Filter_EffectAdded = false;
	// Weitere Synthesizer-Parameter...

	Display->last_note = 1;				// last values have to be different in the beginning, to make sure that display will be refreshed when page is updated
	Display->note = 0;
	Display->last_octave = 1;
	Display->octave = 0;
	Display->last_rate = 1;
	Display->rate = 0;
	Display->last_depth = 1;
	Display->depth = 0;
	Display->last_cutoff = 1;
	Display->cutoff = 0;
	Display->last_Q = 1;
	Display->Q = 0;
	Display->last_distortion_gain = 1;
	Display->distortion_gain = 0;
	Display->last_attack = 1;
	Display->attack = 0;
	Display->last_decay = 1;
	Display->decay = 0;
	Display->last_sustain = 1;
	Display->sustain = 0;
	Display->last_release = 1;
	Display->release = 0;

	Display->LowerLimit = 95;
	Display->UpperLimit = 4000;
	Display->ADC_FullRange = 4095;
	Display->JoystickPatchPosition = 1;
	Display->JoystickModePosition = 1;
	Display->last_JoystickModePosition = 0;
	Display->JoystickParameterPosition = 1;
	Display->last_JoystickParameterPosition = 0;
	Display->last_joystick_x = 0;
	Display->last_joystick_y = 0;
	Display->UpdateThreshold = 2000;

	// Draw parameter
	Display->arrow_flag = true;
	Display->arrow_start_x_position = 180;
	Display->arrow_end_x_position = 200;
	Display-> value_start_x_position =150;
	Display-> value_end_x_position= Display->arrow_start_x_position-1;
	Display-> row_start_x_position= 1;
	Display-> row_end_x_position= Display-> value_start_x_position-1;
	//Page parameter
	Display->pagePosition = 0;
	Display->page_min = 0;
	Display->page_max =

			Display->ENTER_Debounce_State = true;
	Display->BACK_Debounce_State = true;
	Display->SW_Debounce_State = true;
	Display->ENTER = false;
	Display->BACK = false;
	Display->SW = false;

	return DISPLAY_OK;
}

Display_Status Display_Start(EPD* epd, Paint* paint, unsigned char* frame_buffer) {

	//frame_buffer = (unsigned char*)malloc(EPD_WIDTH * EPD_HEIGHT / 8);
	EPD_Init(epd, lut_full_update);
	Paint_Init(paint, frame_buffer, epd->width, epd->height);
	Paint_SetRotate(paint, ROTATE_270);
	// Display the frame_buffer to show the TU Berlin-logo
	EPD_SetFrameMemory(epd, TU_LOGO, 0, 0, Paint_GetWidth(paint), Paint_GetHeight(paint));
	EPD_DisplayFrame(epd);
	EPD_DelayMs(epd, 1000);
	Paint_Clear(paint, UNCOLORED);
	// Display the frame_buffer to show a white screen
	EPD_SetFrameMemory(epd, frame_buffer, 0, 0, Paint_GetWidth(paint), Paint_GetHeight(paint));
	EPD_DisplayFrame(epd);
	EPD_Init(epd, lut_partial_update);

	DISPLAY_DrawArrow(1);

	return DISPLAY_OK;
}



void DISPLAY_processing(void){

	switch(Display.mode){
	case NONE:
		p_StartingMenu(frame_buffer);
		break;

	case BODYSYNTH:
		Display.page_max = 4; // must be cahnegd for every added case
		switch(Display.pagePosition){
		case 1:
			//voices
			p_Dummy();
			break;
		case 2:
			break;
		case 3:

			break;

		}
		break;
		case KEYBOARD:
			Display.page_max = 1; // must be cahnegd for every added case
			switch(Display.pagePosition){
			case 1:
				//		p_KeyboardSetParamters();
				break;
			}
			break;
	}
}
/*Display_Status Display_Start(void) {
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
}*/

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

Display_Status p_StartingMenu(unsigned char* frame_buffer) {

	//Header line
	Paint_DrawStringAt(&paint, 1, 10, "THE BODYSYNTH", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, 30, "Keyboardmode", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, 50, "Synthesizermode", &Font12, COLORED);

//	while(Display.KeyboardmodeSelected == false) {

		//		Display.VRx = Display.ADC2inputs[0];		// read joystick-x-value
		//		Display.Poti_raw = Display.ADC2inputs[2];	// read poti-value



		//		if(Display->Poti_raw < Display->ADC_FullRange/2) {
		//			Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
		//			Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
		//			Display->Keyboardmode_ONOFF = false;
		//			Display->JoystickModePosition = 1;
		//		}
		//		else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
		//			Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
		//			Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
		//			Display->Keyboardmode_ONOFF = true;
		//			Display->JoystickModePosition = 2;
		//			}

		switch(Display.JoystickParameterPosition) {
		case 1:
			Display.mode = KEYBOARD;
			break;
		case 2:
			Display.mode = BODYSYNTH;
			break;
		}
//	}

	//Display->KeyboardmodeSelected = true;
	//		Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content
	//		DISPLAY_Update();

	//		if(Display->JoystickModePosition != Display->last_JoystickModePosition) {
	//				DISPLAY_Update();
	//			Display->last_JoystickModePosition = Display->JoystickModePosition;
	//		}
	//}

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

				// round value to 2 decimal points, so the display does not update permanently
				Display->Keyboard_AttackTime = round(Display->Keyboard_AttackTime * 100)/100;

				sprintf(attacktime_string, "%f", Display->Keyboard_AttackTime);
				Paint_DrawStringAt(&paint, 150, 50, attacktime_string, &Font12, COLORED);

				envelope->adsr_attack_time = Display->Keyboard_AttackTime * LUT_SR;
			}
			// Decay Time
			else if(Display->JoystickParameterPosition == 3) {
				Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
				Display->Keyboard_DecayTime = (((float)Display->Poti_raw/4096) * envelope->adsr_maximum_decay);

				// round value to 2 decimal points, so the display does not update permanently
				Display->Keyboard_DecayTime = round(Display->Keyboard_DecayTime * 100)/100;

				sprintf(decaytime_string, "%f", Display->Keyboard_DecayTime);
				Paint_DrawStringAt(&paint, 150, 70, decaytime_string, &Font12, COLORED);

				envelope->adsr_decay_time = Display->Keyboard_DecayTime * LUT_SR;
			}
			// Sustain Time
			else if(Display->JoystickParameterPosition == 4) {
				Paint_DrawFilledRectangle(&paint, 150, 90, 200, 110, UNCOLORED);
				Display->Keyboard_SustainTime = (((float)Display->Poti_raw/4096) * envelope->adsr_maximum_sustaintime);

				// round value to 2 decimal points, so the display does not update permanently
				Display->Keyboard_SustainTime = round(Display->Keyboard_SustainTime * 100)/100;

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

				// round value to 2 decimal points, so the display does not update permanently
				Display->Keyboard_SustainLevel = round(Display->Keyboard_SustainLevel * 100)/100;

				sprintf(sustainlevel_string, "%f", Display->Keyboard_SustainLevel);
				Paint_DrawStringAt(&paint, 150, 110, sustainlevel_string, &Font12, COLORED);

				envelope->adsr_sustain_amplitude = Display->Keyboard_SustainLevel;
			}
			// Release Time
			else if(Display->JoystickParameterPosition == 6) {
				Paint_DrawFilledRectangle(&paint, 150, 130, 200, 150, UNCOLORED);
				Display->Keyboard_ReleaseTime = (((float)Display->Poti_raw/4096) * envelope->adsr_maximum_release);

				// round value to 2 decimal points, so the display does not update permanently
				Display->Keyboard_ReleaseTime = round(Display->Keyboard_ReleaseTime * 100)/100;

				sprintf(releasetime_string, "%f", Display->Keyboard_ReleaseTime);
				Paint_DrawStringAt(&paint, 150, 130, releasetime_string, &Font12, COLORED);

				envelope->adsr_release_time = Display->Keyboard_ReleaseTime * LUT_SR;
			}

			if( (Display->last_JoystickParameterPosition != Display->JoystickParameterPosition) ||\
					(Display->last_Keyboard_Octave != Display->Keyboard_Octave) ||\
					(Display->last_Keyboard_AttackTime != Display->Keyboard_AttackTime) ||\
					(Display->last_Keyboard_DecayTime != Display->Keyboard_DecayTime) ||\
					(Display->last_Keyboard_SustainTime != Display->Keyboard_SustainTime) ||\
					(Display->last_Keyboard_SustainLevel != Display->Keyboard_SustainLevel) ||\
					(Display->last_Keyboard_ReleaseTime != Display->Keyboard_ReleaseTime)) {
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
				EPD_Init(&epd, lut_partial_update);
			}
			Display->last_JoystickParameterPosition = Display->JoystickParameterPosition;
			Display->last_Keyboard_Octave = Display->Keyboard_Octave;
			Display->last_Keyboard_AttackTime = Display->Keyboard_AttackTime;
			Display->last_Keyboard_DecayTime = Display->Keyboard_DecayTime;
			Display->last_Keyboard_SustainTime = Display->Keyboard_SustainTime;
			Display->last_Keyboard_SustainLevel = Display->Keyboard_SustainLevel;
			Display->last_Keyboard_ReleaseTime = Display->Keyboard_ReleaseTime;

			//OnePress_keyboard_process(Display->ADC1inputs[0], signals, envelope);
			//OnePress_ADSR_Linear_Process(envelope, float* calculate_value);
		}

		// SYNTHESIZERMODE
		else if(Display->Keyboardmode_ONOFF == false) {
			// effect order for patch 1
			Display->Distortion_EffectPosition = 0;
			Display->Tremolo_EffectPosition = 1;
			Display->Filter_EffectPosition = 2;

			//			Display->last_JoystickParameterPosition = 0;
			//			Display->JoystickParameterPosition = 1;

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
					Display->note = keys[(uint8_t)noteindex];
					Display->Voices_Note[0] = Display->note;	// assign Voice1 Note
				}

				// Voice1 Octave
				else if(Display->JoystickParameterPosition == 3) {
					Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
					Display->octave = (char) (((float)Display->Poti_raw/4096) * 6);	// 5 0ctaves
					Display->Voices_Octave[0] = (uint8_t)Display->octave;	// assign Voice1 Octave
				}

				if(Display->Voices_ONOFF[0] == true) {	// if Voice1 ON

					if( (Display->last_note != Display->note) || (Display->last_octave != Display->octave) ) {	// if voice parameters changed

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

				Paint_DrawCharAt(&paint, 150, 50, Display->note, &Font12, COLORED);
				Paint_DrawCharAt(&paint, 150, 70, Display->octave+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen

				if( (Display->last_JoystickParameterPosition != Display->JoystickParameterPosition) ||\
						(Display->last_Voices_ONOFF[0] != Display->Voices_ONOFF[0]) ||\
						(Display->last_note != Display->note) ||\
						(Display->last_octave != Display->octave) ) {
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
				}
				Display->last_JoystickParameterPosition = Display->JoystickParameterPosition;
				Display->last_Voices_ONOFF[0] = Display->Voices_ONOFF[0];
				Display->last_note = Display->note;
				Display->last_octave = Display->octave;

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
					Display->last_note = Display->note++;	// set last_note unequal note to make sure, that the display will be updated, when we switch back from distortion to voices
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
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
				else if(Display->JoystickParameterPosition == 2) {

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

					// round value to 1 decimal point, so the display does not update permanently
					Display->Distortion_Gain = round(Display->Distortion_Gain);

					sprintf(distortion_gain_string, "%f", Display->Distortion_Gain);
					Display->distortion_gain = (uint16_t)(Display->Distortion_Gain * 1000);
				}

				if(Display->Distortion_ONOFF == true) {	// if Distortion ON

					if( abs(Display->last_distortion_gain-Display->distortion_gain)>250 ) {	// only changes when the difference in gain is at least 0.25

						if(Display->Distortion_Type == 0)
							SoftClipping->distortion_gain = round(Display->Distortion_Gain);	// necessary only for soft clipping, because gain is increased in steps
						else if(Display->Distortion_Type == 1)
							HardClipping->distortion_gain = Display->Distortion_Gain;

						//						HardClipping->distortion_gain = Display->Distortion_Gain;
						//						process_dist_hard = true;

						//					if(Display->Distortion_EffectAdded == false) {	// if no distortion effect added yet
						//						effects_add(DIST_H, Display->Distortion_EffectPosition);
						//						Display->Distortion_EffectAdded = true;
						//					}
					}
				}
				else if(Display->Distortion_ONOFF == false) {	// if Distortion OFF

					process_dist_hard = false;
					process_dist_soft = false;

					//				if(Display->Distortion_EffectAdded == true) {
					//					effects_delete(DIST_H, Display->Distortion_EffectPosition);
					//					Display->Distortion_EffectAdded = false;
					//				}
				}

				Paint_DrawStringAt(&paint, 150, 70, distortion_gain_string, &Font12, COLORED);

				if( (Display->last_JoystickParameterPosition != Display->JoystickParameterPosition) ||\
						(Display->last_Distortion_ONOFF != Display->Distortion_ONOFF) ||\
						(Display->last_Distortion_Type != Display->Distortion_Type) ||\
						(Display->last_distortion_gain != Display->distortion_gain) ) {
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
				}
				Display->last_JoystickParameterPosition = Display->JoystickParameterPosition;
				Display->last_Distortion_ONOFF = Display->Distortion_ONOFF;
				Display->last_Distortion_Type = Display->Distortion_Type;
				Display->last_distortion_gain = Display->distortion_gain;

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
					Display->last_distortion_gain = Display->distortion_gain++;	// set last_distortion_gain unequal distortion_gain to make sure, that the display will be updated, when we switch from voices to distortion
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
				}
				else if(Display->VRx < Display->LowerLimit) {
					Display->CurrentModule = 2;	// forward to Tremolo
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Display->last_distortion_gain = Display->distortion_gain++;	// set last_distortion_gain unequal distortion_gain to make sure, that the display will be updated, when we switch back from tremolo to distortion
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
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

				char tremolo_rate_string[9];
				char tremolo_depth_string[9];

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

					// round value to 2 decimal points, so the display does not update permanently
					Display->Tremolo_Rate = round(Display->Tremolo_Rate * 100)/100;

					sprintf(tremolo_rate_string, "%f", Display->Tremolo_Rate);
					Display->rate = (uint16_t)(Display->Tremolo_Rate * 1000);
				}

				// Tremolo Depth
				else if(Display->JoystickParameterPosition == 3) {

					Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
					Display->Tremolo_Depth = ((float)Display->Poti_raw/4096) * Tremolo->tremolo_maximum_depth;

					// round value to 2 decimal points, so the display does not update permanently
					Display->Tremolo_Depth = round(Display->Tremolo_Depth * 100)/100;

					sprintf(tremolo_depth_string, "%f", Display->Tremolo_Depth);
					Display->depth = (uint16_t)(Display->Tremolo_Depth * 1000);
				}

				if(Display->Tremolo_ONOFF == true) {	// if Tremolo ON

					Tremolo->lfo_frequency = Display->Tremolo_Rate;
					Tremolo->lfo_depth = Display->Tremolo_Depth;

					if( abs(Display->last_rate-Display->rate)>=250 || abs(Display->last_depth-Display->depth)>=25 ) {

						process_trem = true;

						//					if(Display->Tremolo_EffectAdded == false) {	// if no tremolo effect added yet
						//						effects_add(TREM, Display->Tremolo_EffectPosition);
						//						Display->Tremolo_EffectAdded = true;
						//					}
					}
				}
				else if(Display->Tremolo_ONOFF == false) {	// if Tremolo OFF

					process_trem = false;

					//				if(Display->Tremolo_EffectAdded == true) {
					//					effects_delete(TREM, Display->Tremolo_EffectPosition);
					//					Display->Tremolo_EffectAdded = false;
					//				}
				}

				Paint_DrawStringAt(&paint, 150, 50, tremolo_rate_string, &Font12, COLORED);
				Paint_DrawStringAt(&paint, 150, 70, tremolo_depth_string, &Font12, COLORED);

				if( (Display->last_JoystickParameterPosition != Display->JoystickParameterPosition) ||\
						(Display->last_rate != Display->rate) ||\
						(Display->last_depth != Display->depth) ) {
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
				}
				Display->last_JoystickParameterPosition = Display->JoystickParameterPosition;
				Display->last_rate = Display->rate;
				Display->last_depth = Display->depth;

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
					Display->last_rate = Display->rate++;	// set last_rate unequal rate to make sure, that the display will be updated, when we switch from distortion to tremolo
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
				}
				else if(Display->VRx < Display->LowerLimit) {
					Display->CurrentModule = 3;	// forward to Equalizer
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Display->last_rate = Display->rate++;	// set last_rate unequal rate to make sure, that the display will be updated, when we switch from equalizer to tremolo
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
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
				Paint_DrawStringAt(&paint, 1, 70, "Guetefaktor", &Font12, COLORED);

				Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
				Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
				Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

				char filter_cutoff_string[9];
				char filter_Q_string[9];

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

					// round value to 2 decimal points, so the display does not update permanently
					Display->Filter_Cutoff = round(Display->Filter_Cutoff * 100)/100;

					sprintf(filter_cutoff_string, "%f", Display->Filter_Cutoff);
					Display->cutoff = (uint16_t)(Display->Filter_Cutoff * 1000);
				}

				// Filter Q
				else if(Display->JoystickParameterPosition == 3) {

					Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
					Display->Filter_Q = (float)Display->Poti_raw/4096;	// maximum Q of 1

					// round value to 2 decimal points, so the display does not update permanently
					Display->Filter_Q = round(Display->Filter_Q * 100)/100;

					sprintf(filter_Q_string, "%f", Display->Filter_Q);
					Display->Q = (uint16_t)(Display->Filter_Q * 1000);
				}

				if(Display->Filter_ONOFF == true) {	// if Filter ON

					if( abs(Display->last_cutoff-Display->cutoff)>=1000 || abs(Display->last_Q-Display->Q)>=100 ) {

						SetupLowpass(&EQ_BAND1_I, Display->Filter_Cutoff, Display->Filter_Q);

						process_filter = true;

						//					if(Display->Filter_EffectAdded == false) {	// if no filter effect added yet
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

				Paint_DrawStringAt(&paint, 150, 50, filter_cutoff_string, &Font12, COLORED);
				Paint_DrawStringAt(&paint, 150, 70, filter_Q_string, &Font12, COLORED);

				if( (Display->last_JoystickParameterPosition != Display->JoystickParameterPosition) ||\
						(Display->last_cutoff != Display->cutoff) ||\
						(Display->last_Q != Display->Q) ) {
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
				}
				Display->last_JoystickParameterPosition = Display->JoystickParameterPosition;
				Display->last_cutoff = Display->cutoff;
				Display->last_Q = Display->Q;

				if(Display->VRx > Display->UpperLimit) {
					Display->CurrentModule = 2;	// back to Tremolo
					Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
					Display->last_Q = Display->Q++;	// set last_Q unequal Q to make sure, that the display will be updated, when we switch from tremolo to equalizer
					Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content
					// Display the frame_buffer
					EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
					EPD_DisplayFrame(&epd);
					EPD_Init(&epd, lut_partial_update);
				}
			}
			// #############################################
			// ########## END EQUALIZER SUBMENU ############
			// #############################################
		}
	}
}


void DISPLAY_Update(void) {
	//	if( abs(Display.ADC2inputs[0]-Display.last_joystick_x) > Display.UpdateThreshold ||\
	//			abs(Display.ADC2inputs[1]-Display.last_joystick_y) > Display.UpdateThreshold) {
//	Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
	EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
	EPD_DisplayFrame(&epd);
	EPD_Init(&epd, lut_partial_update);
	//	}
}


void DISPLAY_DrawArrow(uint8_t JoystickParameterPosition) {
	switch (JoystickParameterPosition){
	case 1:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 30, "<--", &Font12, COLORED);
		break;
	case 2:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 50, "<--", &Font12, COLORED);
		break;
	case 3:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 70, "<--", &Font12, COLORED);
		break;
	case 4:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 90, "<--", &Font12, COLORED);
		break;
	case 5:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 110, "<--", &Font12, COLORED);
		break;
	case 6:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 130, "<--", &Font12, COLORED);
		break;
	case 7:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 150, "<--", &Font12, COLORED);
		break;
	case 8:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 170, "<--", &Font12, COLORED);
		break;
	case 9:
		Paint_DrawStringAt(&paint, Display.arrow_start_x_position, 190, "<--", &Font12, COLORED);
		break;
	}
}

void DISPLAY_DeleteArrow(uint8_t JoystickParameterPosition){
	switch (JoystickParameterPosition){
	case 1:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 30, Display.arrow_end_x_position, 40, UNCOLORED);
		break;
	case 2:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 50, Display.arrow_end_x_position, 60, UNCOLORED);
		break;
	case 3:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 70, Display.arrow_end_x_position, 80, UNCOLORED);
		break;
	case 4:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 90, Display.arrow_end_x_position, 100, UNCOLORED);
		break;
	case 5:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 110, Display.arrow_end_x_position, 120, UNCOLORED);
		break;
	case 6:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 130, Display.arrow_end_x_position, 140, UNCOLORED);
		break;
	case 7:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 150, Display.arrow_end_x_position, 160, UNCOLORED);
		break;
	case 8:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 170, Display.arrow_end_x_position, 180, UNCOLORED);
		break;
	case 9:
		Paint_DrawFilledRectangle(&paint, Display.arrow_start_x_position, 190, Display.arrow_end_x_position, 200, UNCOLORED);
		break;
	}
}


void DISPLAY_ArrowUp(uint8_t *JoystickParameterPosition){
	//always use font 12 for arrow draws, to ensure a page can have 9 parameters


	DISPLAY_DeleteArrow(*JoystickParameterPosition);
	switch (*JoystickParameterPosition){

	case 1:
		break;
	case 2:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	case 3:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	case 4:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	case 5:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	case 6:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	case 7:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	case 8:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	case 9:
		*JoystickParameterPosition = *JoystickParameterPosition-1;
		break;
	}
	DISPLAY_DrawArrow(*JoystickParameterPosition);
}



void DISPLAY_ArrowDown(uint8_t *JoystickParameterPosition){
	//always use font 12 for arrow draws, to ensure a page can have 9 parameters


	DISPLAY_DeleteArrow(*JoystickParameterPosition);
	switch (*JoystickParameterPosition){

	case 1:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 2:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 3:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 4:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 5:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 6:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 7:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 8:
		*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 9:
		break;
	}
	DISPLAY_DrawArrow(*JoystickParameterPosition);
}

void DISPLAY_SwitchPageLeft() {

	Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content

	if (Display.pagePosition > Display.page_min){
		Display.pagePosition = Display.pagePosition-1;
	}
	else if (Display.pagePosition == Display.page_min)
		Display.mode = NONE;
}

void DISPLAY_SwitchPageRight() {

	Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content

	if (Display.pagePosition < Display.page_max){
		Display.pagePosition = Display.pagePosition+1;
	}
}

void p_Dummy() {
	//Header
	char headerstring[] = "VOICES";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "Voice1 ON/OFF";
	char str_2[] = "Voice1 Note";
	char str_3[] = "Voice1 Octave";
	char str_4[] = "Voice2 ON/OFF";
	char str_5[] = "Voice2 Note";
	char str_6[] = "Voice2 Octave";
	char str_7[] = "Voice3 ON/OFF";
	char str_8[] = "Voice3 Note";
	char str_9[] = "Voice3 Octave";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);



	//
	//	// Voice1 Note
	//	else if(Display.JoystickParameterPosition == 2) {
	//		Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
	//		float noteindex = ((float)Display.Poti_raw/4096) * (sizeof(keys)/sizeof(keys[0]));
	//		Display.note = keys[(uint8_t)noteindex];
	//		Display.Voices_Note[0] = Display.note;	// assign Voice1 Note
	//	}
	//
	//	// Voice1 Octave
	//	else if(Display.JoystickParameterPosition == 3) {
	//		Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
	//		Display.octave = (char) (((float)Display.Poti_raw/4096) * 6);	// 5 0ctaves
	//		Display.Voices_Octave[0] = (uint8_t)Display.octave;	// assign Voice1 Octave
	//	}


	switch (Display.JoystickParameterPosition){
	case 1:
		Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
		if(Display.Poti_raw < Display.ADC_FullRange/2) {
			Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
			Display.Voices_ONOFF[0] = false;
		}
		else if(Display.Poti_raw >= Display.ADC_FullRange/2) {
			Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
			Display.Voices_ONOFF[0] = true;
		}
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:
		break;
	case 9:
		break;
	}
}
