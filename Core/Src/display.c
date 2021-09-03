/*
 * display.c
 *
 *  Created on: 21.01.2021
 *      Author: Marc Bielen
 */

#include "display.h"

// for int8_t to string conversion to print the current page
#include <stdio.h>
#include <stdlib.h>

/** @brief this function initiliazes the display struct variables
 * @param Display: display struct
 * @return returns display status flag
 */
Display_Status Display_Init(struct display_variables* Display) {

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

	Display->mode = BODYSYNTH;

	Display->KeyboardmodeSelected = false;

	Display->Keyboardmode_ONOFF = false;

	Display->ActiveEffectsCounter = 0;
	//VOICES
	for(int i=0; i<3; i++) {
		Display -> Voices_Created[i] = false;
		Display -> Voices_ONOFF[i] = false;
	}

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

	//	Display->Filter_ONOFF = false;
	//	Display->Filter_Cutoff = 1.0;
	//	Display->Filter_Q = 1.0;
	Display->Filter_EffectPosition = 0;
	Display->Filter_EffectAdded = false;
	Display->lastState = 0;
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
	Display->Keyboard_Octave = 0;

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
	Display->value_start_x_position = 150;
	Display->value_end_x_position= Display->arrow_start_x_position-1;
	Display->row_start_x_position= 1;
	Display->row_end_x_position= Display-> value_start_x_position-1;

	//Page parameter
	Display->pagePosition = 0;
	Display->page_min = 0;
	Display->page_max = 10;

	Display->ENTER_Debounce_State = true;
	Display->BACK_Debounce_State = true;
	Display->SW_Debounce_State = true;
	Display->ENTER = false;
	Display->BACK = false;
	Display->SW = false;

	Display->poti_moved = true;
	Display->last_Poti = 0;
	Display->Poti_Threshold = 50;	// default (ON/OFF threshold)

	//Display value init/reset values
	strcpy(Display->value_str_dummy[0],"OFF");
	strcpy(Display->value_str_dummy[1],"C");
	strcpy(Display->value_str_dummy[2],"0");
	strcpy(Display->value_str_dummy[3],"OFF");
	strcpy(Display->value_str_dummy[4],"");
	strcpy(Display->value_str_dummy[5],"");
	strcpy(Display->value_str_dummy[6],"");
	strcpy(Display->value_str_dummy[7],"");
	strcpy(Display->value_str_dummy[8],"");
	//	Display->value_str_dummy[1] = "Dummy";
	//	Display->value_str_dummy[2] = "123";
	return DISPLAY_OK;
}

/** @brief this function starts the display
 * @param epd: e-paper display struct from epd1in54-files
 * @param paint: e-paper display struct from epdpaint-files
 * @param frame_buffer: frame buffer of the display
 * @return returns display status flag
 */
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

	DISPLAY_processing();
	DISPLAY_DrawArrow(1);
	DISPLAY_Update();

	return DISPLAY_OK;
}

/** @brief this function updates the display
 *
 */
void DISPLAY_Update(void) {
	EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
	EPD_DisplayFrame(&epd);
	EPD_Init(&epd, lut_partial_update);
}

/** @brief this function draws an arrow
 * @param JoystickParameterPosition: current position of the joystick
 */
void DISPLAY_DrawArrow(uint8_t JoystickParameterPosition) {
	switch(JoystickParameterPosition) {
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
	default:
		break;
	}
}

/** @brief this function deletes an arrow
 * @param JoystickParameterPosition: current position of the joystick
 */
void DISPLAY_DeleteArrow(uint8_t JoystickParameterPosition) {
	switch(JoystickParameterPosition) {
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
	default:
		break;
	}
}

/** @brief this function sets the arrow one more position up
 * @param JoystickParameterPosition: pointer to the current position of the joystick
 */
void DISPLAY_ArrowUp(uint8_t *JoystickParameterPosition){

	//always use font 12 for arrow draws, to ensure a page can have 9 parameters
	DISPLAY_DeleteArrow(*JoystickParameterPosition);

	switch(*JoystickParameterPosition) {
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
	default:
		break;
	}

	DISPLAY_DrawArrow(*JoystickParameterPosition);
}

/** @brief this function sets the arrow one more position down
 * @param JoystickParameterPosition: pointer to the current position of the joystick
 */
void DISPLAY_ArrowDown(uint8_t *JoystickParameterPosition) {

	//always use font 12 for arrow draws, to ensure a page can have 9 parameters
	DISPLAY_DeleteArrow(*JoystickParameterPosition);

	switch(*JoystickParameterPosition) {
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
	default:
		break;
	}

	DISPLAY_DrawArrow(*JoystickParameterPosition);
}

/** @brief this function prints the current display page
 *
 */
void DISPLAY_PrintCurrentPage(void) {
	char current_page[1];
	itoa(Display.pagePosition, current_page, 10);
	Paint_DrawFilledRectangle(&paint, 180, 1, 200, 10, UNCOLORED);	// delete the frame content
	Paint_DrawStringAt(&paint, 180, 1, current_page, &Font12, COLORED);
	DISPLAY_Update();
}

/** @brief this function switches to one page on the left
 *
 */
void DISPLAY_SwitchPageLeft(void) {

	Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content

	if (Display.pagePosition > Display.page_min)
		Display.pagePosition = Display.pagePosition-1;
	else if (Display.pagePosition == Display.page_min)
		Display.mode = NONE;

	DISPLAY_PrintCurrentPage();
}

/** @brief this function switches to one page on the right
 *
 */
void DISPLAY_SwitchPageRight(void) {
	// this is to make sure that the mode gets set before moving to Bodysynth-/Keyboardmode
	//	  if(Display.pagePosition == 0) {
	//	    switch(Display.JoystickParameterPosition) {
	//	    case 1:
	//	      Display.mode = BODYSYNTH;
	//	      break;
	//	    case 2:
	//	      Display.mode = KEYBOARD;
	//	      break;
	//	    case 3:
	//	      Display.mode = GYRO;
	//	      break;
	//	    default:
	//	      break;
	//	    }
	//	  }

	Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content

	if (Display.pagePosition < Display.page_max)
		Display.pagePosition = Display.pagePosition+1;

	DISPLAY_PrintCurrentPage();
}

/** @brief this function prints the start menu
 * @param frame_buffer: frame buffer of the display
 * @return returns display status flag
 */
Display_Status p_StartingMenu(unsigned char* frame_buffer) {

	//Header line
	Paint_DrawStringAt(&paint, 1, 10, "THE BODYSYNTH", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, 30, "Synthesizermode", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, 50, "Keyboardmode", &Font12, COLORED);

	switch(Display.JoystickParameterPosition) {
	case 1:
		Display.mode = BODYSYNTH;
		break;
	case 2:
		Display.mode = KEYBOARD;
		break;
	default:
		break;
	}


	return DISPLAY_OK;
}

///** @brief this function is the main processing function of the display
// *
// */
//void DISPLAY_processing(void) {
//
//	switch(Display.mode) {
//	//		case NONE:
//	//			p_StartingMenu(frame_buffer);
//	//			break;
//
//	case BODYSYNTH:
//		Display.page_max = 6; // must be changed for every added case
//
//		switch(Display.pagePosition) {
//		case 0:
//			p_StartingMenu(frame_buffer);
//			break;
//		case 1:
//			// Voices
//			//			p_Voices();
//			p_Dummy();
//			break;
//		case 2:
//			// Distortion
//			p_Distortion(&HardClipping);
//			break;
//		case 3:
//			// Tremolo
//			p_Tremolo(&Tremolo);
//			break;
//		case 4:
//			// Equalizer
//			p_Equalizer_overview();
//			break;
//		case 5:
//			switch(Display.currentBand){
//			case 0:
//				p_Dummy();
//				break;
//			default:
//				p_Equalizer_Settings();
//				Display.page_max = 5;
//				break;
//			}
//			break;
//			case 6:
//				p_Dummy();
//				break;
//			default:
//				break;
//
//		}
//		break;
//
//		case KEYBOARD:
//			Display.page_max = 1; // must be changed for every added case
//			switch(Display.pagePosition) {
//			case 0:
//				p_StartingMenu(frame_buffer);
//				break;
//			case 1:
//				p_KeyboardSetParameters(&envelope);
//				break;
//			default:
//				break;
//			}
//			break;
//
//			case GYRO:
//				Display.page_max = 2; // must be changed for every added case
//				switch (Display.pagePosition) {
//				case 1:
//					p_Gyro();
//					break;
//				case 2:
//					switch (Display.Gyro_select) {
//					case EQ:
//
//						break;
//					case TREM:
//
//						break;
//
//					case DIST_H:
//
//						break;
//					default:
//						break;
//					}
//					break;
//					default:
//						break;
//				}
//
//				break;
//				default:
//					break;
//	}
//}

/** @brief this function is the main processing function of the display
 *
 */
void DISPLAY_processing(void) {

	switch(Display.mode) {
	//	case NONE:
	//		p_StartingMenu(frame_buffer);
	//		break;

	// BODYSYNTH-MODE
	case BODYSYNTH:
		Display.page_max = 10; // must be changed for every added case

		switch(Display.pagePosition) {
		case 0:
			p_StartingMenu(frame_buffer);
			break;
		case 1:
			// Voices
			p_Voices_overview();
			break;
		case 2:
			switch(Display.currentVoice) {
			case 0:
				// next effect: ADSR
				Display.pagePosition = 3;	// go to p_ADSR_overview
				p_ADSR_overview(&envelope);
				DISPLAY_PrintCurrentPage();
				break;
			default:
				p_Voices_Settings();
//				Display.page_max = 2;
				break;
			}
			break;
			case 3:
				// ADSR
				p_ADSR_overview(&envelope);
				break;
			case 4:
				switch(Display.currentADSR) {
				case 0:
					// next effect: EQ
					Display.pagePosition = 5;
					p_Equalizer_overview();
					DISPLAY_PrintCurrentPage();
					break;
				default:
					p_ADSR_Settings();
					break;
				}
				break;
				case 5:
					// Equalizer
					p_Equalizer_overview();
					break;
				case 6:
					switch(Display.currentBand){
					case 0:
						// next effect: Distortion
						Display.pagePosition = 7;
						//p_Distortion_overview();
						p_Distortion(&HardClipping);
						DISPLAY_PrintCurrentPage();
						break;
					default:
						p_Equalizer_Settings();
						//Display.pagePosition = 6;
						break;
					}
					break;
					case 7:
						// Distortion
						//p_Distortion_overview();
						p_Distortion(&HardClipping);
						break;
					case 8:
						switch(Display.currentDistortion) {
						case 0:
							// next effect: Tremolo
							Display.pagePosition = 9;
							//p_Tremolo_overview();
							p_Tremolo(&Tremolo);
							DISPLAY_PrintCurrentPage();
							break;
						default:
							//p_Distortion_Settings();
							break;
						}
						break;
						case 9:
							// Tremolo
							//p_Tremolo_overview();
							p_Tremolo(&Tremolo);
							break;
						case 10:
							// next effect: ?
							Display.pagePosition = 11;
							//p_Dummy();
							DISPLAY_PrintCurrentPage();
							break;
						default:
							//p_Tremolo_Settings();
							break;
		}
		break;

		// KEYBOARD-MODE
		case KEYBOARD:
			Display.page_max = 1; // must be changed for every added case
			switch(Display.pagePosition) {
			case 0:
				p_StartingMenu(frame_buffer);
				break;
			case 1:
				p_KeyboardSetParameters(&envelope);
				break;
			default:
				break;
			}
			break;

			default:
				break;
	}
}

/** @brief this function edits the ON/OFF settings of the Voices
 *
 */
void p_Voices_overview(void) {

	//Header line
	char headerstring[] = "VOICES";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "next Effect";
	char str_2[] = "Voice 1 ON/OFF";
	char str_3[] = "Voice 2 ON/OFF";
	char str_4[] = "Voice 3 ON/OFF";
	char str_5[] = "Voices Reset";
	char str_6[] = "";
	char str_7[] = "";
	char str_8[] = "";
	char str_9[] = "";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentVoice = 0;
		break;
	case 2:
		// Voice 1 ON/OFF
		Display.Poti_Threshold = 50;	// threshold for ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2 +10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Voices_ONOFF[0] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Voices_ONOFF[0] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, "ON", &Font12, COLORED);
		}
		Display.currentVoice = 1;
		break;

	case 3:
		// Voice 2 ON/OFF
		Display.Poti_Threshold = 50;	// threshold for ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Voices_ONOFF[1] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Voices_ONOFF[1] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, "ON", &Font12, COLORED);
		}
		Display.currentVoice = 2;
		break;
	case 4:
		// Voice 3 ON/OFF
		Display.Poti_Threshold = 50;	// threshold for ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Voices_ONOFF[3] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Voices_ONOFF[3] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, "ON", &Font12, COLORED);
		}
		Display.currentVoice = 3;
		break;
	case 5:
		// TODO: RESET OF ALL VOICES..
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}
}

/** @brief this function edits the sources of the Voices parameters
 *
 */
void p_Voices_Settings(void) {

	//Header line
	char headerstring[] = "Voice ";
	char headerstring_2[5];
	itoa(Display.currentVoice, headerstring_2, 10);
	strcat(headerstring, headerstring_2);
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "Note";
	char str_2[] = "Octave";
	char str_3[] = "Note Source";
	char str_4[] = "Octave Source";
	char str_5[] = "";
	char str_6[] = "";
	char str_7[] = "";
	char str_8[] = "";
	char str_9[] = "";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Note
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
			Display.noteindex = ((float)Display.ADC2inputs[2]/4096) * (sizeof(keys)/sizeof(keys[0]));
			//Display.note = keys[(uint8_t)Display.noteindex];
			//Display.Voices_Note[0] = Display.note;	// assign Voice1 Note
			Display.Voices_Note[Display.currentVoice-1] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
			Paint_DrawCharAt(&paint, Display.value_start_x_position, 30, Display.Voices_Note[0], &Font12, COLORED);
			break;
		case 2:
			// Octave
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
			//Display.octave = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
			//Display.Voices_Octave[0] = (uint8_t)Display.octave;	// assign Voice1 Octave
			Display.Voices_Octave[Display.currentVoice-1] = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
			Paint_DrawCharAt(&paint, Display.value_start_x_position, 50, Display.Voices_Octave[0]+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
			break;
		case 3:
			// Note Source
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 70, Display.value_end_x_position, 80, UNCOLORED);
			uint8_t mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Display.Voice_Note_Sources[Display.currentVoice-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 70, source_names[mode_number], &Font12, COLORED);
			break;
		case 4:
			// Octave Source
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 90, Display.value_end_x_position, 100, UNCOLORED);
			uint8_t mode_number2 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Display.Voice_Octave_Sources[Display.currentVoice-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 90, source_names[mode_number2], &Font12, COLORED);
			break;
		default:
			break;
		}
	}
}

/** @brief this function edits the settings of the ADSR, just the sources have can be edited on another page or you can switch to the next effect
 *
 */
void p_ADSR_overview(struct adsr* envelope) {

	//Header line
	char headerstring[] = "ADSR";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "next Effect";
	char str_2[] = "ADSR ON/OFF";
	char str_3[] = "Attack Time";
	char str_4[] = "Decay Time";
	char str_5[] = "Sustain Time";
	char str_6[] = "Sustain Level";
	char str_7[] = "Release Time";
	char str_8[] = "ADSR Reset";
	char str_9[] = "";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);
	char attacktime_string[5];
	char decaytime_string[5];
	char sustaintime_string[5];
	char sustainlevel_string[5];
	char releasetime_string[5];

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentADSR = 0;
		break;
	case 2:
		// ADSR ON/OFF
		Display.Poti_Threshold = 50;	// threshold for ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1 +10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.ADSR_ONOFF = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.ADSR_ONOFF = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, "ON", &Font12, COLORED);
		}
		Display.currentADSR = 1;
		break;
	case 3:
		// Attack Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+10, UNCOLORED);
		Display.Keyboard_AttackTime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_attack) + 0.05;
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_AttackTime = round(Display.Keyboard_AttackTime * 100)/100;
		sprintf(attacktime_string, "%.2f", Display.Keyboard_AttackTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, attacktime_string, &Font12, COLORED);
		envelope->adsr_attack_time = Display.Keyboard_AttackTime * LUT_SR;
		Display.currentADSR = 2;
		break;
	case 4:
		// Decay Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+10, UNCOLORED);
		Display.Keyboard_DecayTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_decay);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_DecayTime = round(Display.Keyboard_DecayTime * 100)/100;
		sprintf(decaytime_string, "%.2f", Display.Keyboard_DecayTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, decaytime_string, &Font12, COLORED);
		envelope->adsr_decay_time = Display.Keyboard_DecayTime * LUT_SR;
		Display.currentADSR = 3;
		break;
	case 5:
		// Sustain Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+10, UNCOLORED);
		Display.Keyboard_SustainTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_sustaintime);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_SustainTime = round(Display.Keyboard_SustainTime * 100)/100;
		sprintf(sustaintime_string, "%.2f", Display.Keyboard_SustainTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, sustaintime_string, &Font12, COLORED);
		envelope->adsr_sustain_time = Display.Keyboard_SustainTime * LUT_SR;
		Display.currentADSR = 4;
		break;
	case 6:
		// Sustain Level
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+10, UNCOLORED);
		Display.Keyboard_SustainLevel = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_max_amp);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_SustainLevel = round(Display.Keyboard_SustainLevel * 100)/100;
		sprintf(sustainlevel_string, "%.2f", Display.Keyboard_SustainLevel);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, sustainlevel_string, &Font12, COLORED);
		envelope->adsr_sustain_amplitude = Display.Keyboard_SustainLevel;
		Display.currentADSR = 5;
		break;
	case 7:
		// Release Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 130, Display.value_end_x_position, 150, UNCOLORED);
		Display.Keyboard_ReleaseTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_release);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_ReleaseTime = round(Display.Keyboard_ReleaseTime * 100)/100;
		sprintf(releasetime_string, "%.2f", Display.Keyboard_ReleaseTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 130, releasetime_string, &Font12, COLORED);
		envelope->adsr_release_time = Display.Keyboard_ReleaseTime * LUT_SR;
		Display.currentADSR = 6;
		break;
	case 8:
		// TODO: RESET OF ADSR..
		break;
	case 9:
		break;
	default:
		break;
	}
}

/** @brief this function edits the sources of the ADSR parameters
 *
 */
void p_ADSR_Settings(void) {

	//Header line
	char headerstring[] = "ADSR ";
	char headerstring_2[5];
	itoa(Display.currentADSR, headerstring_2, 10);
	strcat(headerstring, headerstring_2);
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "Attack Time Source";
	char str_2[] = "Decay Time Source";
	char str_3[] = "Sustain Time Source";
	char str_4[] = "Sustain Level Source";
	char str_5[] = "Release Time Source";
	char str_6[] = "";
	char str_7[] = "";
	char str_8[] = "";
	char str_9[] = "";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Attack Time Source
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 70, Display.value_end_x_position, 80, UNCOLORED);
			uint8_t mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Display.ADSR_Sources[0] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 70, source_names[mode_number], &Font12, COLORED);
			break;
		case 2:
			// Decay Time Source
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 70, Display.value_end_x_position, 80, UNCOLORED);
			uint8_t mode_number2 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Display.ADSR_Sources[1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 70, source_names[mode_number2], &Font12, COLORED);
			break;
		case 3:
			// Sustain Time Source
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 90, Display.value_end_x_position, 100, UNCOLORED);
			uint8_t mode_number3 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Display.ADSR_Sources[2] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 90, source_names[mode_number3], &Font12, COLORED);
			break;
		case 4:
			// Sustain Level Source
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 110, Display.value_end_x_position, 120, UNCOLORED);
			uint8_t mode_number4 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Display.ADSR_Sources[3] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 90, source_names[mode_number4], &Font12, COLORED);
			break;
		case 5:
			// Release Time Source
			Display.Poti_Threshold = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 130, Display.value_end_x_position, 140, UNCOLORED);
			uint8_t mode_number5 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Display.ADSR_Sources[4] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 90, source_names[mode_number5], &Font12, COLORED);
			break;
		default:
			break;
		}
	}
}

/** @brief this function edits the ON/OFF settings of the Equalizer, the parameters and sources have to be edited on another page or you can switch to the next effect
 *
 */
void p_Equalizer_overview(void) {

	//Header line
	char headerstring[] = "EQ";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "next Effect";
	char str_2[] = "Band 1";
	char str_3[] = "Band 2";
	char str_4[] = "Band 3";
	char str_5[] = "Band 4";
	char str_6[] = "Band 5";
	char str_7[] = "";
	char str_8[] = "";
	char str_9[] = "";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentBand = 0;
		break;
	case 2:
		// Band 1 ON/OFF
		Display.Poti_Threshold = 50;	// threshold for ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2 +10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[0] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[0] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, "ON", &Font12, COLORED);
		}
		Display.currentBand = 1;
		break;

	case 3:
		// Band 2 ON/OFF
		Display.Poti_Threshold = 50;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[1] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[1] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, "ON", &Font12, COLORED);
		}
		Display.currentBand = 2;
		break;
	case 4:
		// Band 3 ON/OFF
		Display.Poti_Threshold = 50;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[3] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[3] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, "ON", &Font12, COLORED);
		}
		Display.currentBand = 3;
		break;
	case 5:
		// Band 4 ON/OFF
		Display.Poti_Threshold = 50;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5 +10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[3] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[3] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, "ON", &Font12, COLORED);
		}
		Display.currentBand = 4;
		break;
	case 6:
		// Band 5 ON/OFF
		Display.Poti_Threshold = 50;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6 +10, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[4] = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Filter_ONOFF[4] = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, "ON", &Font12, COLORED);
		}
		Display.currentBand = 5;
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}
}

/** @brief this function prints the Equalizer submenu and edits its values
 *  @param pointer to 5 Filter band structs
 */
void p_Equalizer_Settings(void) {

	//Header line
	char headerstring[] = "Band ";
	char headerstring_2[5];
	itoa(Display.currentBand, headerstring_2, 10);
	strcat(headerstring, headerstring_2);
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "Q-Factor";
	char str_2[] = "Cutoff";
	char str_3[] = "Gain";
	char str_4[] = "Q-Factor Source";
	char str_5[] = "Cutoff Source";
	char str_6[] = "Gain Source";
	char str_7[] = "";
	char str_8[] = "";
	char str_9[] = "";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);

	//-------------------------------------------------------------------------------------
	// this variables have to be implemented and adjusted for each frequency band in filter-structs
	float filter_maximum_Q = 10.0;
	float filter_maximum_cutoff = 1000.0;
	float filter_maximum_gain = 1.0;
	//-------------------------------------------------------------------------------------
	char filter_Q_string[5];
	char filter_cutoff_string[5];
	char filter_gain_string[5];

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Q-Factor
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
		Display.Filter_Q[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * filter_maximum_Q);
		sprintf(filter_Q_string, "%.2f", Display.Filter_Q[Display.currentBand-1]);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, filter_Q_string, &Font12, COLORED);
		break;
	case 2:
		// Cutoff
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 50, Display.value_end_x_position, 60, UNCOLORED);
		Display.Filter_Cutoff[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * filter_maximum_cutoff);
		sprintf(filter_cutoff_string, "%.2f", Display.Filter_Cutoff[Display.currentBand-1]);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 50, filter_cutoff_string, &Font12, COLORED);
		break;
	case 3:
		// Gain
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 80, UNCOLORED);
		Display.Filter_Gain[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * filter_maximum_gain);
		sprintf(filter_gain_string, "%.2f", Display.Filter_Gain[Display.currentBand-1]);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 70, filter_gain_string, &Font12, COLORED);
		break;
	case 4:
		// Q-Factor Source
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 90, Display.value_end_x_position, 100, UNCOLORED);
		uint8_t mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Display.EQ_Q_factor_Sources[Display.currentBand-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 90, source_names[mode_number], &Font12, COLORED);
		break;
	case 5:
		// Cutoff Source
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 110, Display.value_end_x_position, 120, UNCOLORED);
		uint8_t mode_number2 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Display.EQ_Cutoff_Sources[Display.currentBand-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 110, source_names[mode_number2], &Font12, COLORED);
		break;
	case 6:
		// Gain Source
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 130, Display.value_end_x_position, 140, UNCOLORED);
		uint8_t mode_number3 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Display.EQ_Gain_Sources[Display.currentBand-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 130, source_names[mode_number3], &Font12, COLORED);
		break;
	default:
		break;
	}
}


/** @brief this function prints the Distortion submenu and edits its values
 *  @param HardClipping: struct of hard clipping distortion effect
 *
 */
void p_Distortion(struct effects_distortion* HardClipping) {

	// Header line
	char headerstring[] = "DISTORTION";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	// row cases
	char str_1[] = "Distortion ON/OFF";
	char str_2[] = "Gain";
	char str_3[] = "Source";
	char str_4[] = "Distortion Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);

	switch (Display.JoystickParameterPosition){
	case 1:	// Distortion ON/OFF
		Display.Poti_Threshold = 50;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {
			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "OFF", &Font12, COLORED);
			Display.Distortion_ONOFF = false;
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {
			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "ON", &Font12, COLORED);
			Display.Distortion_ONOFF = true;
		}
		break;
		//	case 2:	// Distortion Type
		//		Display.Poti_Threshold = 1;
		//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
		//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {
		//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 50, "Soft", &Font12, COLORED);
		//			Display.Distortion_Type = 0;
		//		}
		//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {
		//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 50, "Hard", &Font12, COLORED);
		//			Display.Distortion_Type = 1;
		//		}
		//		break;
	case 2:	// Distortion Gain
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
		Display.Distortion_Gain = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * HardClipping->distortion_maximum_gain) + 1;
		Paint_DrawCharAt(&paint, Display.value_start_x_position, 50, Display.Distortion_Gain+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
		break;
	case 3:	// Distortion Gain Source
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 80, UNCOLORED);
		uint8_t mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Display.Distortion_Sources = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 70, source_names[mode_number], &Font12, COLORED);
		break;
	case 4:
		// TODO: RESET OF DISTORTION..
		break;
	default:
		break;
	}
}

/** @brief this function prints the Tremolo submenu and edits its values
 *
 */
void p_Tremolo(struct Tremolo_t* Tremolo) {

	//Header line
	char headerstring[] = "TREMOLO";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "Tremolo ON/OFF";
	char str_2[] = "Tremolo  Rate";
	char str_3[] = "Tremolo Depth";
	char str_4[] = "Rate Source";
	char str_5[] = "Depth Source";
	char str_6[] = "Tremolo Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Tremolo ON/OFF
		Display.Poti_Threshold = 50;	// threshold for ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Tremolo_ONOFF = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Tremolo_ONOFF = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "ON", &Font12, COLORED);
		}
		break;
	case 2:
		// Tremolo Rate
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
		Display.Tremolo_Rate = (((float)Display.ADC2inputs[2]/4096) * Tremolo->tremolo_maximum_rate) + 1;
		Paint_DrawCharAt(&paint, Display.value_start_x_position, 50, Display.Tremolo_Rate+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
		break;
	case 3:
		// Tremolo Depth
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 80, UNCOLORED);
		Display.Tremolo_Depth = (((float)Display.ADC2inputs[2]/4096) * Tremolo->tremolo_maximum_depth);
		char tremolo_depth_string[5];
		sprintf(tremolo_depth_string, "%.2f", Display.Tremolo_Depth);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 70, tremolo_depth_string, &Font12, COLORED);
		break;
	case 4:
		// Tremolo Rate Source
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 90, Display.value_end_x_position, 100, UNCOLORED);
		uint8_t mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Display.Tremolo_Sources[0] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 90, source_names[mode_number], &Font12, COLORED);
		break;
	case 5:
		// Tremolo Depth Source
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 110, Display.value_end_x_position, 120, UNCOLORED);
		uint8_t mode_number2 = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Display.Tremolo_Sources[1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LEFT+1)));
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 110, source_names[mode_number2], &Font12, COLORED);
		break;
	case 6:
		// TODO: RESET OF TREMOLO..
		break;
	default:
		break;
	}
}


///** @brief this function prints the Voices submenu and edits its values
// *
// */
//void p_Voices(void) {
//
//	//Header line
//	char headerstring[] = "VOICES";
//	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);
//
//	//row cases
//	char str_1[] = "Voice1 ON/OFF";
//	char str_2[] = "Voice1 Note";
//	char str_3[] = "Voice1 Octave";
//	char str_4[] = "Voice2 ON/OFF";
//	char str_5[] = "Voice2 Note";
//	char str_6[] = "Voice2 Octave";
//	char str_7[] = "Voice3 ON/OFF";
//	char str_8[] = "Voice3 Note";
//	char str_9[] = "Voice3 Octave";
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);
//
//	if(Display.poti_moved == true){
//
//		switch(Display.JoystickParameterPosition) {
//
//		case 1:
//			// Voice1 ON/OFF
//			Display.Poti_Threshold = 50;	// threshold for ON/OFF
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
//			if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//				Display.Voices_ONOFF[0] = false;
//				Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "OFF", &Font12, COLORED);
//			}
//			else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//				Display.Voices_ONOFF[0] = true;
//				Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "ON", &Font12, COLORED);
//			}
//			break;
//		case 2:
//			// Voice1 Note
//			Display.Poti_Threshold = 1;
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
//			Display.noteindex = ((float)Display.ADC2inputs[2]/4096) * (sizeof(keys)/sizeof(keys[0]));
//			//Display.note = keys[(uint8_t)Display.noteindex];
//			//Display.Voices_Note[0] = Display.note;	// assign Voice1 Note
//			Display.Voices_Note[0] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
//			Paint_DrawCharAt(&paint, Display.value_start_x_position, 50, Display.Voices_Note[0], &Font12, COLORED);
//			break;
//		case 3:
//			// Voice1 Octave
//			Display.Poti_Threshold = 1;
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 80, UNCOLORED);
//			//Display.octave = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
//			//Display.Voices_Octave[0] = (uint8_t)Display.octave;	// assign Voice1 Octave
//			Display.Voices_Octave[0] = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
//			Paint_DrawCharAt(&paint, Display.value_start_x_position, 70, Display.Voices_Octave[0]+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
//			break;
//		case 4:
//			// Voice2 ON/OFF
//			Display.Poti_Threshold = 50;	// threshold for ON/OFF
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 90, Display.value_end_x_position, 100, UNCOLORED);
//			if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//				Display.Voices_ONOFF[1] = false;
//				Paint_DrawStringAt(&paint, Display.value_start_x_position, 90, "OFF", &Font12, COLORED);
//			}
//			else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//				Display.Voices_ONOFF[1] = true;
//				Paint_DrawStringAt(&paint, Display.value_start_x_position, 90, "ON", &Font12, COLORED);
//			}
//			break;
//		case 5:
//			// Voice2 Note
//			Display.Poti_Threshold = 1;
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 110, Display.value_end_x_position, 120, UNCOLORED);
//			Display.noteindex = ((float)Display.ADC2inputs[2]/4096) * (sizeof(keys)/sizeof(keys[0]));
//			//Display.note = keys[(uint8_t)Display.noteindex];
//			//Display.Voices_Note[0] = Display.note;	// assign Voice1 Note
//			Display.Voices_Note[1] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
//			Paint_DrawCharAt(&paint, Display.value_start_x_position, 110, Display.Voices_Note[1], &Font12, COLORED);
//			break;
//		case 6:
//			// Voice2 Octave
//			Display.Poti_Threshold = 1;
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 130, Display.value_end_x_position, 140, UNCOLORED);
//			//Display.octave = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
//			//Display.Voices_Octave[0] = (uint8_t)Display.octave;	// assign Voice1 Octave
//			Display.Voices_Octave[1] = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
//			Paint_DrawCharAt(&paint, Display.value_start_x_position, 130, Display.Voices_Octave[1]+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
//			break;
//		case 7:
//			// Voice3 ON/OFF
//			Display.Poti_Threshold = 50;	// threshold for ON/OFF
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 150, Display.value_end_x_position, 160, UNCOLORED);
//			if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//				Display.Voices_ONOFF[2] = false;
//				Paint_DrawStringAt(&paint, Display.value_start_x_position, 150, "OFF", &Font12, COLORED);
//			}
//			else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//				Display.Voices_ONOFF[2] = true;
//				Paint_DrawStringAt(&paint, Display.value_start_x_position, 150, "ON", &Font12, COLORED);
//			}
//			break;
//		case 8:
//			// Voice3 Note
//			Display.Poti_Threshold = 1;
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 170, Display.value_end_x_position, 180, UNCOLORED);
//			Display.noteindex = ((float)Display.ADC2inputs[2]/4096) * (sizeof(keys)/sizeof(keys[0]));
//			//Display.note = keys[(uint8_t)Display.noteindex];
//			//Display.Voices_Note[0] = Display.note;	// assign Voice1 Note
//			Display.Voices_Note[2] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
//			Paint_DrawCharAt(&paint, Display.value_start_x_position, 170, Display.Voices_Note[2], &Font12, COLORED);
//			break;
//		case 9:
//			// Voice3 Octave
//			Display.Poti_Threshold = 1;
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 190, Display.value_end_x_position, 200, UNCOLORED);
//			//Display.octave = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
//			//Display.Voices_Octave[0] = (uint8_t)Display.octave;	// assign Voice1 Octave
//			Display.Voices_Octave[2] = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
//			Paint_DrawCharAt(&paint, Display.value_start_x_position, 190, Display.Voices_Octave[2]+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
//			break;
//		default:
//			break;
//		}
//		Display.poti_moved = false;
//	}
//
//}
//
///** @brief this function prints the Distortion submenu and edits its values
// *  @param HardClipping: struct of hard clipping distortion effect
// *
// */
//void p_Distortion(struct effects_distortion* HardClipping) {
//
//	// Header line
//	char headerstring[] = "DISTORTION";
//	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);
//
//	// row cases
//	char str_1[] = "Distortion ON/OFF";
//	char str_2[] = "Distortion Type";
//	char str_3[] = "Distortion Gain";
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
//
//	switch (Display.JoystickParameterPosition){
//	case 1:	// Distortion ON/OFF
//		Display.Poti_Threshold = 50;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "OFF", &Font12, COLORED);
//			Display.Distortion_ONOFF = false;
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "ON", &Font12, COLORED);
//			Display.Distortion_ONOFF = true;
//		}
//		break;
//	case 2:	// Distortion Type
//		Display.Poti_Threshold = 1;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 50, "Soft", &Font12, COLORED);
//			Display.Distortion_Type = 0;
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 50, "Hard", &Font12, COLORED);
//			Display.Distortion_Type = 1;
//		}
//		break;
//	case 3:	// Distortion Gain
//		Display.Poti_Threshold = 1;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 80, UNCOLORED);
//		Display.Distortion_Gain = (((float)Display.ADC2inputs[2]/4096) * HardClipping->distortion_maximum_gain) + 1;
//		Paint_DrawCharAt(&paint, Display.value_start_x_position, 70, Display.Distortion_Gain+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
//		break;
//	default:
//		break;
//	}
//}
//
///** @brief this function prints the Tremolo submenu and edits its values
// *
// */
//void p_Tremolo(struct Tremolo_t* Tremolo) {
//
//	//Header line
//	char headerstring[] = "TREMOLO";
//	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);
//
//	//row cases
//	char str_1[] = "Tremolo ON/OFF";
//	char str_2[] = "Tremolo  Rate";
//	char str_3[] = "Tremolo Depth";
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
//
//	switch(Display.JoystickParameterPosition) {
//	case 1:
//		// Tremolo ON/OFF
//		Display.Poti_Threshold = 50;	// threshold for ON/OFF
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Tremolo_ONOFF = false;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "OFF", &Font12, COLORED);
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Tremolo_ONOFF = true;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "ON", &Font12, COLORED);
//		}
//		break;
//	case 2:
//		// Tremolo Rate
//		Display.Poti_Threshold = 1;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
//		Display.Tremolo_Rate = (((float)Display.ADC2inputs[2]/4096) * Tremolo->tremolo_maximum_rate) + 1;
//		Paint_DrawCharAt(&paint, Display.value_start_x_position, 50, Display.Tremolo_Rate+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
//		break;
//	case 3:
//		// Tremolo Depth
//		Display.Poti_Threshold = 1;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 80, UNCOLORED);
//		Display.Tremolo_Depth = (((float)Display.ADC2inputs[2]/4096) * Tremolo->tremolo_maximum_depth);
//		char tremolo_depth_string[5];
//		sprintf(tremolo_depth_string, "%.2f", Display.Tremolo_Depth);
//		Paint_DrawStringAt(&paint, Display.value_start_x_position, 70, tremolo_depth_string, &Font12, COLORED);
//		break;
//	default:
//		break;
//	}
//}
//
//void p_Equalizer_overview(void) {
//
//	//Header line
//	char headerstring[] = "EQ";
//	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);
//
//	//row cases
//	char str_1[] = "next Effect";
//	char str_2[] = "Band 1";
//	char str_3[] = "Band 2";
//	char str_4[] = "Band 3";
//	char str_5[] = "Band 4";
//	char str_6[] = "Band 5";
//	char str_7[] = "";
//	char str_8[] = "";
//	char str_9[] = "";
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);
//
//
//
//	switch(Display.JoystickParameterPosition) {
//	case 1:
//		// Next Effect
//		Display.currentBand = 0;
//		break;
//	case 2:
//		// Band 1 ON/OFF
//		Display.Poti_Threshold = 50;	// threshold for ON/OFF
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2 +10, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[0] = false;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, "OFF", &Font12, COLORED);
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[0] = true;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, "ON", &Font12, COLORED);
//		}
//		Display.currentBand = 1;
//		break;
//
//	case 3:
//		// Band 2 ON/OFF
//		Display.Poti_Threshold = 50;	// threshold for ON/OFF
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+10, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[1] = false;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, "OFF", &Font12, COLORED);
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[1] = true;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, "ON", &Font12, COLORED);
//		}
//		Display.currentBand = 2;
//		break;
//	case 4:
//		// Band 3 ON/OFF
//		Display.Poti_Threshold = 50;	// threshold for ON/OFF
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+10, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[3] = false;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, "OFF", &Font12, COLORED);
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[3] = true;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, "ON", &Font12, COLORED);
//		}
//		Display.currentBand = 3;
//		break;
//	case 5:
//		// Band 4 ON/OFF
//		Display.Poti_Threshold = 50;	// threshold for ON/OFF
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5 +10, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[3] = false;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, "OFF", &Font12, COLORED);
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[3] = true;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, "ON", &Font12, COLORED);
//		}
//		Display.currentBand = 4;
//		break;
//	case 6:
//		// Band 5 ON/OFF
//		Display.Poti_Threshold = 50;	// threshold for ON/OFF
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6 +10, UNCOLORED);
//		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[4] = false;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, "OFF", &Font12, COLORED);
//		}
//		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
//			Display.Filter_ONOFF[4] = true;
//			Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, "ON", &Font12, COLORED);
//		}
//		Display.currentBand = 5;
//		break;
//	case 7:
//		break;
//	case 8:
//		break;
//	case 9:
//		break;
//	default:
//		break;
//	}
//}
//
///** @brief this function prints the Equalizer submenu and edits its values
// *  @param pointer to 5 Filter band structs
// */
//void p_Equalizer_Settings(struct BQFilter* EQ_BAND1, struct BQFilter* EQ_BAND2, struct BQFilter* EQ_BAND3, struct BQFilter* EQ_BAND4, struct BQFilter* EQ_BAND5) {
//	//Header line
//	char headerstring[] = "Band";
//	char headerstring_2[5];
//	itoa(Display.currentBand, headerstring_2, 10);
//	strcat(headerstring, headerstring_2);
//	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);
//
//	//row cases
//	char str_1[] = "Q-Factor";
//	char str_2[] = "Cutoff";
//	char str_3[] = "Gain";
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
//
//	//-------------------------------------------------------------------------------------
//	// this variables have to be implemented and adjusted for each frequency band in filter-structs
//	float filter_maximum_Q = 10.0;
//	float filter_maximum_cutoff = 1000.0;
//	float filter_maximum_gain = 1.0;
//	//-------------------------------------------------------------------------------------
//	char filter_Q_string[5];
//	char filter_cutoff_string[5];
//	char filter_gain_string[5];
//
//	switch(Display.JoystickParameterPosition) {
//	case 1:
//		// Q-Factor
//		Display.Poti_Threshold = 1;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
//		Display.Filter_Q[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/4096) * filter_maximum_Q);
//		sprintf(filter_Q_string, "%.2f", Display.Filter_Q[Display.currentBand-1]);
//		Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, filter_Q_string, &Font12, COLORED);
//		break;
//	case 2:
//		// Cutoff
//		Display.Poti_Threshold = 1;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, 50, Display.value_end_x_position, 60, UNCOLORED);
//		Display.Filter_Cutoff[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/4096) * filter_maximum_cutoff);
//		sprintf(filter_cutoff_string, "%.2f", Display.Filter_Cutoff[Display.currentBand-1]);
//		Paint_DrawStringAt(&paint, Display.value_start_x_position-20, 50, filter_cutoff_string, &Font12, COLORED);
//		break;
//	case 3:
//		// Gain
//		Display.Poti_Threshold = 1;
//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 80, UNCOLORED);
//		Display.Filter_Gain[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/4096) * filter_maximum_gain);
//		sprintf(filter_gain_string, "%.2f", Display.Filter_Gain[Display.currentBand-1]);
//		Paint_DrawStringAt(&paint, Display.value_start_x_position, 70, filter_gain_string, &Font12, COLORED);
//		break;
//	default:
//		break;
//	}
//}

void p_KeyboardSetParameters(struct adsr* envelope) {

	//Header line
	char headerstring[] = "KEYBOARDMODE";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	char attacktime_string[9], decaytime_string[9], sustaintime_string[9], sustainlevel_string[9], releasetime_string[9];

	//row cases
	char str_1[] = "Octave";
	char str_2[] = "Attack Time";
	char str_3[] = "Decay Time";
	char str_4[] = "Sustain Time";
	char str_5[] = "Sustain Level";
	char str_6[] = "Release Time";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);

	switch(Display.JoystickParameterPosition) {
	case 1:	// Octave
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
		//Display.octave = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
		//Display.Keyboard_Octave = (uint8_t)Display.octave;	// assign Keyboard Octave
		Display.Keyboard_Octave = (char)(((float)Display.ADC2inputs[2]/4096) * 6);	// 5 0ctaves
		Paint_DrawCharAt(&paint, Display.value_start_x_position, 30, Display.Keyboard_Octave+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
		break;
	case 2:	// Attack Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 50, Display.value_end_x_position, 60, UNCOLORED);
		Display.Keyboard_AttackTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_attack) + 0.05;
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_AttackTime = round(Display.Keyboard_AttackTime * 100)/100;
		sprintf(attacktime_string, "%.2f", Display.Keyboard_AttackTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 50, attacktime_string, &Font12, COLORED);
		envelope->adsr_attack_time = Display.Keyboard_AttackTime * LUT_SR;
		break;
	case 3:	// Decay Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 70, Display.value_end_x_position, 90, UNCOLORED);
		Display.Keyboard_DecayTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_decay);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_DecayTime = round(Display.Keyboard_DecayTime * 100)/100;
		sprintf(decaytime_string, "%.2f", Display.Keyboard_DecayTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 70, decaytime_string, &Font12, COLORED);
		envelope->adsr_decay_time = Display.Keyboard_DecayTime * LUT_SR;
		break;
	case 4:	// Sustain Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 90, Display.value_end_x_position, 110, UNCOLORED);
		Display.Keyboard_SustainTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_sustaintime);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_SustainTime = round(Display.Keyboard_SustainTime * 100)/100;
		sprintf(sustaintime_string, "%.2f", Display.Keyboard_SustainTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 90, sustaintime_string, &Font12, COLORED);
		envelope->adsr_sustain_time = Display.Keyboard_SustainTime * LUT_SR;
		break;
	case 5:	// Sustain Level
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 110, Display.value_end_x_position, 130, UNCOLORED);
		Display.Keyboard_SustainLevel = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_max_amp);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_SustainLevel = round(Display.Keyboard_SustainLevel * 100)/100;
		sprintf(sustainlevel_string, "%.2f", Display.Keyboard_SustainLevel);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 110, sustainlevel_string, &Font12, COLORED);
		envelope->adsr_sustain_amplitude = Display.Keyboard_SustainLevel;
		break;
	case 6:	// Release Time
		Display.Poti_Threshold = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 130, Display.value_end_x_position, 150, UNCOLORED);
		Display.Keyboard_ReleaseTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_release);
		// round value to 2 decimal points, so the display does not update permanently
		//Display.Keyboard_ReleaseTime = round(Display.Keyboard_ReleaseTime * 100)/100;
		sprintf(releasetime_string, "%.2f", Display.Keyboard_ReleaseTime);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, 130, releasetime_string, &Font12, COLORED);
		envelope->adsr_release_time = Display.Keyboard_ReleaseTime * LUT_SR;
		break;
	default:
		break;
	}
}

void p_Gyro(void) {

	//Header line
	char headerstring[] = "Gyroskop";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "ON/OFF";
	char str_2[] = "EQ";
	char str_3[] = "DISTORTION";
	char str_4[] = "TREMOLO";
	char str_5[] = "Voices";
	char str_6[] = "";
	char str_7[] = "";
	char str_8[] = "";
	char str_9[] = "";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 30, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 50, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 70, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 90, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 110, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 130, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 150, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 170, str_8, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, 190, str_9, &Font12, COLORED);

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Voice1 ON/OFF
		Display.Poti_Threshold = 50;	// threshold for ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, 30, Display.value_end_x_position, 40, UNCOLORED);
		if(Display.ADC2inputs[2] < Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Gyro_ON = false;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "OFF", &Font12, COLORED);
		}
		else if(Display.ADC2inputs[2] >= Display.ADC_FullRange/2) {	// Potentiometer: Display.ADC2inputs[2]
			Display.Gyro_ON = true;
			Paint_DrawStringAt(&paint, Display.value_start_x_position, 30, "ON", &Font12, COLORED);
		}
		break;
	case 2:

		Display.Gyro_select = EQ;
		break;
	case 3:
		Display.Gyro_select = DIST_H;
		break;
	case 4:

		Display.Gyro_select = TREM;
		break;
	case 5:

		Display.Gyro_select = VOICES;
	default:
		break;
	}
}


void p_Dummy(void) {

	//Header line
	char headerstring[] = "Dummy";
	Paint_DrawStringAt(&paint, 1, 10, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "label 1";
	char str_2[] = "label 2";
	char str_3[] = "label 3";
	char str_4[] = "label 4";
	//	char str_5[] = "";
	//	char str_6[] = "";
	//	char str_7[] = "";
	//	char str_8[] = "";
	//	char str_9[] = "";

	//print info row
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);
	//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, str_7, &Font12, COLORED);
	//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE8, str_8, &Font12, COLORED);
	//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE9, str_9, &Font12, COLORED);

	//string for chnaging the value strings

	//check if potentiometer has been moved
	if (Display.poti_moved == true){

		//Potentiometer Input in %
		float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange *100;

		char write_str[5];

		switch(Display.JoystickParameterPosition) {
		case 1:
			/* ON-OFF-Decision
			 */

			// fill value line with uncolored rectangle
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {

				//Value to be set
				Display.Voices_ONOFF[0] = false;

				//value display
				char write_str[] = "OFF";
				strcpy(Display.value_str_dummy[0],write_str);
			}
			else if(potVal >= 50) {

				//Value to be set
				Display.Voices_ONOFF[0] = false;

				//value display
				char write_str[] = "ON";
				strcpy(Display.value_str_dummy[0],write_str);
			}
			break;
		case 2:
			/* Processing with floats
			 */

			// fill value line with uncolored rectangle
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2 + VALUE_ROW_LENGTH, UNCOLORED);

			//Value to be set
			//			Display.Voices_ONOFF[0] = false;



			//display the value
			//prints a float value
			float printFloat = potVal;
			sprintf(write_str,"%f", printFloat);
			memcpy(Display.value_str_dummy[1],write_str,3); //float can only displayed with two digits after dot

			break;
		case 3:
			/* Processing with Int
			 */

			// fill value line with uncolored rectangle
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3 + VALUE_ROW_LENGTH, UNCOLORED);

			//Value to be set
			//			Display.Voices_ONOFF[0] = false;


			//display the value
			//prints an int value
			uint8_t printInt = (uint)(potVal);
			sprintf(write_str,"%i", printInt);
			memcpy(Display.value_str_dummy[1],write_str,3); //float can only displayed with two digits after dot
			break;

		case 4:
			// fill value line with uncolored rectangle
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4 + VALUE_ROW_LENGTH, UNCOLORED);

			break;
			//
		default:
			break;
		}

	}
	//print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_dummy[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_dummy[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_dummy[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_dummy[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_dummy[4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, Display.value_str_dummy[5], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE7, Display.value_str_dummy[6], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE8, Display.value_str_dummy[7], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE9, Display.value_str_dummy[8], &Font12, COLORED);

}
