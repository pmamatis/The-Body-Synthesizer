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

	strcpy(&Display->source_names[GYRO_LR], "Gyro L/R");
	strcpy(&Display->source_names[GYRO_FB], "Gyro F/B");
	strcpy(&Display->source_names[EMG], "EMG");
	strcpy(&Display->source_names[EKG], "EKG");
	strcpy(&Display->source_names[POTI], "POTI");

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


	//Keyboard
	Display->Keyboard_Octave = 3;


	//VOICES
	for(int i=0; i<3; i++) {
		Display -> Voices_Created[i] = false;
		Display -> Voices_ONOFF[i] = false;
	}

	Display->ADSR_ONOFF = false;
	Display->ADSR_Attacktime = 0.10;
	Display->ADSR_Decaytime = 0.10;
	Display->ADSR_Sustaintime = 0.30;
	Display->ADSR_Sustainlevel = 0.50;
	Display->ADSR_Releasetime = 0.05;
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
	Display->Tremolo_Rate = 2;
	Display->Tremolo_Depth = 0.0;
	Display->Tremolo_EffectPosition = 0;
	Display->Tremolo_EffectAdded = false;

	for(int i=0; i<5; i++) {
		Display->Filter_Cutoff[i] = 100.0;
		Display->Filter_ONOFF[i] = false;
	}
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
	//	Display->Keyboard_Octave = 0;

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
	//	Display->page_min = 0;
	Display->page_min = -1;
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
	strcpy(Display->value_str_dummy[0],"OFF");	// dummy
	strcpy(Display->value_str_dummy[1],"C");
	strcpy(Display->value_str_dummy[2],"0");
	strcpy(Display->value_str_dummy[3],"OFF");
	strcpy(Display->value_str_dummy[4],"");
	strcpy(Display->value_str_dummy[5],"");
	strcpy(Display->value_str_dummy[6],"");
	strcpy(Display->value_str_dummy[7],"");
	strcpy(Display->value_str_dummy[8],"");

	strcpy(Display->value_str_voices_overview[0],"");	// voices overview
	strcpy(Display->value_str_voices_overview[1],"OFF");
	strcpy(Display->value_str_voices_overview[2],"OFF");
	strcpy(Display->value_str_voices_overview[3],"OFF");
	strcpy(Display->value_str_voices_overview[4],"OFF");
	strcpy(Display->value_str_voices_overview[5],"");
	strcpy(Display->value_str_voices_overview[6],"");
	strcpy(Display->value_str_voices_overview[7],"");
	strcpy(Display->value_str_voices_overview[8],"");

	strcpy(Display->value_str_voices_settings[0],"");	// voices settings
	strcpy(Display->value_str_voices_settings[1],"");
	strcpy(Display->value_str_voices_settings[2],"POTI");
	strcpy(Display->value_str_voices_settings[3],"POTI");
	strcpy(Display->value_str_voices_settings[4],"");
	strcpy(Display->value_str_voices_settings[5],"");
	strcpy(Display->value_str_voices_settings[6],"");
	strcpy(Display->value_str_voices_settings[7],"");
	strcpy(Display->value_str_voices_settings[8],"");

	strcpy(Display->value_str_adsr_overview[0],"");	// adsr overview
	strcpy(Display->value_str_adsr_overview[1],"OFF");
	strcpy(Display->value_str_adsr_overview[2],"0.10");
	strcpy(Display->value_str_adsr_overview[3],"0.10");
	strcpy(Display->value_str_adsr_overview[4],"0.30");
	strcpy(Display->value_str_adsr_overview[5],"0.50");
	strcpy(Display->value_str_adsr_overview[6],"0.05");
	strcpy(Display->value_str_adsr_overview[7],"OFF");
	strcpy(Display->value_str_adsr_overview[8],"");

	strcpy(Display->value_str_adsr_settings[0],"POTI");	// adsr settings
	strcpy(Display->value_str_adsr_settings[1],"POTI");
	strcpy(Display->value_str_adsr_settings[2],"POTI");
	strcpy(Display->value_str_adsr_settings[3],"POTI");
	strcpy(Display->value_str_adsr_settings[4],"POTI");
	strcpy(Display->value_str_adsr_settings[5],"");
	strcpy(Display->value_str_adsr_settings[6],"");
	strcpy(Display->value_str_adsr_settings[7],"");
	strcpy(Display->value_str_adsr_settings[8],"");

	strcpy(Display->value_str_equalizer_overview[0],"");	// equalizer overview
	strcpy(Display->value_str_equalizer_overview[1],"OFF");
	strcpy(Display->value_str_equalizer_overview[2],"OFF");
	strcpy(Display->value_str_equalizer_overview[3],"OFF");
	strcpy(Display->value_str_equalizer_overview[4],"OFF");
	strcpy(Display->value_str_equalizer_overview[5],"OFF");
	strcpy(Display->value_str_equalizer_overview[6],"OFF");
	strcpy(Display->value_str_equalizer_overview[7],"");
	strcpy(Display->value_str_equalizer_overview[8],"");

	strcpy(Display->value_str_equalizer_settings[0],"");	// equalizer settings
	strcpy(Display->value_str_equalizer_settings[1],"");
	strcpy(Display->value_str_equalizer_settings[2],"");
	strcpy(Display->value_str_equalizer_settings[3],"");
	strcpy(Display->value_str_equalizer_settings[4],"");
	strcpy(Display->value_str_equalizer_settings[5],"");
	strcpy(Display->value_str_equalizer_settings[6],"");
	strcpy(Display->value_str_equalizer_settings[7],"");
	strcpy(Display->value_str_equalizer_settings[8],"");

	strcpy(Display->value_str_distortion[0],"OFF");	// distortion overview
	strcpy(Display->value_str_distortion[1],"1");
	strcpy(Display->value_str_distortion[2],"POTI");
	strcpy(Display->value_str_distortion[3],"OFF");
	strcpy(Display->value_str_distortion[4],"");
	strcpy(Display->value_str_distortion[5],"");
	strcpy(Display->value_str_distortion[6],"");
	strcpy(Display->value_str_distortion[7],"");
	strcpy(Display->value_str_distortion[8],"");

	strcpy(Display->value_str_tremolo[0],"OFF");	// tremolo overview
	strcpy(Display->value_str_tremolo[1],"4");
	strcpy(Display->value_str_tremolo[2],"0.00");
	strcpy(Display->value_str_tremolo[3],"POTI");
	strcpy(Display->value_str_tremolo[4],"POTI");
	strcpy(Display->value_str_tremolo[5],"POTI");
	strcpy(Display->value_str_tremolo[6],"OFF");
	strcpy(Display->value_str_tremolo[7],"");
	strcpy(Display->value_str_tremolo[8],"");

	// Drumcomputer
	Display->lastCurrentSampleRow = 1;
	Display->CurrentSampleRow = 1;
	//Display->MaxNumberOfSamples = 4;
	Display->lastCurrentDrumstep = 1;
	Display->CurrentDrumstep = 1;
	//Display->NumberOfDrumsteps = 8;
	for(int i=0; i<MAX_NUMBER_OF_SAMPLES; i++) {
		for(int j=0; j<NUMBER_OF_DRUMSTEPS; j++) {
			Display->DrumMatrix[i][j] = false;
		}
	}
	Display->UpdateDisplay = false;
	Display->Drumcomputer_ONOFF = false;
	Display->EditDrums = false;
	Display->LoadDrumkit = false;

	// Sequencer
	for(int i=0; i<MAX_NUMBER_OF_NOTES; i++) {
		for(int j=0; j<NUMBER_OF_SEQUENCERSTEPS; j++) {
			Display->SequencerMatrix[i][j] = false;
		}
	}
	Display->CurrentNoteRow = 1;
	Display->CurrentSequencestep = 1;
	Display->Sequencer_ONOFF = false;
	Display->EditSteps = false;

	// WahWah
	Display->WahWah_Mode = 0;

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
	//Paint_SetRotate(paint, ROTATE_90);
	// Display the frame_buffer to show the TU Berlin-logo
	EPD_SetFrameMemory(epd, TU_LOGO, 0, 0, Paint_GetWidth(paint), Paint_GetHeight(paint));
	EPD_DisplayFrame(epd);
	EPD_DelayMs(epd, 1000);
	Paint_Clear(paint, UNCOLORED);
	// Display the frame_buffer to show a white screen
	EPD_SetFrameMemory(epd, frame_buffer, 0, 0, Paint_GetWidth(paint), Paint_GetHeight(paint));
	EPD_DisplayFrame(epd);
	EPD_Init(epd, lut_partial_update);

	//	DISPLAY_processing();
	//	DISPLAY_DrawArrow(1);
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

	// this has to be done to make sure that the "current" variables are reset to 0, when we switch back from settings pages to overview pages
	if(Display.currentVoice > 0)
		Display.currentVoice = 0;
	else if(Display.currentBand > 0)
		Display.currentBand = 0;
	else if(Display.currentADSR > 0)
		Display.currentADSR = 0;
	else if(Display.currentDistortion > 0)
		Display.currentDistortion = 0;
	else if(Display.currentTremolo > 0)
		Display.currentTremolo = 0;
	else if(Display.currentDrumcomputer > 0)
		Display.currentDrumcomputer = 0;
	else if(Display.currentWahWah > 0)
		Display.currentWahWah = 0;

	Display.JoystickParameterPosition = 1;

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

	Display.JoystickParameterPosition = 1;

	Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);	// delete the frame content

	if (Display.pagePosition < Display.page_max)
		Display.pagePosition = Display.pagePosition+1;

	DISPLAY_PrintCurrentPage();
}

/** @brief this function is the main processing function of the display
 *
 */
void DISPLAY_processing(void) {

	switch(Display.mode) {

	case NONE:
		p_StartingMenu(frame_buffer);
		break;

	case BODYSYNTH:
		Display.page_max = 9; // has to be changed for every added case

		switch(Display.pagePosition) {
		case -1:
			p_Presets();
			break;
		case 0:
			p_StartingMenu(frame_buffer);
			break;
		case 1:
			p_Volume();
			break;
		case 2:
			p_Drumcomputer_overview();
			break;
		case 3:
			switch(Display.currentDrumcomputer) {
			case 0:
				p_Sequencer_overview();
				break;
			default:
				p_Drumcomputer_Settings();
				//				Display.page_max = 3;
				Display.page_max = Display.pagePosition;
				break;
			}
			break;
			case 4:
				switch(Display.currentSequencer) {
				case 0:
					p_Voices_overview();
					break;
				default:
					p_Sequencer_Settings();
					//					Display.page_max = 4;
					Display.page_max = Display.pagePosition;
					break;
				}
				break;
				case 5:
					switch(Display.currentVoice) {
					case 0:
						p_ADSR_overview(&envelope);
						break;
					default:
						p_Voices_Settings();
						//						Display.page_max = 5;
						Display.page_max = Display.pagePosition;
						break;
					}
					break;
					case 6:
						switch(Display.currentADSR) {
						case 0:
							p_Equalizer_overview();
							break;
						default:
							p_ADSR_Settings();
							//							Display.page_max = 6;
							Display.page_max = Display.pagePosition;
							break;
						}
						break;
						case 7:
							switch(Display.currentBand) {
							case 0:
								p_WahWah_overview(&WahWah);
								break;
							default:
								p_Equalizer_Settings();
								//								Display.page_max = 7;
								Display.page_max = Display.pagePosition;
								break;
							}
							break;
							case 8:
								switch(Display.currentWahWah) {
								case 0:
									p_Distortion(&HardClipping);
									break;
								default:
									p_WahWah_Settings(&WahWah);
									//									Display.page_max = 8;
									Display.page_max = Display.pagePosition;
									break;
								}
								break;
								case 9:
									p_Tremolo(&Tremolo);
									break;
								default:
									break;
		}
		break;

		case KEYBOARD:
			Display.page_max = 1; // has to be changed for every added case
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
			//				break;
			//				default:
			//					break;
	}
}

/** @brief this function prints the start menu
 * @param frame_buffer: frame buffer of the display
 * @return returns display status flag
 */
Display_Status p_StartingMenu(unsigned char* frame_buffer) {

	//Header line
	Paint_DrawStringAt(&paint, 1, CASE0, "THE BODYSYNTH", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE1, "Synthesizermode", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE2, "Keyboardmode", &Font12, COLORED);

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

Display_Status p_Drumcomputer_overview(void) {

	//Header line
	char headerstring[] = "DRUMCOMPUTER";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Next effect";
	char str_2[] = "Drumcomputer ON/OFF";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentDrumcomputer = 0;
		break;
	case 2:
		// Drumcomputer Settings
		Display.currentDrumcomputer = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
		float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %
		if(potVal < 50) {	// smaller than 50 %
			Display.Drumcomputer_ONOFF = false;
			strcpy(Display.value_str_drumcomputer[0], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Drumcomputer_ONOFF = true;
			strcpy(Display.value_str_drumcomputer[0], "ON");
		}
		break;
	}

	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_drumcomputer[0], &Font12, COLORED);

	return DISPLAY_OK;
}

Display_Status p_Drumcomputer_Settings(void) {

	char drumkit_str[10];

	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, "Last page", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, "BPM", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, "Load sample", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, "Edit drums", &Font12, COLORED);
	Display_DrawDrumcomputerIcons(Display.sample1, Display.sample2, Display.sample3, Display.sample4);
	DISPLAY_DrawDrumcomputerPatternFrame(8);

	if(Display.JoystickParameterPosition == 1) {	// last page
		Display.EditDrums = false;
	}
	else if(Display.JoystickParameterPosition == 2) {	// change BPM -> processing done in interrupt
		Display.EditDrums = false;
	}
	else if(Display.JoystickParameterPosition == 3) {	// load sample from sd card
		Display.EditDrums = false;

		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-35, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
		float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %

		if(potVal >= 0 && potVal < 25) {
			strcpy(drumkit_str, "909");
			strcpy(Display.sample1, "Kick");
			strcpy(Display.sample2, "Op.HH");
			strcpy(Display.sample3, "Clap");
			strcpy(Display.sample4, "L.Tom");
			Paint_DrawStringAt(&paint, Display.value_start_x_position-35, CASE3, drumkit_str, &Font12, COLORED);
			DISPLAY_Update();
			if(Display.LoadDrumkit == true) {
				Display_LoadDrumKits(0);
				Display.LoadDrumkit = false;
			}
		}
		else if(potVal >= 25 && potVal < 50) {
			strcpy(drumkit_str, "Rock loud");
			strcpy(Display.sample1, "Kick");
			strcpy(Display.sample2, "Hihat");
			strcpy(Display.sample3, "Snare");
			strcpy(Display.sample4, "Ride");
			Paint_DrawStringAt(&paint, Display.value_start_x_position-35, CASE3, drumkit_str, &Font12, COLORED);
			DISPLAY_Update();
			if(Display.LoadDrumkit == true) {
				Display_LoadDrumKits(1);
				Display.LoadDrumkit = false;
			}
		}
		else if(potVal >= 50 && potVal < 75) {
			strcpy(drumkit_str, "Rock");
			strcpy(Display.sample1, "Kick");
			strcpy(Display.sample2, "Hihat");
			strcpy(Display.sample3, "Snare");
			strcpy(Display.sample4, "Ride");
			Paint_DrawStringAt(&paint, Display.value_start_x_position-35, CASE3, drumkit_str, &Font12, COLORED);
			DISPLAY_Update();
			if(Display.LoadDrumkit == true) {
				Display_LoadDrumKits(2);
				Display.LoadDrumkit = false;
			}
		}
		else if(potVal >= 75 && potVal <= 100) {
			strcpy(drumkit_str, "TODO");
			Paint_DrawStringAt(&paint, Display.value_start_x_position-35, CASE3, drumkit_str, &Font12, COLORED);
			DISPLAY_Update();
			if(Display.LoadDrumkit == true) {
				Display_LoadDrumKits(3);
				Display.LoadDrumkit = false;
			}
		}
	}
	else if(Display.JoystickParameterPosition == 4) {	// edit drums on/off
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
		float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %
		if(potVal < 50) {	// smaller than 50 %
			Display.EditDrums = false;
			strcpy(Display.value_str_drumcomputer[1], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.EditDrums = true;
			strcpy(Display.value_str_drumcomputer[1], "ON");
		}
	}

	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_drumcomputer[1], &Font12, COLORED);

	return DISPLAY_OK;
}

Display_Status Display_LoadDrumKits(uint8_t Drumkit) {

	__disable_irq();	// disable interrupts for a while to make sure that the samples are loaded more quickly

	if(Drumkit == 0) {
		// INIT: 909 LUTs
		// POSSIBLE: Kick, ClosedHihat, OpenHihat, Clap, Rimshot, LowTom, MidTom, HiTom
		sd_card_mount();
		sd_card_read("909_Kick.txt", &DS1);
		sd_card_read("909_OpenHihat.txt", &DS2);
		sd_card_read("909_Clap.txt", &DS3);
		sd_card_read("909_LowTom.txt", &DS4);
		sd_card_unmount();
	}

	else if(Drumkit == 1) {
		// INIT: Rock Loud LUTs
		// POSSIBLE: Kick, Hihat, Snare, Ride
		sd_card_mount();
		sd_card_read("Rock_loud_Kick.txt", &DS1);
		sd_card_read("Rock_loud_Hihat.txt", &DS2);
		sd_card_read("Rock_loud_Snare.txt", &DS3);
		sd_card_read("Rock_loud_Ride.txt", &DS4);
		sd_card_unmount();
	}

	else if(Drumkit == 2) {
		// INIT: Rock LUTs
		// POSSIBLE: Kick, Hihat, Snare, Ride
		sd_card_mount();
		sd_card_read("Rock_Kick.txt", &DS1);
		sd_card_read("Rock_Hihat.txt", &DS2);
		sd_card_read("Rock_Snare.txt", &DS3);
		sd_card_read("Rock_Ride.txt", &DS4);
		sd_card_unmount();
	}

	else if(Drumkit == 3) {
		// todo
	}

	__enable_irq();

	return DISPLAY_OK;
}

Display_Status Display_DrawDrumcomputerIcons(char* S1, char* S2, char* S3, char* S4) {

	Paint_DrawStringAt(&paint, 1, CASE0, "DRUMCOMPUTER", &Font16, COLORED);

	Paint_DrawFilledRectangle(&paint, 1, CASE5+5, STEP1, CASE6+5, UNCOLORED);
	Paint_DrawFilledRectangle(&paint, 1, CASE6+5, STEP1, CASE7+5, UNCOLORED);
	Paint_DrawFilledRectangle(&paint, 1, CASE7+5, STEP1, CASE8+5, UNCOLORED);
	Paint_DrawFilledRectangle(&paint, 1, CASE8+5, STEP1, CASE9+5, UNCOLORED);

	Paint_DrawStringAt(&paint, 1, CASE5+5, S1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE6+5, S2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE7+5, S3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE8+5, S4, &Font12, COLORED);

	return DISPLAY_OK;
}

Display_Status DISPLAY_DrawDrumcomputerPatternFrame(uint8_t Drumsteps) {

	// draw horizontal lines
	Paint_DrawRectangle(&paint, STEP1, CASE5, 200, CASE6, COLORED);
	Paint_DrawRectangle(&paint, STEP1, CASE6, 200, CASE7, COLORED);
	Paint_DrawRectangle(&paint, STEP1, CASE7, 200, CASE8, COLORED);
	Paint_DrawRectangle(&paint, STEP1, CASE8, 200, CASE9, COLORED);

	if(NUMBER_OF_DRUMSTEPS == 8) {	// at the moment the drum machine is limited to 8 steps
		// draw vertical lines
		Paint_DrawRectangle(&paint, STEP1, CASE5, STEP2, CASE9, COLORED);
		Paint_DrawRectangle(&paint, STEP2, CASE5, STEP3, CASE9, COLORED);
		Paint_DrawRectangle(&paint, STEP3, CASE5, STEP4, CASE9, COLORED);
		Paint_DrawRectangle(&paint, STEP4, CASE5, STEP5, CASE9, COLORED);
		Paint_DrawRectangle(&paint, STEP5, CASE5, STEP6, CASE9, COLORED);
		Paint_DrawRectangle(&paint, STEP6, CASE5, STEP7, CASE9, COLORED);
		Paint_DrawRectangle(&paint, STEP7, CASE5, STEP8, CASE9, COLORED);
		Paint_DrawRectangle(&paint, STEP8, CASE5, STEP8+19, CASE9, COLORED);
	}

	// draw the drumcomputerpattern
	DISPLAY_DrawDrumcomputerPattern();

	//DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_DrawDrumcomputerPattern(void) {

	uint8_t filledrectangle_subtract = 5;
	uint16_t STEP, CASE;

	for(int i=0; i<MAX_NUMBER_OF_SAMPLES; i++) {

		for(int j=0; j<NUMBER_OF_DRUMSTEPS; j++) {

			if(Display.DrumMatrix[i][j] == true) {

				// set coordinate for sample rows
				if( i+1 == 1 )
					CASE = CASE5;
				else if( i+1 == 2 )
					CASE = CASE6;
				else if( i+1 == 3 )
					CASE = CASE7;
				else if( i+1 == 4 )
					CASE = CASE8;

				// set coordinate for drumsteps
				if( j+1 == 1 )
					STEP = STEP1;
				else if( j+1 == 2 )
					STEP = STEP2;
				else if( j+1 == 3 )
					STEP = STEP3;
				else if( j+1 == 4 )
					STEP = STEP4;
				else if( j+1 == 5 )
					STEP = STEP5;
				else if( j+1 == 6 )
					STEP = STEP6;
				else if( j+1 == 7 )
					STEP = STEP7;
				else if( j+1 == 8 )
					STEP = STEP8;

				Paint_DrawFilledRectangle(&paint, STEP+filledrectangle_subtract, CASE+filledrectangle_subtract, STEP+20-filledrectangle_subtract, CASE+20-filledrectangle_subtract, COLORED);
			}
		}
	}

	return DISPLAY_OK;
}

Display_Status DISPLAY_SetDrumcomputerStep(void) {

	uint8_t filledrectangle_subtract = 5;

	switch(Display.CurrentSampleRow) {
	case 1:	// Sample1 Row
		switch(Display.CurrentDrumstep) {
		case 1:	// Step 1..
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[0] = 1;
				Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 2:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[1] = 1;
				Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 3:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[2] = 1;
				Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 4:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[3] = 1;
				Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 5:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[4] = 1;
				Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 6:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[5] = 1;
				Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 7:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[6] = 1;
				Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 8:	// ..Step 8
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				timing_DS1[7] = 1;
				Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		default:
			break;
		}
		break;
		case 2:	// Sample2 Row
			switch(Display.CurrentDrumstep) {
			case 1:	// Step 1..
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[0] = 1;
					Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 2:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[1] = 1;
					Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 3:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[2] = 1;
					Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 4:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[3] = 1;
					Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 5:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[4] = 1;
					Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 6:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[5] = 1;
					Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 7:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[6] = 1;
					Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 8:	// ..Step 8
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
					timing_DS2[7] = 1;
					Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			default:
				break;
			}
			break;
			case 3:	// Sample 3 Row
				switch(Display.CurrentDrumstep) {
				case 1:	// Step 1..
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[0] = 1;
						Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 2:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[1] = 1;
						Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 3:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[2] = 1;
						Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 4:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[3] = 1;
						Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 5:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[4] = 1;
						Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 6:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[5] = 1;
						Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 7:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[6] = 1;
						Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 8:	// ..Step 8
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
						timing_DS3[7] = 1;
						Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				default:
					break;
				}
				break;
				case 4:	// Sample 4 Row
					switch(Display.CurrentDrumstep) {
					case 1:	// Step 1..
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[0] = 1;
							Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					case 2:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[1] = 1;
							Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					case 3:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[2] = 1;
							Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					case 4:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[3] = 1;
							Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					case 5:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[4] = 1;
							Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					case 6:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[5] = 1;
							Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					case 7:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[6] = 1;
							Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					case 8:	// ..Step 8
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
							timing_DS4[7] = 1;
							Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, COLORED);
						}
						break;
					default:
						break;
					}
					break;
					default:
						break;
	}

	//DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_DeleteDrumcomputerStep(void) {

	uint8_t filledrectangle_subtract = 5;
	//Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE1+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE1+20-filledrectangle_subtract, UNCOLORED);

	switch(Display.CurrentSampleRow) {
	case 1:	// Sample1 Row
		switch(Display.CurrentDrumstep) {
		case 1:	// Step 1..
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[0] = 0;
				Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 2:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[1] = 0;
				Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 3:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[2] = 0;
				Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 4:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[3] = 0;
				Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 5:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[4] = 0;
				Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 6:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[5] = 0;
				Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 7:
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[6] = 0;
				Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 8:	// ..Step 8
			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				timing_DS1[7] = 0;
				Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		default:
			break;
		}
		break;
		case 2:	// Sample2 Row
			switch(Display.CurrentDrumstep) {
			case 1:	// Step 1..
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[0] = 0;
					Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 2:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[1] = 0;
					Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 3:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[2] = 0;
					Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 4:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[3] = 0;
					Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 5:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[4] = 0;
					Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 6:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[5] = 0;
					Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 7:
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[6] = 0;
					Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 8:	// ..Step 8
				if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
					timing_DS2[7] = 0;
					Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			default:
				break;
			}
			break;
			case 3:	// Sample 3 Row
				switch(Display.CurrentDrumstep) {
				case 1:	// Step 1..
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[0] = 0;
						Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 2:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[1] = 0;
						Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 3:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[2] = 0;
						Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 4:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[3] = 0;
						Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 5:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[4] = 0;
						Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 6:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[5] = 0;
						Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 7:
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[6] = 0;
						Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 8:	// ..Step 8
					if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
						timing_DS3[7] = 0;
						Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				default:
					break;
				}
				break;
				case 4:	// Sample 4 Row
					switch(Display.CurrentDrumstep) {
					case 1:	// Step 1..
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[0] = 0;
							Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					case 2:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[1] = 0;
							Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					case 3:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[2] = 0;
							Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					case 4:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[3] = 0;
							Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					case 5:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[4] = 0;
							Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					case 6:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[5] = 0;
							Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					case 7:
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[6] = 0;
							Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					case 8:	// ..Step 8
						if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
							timing_DS4[7] = 0;
							Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE8+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE8+20-filledrectangle_subtract, UNCOLORED);
						}
						break;
					default:
						break;
					}
					break;
					default:
						break;
	}

	//	DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_SetDrumcomputerStepCursor(void) {

	uint8_t rectangle_subtract = 3;

	switch(Display.CurrentSampleRow) {
	case 1:	// Sample1 Row
		switch(Display.CurrentDrumstep) {
		case 1:	// Step 1..
			Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE5+rectangle_subtract, STEP1+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 2:
			Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE5+rectangle_subtract, STEP2+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 3:
			Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE5+rectangle_subtract, STEP3+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 4:
			Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE5+rectangle_subtract, STEP4+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 5:
			Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE5+rectangle_subtract, STEP5+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 6:
			Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE5+rectangle_subtract, STEP6+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 7:
			Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE5+rectangle_subtract, STEP7+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 8:	// ..Step 8
			Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE5+rectangle_subtract, STEP8+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		default:
			break;
		}
		break;
		case 2:	// Sample2 Row
			switch(Display.CurrentDrumstep) {
			case 1:	// Step 1..
				Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE6+rectangle_subtract, STEP1+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 2:
				Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE6+rectangle_subtract, STEP2+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 3:
				Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE6+rectangle_subtract, STEP3+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 4:
				Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE6+rectangle_subtract, STEP4+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 5:
				Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE6+rectangle_subtract, STEP5+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 6:
				Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE6+rectangle_subtract, STEP6+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 7:
				Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE6+rectangle_subtract, STEP7+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 8:	// ..Step 8
				Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE6+rectangle_subtract, STEP8+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			default:
				break;
			}
			break;
			case 3:	// Sample 3 Row
				switch(Display.CurrentDrumstep) {
				case 1:	// Step 1..
					Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE7+rectangle_subtract, STEP1+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 2:
					Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE7+rectangle_subtract, STEP2+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 3:
					Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE7+rectangle_subtract, STEP3+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 4:
					Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE7+rectangle_subtract, STEP4+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 5:
					Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE7+rectangle_subtract, STEP5+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 6:
					Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE7+rectangle_subtract, STEP6+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 7:
					Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE7+rectangle_subtract, STEP7+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 8:	// ..Step 8
					Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE7+rectangle_subtract, STEP8+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				default:
					break;
				}
				break;
				case 4:	// Sample 4 Row
					switch(Display.CurrentDrumstep) {
					case 1:	// Step 1..
						Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE8+rectangle_subtract, STEP1+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					case 2:
						Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE8+rectangle_subtract, STEP2+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					case 3:
						Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE8+rectangle_subtract, STEP3+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					case 4:
						Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE8+rectangle_subtract, STEP4+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					case 5:
						Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE8+rectangle_subtract, STEP5+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					case 6:
						Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE8+rectangle_subtract, STEP6+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					case 7:
						Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE8+rectangle_subtract, STEP7+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					case 8:	// ..Step 8
						Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE8+rectangle_subtract, STEP8+20-rectangle_subtract, CASE8+20-rectangle_subtract, COLORED);
						break;
					default:
						break;
					}
					break;
					default:
						break;
	}

	DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_DeleteDrumcomputerStepCursor(void) {

	uint8_t rectangle_subtract = 3;

	switch(Display.CurrentSampleRow) {
	case 1:	// Sample1 Row
		switch(Display.CurrentDrumstep) {
		case 1:	// Step 1..
			Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE5+rectangle_subtract, STEP1+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 2:
			Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE5+rectangle_subtract, STEP2+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 3:
			Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE5+rectangle_subtract, STEP3+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 4:
			Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE5+rectangle_subtract, STEP4+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 5:
			Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE5+rectangle_subtract, STEP5+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 6:
			Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE5+rectangle_subtract, STEP6+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 7:
			Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE5+rectangle_subtract, STEP7+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 8:	// ..Step 8
			Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE5+rectangle_subtract, STEP8+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		default:
			break;
		}
		break;
		case 2:	// Sample2 Row
			switch(Display.CurrentDrumstep) {
			case 1:	// Step 1..
				Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE6+rectangle_subtract, STEP1+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 2:
				Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE6+rectangle_subtract, STEP2+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 3:
				Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE6+rectangle_subtract, STEP3+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 4:
				Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE6+rectangle_subtract, STEP4+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 5:
				Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE6+rectangle_subtract, STEP5+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 6:
				Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE6+rectangle_subtract, STEP6+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 7:
				Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE6+rectangle_subtract, STEP7+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 8:	// ..Step 8
				Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE6+rectangle_subtract, STEP8+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			default:
				break;
			}
			break;
			case 3:	// Sample 3 Row
				switch(Display.CurrentDrumstep) {
				case 1:	// Step 1..
					Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE7+rectangle_subtract, STEP1+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 2:
					Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE7+rectangle_subtract, STEP2+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 3:
					Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE7+rectangle_subtract, STEP3+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 4:
					Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE7+rectangle_subtract, STEP4+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 5:
					Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE7+rectangle_subtract, STEP5+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 6:
					Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE7+rectangle_subtract, STEP6+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 7:
					Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE7+rectangle_subtract, STEP7+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 8:	// ..Step 8
					Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE7+rectangle_subtract, STEP8+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				default:
					break;
				}
				break;
				case 4:	// Sample 4 Row
					switch(Display.CurrentDrumstep) {
					case 1:	// Step 1..
						Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE8+rectangle_subtract, STEP1+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					case 2:
						Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE8+rectangle_subtract, STEP2+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					case 3:
						Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE8+rectangle_subtract, STEP3+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					case 4:
						Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE8+rectangle_subtract, STEP4+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					case 5:
						Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE8+rectangle_subtract, STEP5+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					case 6:
						Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE8+rectangle_subtract, STEP6+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					case 7:
						Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE8+rectangle_subtract, STEP7+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					case 8:	// ..Step 8
						Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE8+rectangle_subtract, STEP8+20-rectangle_subtract, CASE8+20-rectangle_subtract, UNCOLORED);
						break;
					default:
						break;
					}
					break;
					default:
						break;
	}

	DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status p_Sequencer_overview(void) {

	//Header line
	char headerstring[] = "SEQUENCER";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Next effect";
	char str_2[] = "Sequencer ON/OFF";
	char str_3[] = "Seq. Note 1";
	char str_4[] = "Seq. Octave 1";
	char str_5[] = "Seq. Note 2";
	char str_6[] = "Seq. Octave 2";
	char str_7[] = "Seq. Note 3";
	char str_8[] = "Seq. Octave 3";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE8, str_8, &Font12, COLORED);

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Next Effect
			Display.currentSequencer = 0;
			break;
		case 2:
			// Sequencer ON/OFF
			Display.currentSequencer = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %
			if(potVal < 50) {	// smaller than 50 %
				Display.Sequencer_ONOFF = false;
				strcpy(Display.value_str_sequencer[0], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Sequencer_ONOFF = true;
				strcpy(Display.value_str_sequencer[0], "ON");
			}
			break;
		case 3:
			// Sequencer Note 1
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.noteindex = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * (sizeof(keys)/sizeof(keys[0]));
			Display.Sequencer_Note[0] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
			sprintf(Display.value_str_sequencer[1], "%c", Display.Sequencer_Note[0]);

			freq_index_SN1 = Get_Note_Index(Display.Sequencer_Note[0], (uint8_t)Display.Sequencer_Octave[0]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
			}
			break;
		case 4:
			// Sequencer Octave 1
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Sequencer_Octave[0] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 6);
			sprintf(Display.value_str_sequencer[2], "%d", Display.Sequencer_Octave[0]);

			freq_index_SN1 = Get_Note_Index(Display.Sequencer_Note[0], (uint8_t)Display.Sequencer_Octave[0]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
			}
			break;
		case 5:
			// Sequencer Note 2
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
			Display.noteindex = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * (sizeof(keys)/sizeof(keys[0]));
			Display.Sequencer_Note[1] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
			sprintf(Display.value_str_sequencer[3], "%c", Display.Sequencer_Note[1]);

			freq_index_SN2 = Get_Note_Index(Display.Sequencer_Note[1], (uint8_t)Display.Sequencer_Octave[1]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
			}
			break;
		case 6:
			// Sequencer Octave 2
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Sequencer_Octave[1] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 6);
			sprintf(Display.value_str_sequencer[4], "%d", Display.Sequencer_Octave[1]);

			freq_index_SN2 = Get_Note_Index(Display.Sequencer_Note[1], (uint8_t)Display.Sequencer_Octave[1]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
			}
			break;
		case 7:
			// Sequencer Note 3
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH, UNCOLORED);
			Display.noteindex = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * (sizeof(keys)/sizeof(keys[0]));
			Display.Sequencer_Note[2] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
			sprintf(Display.value_str_sequencer[5], "%c", Display.Sequencer_Note[2]);

			freq_index_SN3 = Get_Note_Index(Display.Sequencer_Note[2], (uint8_t)Display.Sequencer_Octave[2]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
			}
			break;
		case 8:
			// Sequencer Octave 3
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE8, Display.value_end_x_position, CASE8+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Sequencer_Octave[2] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 6);
			sprintf(Display.value_str_sequencer[6], "%d", Display.Sequencer_Octave[2]);

			freq_index_SN3 = Get_Note_Index(Display.Sequencer_Note[2], (uint8_t)Display.Sequencer_Octave[2]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
			}
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_sequencer[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_sequencer[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_sequencer[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_sequencer[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, Display.value_str_sequencer[4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE7, Display.value_str_sequencer[5], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE8, Display.value_str_sequencer[6], &Font12, COLORED);

	return DISPLAY_OK;
}

Display_Status p_Sequencer_Settings(void) {

	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, "Last page", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, "BPM", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, "Edit sequence", &Font12, COLORED);
	Display_DrawSequencerIcons();
	DISPLAY_DrawSequencerPatternFrame(8);

	if(Display.JoystickParameterPosition == 1) {	// last page
		Display.EditSteps = false;
	}
	else if(Display.JoystickParameterPosition == 2) {	// change BPM -> processing done in interrupt
		Display.EditSteps = false;
	}
	else if(Display.JoystickParameterPosition == 3) {	// edit sequence on/off
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
		float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %
		if(potVal < 50) {	// smaller than 50 %
			Display.EditSteps = false;
			strcpy(Display.value_str_sequencer[7], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.EditSteps = true;
			strcpy(Display.value_str_sequencer[7], "ON");
		}
	}

	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_sequencer[7], &Font12, COLORED);

	return DISPLAY_OK;
}

Display_Status Display_DrawSequencerIcons(void) {

	Paint_DrawStringAt(&paint, 1, CASE0, "SEQUENCER", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE5+5, "Note1", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE6+5, "Note2", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE7+5, "Note3", &Font12, COLORED);

	return DISPLAY_OK;
}

Display_Status DISPLAY_DrawSequencerPatternFrame(uint8_t Drumsteps) {

	// draw horizontal lines
	Paint_DrawRectangle(&paint, STEP1, CASE5, 200, CASE6, COLORED);
	Paint_DrawRectangle(&paint, STEP1, CASE6, 200, CASE7, COLORED);
	Paint_DrawRectangle(&paint, STEP1, CASE7, 200, CASE8, COLORED);

	if(NUMBER_OF_SEQUENCERSTEPS == 8) {	// at the moment the sequencer is limited to 8 steps
		// draw vertical lines
		Paint_DrawRectangle(&paint, STEP1, CASE5, STEP2, CASE8, COLORED);
		Paint_DrawRectangle(&paint, STEP2, CASE5, STEP3, CASE8, COLORED);
		Paint_DrawRectangle(&paint, STEP3, CASE5, STEP4, CASE8, COLORED);
		Paint_DrawRectangle(&paint, STEP4, CASE5, STEP5, CASE8, COLORED);
		Paint_DrawRectangle(&paint, STEP5, CASE5, STEP6, CASE8, COLORED);
		Paint_DrawRectangle(&paint, STEP6, CASE5, STEP7, CASE8, COLORED);
		Paint_DrawRectangle(&paint, STEP7, CASE5, STEP8, CASE8, COLORED);
		Paint_DrawRectangle(&paint, STEP8, CASE5, STEP8+19, CASE8, COLORED);
	}

	// draw the sequencer pattern
	DISPLAY_DrawSequencerPattern();

	//DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_DrawSequencerPattern(void) {

	uint8_t filledrectangle_subtract = 5;
	uint16_t STEP, CASE;

	for(int i=0; i<MAX_NUMBER_OF_NOTES; i++) {
		for(int j=0; j<NUMBER_OF_SEQUENCERSTEPS; j++) {

			if(Display.SequencerMatrix[i][j] == true) {

				// set coordinate for notes rows
				if( i+1 == 1 )
					CASE = CASE5;
				else if( i+1 == 2 )
					CASE = CASE6;
				else if( i+1 == 3 )
					CASE = CASE7;

				// set coordinate for sequencer steps
				if( j+1 == 1 )
					STEP = STEP1;
				else if( j+1 == 2 )
					STEP = STEP2;
				else if( j+1 == 3 )
					STEP = STEP3;
				else if( j+1 == 4 )
					STEP = STEP4;
				else if( j+1 == 5 )
					STEP = STEP5;
				else if( j+1 == 6 )
					STEP = STEP6;
				else if( j+1 == 7 )
					STEP = STEP7;
				else if( j+1 == 8 )
					STEP = STEP8;

				Paint_DrawFilledRectangle(&paint, STEP+filledrectangle_subtract, CASE+filledrectangle_subtract, STEP+20-filledrectangle_subtract, CASE+20-filledrectangle_subtract, COLORED);
			}
		}
	}

	return DISPLAY_OK;
}

Display_Status DISPLAY_SetSequencerStep(void) {

	uint8_t filledrectangle_subtract = 5;

	switch(Display.CurrentNoteRow) {
	case 1:	// Note 1 Row
		switch(Display.CurrentSequencestep) {
		case 1:	// Step 1..
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[0] = 1;
				Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 2:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[1] = 1;
				Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 3:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[2] = 1;
				Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 4:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[3] = 1;
				Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 5:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[4] = 1;
				Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 6:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[5] = 1;
				Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 7:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[6] = 1;
				Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		case 8:	// ..Step 8
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				timing_SN1[7] = 1;
				Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, COLORED);
			}
			break;
		default:
			break;
		}
		break;
		case 2:	// Note 2 Row
			switch(Display.CurrentSequencestep) {
			case 1:	// Step 1..
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[0] = 1;
					Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 2:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[1] = 1;
					Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 3:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[2] = 1;
					Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 4:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[3] = 1;
					Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 5:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[4] = 1;
					Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 6:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[5] = 1;
					Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 7:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[6] = 1;
					Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			case 8:	// ..Step 8
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
					timing_SN2[7] = 1;
					Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, COLORED);
				}
				break;
			default:
				break;
			}
			break;
			case 3:	// Note 3 Row
				switch(Display.CurrentSequencestep) {
				case 1:	// Step 1..
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[0] = 1;
						Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 2:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[1] = 1;
						Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 3:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[2] = 1;
						Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 4:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[3] = 1;
						Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 5:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[4] = 1;
						Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 6:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[5] = 1;
						Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 7:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[6] = 1;
						Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				case 8:	// ..Step 8
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
						timing_SN3[7] = 1;
						Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, COLORED);
					}
					break;
				default:
					break;
				}
				break;
				default:
					break;
	}

	//	DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_DeleteSequencerStep(void) {

	uint8_t filledrectangle_subtract = 5;
	//Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE1+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE1+20-filledrectangle_subtract, UNCOLORED);

	switch(Display.CurrentNoteRow) {
	case 1:	// Note 1 Row
		switch(Display.CurrentSequencestep) {
		case 1:	// Step 1..
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[0] = 0;
				Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 2:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[1] = 0;
				Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 3:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[2] = 0;
				Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 4:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[3] = 0;
				Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 5:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[4] = 0;
				Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 6:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[5] = 0;
				Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 7:
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[6] = 0;
				Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		case 8:	// ..Step 8
			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				timing_SN1[7] = 0;
				Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE5+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE5+20-filledrectangle_subtract, UNCOLORED);
			}
			break;
		default:
			break;
		}
		break;
		case 2:	// Note 2 Row
			switch(Display.CurrentSequencestep) {
			case 1:	// Step 1..
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[0] = 0;
					Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 2:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[1] = 0;
					Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 3:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[2] = 0;
					Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 4:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[3] = 0;
					Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 5:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[4] = 0;
					Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 6:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[5] = 0;
					Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 7:
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[6] = 0;
					Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			case 8:	// ..Step 8
				if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
					timing_SN2[7] = 0;
					Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE6+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE6+20-filledrectangle_subtract, UNCOLORED);
				}
				break;
			default:
				break;
			}
			break;
			case 3:	// Note 3 Row
				switch(Display.CurrentSequencestep) {
				case 1:	// Step 1..
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[0] = 0;
						Paint_DrawFilledRectangle(&paint, STEP1+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP1+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 2:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[1] = 0;
						Paint_DrawFilledRectangle(&paint, STEP2+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP2+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 3:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[2] = 0;
						Paint_DrawFilledRectangle(&paint, STEP3+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP3+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 4:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[3] = 0;
						Paint_DrawFilledRectangle(&paint, STEP4+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP4+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 5:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[4] = 0;
						Paint_DrawFilledRectangle(&paint, STEP5+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP5+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 6:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[5] = 0;
						Paint_DrawFilledRectangle(&paint, STEP6+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP6+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 7:
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[6] = 0;
						Paint_DrawFilledRectangle(&paint, STEP7+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP7+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				case 8:	// ..Step 8
					if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
						timing_SN3[7] = 0;
						Paint_DrawFilledRectangle(&paint, STEP8+filledrectangle_subtract, CASE7+filledrectangle_subtract, STEP8+20-filledrectangle_subtract, CASE7+20-filledrectangle_subtract, UNCOLORED);
					}
					break;
				default:
					break;
				}
				break;
				default:
					break;
	}

	//	DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_SetSequencerStepCursor(void) {

	uint8_t rectangle_subtract = 3;

	switch(Display.CurrentNoteRow) {
	case 1:	// Note 1 Row
		switch(Display.CurrentSequencestep) {
		case 1:	// Step 1..
			Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE5+rectangle_subtract, STEP1+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 2:
			Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE5+rectangle_subtract, STEP2+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 3:
			Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE5+rectangle_subtract, STEP3+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 4:
			Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE5+rectangle_subtract, STEP4+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 5:
			Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE5+rectangle_subtract, STEP5+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 6:
			Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE5+rectangle_subtract, STEP6+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 7:
			Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE5+rectangle_subtract, STEP7+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		case 8:	// ..Step 8
			Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE5+rectangle_subtract, STEP8+20-rectangle_subtract, CASE5+20-rectangle_subtract, COLORED);
			break;
		default:
			break;
		}
		break;
		case 2:	// Note 2 Row
			switch(Display.CurrentSequencestep) {
			case 1:	// Step 1..
				Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE6+rectangle_subtract, STEP1+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 2:
				Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE6+rectangle_subtract, STEP2+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 3:
				Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE6+rectangle_subtract, STEP3+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 4:
				Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE6+rectangle_subtract, STEP4+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 5:
				Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE6+rectangle_subtract, STEP5+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 6:
				Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE6+rectangle_subtract, STEP6+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 7:
				Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE6+rectangle_subtract, STEP7+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			case 8:	// ..Step 8
				Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE6+rectangle_subtract, STEP8+20-rectangle_subtract, CASE6+20-rectangle_subtract, COLORED);
				break;
			default:
				break;
			}
			break;
			case 3:	// Note 3 Row
				switch(Display.CurrentSequencestep) {
				case 1:	// Step 1..
					Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE7+rectangle_subtract, STEP1+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 2:
					Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE7+rectangle_subtract, STEP2+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 3:
					Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE7+rectangle_subtract, STEP3+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 4:
					Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE7+rectangle_subtract, STEP4+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 5:
					Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE7+rectangle_subtract, STEP5+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 6:
					Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE7+rectangle_subtract, STEP6+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 7:
					Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE7+rectangle_subtract, STEP7+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				case 8:	// ..Step 8
					Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE7+rectangle_subtract, STEP8+20-rectangle_subtract, CASE7+20-rectangle_subtract, COLORED);
					break;
				default:
					break;
				}
				break;
				default:
					break;
	}

	DISPLAY_Update();

	return DISPLAY_OK;
}

Display_Status DISPLAY_DeleteSequencerStepCursor(void) {

	uint8_t rectangle_subtract = 3;

	switch(Display.CurrentNoteRow) {
	case 1:	// Note 1 Row
		switch(Display.CurrentSequencestep) {
		case 1:	// Step 1..
			Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE5+rectangle_subtract, STEP1+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 2:
			Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE5+rectangle_subtract, STEP2+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 3:
			Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE5+rectangle_subtract, STEP3+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 4:
			Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE5+rectangle_subtract, STEP4+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 5:
			Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE5+rectangle_subtract, STEP5+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 6:
			Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE5+rectangle_subtract, STEP6+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 7:
			Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE5+rectangle_subtract, STEP7+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		case 8:	// ..Step 8
			Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE5+rectangle_subtract, STEP8+20-rectangle_subtract, CASE5+20-rectangle_subtract, UNCOLORED);
			break;
		default:
			break;
		}
		break;
		case 2:	// Note 2 Row
			switch(Display.CurrentSequencestep) {
			case 1:	// Step 1..
				Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE6+rectangle_subtract, STEP1+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 2:
				Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE6+rectangle_subtract, STEP2+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 3:
				Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE6+rectangle_subtract, STEP3+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 4:
				Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE6+rectangle_subtract, STEP4+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 5:
				Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE6+rectangle_subtract, STEP5+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 6:
				Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE6+rectangle_subtract, STEP6+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 7:
				Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE6+rectangle_subtract, STEP7+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			case 8:	// ..Step 8
				Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE6+rectangle_subtract, STEP8+20-rectangle_subtract, CASE6+20-rectangle_subtract, UNCOLORED);
				break;
			default:
				break;
			}
			break;
			case 3:	// Note 3 Row
				switch(Display.CurrentSequencestep) {
				case 1:	// Step 1..
					Paint_DrawRectangle(&paint, STEP1+rectangle_subtract, CASE7+rectangle_subtract, STEP1+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 2:
					Paint_DrawRectangle(&paint, STEP2+rectangle_subtract, CASE7+rectangle_subtract, STEP2+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 3:
					Paint_DrawRectangle(&paint, STEP3+rectangle_subtract, CASE7+rectangle_subtract, STEP3+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 4:
					Paint_DrawRectangle(&paint, STEP4+rectangle_subtract, CASE7+rectangle_subtract, STEP4+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 5:
					Paint_DrawRectangle(&paint, STEP5+rectangle_subtract, CASE7+rectangle_subtract, STEP5+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 6:
					Paint_DrawRectangle(&paint, STEP6+rectangle_subtract, CASE7+rectangle_subtract, STEP6+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 7:
					Paint_DrawRectangle(&paint, STEP7+rectangle_subtract, CASE7+rectangle_subtract, STEP7+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				case 8:	// ..Step 8
					Paint_DrawRectangle(&paint, STEP8+rectangle_subtract, CASE7+rectangle_subtract, STEP8+20-rectangle_subtract, CASE7+20-rectangle_subtract, UNCOLORED);
					break;
				default:
					break;
				}
				break;
				default:
					break;
	}

	DISPLAY_Update();

	return DISPLAY_OK;
}

/** @brief this function edits the ON/OFF settings of the Voices
 *
 */
void p_Voices_overview(void) {

	//Header line
	char headerstring[] = "VOICES";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "next Effect";
	char str_2[] = "Voice 1 ON/OFF";
	char str_3[] = "Voice 2 ON/OFF";
	char str_4[] = "Voice 3 ON/OFF";
	char str_5[] = "Voices Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);

	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentVoice = 0;
		break;
	case 2:
		// Voice 1 ON/OFF
		Display.currentVoice = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);

		if(potVal < 50) {	// smaller than 50 %
			Display.Voices_ONOFF[Display.currentVoice-1] = false;
			strcpy(Display.value_str_voices_overview[1], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Voices_ONOFF[Display.currentVoice-1] = true;
			strcpy(Display.value_str_voices_overview[1], "ON");
		}
		break;

	case 3:
		// Voice 2 ON/OFF
		Display.currentVoice = 2;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH , UNCOLORED);

		if(potVal < 50) {	// smaller than 50 %
			Display.Voices_ONOFF[Display.currentVoice-1] = false;
			strcpy(Display.value_str_voices_overview[2], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Voices_ONOFF[Display.currentVoice-1] = true;
			strcpy(Display.value_str_voices_overview[2], "ON");
		}
		break;

	case 4:
		// Voice 3 ON/OFF
		Display.currentVoice = 3;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH , UNCOLORED);

		if(potVal < 50) {	// smaller than 50 %
			Display.Voices_ONOFF[Display.currentVoice-1] = false;
			strcpy(Display.value_str_voices_overview[3], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Voices_ONOFF[Display.currentVoice-1] = true;
			strcpy(Display.value_str_voices_overview[3], "ON");
		}
		break;

	case 5:
		// TODO: RESET OF ALL VOICES..
		// Voices Reset ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH , UNCOLORED);

		if(potVal < 50) {	// smaller than 50 %
			strcpy(Display.value_str_voices_overview[4], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			strcpy(Display.value_str_voices_overview[4], "ON");
		}
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

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_voices_overview[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_voices_overview[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_voices_overview[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_voices_overview[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_voices_overview[4], &Font12, COLORED);
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
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Note";
	char str_2[] = "Octave";
	char str_3[] = "Note Source";
	char str_4[] = "Octave Source";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);

	uint8_t mode_number = 0;

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Note
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			Display.noteindex = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * (sizeof(keys)/sizeof(keys[0]));
			Display.Voices_Note[Display.currentVoice-1] = (uint8_t)(keys[(uint8_t)Display.noteindex]);
			sprintf(Display.value_str_voices_settings[Display.currentVoice-1][0], "%c", Display.Voices_Note[Display.currentVoice-1]);
			break;
		case 2:
			// Octave
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Voices_Octave[Display.currentVoice-1] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 6);	// 0ctave 0 to 6
			//sprintf(Display.value_str_voices_settings[1], "%c", Display.Voices_Octave[Display.currentVoice-1]+'0');
			sprintf(Display.value_str_voices_settings[Display.currentVoice-1][1], "%d", Display.Voices_Octave[Display.currentVoice-1]);
			break;
		case 3:
			// Note Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.Voice_Note_Sources[Display.currentVoice-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_voices_settings[Display.currentVoice-1][2], Display.source_names[mode_number]);
			break;
		case 4:
			// Octave Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.Voice_Octave_Sources[Display.currentVoice-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_voices_settings[Display.currentVoice-1][3], Display.source_names[mode_number]);
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_voices_settings[Display.currentVoice-1][0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_voices_settings[Display.currentVoice-1][1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE3, Display.value_str_voices_settings[Display.currentVoice-1][2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE4, Display.value_str_voices_settings[Display.currentVoice-1][3], &Font12, COLORED);
}

/** @brief this function edits the settings of the ADSR, just the sources have can be edited on another page or you can switch to the next effect
 *
 */
void p_ADSR_overview(struct adsr* envelope) {

	//Header line
	char headerstring[] = "ADSR";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "next Effect";
	char str_2[] = "ADSR ON/OFF";
	char str_3[] = "Attack Time";
	char str_4[] = "Decay Time";
	char str_5[] = "Sustain Time";
	char str_6[] = "Sustain Level";
	char str_7[] = "Release Time";
	char str_8[] = "ADSR Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, str_7, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE8, str_8, &Font12, COLORED);

	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %
	char write_str[10];

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Next Effect
			Display.currentADSR = 0;
			break;
		case 2:
			// ADSR ON/OFF
			Display.currentADSR = 1;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				Display.ADSR_ONOFF = false;
				strcpy(Display.value_str_adsr_overview[1], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.ADSR_ONOFF = true;
				strcpy(Display.value_str_adsr_overview[1], "ON");
			}
			break;

		case 3:
			// Attack Time
			Display.currentADSR = 2;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Attacktime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_attack) + 0.05;	// 0.05 to prevent 0 -> fuckup
			envelope->adsr_attack_time = Display.ADSR_Attacktime * LUT_SR;
			sprintf(write_str, "%f", Display.ADSR_Attacktime);
			memcpy(Display.value_str_adsr_overview[2], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 4:
			// Decay Time
			Display.currentADSR = 3;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Decaytime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_decay);
			envelope->adsr_decay_time = Display.ADSR_Decaytime * LUT_SR;
			sprintf(write_str, "%f", Display.ADSR_Decaytime);
			memcpy(Display.value_str_adsr_overview[3], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 5:
			// Sustain Time
			Display.currentADSR = 4;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Sustaintime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_sustaintime);
			envelope->adsr_sustain_time = Display.ADSR_Sustaintime * LUT_SR;
			sprintf(write_str, "%f", Display.ADSR_Sustaintime);
			memcpy(Display.value_str_adsr_overview[4], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 6:
			// Sustain Level
			Display.currentADSR = 5;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Sustainlevel = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_max_amp);
			envelope->adsr_sustain_amplitude = Display.ADSR_Sustainlevel;
			sprintf(write_str, "%f", Display.ADSR_Sustainlevel);
			memcpy(Display.value_str_adsr_overview[5], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 7:
			// Release Time
			Display.currentADSR = 6;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Releasetime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_release);
			envelope->adsr_release_time = Display.ADSR_Releasetime * LUT_SR;
			sprintf(write_str, "%f", Display.ADSR_Releasetime);
			memcpy(Display.value_str_adsr_overview[6], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 8:
			// TODO: RESET OF ADSR..
			// ADSR Reset ON/OFF
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE8, Display.value_end_x_position, CASE8+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				strcpy(Display.value_str_adsr_overview[4], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				strcpy(Display.value_str_adsr_overview[4], "ON");
			}
			break;
		case 9:
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_adsr_overview[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_adsr_overview[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_adsr_overview[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_adsr_overview[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_adsr_overview[4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, Display.value_str_adsr_overview[5], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE7, Display.value_str_adsr_overview[6], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE8, Display.value_str_adsr_overview[7], &Font12, COLORED);
}

/** @brief this function edits the sources of the ADSR parameters
 *
 */
void p_ADSR_Settings(void) {

	//Header line
	char headerstring[] = "ADSR";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "A. Time Source";
	char str_2[] = "D. Time Source";
	char str_3[] = "S. Time Source";
	char str_4[] = "S. Level Source";
	char str_5[] = "R. Time Source";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);

	uint8_t mode_number = 0;

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Attack Time Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE1, Display.value_end_x_position, CASE1+10, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.ADSR_Sources[0] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_adsr_settings[0], Display.source_names[mode_number]);
			break;
		case 2:
			// Decay Time Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE2, Display.value_end_x_position, CASE2+10, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.ADSR_Sources[1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_adsr_settings[1], Display.source_names[mode_number]);
			break;
		case 3:
			// Sustain Time Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+10, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.ADSR_Sources[2] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_adsr_settings[2], Display.source_names[mode_number]);
			break;
		case 4:
			// Sustain Level Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE4, Display.value_end_x_position, CASE4+10, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.ADSR_Sources[3] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_adsr_settings[3], Display.source_names[mode_number]);
			break;
		case 5:
			// Release Time Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE5, Display.value_end_x_position, CASE5+10, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.ADSR_Sources[4] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_adsr_settings[4], Display.source_names[mode_number]);
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE1, Display.value_str_adsr_settings[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE2, Display.value_str_adsr_settings[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE3, Display.value_str_adsr_settings[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE4, Display.value_str_adsr_settings[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE5, Display.value_str_adsr_settings[4], &Font12, COLORED);
}

/** @brief this function edits the ON/OFF settings of the Equalizer, the parameters and sources have to be edited on another page or you can switch to the next effect
 *
 */
void p_Equalizer_overview(void) {

	//Header line
	char headerstring[] = "EQUALIZER";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);

	//row cases
	char str_1[] = "next Effect";
	char str_2[] = "Band 1";
	char str_3[] = "Band 2";
	char str_4[] = "Band 3";
	char str_5[] = "Band 4";
	char str_6[] = "Band 5";
	char str_7[] = "EQ Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, str_7, &Font12, COLORED);

	//Potentiometer Input in %
	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentBand = 0;
		break;
	case 2:
		// Band 1 ON/OFF
		Display.currentBand = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);
		if(potVal < 50) {	// smaller than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = false;
			strcpy(Display.value_str_equalizer_overview[1], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = true;
			strcpy(Display.value_str_equalizer_overview[1], "ON");
		}
		break;

	case 3:
		// Band 2 ON/OFF
		Display.currentBand = 2;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH , UNCOLORED);
		if(potVal < 50) {	// smaller than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = false;
			strcpy(Display.value_str_equalizer_overview[2], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = true;
			strcpy(Display.value_str_equalizer_overview[2], "ON");
		}
		break;
	case 4:
		// Band 3 ON/OFF
		Display.currentBand = 3;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH , UNCOLORED);
		if(potVal < 50) {	// smaller than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = false;
			strcpy(Display.value_str_equalizer_overview[3], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = true;
			strcpy(Display.value_str_equalizer_overview[3], "ON");
		}
		break;
	case 5:
		// Band 4 ON/OFF
		Display.currentBand = 4;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH , UNCOLORED);
		if(potVal < 50) {	// smaller than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = false;
			strcpy(Display.value_str_equalizer_overview[4], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = true;
			strcpy(Display.value_str_equalizer_overview[4], "ON");
		}
		break;
	case 6:
		// Band 5 ON/OFF
		Display.currentBand = 5;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH , UNCOLORED);
		if(potVal < 50) {	// smaller than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = false;
			strcpy(Display.value_str_equalizer_overview[5], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.Filter_ONOFF[Display.currentBand-1] = true;
			strcpy(Display.value_str_equalizer_overview[5], "ON");
		}
		break;
	case 7:
		// TODO: Equalizer Reset..
		// EQUALIZER Reset ON/OFF
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH , UNCOLORED);

		if(potVal < 50) {	// smaller than 50 %
			strcpy(Display.value_str_equalizer_overview[6], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			strcpy(Display.value_str_equalizer_overview[6], "ON");
		}
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_equalizer_overview[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_equalizer_overview[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_equalizer_overview[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_equalizer_overview[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_equalizer_overview[4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, Display.value_str_equalizer_overview[5], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE7, Display.value_str_equalizer_overview[6], &Font12, COLORED);
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
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Q-Factor";
	char str_2[] = "Cutoff";
	char str_3[] = "Gain";
	char str_4[] = "Q-Factor Source";
	char str_5[] = "Cutoff Source";
	char str_6[] = "Gain Source";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);

	//-------------------------------------------------------------------------------------
	// this variables have to be implemented and adjusted for each frequency band in filter-structs
	float filter_maximum_Q = 10.0;
	float filter_maximum_cutoff = LUT_FMAX;
	float filter_maximum_gain = 1.0;
	//-------------------------------------------------------------------------------------

	char write_str[10];
	uint8_t mode_number = 0;

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Q-Factor
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Filter_Q[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * filter_maximum_Q);
			sprintf(write_str, "%f", Display.Filter_Q[Display.currentBand-1]);
			memcpy(Display.value_str_equalizer_settings[Display.currentBand-1][0], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 2:
			// Cutoff
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Filter_Cutoff[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * filter_maximum_cutoff);
			sprintf(write_str, "%f", Display.Filter_Cutoff[Display.currentBand-1]);
			memcpy(Display.value_str_equalizer_settings[Display.currentBand-1][1], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 3:
			// Gain
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Filter_Gain[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * filter_maximum_gain);
			sprintf(write_str, "%f", Display.Filter_Gain[Display.currentBand-1]);
			memcpy(Display.value_str_equalizer_settings[Display.currentBand-1][2], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 4:
			// Q-Factor Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.EQ_Q_factor_Sources[Display.currentBand-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_equalizer_settings[Display.currentBand-1][3], Display.source_names[mode_number]);
			break;
		case 5:
			// Cutoff Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.EQ_Cutoff_Sources[Display.currentBand-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_equalizer_settings[Display.currentBand-1][4], Display.source_names[mode_number]);
			break;
		case 6:
			// Gain Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.EQ_Gain_Sources[Display.currentBand-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_equalizer_settings[Display.currentBand-1][5], Display.source_names[mode_number]);
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_equalizer_settings[Display.currentBand-1][0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_equalizer_settings[Display.currentBand-1][1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_equalizer_settings[Display.currentBand-1][2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE4, Display.value_str_equalizer_settings[Display.currentBand-1][3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE5, Display.value_str_equalizer_settings[Display.currentBand-1][4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE6, Display.value_str_equalizer_settings[Display.currentBand-1][5], &Font12, COLORED);
}

void p_WahWah_overview(struct WahWah_t *WahWah) {

	// Header line
	char headerstring[] = "WAHWAH";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	// row cases
	char str_1[] = "next effect";
	char str_2[] = "WahWah ON/OFF";
	char str_3[] = "Mode";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);

	// Potentiometer Input in %
	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;

	switch (Display.JoystickParameterPosition){

	case 1:
		// Next Effect
		Display.currentWahWah = 0;
		break;
	case 2:	// WahWah ON/OFF
		Display.currentWahWah = 1;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);
		if(potVal < 50) {	// smaller than 50 %
			Display.WahWah_ONOFF = false;
			strcpy(Display.value_str_wahwah[0], "OFF");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.WahWah_ONOFF = true;
			strcpy(Display.value_str_wahwah[0], "ON");
		}
		break;
	case 3:	// WahWah Mode
		Display.currentWahWah = 2;
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH , UNCOLORED);
		if(potVal < 50) {	// smaller than 50 %
			Display.WahWah_Mode = 0;
			strcpy(Display.value_str_wahwah[1], "WahWah");
		}
		else if(potVal >= 50) {	// greater than 50 %
			Display.WahWah_Mode = 1;
			strcpy(Display.value_str_wahwah[1], "AutoWahWah");
		}
		break;
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_wahwah[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_wahwah[1], &Font12, COLORED);
}

void p_WahWah_Settings(struct WahWah_t *WahWah) {

	uint8_t mode_number = 0;

	if(Display.WahWah_Mode == 0) {	// Normal WahWah
		char str_1[] = "Mid Freq.";
		char str_2[] = "Q-factor";
		char str_4[] = "Mid Freq. Source";
		char str_5[] = "Q Source";

		switch(Display.JoystickParameterPosition) {
		case 1:	// WahWah Mid Frequency
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			Display.WahWah_MidFreq = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * WahWah->max_mid_freq;
			//			WahWah->mid_freq = ((float)Display.ADC2inputs[2] / Display.ADC_FullRange) * WahWah->max_mid_freq;
			sprintf(Display.value_str_wahwah[2], "%.2f", Display.WahWah_MidFreq);
			break;
		case 2:	// WahWah Q-factor
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Display.WahWah_Q = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * WahWah->max_Q) + 0.5;
			//			WahWah->bandpass->Q = (((float)Display.ADC2inputs[3] / Display.ADC_FullRange) * 10) + 0.5;W	// DISPLAY!!!
			sprintf(Display.value_str_wahwah[3], "%.2f", Display.WahWah_Q);
			break;
		case 3:	// WahWah Mid Frequency Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.WahWah_Sources[0] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_wahwah[4], Display.source_names[mode_number]);
			break;
		case 4:	// Q-factor Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.WahWah_Sources[1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_wahwah[5], Display.source_names[mode_number]);
			break;
		}
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, Display.value_str_wahwah[2], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, Display.value_str_wahwah[3], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, Display.value_str_wahwah[4], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, Display.value_str_wahwah[5], &Font12, COLORED);
	}
	else if(Display.WahWah_Mode == 1) {	// Auto-WahWah
		char str_1[] = "Mid Freq.";
		char str_2[] = "Q-factor";
		char str_3[] = "Range";
		char str_4[] = "LFO Freq.";
		char str_5[] = "Mid Freq. Source";
		char str_6[] = "Q Source";
		char str_7[] = "Range Source";
		char str_8[] = "LFO Freq. Source";

		//	WahWah->mid_freq = (float)Display.ADC2inputs[2] / 4;	// DISPLAY!!!
		//	WahWah->max_range = (WahWah->mid_freq - 50) * 2;	// max range calculated in DISPLAY depending on the current mid_freq value
		//	WahWah->range = WahWah->max_range/4;	// DISPLAY!!!

		switch(Display.JoystickParameterPosition) {
		case 1:	// Auto-WahWah Mid Frequency
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			Display.WahWah_MidFreq = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * WahWah->max_mid_freq;
			WahWah->max_range = (Display.WahWah_MidFreq - 50) * 2;	// max range calculated depending on the current mid freq value
			//			WahWah->mid_freq = ((float)Display.ADC2inputs[2] / Display.ADC_FullRange) * WahWah->max_mid_freq;
			sprintf(Display.value_str_wahwah[2], "%.2f", Display.WahWah_MidFreq);
			break;
		case 2:	// Auto-WahWah Q-factor
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Display.WahWah_Q = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * WahWah->max_Q) + 0.5;
			WahWah->bandpass->Q = Display.WahWah_Q;
			sprintf(Display.value_str_wahwah[3], "%.2f", Display.WahWah_Q);
			break;
		case 3:	// Auto-WahWah Range
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.WahWah_Range = ((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * WahWah->max_range;
			WahWah->range = Display.WahWah_Range;
			sprintf(Display.value_str_wahwah[4], "%.2f", Display.WahWah_Range);
			break;
		case 4:	// Auto-WahWah LFO Frequency
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			uint index = ((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * (sizeof(LFO_FREQUENCYS)/sizeof(LFO_FREQUENCYS[0])-1);
			Display.WahWah_LFOfreq = LFO_FREQUENCYS[index];
			sprintf(Display.value_str_wahwah[5], "%.3f", Display.WahWah_LFOfreq);
			break;
		case 5:	// Auto-WahWah Mid Frequency Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.WahWah_Sources[0] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_wahwah[6], Display.source_names[mode_number]);
			break;
		case 6:	// Auto-WahWah Q Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.WahWah_Sources[1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_wahwah[7], Display.source_names[mode_number]);
			break;
		case 7:	// Auto-WahWah Range Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.WahWah_Sources[2] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_wahwah[8], Display.source_names[mode_number]);
			break;
		case 8:	// Auto-WahWah LFO Frequency Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE8, Display.value_end_x_position, CASE8+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.WahWah_Sources[3] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_wahwah[9], Display.source_names[mode_number]);
			break;
		default:
			break;
		}
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, Display.value_str_wahwah[2], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, Display.value_str_wahwah[3], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, Display.value_str_wahwah[4], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, Display.value_str_wahwah[5], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, Display.value_str_wahwah[6], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, Display.value_str_wahwah[7], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, Display.value_str_wahwah[8], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE8, Display.value_str_wahwah[9], &Font12, COLORED);
	}
}

///** @brief this function prints the WahWah submenu and edits its values
// *  @param
// *
// */
//void p_WahWah(struct WahWah_t *WahWah) {
//
//	// normal wahwah:
//	// WahWah->mid_freq = ((float)Display.ADC2inputs[2] / Display.ADC_FullRange) * WahWah->max_mid_freq;	// DISPLAY!!!
//	// WahWah->bandpass->Q = (((float)Display.ADC2inputs[3] / Display.ADC_FullRange) * 10) + 0.5;	// DISPLAY!!!
//
//	// autowahwah:
//	// WahWah->mid_freq = (float)Display.ADC2inputs[2] / 4;	// DISPLAY!!!
//	// WahWah->max_range = (WahWah->mid_freq - 50) * 2;	// max range calculated in display depending on the current mid_freq value
//	// WahWah->range = WahWah->max_range/4;	// set in display!
//
//	// Header line
//	char headerstring[] = "WAHWAH";
//	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
//	// row cases
//	char str_1[] = "WahWah ON/OFF";
//	char str_2[] = "Mode";
//	char str_3[] = "Mid Freq.";
//	char str_4[] = "Q-factor";
//	if(Display.WahWahMode == 1) {	// AutoWahWah
//		char str_5[] = "Range";
//		char str_6[] = "LFO Freq.";
//	}
//	char str_7[] = "LFO Freq. Source";
//	char str_8[] = "Range Source";
//	char str_9[] = "Mid Freq. Source";
//	char str_10[] = "Q Source";
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, str_7, &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE8, str_8, &Font12, COLORED);
//
//	// Potentiometer Input in %
//	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;
//	uint8_t mode_number = 0;
//
//	if(Display.poti_moved == true) {
//
//		switch (Display.JoystickParameterPosition){
//		case 1:	// WahWah ON/OFF
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH , UNCOLORED);
//			if(potVal < 50) {	// smaller than 50 %
//				Display.WahWah_ONOFF = false;
//				strcpy(Display.value_str_wahwah[0], "OFF");
//			}
//			else if(potVal >= 50) {	// greater than 50 %
//				Display.WahWah_ONOFF = true;
//				strcpy(Display.value_str_wahwah[0], "ON");
//			}
//			break;
//		case 2:	// WahWah LFO Frequency
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
//			uint index = ((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * (sizeof(LFO_FREQUENCYS)/sizeof(LFO_FREQUENCYS[0])-1);
//			Display.WahWah_LFOFreq = LFO_FREQUENCYS[index];
//			sprintf(Display.value_str_wahwah[1], "%.3f", Display.WahWah_LFOFreq);
//			break;
//		case 3:	// WahWah Frequency Range
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
//			Display.WahWah_Range = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * WahWah->max_range;
//			sprintf(Display.value_str_wahwah[2], "%.2f", Display.WahWah_Range);
//			break;
//		case 4:	// WahWah Mid Frequency
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
//			Display.WahWah_MidFreq = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * WahWah->max_mid_freq;
//			sprintf(Display.value_str_wahwah[3], "%.2f", Display.WahWah_MidFreq);
//			break;
//		case 5:	// WahWah LFO Frequency Source
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
//			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
//			Display.WahWah_Sources[0] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
//			strcpy(Display.value_str_wahwah[4], Display.source_names[mode_number]);
//			break;
//		case 6:	// WahWah Frequency Range Source
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
//			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
//			Display.WahWah_Sources[1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
//			strcpy(Display.value_str_wahwah[5], Display.source_names[mode_number]);
//			break;
//		case 7:	// WahWah Mid Frequency Source
//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH, UNCOLORED);
//			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
//			Display.WahWah_Sources[2] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
//			strcpy(Display.value_str_wahwah[6], Display.source_names[mode_number]);
//			break;
//		case 8:
//			// TODO: RESET OF WAHWAH..
//			break;
//		default:
//			break;
//		}
//	}
//
//	// print value row
//	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_wahwah[0], &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE2, Display.value_str_wahwah[1], &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE3, Display.value_str_wahwah[2], &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE4, Display.value_str_wahwah[3], &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE5, Display.value_str_wahwah[4], &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE6, Display.value_str_wahwah[5], &Font12, COLORED);
//	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE7, Display.value_str_wahwah[6], &Font12, COLORED);
//}

/** @brief this function prints the Distortion submenu and edits its values
 *  @param HardClipping: struct of hard clipping distortion effect
 *
 */
void p_Distortion(struct effects_distortion* HardClipping) {

	// Header line
	char headerstring[] = "DISTORTION";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	// row cases
	char str_1[] = "Distortion ON/OFF";
	char str_2[] = "Gain";
	char str_3[] = "Source";
	char str_4[] = "Distortion Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);

	// Potentiometer Input in %
	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;
	uint8_t mode_number = 0;

	if(Display.poti_moved == true) {

		switch (Display.JoystickParameterPosition){
		case 1:	// Distortion ON/OFF
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.Distortion_ONOFF = false;
				strcpy(Display.value_str_distortion[0], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Distortion_ONOFF = true;
				strcpy(Display.value_str_distortion[0], "ON");
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
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Distortion_Gain = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * HardClipping->distortion_maximum_gain) + 1;
			sprintf(Display.value_str_distortion[1], "%u", Display.Distortion_Gain);
			break;
		case 3:	// Distortion Gain Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			//			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LR+1)));
			//			Display.Distortion_Sources = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (POTI-GYRO_LR+1)));
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.Distortion_Sources = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_distortion[2], Display.source_names[mode_number]);
			break;
		case 4:
			// TODO: RESET OF DISTORTION..
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_distortion[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_distortion[1], &Font12, COLORED);
	//Paint_DrawCharAt(&paint, Display.value_start_x_position, CASE2, Display.Distortion_Gain+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE3, Display.value_str_distortion[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_distortion[3], &Font12, COLORED);
}

/** @brief this function prints the Tremolo submenu and edits its values
 * @param Tremolo struct
 */
void p_Tremolo(struct Tremolo_t* Tremolo) {

	//Header line
	char headerstring[] = "TREMOLO";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Tremolo ON/OFF";
	char str_2[] = "Tremolo  Rate";
	char str_3[] = "Tremolo Depth";
	char str_4[] = "Rate Source";
	char str_5[] = "Depth Source";
	char str_6[] = "Tremolo Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);

	// Potentiometer Input in %
	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;
	uint8_t mode_number = 0;
	char write_str[10];

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Tremolo ON/OFF
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.Tremolo_ONOFF = false;
				strcpy(Display.value_str_tremolo[0], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Tremolo_ONOFF = true;
				strcpy(Display.value_str_tremolo[0], "ON");
			}
			break;
		case 2:
			// Tremolo Rate
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			uint index = ((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * (sizeof(LFO_FREQUENCYS)/sizeof(LFO_FREQUENCYS[0])-1);
			Display.Tremolo_Rate = LFO_FREQUENCYS[index];
			sprintf(Display.value_str_tremolo[1], "%.3f", Display.Tremolo_Rate);
			//			Paint_DrawCharAt(&paint, Display.value_start_x_position, CASE2, Display.Tremolo_Rate+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
			break;
		case 3:
			// Tremolo Depth
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Tremolo_Depth = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * Tremolo->tremolo_maximum_depth);
			sprintf(write_str, "%f", Display.Tremolo_Depth);
			memcpy(Display.value_str_tremolo[2], write_str, 3);	// float can only be displayed with two digits after the dot
			break;
		case 4:
			// Tremolo Rate Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.Tremolo_Sources[0] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_tremolo[3], Display.source_names[mode_number]);
			break;
		case 5:
			// Tremolo Depth Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
			mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			Display.Tremolo_Sources[1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
			strcpy(Display.value_str_tremolo[4], Display.source_names[mode_number]);
			break;
		case 6:
			// TODO: RESET OF TREMOLO..
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_tremolo[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE2, Display.value_str_tremolo[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_tremolo[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE4, Display.value_str_tremolo[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE5, Display.value_str_tremolo[4], &Font12, COLORED);
}

void p_Volume(void) {

	//Header line
	char headerstring[] = "VOLUME";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Voices Vol.";
	char str_2[] = "Drumcomputer Vol.";
	char str_3[] = "Sequencer Vol.";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Volume Voices
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			volume[0] = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange;
			sprintf(Display.value_str_volume[0], "%.2f", volume[0]);
			break;
		case 2:
			// Volume Drumcomputer
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			volume[1] = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange;
			sprintf(Display.value_str_volume[1], "%.2f", volume[1]);
			break;
		case 3:
			// Volume Sequencer
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			volume[2] = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange;
			sprintf(Display.value_str_volume[2], "%.2f", volume[2]);
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE1, Display.value_str_volume[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE2, Display.value_str_volume[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE3, Display.value_str_volume[2], &Font12, COLORED);
}

void p_Presets(void) {

	//Header line
	char headerstring[] = "PRESETS";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Drums Preset";
	char str_2[] = "Seq. Preset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);

	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;


	NewSignal(&signals1,SIN, 'C',1,6);
	NewSignal(&signals1,SIN, 'E',1,7);
	NewSignal(&signals1,SIN, 'G',1,8);
	NewSignal(&signals1,SIN, 'C',2,9);
	NewSignal(&signals1,SIN, 'E',2,10);
	NewSignal(&signals1,SIN, 'G',2,11);
	NewSignal(&signals1,SIN, 'C',3,12);
	NewSignal(&signals1,SIN, 'E',3,13);
	NewSignal(&signals1,SIN, 'G',3,14);
	NewSignal(&signals1,SIN, 'C',4,15);
	NewSignal(&signals1,SIN, 'E',4,16);
	NewSignal(&signals1,SIN, 'G',4,17);
	NewSignal(&signals1,SIN, 'C',5,18);
	NewSignal(&signals1,SIN, 'E',5,19);
	NewSignal(&signals1,SIN, 'G',5,20);


	Display.Tremolo_ONOFF = true;
	Display.Tremolo_Sources[1] = GYRO_LR;


	Display.Filter_ONOFF[0] = true;
	Display.EQ_Cutoff_Sources[0] = GYRO_FB;
	Display.currentBand = 0;

	Display.Voices_Note[0] = 'C';
	Display.Voices_ONOFF[0] = true;
	Display.Voices_Octave[0] = 3;
	Display.Voice_Note_Sources[0] = EKG;

	switch(Display.JoystickParameterPosition) {
	case 1:	// Drums Preset
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
		if(potVal < 50) {
			sprintf(Display.value_str_presets[0], "%d", 1);
			timing_DS1[0] = 1;	// Techno Beat
			timing_DS1[1] = 0;
			timing_DS1[2] = 0;
			timing_DS1[3] = 0;
			timing_DS1[4] = 1;
			timing_DS1[5] = 0;
			timing_DS1[6] = 0;
			timing_DS1[7] = 0;
			timing_DS2[0] = 0;
			timing_DS2[1] = 0;
			timing_DS2[2] = 1;
			timing_DS2[3] = 0;
			timing_DS2[4] = 0;
			timing_DS2[5] = 0;
			timing_DS2[6] = 1;
			timing_DS2[7] = 0;
			timing_DS3[0] = 0;
			timing_DS3[1] = 0;
			timing_DS3[2] = 0;
			timing_DS3[3] = 0;
			timing_DS3[4] = 1;
			timing_DS3[5] = 0;
			timing_DS3[6] = 0;
			timing_DS3[7] = 0;
			timing_DS4[0] = 0;
			timing_DS4[1] = 0;
			timing_DS4[2] = 0;
			timing_DS4[3] = 0;
			timing_DS4[4] = 0;
			timing_DS4[5] = 0;
			timing_DS4[6] = 0;
			timing_DS4[7] = 0;
			//			timing_DS4[0] = 0;
			//			timing_DS4[1] = 0;
			//			timing_DS4[2] = 1;
			//			timing_DS4[3] = 1;
			//			timing_DS4[4] = 0;
			//			timing_DS4[5] = 0;
			//			timing_DS4[6] = 0;
			//			timing_DS4[7] = 1;
		}
		else if(potVal >= 50) {
			sprintf(Display.value_str_presets[0], "%d", 2);
			timing_DS1[0] = 1;	// Advanced Techno Beat
			timing_DS1[1] = 0;
			timing_DS1[2] = 1;
			timing_DS1[3] = 0;
			timing_DS1[4] = 1;
			timing_DS1[5] = 0;
			timing_DS1[6] = 0;
			timing_DS1[7] = 0;
			timing_DS2[0] = 0;
			timing_DS2[1] = 0;
			timing_DS2[2] = 1;
			timing_DS2[3] = 0;
			timing_DS2[4] = 0;
			timing_DS2[5] = 0;
			timing_DS2[6] = 1;
			timing_DS2[7] = 0;
			timing_DS3[0] = 0;
			timing_DS3[1] = 0;
			timing_DS3[2] = 0;
			timing_DS3[3] = 0;
			timing_DS3[4] = 1;
			timing_DS3[5] = 0;
			timing_DS3[6] = 0;
			timing_DS3[7] = 1;
			timing_DS4[0] = 0;
			timing_DS4[1] = 0;
			timing_DS4[2] = 1;
			timing_DS4[3] = 1;
			timing_DS4[4] = 0;
			timing_DS4[5] = 0;
			timing_DS4[6] = 0;
			timing_DS4[7] = 1;
		}
		break;
	case 2:	// Sequencer Preset
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
		if(potVal < 50) {
			sprintf(Display.value_str_presets[1], "%d", 1);
			freq_index_SN1 = Get_Note_Index('C', 1);	// load notes
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
			}
			freq_index_SN2 = Get_Note_Index('D', 1);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
			}
			freq_index_SN3 = Get_Note_Index('d', 1);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
			}
			timing_SN1[0] = 1;	// Sequence Pattern
			timing_SN1[1] = 0;
			timing_SN1[2] = 0;
			timing_SN1[3] = 0;
			timing_SN1[4] = 0;
			timing_SN1[5] = 0;
			timing_SN1[6] = 0;
			timing_SN1[7] = 0;
			timing_SN2[0] = 0;
			timing_SN2[1] = 0;
			timing_SN2[2] = 0;
			timing_SN2[3] = 1;
			timing_SN2[4] = 0;
			timing_SN2[5] = 0;
			timing_SN2[6] = 0;
			timing_SN2[7] = 0;
			timing_SN3[0] = 0;
			timing_SN3[1] = 0;
			timing_SN3[2] = 0;
			timing_SN3[3] = 0;
			timing_SN3[4] = 0;
			timing_SN3[5] = 0;
			timing_SN3[6] = 1;
			timing_SN3[7] = 0;
		}
		else if(potVal >= 50) {
			sprintf(Display.value_str_presets[1], "%d", 2);
		}
		break;
	default:
		break;
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_presets[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_presets[1], &Font12, COLORED);
}

/** @brief this function prints the Keyboardmode and edits its values
 * @param envelope struct
 */
void p_KeyboardSetParameters(struct adsr* envelope) {

	//Header line
	char headerstring[] = "KEYBOARDMODE";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Octave";
	char str_2[] = "Attack Time";
	char str_3[] = "Decay Time";
	char str_4[] = "Sustain Time";
	char str_5[] = "Sustain Level";
	char str_6[] = "Release Time";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);

	char write_str[10];

	switch(Display.JoystickParameterPosition) {
	case 1:	// Octave
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
		Display.Keyboard_Octave = (char)(((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * 6);	// Octave 0 to 6
		sprintf(Display.value_str_keyboardmode[0], "%d", Display.Keyboard_Octave);
		break;
	case 2:	// Attack Time
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
		Display.Keyboard_AttackTime = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * envelope->adsr_maximum_attack) + 0.05;	// +0.05 to make sure that attack time is not 0
		envelope->adsr_attack_time = Display.Keyboard_AttackTime * LUT_SR;
		sprintf(write_str, "%f", Display.Keyboard_AttackTime);
		memcpy(Display.value_str_keyboardmode[1], write_str, 3);	// float can only be displayed with two digits after the dot
		break;
	case 3:	// Decay Time
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
		Display.Keyboard_DecayTime = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * envelope->adsr_maximum_decay);
		envelope->adsr_decay_time = Display.Keyboard_DecayTime * LUT_SR;
		sprintf(write_str, "%f", Display.Keyboard_DecayTime);
		memcpy(Display.value_str_keyboardmode[2], write_str, 3);	// float can only be displayed with two digits after the dot
		break;
	case 4:	// Sustain Time
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
		Display.Keyboard_SustainTime = (((float)Display.ADC2inputs[2]/4096) * envelope->adsr_maximum_sustaintime);
		envelope->adsr_sustain_time = Display.Keyboard_SustainTime * LUT_SR;
		sprintf(write_str, "%f", Display.Keyboard_SustainTime);
		memcpy(Display.value_str_keyboardmode[3], write_str, 3);	// float can only be displayed with two digits after the dot
		break;
	case 5:	// Sustain Level
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
		Display.Keyboard_SustainLevel = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * envelope->adsr_max_amp);
		envelope->adsr_sustain_amplitude = Display.Keyboard_SustainLevel;
		sprintf(write_str, "%f", Display.Keyboard_SustainLevel);
		memcpy(Display.value_str_keyboardmode[4], write_str, 3);	// float can only be displayed with two digits after the dot
		break;
	case 6:	// Release Time
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
		Display.Keyboard_ReleaseTime = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * envelope->adsr_maximum_release);
		envelope->adsr_release_time = Display.Keyboard_ReleaseTime * LUT_SR;
		sprintf(write_str, "%f", Display.Keyboard_ReleaseTime);
		memcpy(Display.value_str_keyboardmode[5], write_str, 3);	// float can only be displayed with two digits after the dot
		break;
	default:
		break;
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_keyboardmode[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_keyboardmode[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_keyboardmode[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_keyboardmode[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_keyboardmode[4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, Display.value_str_keyboardmode[5], &Font12, COLORED);
}



/** @brief this function prints the dummy submenu and edits its values
 *
 */
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
		float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;

		char write_str[5];

		switch(Display.JoystickParameterPosition) {
		case 1:
			/* ON-OFF-Decision
			 */

			// fill value line with uncolored rectangle
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH , UNCOLORED);

			// ON/OFF setting
			if(potVal < 50) {	// smaller than 50 %

				//Value to be set
				Display.Voices_ONOFF[0] = false;

				//value display
				char write_str[] = "OFF";
				strcpy(Display.value_str_dummy[0],write_str);
			}
			else if(potVal >= 50) {	// greater than 50 %

				//Value to be set
				Display.Voices_ONOFF[0] = true;

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
			memcpy(Display.value_str_dummy[2],write_str,3); //float can only displayed with two digits after dot
			break;

		case 4:
			// fill value line with uncolored rectangle
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4 + VALUE_ROW_LENGTH, UNCOLORED);
			break;
		default:
			break;
		}
	}

	// print value row
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
