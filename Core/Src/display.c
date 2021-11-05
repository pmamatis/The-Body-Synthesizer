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
	for(int i=0; i<NUMBER_OF_VOICES; i++) {
		Display->Voices_Created[i] = false;
		Display->Voices_ONOFF[i] = false;
		Display->Voices_Note[i] = 'C';
		Display->Voices_Octave[i] = 0;
		Display->Voices_Noteindex[i] = 0;
		Display->last_Voices_Noteindex[i] = 0;
		Display->Voices_Volume[i] = 1.0;
	}

	// Noise
	Display->Noise_ONOFF = false;
	Display->Noise_Volume = 1.0;

	//	Display->ADSR_Attacktime = 0.10;
	//	Display->ADSR_Decaytime = 0.10;
	//	Display->ADSR_Sustaintime = 0.30;
	//	Display->ADSR_Sustainlevel = 0.50;
	//	Display->ADSR_Releasetime = 0.05;
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
	Display->last_Tremolo_ONOFF = false;
	Display->Tremolo_Rate = 1;
	Display->Tremolo_Depth = 0.5;
	Display->Tremolo_EffectPosition = 0;
	Display->Tremolo_EffectAdded = false;
	Display->Tremolo_Rate_Index = Display->last_Tremolo_Rate_Index = 3;	// 1 Hz

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

	Display->JoystickMiddle = 2000;
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
	Display->page_min = -1;
	Display->page_max = 10;

	Display->ENTER_Debounce_State = true;
	Display->BACK_Debounce_State = true;
	Display->SW_Debounce_State = true;
	Display->ENTER = false;
	Display->BACK = false;
	Display->SW = false;
	Display->button_pressed_flag = false;

	Display->poti_moved = false;
	Display->PotiMean_tmp = 0;
	Display->PotiMean = 0;
	Display->PotiMean_counter = 0;
	Display->Poti_Threshold = 15;
	Display->last_Poti = Display->PotiMean + Display->Poti_Threshold + 1;	// has to be initialized like this to make sure that the display will be updated at restart

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
	Display->Drumfilter_Cutoff = 10;

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
	for(int i=0; i<MAX_NUMBER_OF_NOTES; i++) {
		Display->Sequencer_Note[i] = 'C';
		Display->Sequencer_Octave[i] = 0;
		Display->last_Sequencer_Octave[i] = 0;
		Display->Sequencer_Noteindex[i] = 0;
		Display->last_Sequencer_Noteindex[i] = 0;
	}

	freq_index_SN1 = Get_Note_Index(Display->Sequencer_Note[0], (uint8_t)Display->Sequencer_Octave[0]);
	freq_index_SN2 = Get_Note_Index(Display->Sequencer_Note[1], (uint8_t)Display->Sequencer_Octave[1]);
	freq_index_SN3 = Get_Note_Index(Display->Sequencer_Note[2], (uint8_t)Display->Sequencer_Octave[2]);
	for(int i=0; i<FourFour; i++) {
		current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
		current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
		current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
	}

	// WahWah
	Display->WahWah_Mode = 0;
	Display->WahWah_LFOfreq_Index = Display->last_WahWah_LFOfreq_Index = 3;	// 1 Hz

	// Play Single Sample
	Display->PlaySingleSample_ONOFF = false;

	Display->Drumfilter_ONOFF = false;

	//Sources
	Display->Drumfilter_Cutoff_Source = POTI;

	// Preset
	for(uint8_t i=0; i<(sizeof(Display->GyroResetPreset)/sizeof(Display->GyroResetPreset[0])); i++)
		Display->GyroResetPreset[i] = false;

	// Display value init/reset values
	strcpy(Display->value_str_dummy[0],"OFF");	// dummy
	strcpy(Display->value_str_dummy[1],"C");
	strcpy(Display->value_str_dummy[2],"0");
	strcpy(Display->value_str_dummy[3],"OFF");
	strcpy(Display->value_str_dummy[4],"");
	strcpy(Display->value_str_dummy[5],"");
	strcpy(Display->value_str_dummy[6],"");
	strcpy(Display->value_str_dummy[7],"");
	strcpy(Display->value_str_dummy[8],"");

	sprintf(Display->value_str_volume[0], "%.2f", volume[0]);	// volumes
	sprintf(Display->value_str_volume[1], "%.2f", volume[1]);
	sprintf(Display->value_str_volume[2], "%.2f", volume[2]);
	sprintf(Display->value_str_volume[3], "%.2f", volume[3]);

	strcpy(Display->value_str_drumcomputer[0], "OFF");	// drumcomputer
	sprintf(Display->value_str_drumcomputer[1], "%.f", BPM);
	strcpy(Display->value_str_drumcomputer[2], "909");
	strcpy(Display->value_str_drumcomputer[3], "OFF");
	strcpy(Display->value_str_drumcomputer[4], "");	// reset


	strcpy(Display->value_str_sequencer[0], "OFF");	// sequencer
	sprintf(Display->value_str_sequencer[1], "%c", Display->Sequencer_Note[0]);
	sprintf(Display->value_str_sequencer[2], "%d", Display->Sequencer_Octave[0]);
	sprintf(Display->value_str_sequencer[3], "%c", Display->Sequencer_Note[1]);
	sprintf(Display->value_str_sequencer[4], "%d", Display->Sequencer_Octave[1]);
	sprintf(Display->value_str_sequencer[5], "%c", Display->Sequencer_Note[2]);
	sprintf(Display->value_str_sequencer[6], "%d", Display->Sequencer_Octave[2]);
	strcpy(Display->value_str_sequencer[7], "OFF");
	strcpy(Display->value_str_sequencer[8], "");	// reset


	strcpy(Display->value_str_voices_overview[0],"");	// voices overview
	strcpy(Display->value_str_voices_overview[1],"OFF");
	strcpy(Display->value_str_voices_overview[2],"OFF");
	strcpy(Display->value_str_voices_overview[3],"OFF");
	strcpy(Display->value_str_voices_overview[4],"OFF");
	strcpy(Display->value_str_voices_overview[5],"OFF");
	strcpy(Display->value_str_voices_overview[6],"");	// reset

	// 3 voices
	for(uint8_t i=0; i<3; i++) {
		Display->Voices_Note[i] = 'C';
		Display->Voices_Octave[i] = 0;

		sprintf(Display->value_str_voices_settings[i][0], "%c", Display->Voices_Note[i]);
		sprintf(Display->value_str_voices_settings[i][1], "%d", Display->Voices_Octave[i]);
		strcpy(Display->value_str_voices_settings[i][2],"POTI");
		strcpy(Display->value_str_voices_settings[i][3],"POTI");
	}

	Display->ADSR_Attacktime = envelope.adsr_attack_time/LUT_SR;
	Display->ADSR_Decaytime = envelope.adsr_decay_time/LUT_SR;
	Display->ADSR_Sustaintime = envelope.adsr_sustain_time/LUT_SR;
	Display->ADSR_Sustainlevel = envelope.adsr_sustain_amplitude;
	Display->ADSR_Releasetime = envelope.adsr_release_time/LUT_SR;

	sprintf(Display->value_str_adsr_overview[0], "%.2f", Display->ADSR_Attacktime);	// adsr overview
	sprintf(Display->value_str_adsr_overview[1], "%.2f", Display->ADSR_Decaytime);
	sprintf(Display->value_str_adsr_overview[2], "%.2f", Display->ADSR_Sustaintime);
	sprintf(Display->value_str_adsr_overview[3], "%.2f", Display->ADSR_Sustainlevel);
	sprintf(Display->value_str_adsr_overview[4], "%.2f", Display->ADSR_Releasetime);
	strcpy(Display->value_str_adsr_overview[5],"");	// reset

	strcpy(Display->value_str_adsr_settings[0],"POTI");	// adsr settings
	strcpy(Display->value_str_adsr_settings[1],"POTI");
	strcpy(Display->value_str_adsr_settings[2],"POTI");
	strcpy(Display->value_str_adsr_settings[3],"POTI");
	strcpy(Display->value_str_adsr_settings[4],"POTI");

	strcpy(Display->value_str_equalizer_overview[0],"OFF");	// equalizer overview
	strcpy(Display->value_str_equalizer_overview[1],"OFF");
	strcpy(Display->value_str_equalizer_overview[2],"OFF");
	strcpy(Display->value_str_equalizer_overview[3],"OFF");
	strcpy(Display->value_str_equalizer_overview[4],"OFF");
	strcpy(Display->value_str_equalizer_overview[5],"");	// reset

	// 5 filter frequency bands
	// BAND 1: Low-Shelf filter
	Display->Filter_Q[0] = EQ_BAND1.Q;
	Display->Filter_Cutoff[0] = EQ_BAND1.cutoff;
	Display->Filter_Gain[0] = EQ_BAND1.dBGain;
	// BAND 2: Peaking-EQ
	Display->Filter_Q[1] = EQ_BAND2.Q;
	Display->Filter_Cutoff[1] = EQ_BAND2.cutoff;
	Display->Filter_Gain[1] = EQ_BAND2.dBGain;
	// BAND 3: Peaking-EQ
	Display->Filter_Q[2] = EQ_BAND3.Q;
	Display->Filter_Cutoff[2] = EQ_BAND3.cutoff;
	Display->Filter_Gain[2] = EQ_BAND3.dBGain;
	// BAND 4: Peaking-EQ
	Display->Filter_Q[3] = EQ_BAND4.Q;
	Display->Filter_Cutoff[3] = EQ_BAND4.cutoff;
	Display->Filter_Gain[3] = EQ_BAND4.dBGain;
	// BAND 5: High-Shelf filter
	Display->Filter_Q[4] = EQ_BAND5.Q;
	Display->Filter_Cutoff[4] = EQ_BAND5.cutoff;
	Display->Filter_Gain[4] = EQ_BAND5.dBGain;

	for(uint8_t i=0; i<5; i++) {
		sprintf(Display->value_str_equalizer_settings[i][0], "%.3f", Display->Filter_Q[i]);	// equalizer settings
		sprintf(Display->value_str_equalizer_settings[i][1], "%.f", Display->Filter_Cutoff[i]);
		sprintf(Display->value_str_equalizer_settings[i][2], "%.f", Display->Filter_Gain[i]);
		strcpy(Display->value_str_equalizer_settings[i][3],"POTI");
		strcpy(Display->value_str_equalizer_settings[i][4],"POTI");
		strcpy(Display->value_str_equalizer_settings[i][5],"POTI");
	}

	Display->WahWah_MidFreq = WahWah.mid_freq;
	Display->WahWah_Q = WahWah.bandpass->Q;
	Display->WahWah_Range = WahWah.range;
	Display->WahWah_LFOfreq = LFO_FREQUENCYS[Display->WahWah_LFOfreq_Index];
	strcpy(Display->value_str_wahwah[0],"OFF");	// wahwah overview
	strcpy(Display->value_str_wahwah[1], "WahWah");
	sprintf(Display->value_str_wahwah[2], "%.2f", Display->WahWah_MidFreq);	// Normal WahWah settings
	sprintf(Display->value_str_wahwah[3], "%.3f", Display->WahWah_Q);
	strcpy(Display->value_str_wahwah[4],"POTI");
	strcpy(Display->value_str_wahwah[5],"POTI");
	sprintf(Display->value_str_wahwah[6], "%.2f", Display->WahWah_MidFreq);	// Auto-WahWah settings
	sprintf(Display->value_str_wahwah[7], "%.3f", Display->WahWah_Q);
	sprintf(Display->value_str_wahwah[8], "%.2f", Display->WahWah_Range);
	sprintf(Display->value_str_wahwah[9], "%.3f", Display->WahWah_LFOfreq);
	strcpy(Display->value_str_wahwah[10],"POTI");
	strcpy(Display->value_str_wahwah[11],"POTI");
	strcpy(Display->value_str_wahwah[12],"POTI");
	strcpy(Display->value_str_wahwah[13],"POTI");

	Display->Distortion_Gain = HardClipping.distortion_gain;
	strcpy(Display->value_str_distortion[0],"OFF");	// distortion
	sprintf(Display->value_str_distortion[1], "%u", Display->Distortion_Gain);
	strcpy(Display->value_str_distortion[2],"POTI");
	strcpy(Display->value_str_distortion[3],"");	// reset

	Display->Tremolo_Rate = Tremolo.lfo->lfo_frequency;
	Display->Tremolo_Depth = Tremolo.lfo->lfo_depth;
	strcpy(Display->value_str_tremolo[0],"OFF");	// tremolo
	sprintf(Display->value_str_tremolo[1], "%.3f", Display->Tremolo_Rate);
	sprintf(Display->value_str_tremolo[2], "%.3f", Display->Tremolo_Depth);
	strcpy(Display->value_str_tremolo[3],"POTI");
	strcpy(Display->value_str_tremolo[4],"POTI");
	strcpy(Display->value_str_tremolo[5],"");

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

	Display.UpdateDisplay = true;

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
		if(*JoystickParameterPosition < Display.max_parameter)
			*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 2:
		if(*JoystickParameterPosition < Display.max_parameter)
			*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 3:
		if(*JoystickParameterPosition < Display.max_parameter)
			*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 4:
		if(*JoystickParameterPosition < Display.max_parameter)
			*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 5:
		if(*JoystickParameterPosition < Display.max_parameter)
			*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 6:
		if(*JoystickParameterPosition < Display.max_parameter)
			*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 7:
		if(*JoystickParameterPosition < Display.max_parameter)
			*JoystickParameterPosition = *JoystickParameterPosition+1;
		break;
	case 8:
		if(*JoystickParameterPosition < Display.max_parameter)
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
	//	DISPLAY_Update();
	Display.UpdateDisplay = true;
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
	else if(Display.currentSequencer > 0)
		Display.currentSequencer = 0;
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

			default:
				break;
	}
}

/** @brief this function prints the start menu
 * @param frame_buffer: frame buffer of the display
 * @return returns display status flag
 */
Display_Status p_StartingMenu(unsigned char* frame_buffer) {

	//	//Header line
	//	Paint_DrawStringAt(&paint, 1, CASE0, "THE BODYSYNTH", &Font16, COLORED);
	//	Paint_DrawStringAt(&paint, 1, CASE1, "Synthesizermode", &Font12, COLORED);
	//	Paint_DrawStringAt(&paint, 1, CASE2, "Keyboardmode", &Font12, COLORED);
	//
	//	switch(Display.JoystickParameterPosition) {
	//	case 1:
	//		Display.mode = BODYSYNTH;
	//		break;
	//	case 2:
	//		Display.mode = KEYBOARD;
	//		break;
	//	default:
	//		break;
	//	}

	Paint_DrawStringAt(&paint, 1, CASE0, "THE BODYSYNTH", &Font16, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE1, "DSP-Projekt WS 21/22", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE2, "Wiselom Abevi Abbey", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE3, "Maximilian Lehmer", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE4, "Paul Mamatis", &Font12, COLORED);
	Paint_DrawStringAt(&paint, 1, CASE5, "Marc Bielen", &Font12, COLORED);

	Paint_DrawStringAt(&paint, 1, CASE7, "<- Presets       Settings ->", &Font12, COLORED);

	Display.mode = BODYSYNTH;

	Display.UpdateDisplay = true;

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

	// as big as the number of parameters
	Display.max_parameter = 2;

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentDrumcomputer = 0;
		break;
	case 2:
		// Drumcomputer Settings
		Display.currentDrumcomputer = 1;
		if(Display.poti_moved == true) {
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
		}
		break;
	default:
		break;
	}

	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_drumcomputer[0], &Font12, COLORED);

	return DISPLAY_OK;
}

Display_Status p_Drumcomputer_Settings(void) {

	//	char drumkit_str[10];

	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, "Last page", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, "BPM", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, "Load sample", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, "Edit drums", &Font12, COLORED);

	// as big as the number of parameters
	Display.max_parameter = 4;

	if(Display.JoystickParameterPosition == 1) {	// last page
		Display.EditDrums = false;
	}
	else if(Display.JoystickParameterPosition == 2) {	// change BPM -> processing done in interrupt
		Display.EditDrums = false;
	}
	else if(Display.JoystickParameterPosition == 3) {	// load sample from sd card -> right button pressed registered in gpio exti callback
		Display.EditDrums = false;

		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-50, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
		float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %

		if(potVal >= 0 && potVal < 25) {
			strcpy(Display.value_str_drumcomputer[2], "909");
			Paint_DrawStringAt(&paint, Display.value_start_x_position-50, CASE3, Display.value_str_drumcomputer[2], &Font12, COLORED);
			Display.UpdateDisplay = true;
			if(Display.LoadDrumkit == true) {

				// Reset drumcomputer variables when a new drumkit is loaded
				// INIT: Sound bins
				DS1s = 0;
				DS2s = 0;
				DS3s = 0;
				DS4s = 0;
				drums = 0;

				// Drums: Index
				drum_index = 0;
				counter_master = 0;

				for(int i=0; i<FourFour; i++) {
					counter_DS1[i] = 0;
					flag_DS1[i]    = 0;
					counter_DS2[i] = 0;
					flag_DS2[i]    = 0;
					counter_DS3[i] = 0;
					flag_DS3[i]    = 0;
					counter_DS4[i] = 0;
					flag_DS4[i]    = 0;
				}

				Paint_DrawFilledRectangle(&paint, Display.row_start_x_position, CASE5-10, Display.row_start_x_position+50, CASE5-10+VALUE_ROW_LENGTH, UNCOLORED);
				Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5-10, "909", &Font8, COLORED);
				Display_LoadDrumKits(0);
				Display.LoadDrumkit = false;
				strcpy(Display.sample1, "Kick");
				strcpy(Display.sample2, "Op.HH");
				strcpy(Display.sample3, "Clap");
				strcpy(Display.sample4, "L.Tom");
			}
		}
		else if(potVal >= 25 && potVal < 50) {
			strcpy(Display.value_str_drumcomputer[2], "Rock loud");
			//			Paint_DrawStringAt(&paint, Display.value_start_x_position-50, CASE3, Display.value_str_drumcomputer[2], &Font12, COLORED);
			Display.UpdateDisplay = true;
			if(Display.LoadDrumkit == true) {

				// Reset drumcomputer variables when a new drumkit is loaded
				// INIT: Sound bins
				DS1s = 0;
				DS2s = 0;
				DS3s = 0;
				DS4s = 0;
				drums = 0;

				// Drums: Index
				drum_index = 0;
				counter_master = 0;

				for(int i=0; i<FourFour; i++) {
					counter_DS1[i] = 0;
					flag_DS1[i]    = 0;
					counter_DS2[i] = 0;
					flag_DS2[i]    = 0;
					counter_DS3[i] = 0;
					flag_DS3[i]    = 0;
					counter_DS4[i] = 0;
					flag_DS4[i]    = 0;
				}

				Paint_DrawFilledRectangle(&paint, Display.row_start_x_position, CASE5-10, Display.row_start_x_position+50, CASE5-10+VALUE_ROW_LENGTH, UNCOLORED);
				Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5-10, "Rock loud", &Font8, COLORED);
				Display_LoadDrumKits(1);
				Display.LoadDrumkit = false;
				strcpy(Display.sample1, "Kick");
				strcpy(Display.sample2, "Hihat");
				strcpy(Display.sample3, "Snare");
				strcpy(Display.sample4, "Ride");
			}
		}
		else if(potVal >= 50 && potVal < 75) {
			strcpy(Display.value_str_drumcomputer[2], "Rock");
			//			Paint_DrawStringAt(&paint, Display.value_start_x_position-50, CASE3, Display.value_str_drumcomputer[2], &Font12, COLORED);
			Display.UpdateDisplay = true;
			if(Display.LoadDrumkit == true) {

				// Reset drumcomputer variables when a new drumkit is loaded
				// INIT: Sound bins
				DS1s = 0;
				DS2s = 0;
				DS3s = 0;
				DS4s = 0;
				drums = 0;

				// Drums: Index
				drum_index = 0;
				counter_master = 0;

				for(int i=0; i<FourFour; i++) {
					counter_DS1[i] = 0;
					flag_DS1[i]    = 0;
					counter_DS2[i] = 0;
					flag_DS2[i]    = 0;
					counter_DS3[i] = 0;
					flag_DS3[i]    = 0;
					counter_DS4[i] = 0;
					flag_DS4[i]    = 0;
				}

				Paint_DrawFilledRectangle(&paint, Display.row_start_x_position, CASE5-10, Display.row_start_x_position+50, CASE5-10+VALUE_ROW_LENGTH, UNCOLORED);
				Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5-10, "Rock", &Font8, COLORED);
				Display_LoadDrumKits(2);
				Display.LoadDrumkit = false;
				strcpy(Display.sample1, "Kick");
				strcpy(Display.sample2, "Hihat");
				strcpy(Display.sample3, "Snare");
				strcpy(Display.sample4, "Ride");
			}
		}
		else if(potVal >= 75 && potVal <= 100) {
			strcpy(Display.value_str_drumcomputer[2], "Windows");
			//			Paint_DrawStringAt(&paint, Display.value_start_x_position-50, CASE3, Display.value_str_drumcomputer[2], &Font12, COLORED);
			Display.UpdateDisplay = true;
			if(Display.LoadDrumkit == true) {

				// Reset drumcomputer variables when a new drumkit is loaded
				// INIT: Sound bins
				DS1s = 0;
				DS2s = 0;
				DS3s = 0;
				DS4s = 0;
				drums = 0;

				// Drums: Index
				drum_index = 0;
				counter_master = 0;

				for(int i=0; i<FourFour; i++) {
					counter_DS1[i] = 0;
					flag_DS1[i]    = 0;
					counter_DS2[i] = 0;
					flag_DS2[i]    = 0;
					counter_DS3[i] = 0;
					flag_DS3[i]    = 0;
					counter_DS4[i] = 0;
					flag_DS4[i]    = 0;
				}

				Paint_DrawFilledRectangle(&paint, Display.row_start_x_position, CASE5-10, Display.row_start_x_position+50, CASE5-10+VALUE_ROW_LENGTH, UNCOLORED);
				Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5-10, "Windows", &Font8, COLORED);
				Display_LoadDrumKits(3);
				Display.LoadDrumkit = false;
				strcpy(Display.sample1, "Chord");
				strcpy(Display.sample2, "Trash");
				strcpy(Display.sample3, "Remove");
				strcpy(Display.sample4, "Back");
			}
		}
	}
	else if(Display.JoystickParameterPosition == 4) {	// edit drums on/off

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %
			if(potVal < 50) {	// smaller than 50 %
				Display.EditDrums = false;
				strcpy(Display.value_str_drumcomputer[3], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.EditDrums = true;
				strcpy(Display.value_str_drumcomputer[3], "ON");
			}
		}
	}

	Display_DrawDrumcomputerIcons(Display.sample1, Display.sample2, Display.sample3, Display.sample4);
	DISPLAY_DrawDrumcomputerPatternFrame(8);

	Paint_DrawStringAt(&paint, Display.value_start_x_position-20, CASE2, Display.value_str_drumcomputer[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-50, CASE3, Display.value_str_drumcomputer[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_drumcomputer[3], &Font12, COLORED);

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

Display_Status Display_LoadDrumKits(uint8_t Drumkit) {

	//	__disable_irq();	// disable interrupts for a while to make sure that the samples are loaded more quickly

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
		// INIT: Windows LUTs
		// POSSIBLE: Recycle, Background, Chord, Critical Stop, Error, Hardware Remove
		sd_card_mount();
		sd_card_read("Windows_Chord.txt", &DS1);
		sd_card_read("Windows_Recycle.txt", &DS2);
		sd_card_read("Windows_Hardware_Remove.txt", &DS3);
		sd_card_read("Windows_Background.txt", &DS4);
		sd_card_unmount();
	}

	//	__enable_irq();

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

	//	DISPLAY_Update();
	Display.UpdateDisplay = true;

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

	//	DISPLAY_Update();
	Display.UpdateDisplay = true;

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

	// as big as the number of parameters
	Display.max_parameter = 8;

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentSequencer = 0;
		break;
	case 2:
		// Sequencer ON/OFF
		Display.currentSequencer = 1;

		if(Display.poti_moved == true) {
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
		}
		break;
	case 3:
		// Sequencer Note 1
		//		if(Display.poti_moved == true) {
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
		//			Display.Sequencer_Noteindex[0] = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 12;

		if(Display.last_Sequencer_Noteindex[0] != Display.Sequencer_Noteindex[0]) {

			Display.Sequencer_Note[0] = (uint8_t)(keys[(uint8_t)Display.Sequencer_Noteindex[0]]);
			sprintf(Display.value_str_sequencer[1], "%c", Display.Sequencer_Note[0]);

			freq_index_SN1 = Get_Note_Index(Display.Sequencer_Note[0], (uint8_t)Display.Sequencer_Octave[0]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
			}
			Display.last_Sequencer_Noteindex[0] = Display.Sequencer_Noteindex[0];
		}
		//		}
		break;
	case 4:
		// Sequencer Octave 1
		//		if(Display.poti_moved == true) {
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
		//			Display.Sequencer_Octave[0] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 6);

		if(Display.last_Sequencer_Octave[0] != Display.Sequencer_Octave[0]) {

			sprintf(Display.value_str_sequencer[2], "%d", Display.Sequencer_Octave[0]);

			freq_index_SN1 = Get_Note_Index(Display.Sequencer_Note[0], (uint8_t)Display.Sequencer_Octave[0]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
			}
			Display.last_Sequencer_Octave[0] = Display.Sequencer_Octave[0];
		}
		//		}
		break;
	case 5:
		// Sequencer Note 2
		//		if(Display.poti_moved == true) {
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
		//			Display.noteindex = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 12;

		if(Display.last_Sequencer_Noteindex[1] != Display.Sequencer_Noteindex[1]) {

			Display.Sequencer_Note[1] = (uint8_t)(keys[(uint8_t)Display.Sequencer_Noteindex[1]]);
			sprintf(Display.value_str_sequencer[3], "%c", Display.Sequencer_Note[1]);

			freq_index_SN2 = Get_Note_Index(Display.Sequencer_Note[1], (uint8_t)Display.Sequencer_Octave[1]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
			}
			Display.last_Sequencer_Noteindex[1] = Display.Sequencer_Noteindex[1];
		}
		//		}
		break;
	case 6:
		// Sequencer Octave 2
		//		if(Display.poti_moved == true) {
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
		//			Display.Sequencer_Octave[1] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 6);

		if(Display.last_Sequencer_Octave[1] != Display.Sequencer_Octave[1]) {

			sprintf(Display.value_str_sequencer[4], "%d", Display.Sequencer_Octave[1]);

			freq_index_SN2 = Get_Note_Index(Display.Sequencer_Note[1], (uint8_t)Display.Sequencer_Octave[1]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
			}
			Display.last_Sequencer_Octave[1] = Display.Sequencer_Octave[1];
		}
		//		}
		break;
	case 7:
		// Sequencer Note 3
		//		if(Display.poti_moved == true) {
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH, UNCOLORED);
		//			Display.noteindex = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 12;

		if(Display.last_Sequencer_Noteindex[2] != Display.Sequencer_Noteindex[2]) {

			Display.Sequencer_Note[2] = (uint8_t)(keys[(uint8_t)Display.Sequencer_Noteindex[2]]);
			sprintf(Display.value_str_sequencer[5], "%c", Display.Sequencer_Note[2]);

			freq_index_SN3 = Get_Note_Index(Display.Sequencer_Note[2], (uint8_t)Display.Sequencer_Octave[2]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
			}
			Display.last_Sequencer_Noteindex[2] = Display.Sequencer_Noteindex[2];
		}
		//		}
		break;
	case 8:
		// Sequencer Octave 3
		//		if(Display.poti_moved == true) {
		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE8, Display.value_end_x_position, CASE8+VALUE_ROW_LENGTH, UNCOLORED);
		//			Display.Sequencer_Octave[2] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 6);

		if(Display.last_Sequencer_Octave[2] != Display.Sequencer_Octave[2]) {

			sprintf(Display.value_str_sequencer[6], "%d", Display.Sequencer_Octave[2]);

			freq_index_SN3 = Get_Note_Index(Display.Sequencer_Note[2], (uint8_t)Display.Sequencer_Octave[2]);
			for(int i=0; i<FourFour; i++) {
				current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
			}
			Display.last_Sequencer_Octave[2] = Display.Sequencer_Octave[2];
		}
		//		}
		break;
	default:
		break;
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
	//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, "BPM", &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, "Edit sequence", &Font12, COLORED);
	Display_DrawSequencerIcons();
	DISPLAY_DrawSequencerPatternFrame(8);

	// as big as the number of parameters
	Display.max_parameter = 2;

	if(Display.JoystickParameterPosition == 1) {	// last page
		Display.EditSteps = false;
	}
	//	else if(Display.JoystickParameterPosition == 2) {	// change BPM -> processing done in interrupt
	//		Display.EditSteps = false;
	//	}
	else if(Display.JoystickParameterPosition == 2) {	// edit sequence on/off
		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
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
	}

	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_sequencer[7], &Font12, COLORED);

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

	Display.UpdateDisplay = true;

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

	Display.UpdateDisplay = true;

	return DISPLAY_OK;
}

/** @brief this function edits the ON/OFF settings of the Voices
 *
 */
void p_Voices_overview(void) {

	// Header line
	char headerstring[] = "VOICES";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	// row cases
	char str_1[] = "next Effect";
	char str_2[] = "Voice 1 ON/OFF";
	char str_3[] = "Voice 2 ON/OFF";
	char str_4[] = "Voice 3 ON/OFF";
	char str_5[] = "Noise ON/OFF";
	char str_6[] = "Voices Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);

	// as big as the number of parameters
	Display.max_parameter = 6;

	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %

	switch(Display.JoystickParameterPosition) {

	case 1:
		// Next Effect
		Display.currentVoice = 0;
		break;
	case 2:
		// Voice 1 ON/OFF
		Display.currentVoice = 1;
		Display.Voices_Kind[Display.currentVoice-1] = SIN;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				Display.Voices_ONOFF[Display.currentVoice-1] = false;
				strcpy(Display.value_str_voices_overview[1], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Voices_ONOFF[Display.currentVoice-1] = true;
				strcpy(Display.value_str_voices_overview[1], "ON");
			}
		}
		break;
	case 3:
		// Voice 2 ON/OFF
		Display.currentVoice = 2;
		Display.Voices_Kind[Display.currentVoice-1] = SIN;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				Display.Voices_ONOFF[Display.currentVoice-1] = false;
				strcpy(Display.value_str_voices_overview[2], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Voices_ONOFF[Display.currentVoice-1] = true;
				strcpy(Display.value_str_voices_overview[2], "ON");
			}
		}
		break;
	case 4:
		// Voice 3 ON/OFF
		Display.currentVoice = 3;
		Display.Voices_Kind[Display.currentVoice-1] = SIN;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				Display.Voices_ONOFF[Display.currentVoice-1] = false;
				strcpy(Display.value_str_voices_overview[3], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Voices_ONOFF[Display.currentVoice-1] = true;
				strcpy(Display.value_str_voices_overview[3], "ON");
			}
		}
		break;
	case 5:
		// Noise ON/OFF
		Display.currentVoice = 4;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				Display.Noise_ONOFF = false;
				strcpy(Display.value_str_voices_overview[4], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Noise_ONOFF = true;
				strcpy(Display.value_str_voices_overview[4], "ON");
			}
		}
		break;
	case 6:
		// TODO: RESET OF ALL VOICES..
		// Voices Reset ON/OFF
		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				strcpy(Display.value_str_voices_overview[4], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				strcpy(Display.value_str_voices_overview[4], "ON");
			}
		}
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

void p_Voices_Settings(void) {

	//	if(Display.Voices_Kind[Display.currentVoice-1] == SIN) {
	if(Display.currentVoice < NUMBER_OF_VOICES+1) {

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

		// as big as the number of parameters
		Display.max_parameter = 4;

		uint8_t mode_number = 0;

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Note
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			//			Display.Voices_Noteindex[Display.currentVoice-1] = ((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 12;
			Display.Voices_Note[Display.currentVoice-1] = (uint8_t)(keys[(uint8_t)Display.Voices_Noteindex[Display.currentVoice-1]]);
			sprintf(Display.value_str_voices_settings[Display.currentVoice-1][0], "%c", Display.Voices_Note[Display.currentVoice-1]);
			break;
		case 2:
			// Octave
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			//			Display.Voices_Octave[Display.currentVoice-1] = (char)(((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * 5);	// 0ctave 0 to 5
			//sprintf(Display.value_str_voices_settings[1], "%c", Display.Voices_Octave[Display.currentVoice-1]+'0');
			sprintf(Display.value_str_voices_settings[Display.currentVoice-1][1], "%d", Display.Voices_Octave[Display.currentVoice-1]);
			break;
		case 3:
			// Note Source
			if(Display.poti_moved == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
				mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
				Display.Voice_Note_Sources[Display.currentVoice-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
				strcpy(Display.value_str_voices_settings[Display.currentVoice-1][2], Display.source_names[mode_number]);
			}
			break;
		case 4:
			// Octave Source
			if(Display.poti_moved == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
				mode_number = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
				Display.Voice_Octave_Sources[Display.currentVoice-1] = ((uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES)));
				strcpy(Display.value_str_voices_settings[Display.currentVoice-1][3], Display.source_names[mode_number]);
			}
			break;
		default:
			break;
		}

		// print value row
		Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_voices_settings[Display.currentVoice-1][0], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_voices_settings[Display.currentVoice-1][1], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE3, Display.value_str_voices_settings[Display.currentVoice-1][2], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE4, Display.value_str_voices_settings[Display.currentVoice-1][3], &Font12, COLORED);
	}

	//	else if(Display.Voices_Kind[Display.currentVoice-1] == NOISE) {
	else {

		//Header line
		char headerstring[] = "Noise";
		Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);

		//row cases
		char str_1[] = "Volume";
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);

		// as big as the number of parameters
		Display.max_parameter = 1;

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Volume
			if(Display.poti_moved == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
				Display.Noise_Volume = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange;
				sprintf(Display.value_str_voices_settings[Display.currentVoice-1][0], "%.2f", Display.Noise_Volume);
			}
			break;
		default:
			break;
		}

		// print value row
		Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_voices_settings[Display.currentVoice-1][0], &Font12, COLORED);
	}
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
	char str_2[] = "Attack Time";
	char str_3[] = "Decay Time";
	char str_4[] = "Sustain Time";
	char str_5[] = "Sustain Level";
	char str_6[] = "Release Time";
	char str_7[] = "ADSR Reset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, str_7, &Font12, COLORED);

	// as big as the number of parameters
	Display.max_parameter = 7;

	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;	// Potentiometer Input in %
	//	char write_str[10];

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentADSR = 0;
		break;
	case 2:
		// Attack Time
		Display.currentADSR = 1;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Attacktime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_attack);

			// 0.05 to prevent 0 -> fuckup
			if(Display.ADSR_Attacktime < 0.05)
				Display.ADSR_Attacktime = 0.05;

			for(uint8_t i=0; i<MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++)
				adsr_keyboard[i].adsr_attack_time = Display.ADSR_Attacktime * LUT_SR;

			sprintf(Display.value_str_adsr_overview[0], "%.2f", Display.ADSR_Attacktime);
		}
		break;
	case 3:
		// Decay Time
		Display.currentADSR = 2;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Decaytime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_decay);

			for(uint8_t i=0; i<MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++)
				adsr_keyboard[i].adsr_decay_time = Display.ADSR_Decaytime * LUT_SR;

			sprintf(Display.value_str_adsr_overview[1], "%.2f", Display.ADSR_Decaytime);
		}
		break;
	case 4:
		// Sustain Time
		Display.currentADSR = 3;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Sustaintime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_sustaintime);

			for(uint8_t i=0; i<MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++)
				adsr_keyboard[i].adsr_sustain_time = Display.ADSR_Sustaintime * LUT_SR;

			sprintf(Display.value_str_adsr_overview[2], "%.2f", Display.ADSR_Sustaintime);
		}
		break;
	case 5:
		// Sustain Level
		Display.currentADSR = 4;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Sustainlevel = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_max_amp);

			for(uint8_t i=0; i<MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++)
				adsr_keyboard[i].adsr_sustain_amplitude = Display.ADSR_Sustainlevel;

			sprintf(Display.value_str_adsr_overview[3], "%.2f", Display.ADSR_Sustainlevel);
		}
		break;
	case 6:
		// Release Time
		Display.currentADSR = 5;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
			Display.ADSR_Releasetime = (((float)Display.ADC2inputs[2]/Display.ADC_FullRange) * envelope->adsr_maximum_release);

			for(uint8_t i=0; i<MAX_SIMULTANEOUS_KEYBOARD_NOTES; i++)
				adsr_keyboard[i].adsr_release_time = Display.ADSR_Releasetime * LUT_SR;

			sprintf(Display.value_str_adsr_overview[4], "%.2f", Display.ADSR_Releasetime);
		}
		break;
	case 7:
		// TODO: RESET OF ADSR..
		// ADSR Reset ON/OFF

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				strcpy(Display.value_str_adsr_overview[5], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				strcpy(Display.value_str_adsr_overview[5], "ON");
			}
		}
		break;
	default:
		break;
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_adsr_overview[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_adsr_overview[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_adsr_overview[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_adsr_overview[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, Display.value_str_adsr_overview[4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE7, Display.value_str_adsr_overview[5], &Font12, COLORED);
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

	// as big as the number of parameters
	Display.max_parameter = 5;

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

	// as big as the number of parameters
	Display.max_parameter = 7;

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

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = false;
				strcpy(Display.value_str_equalizer_overview[0], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = true;
				strcpy(Display.value_str_equalizer_overview[0], "ON");
			}
		}
		break;
	case 3:
		// Band 2 ON/OFF
		Display.currentBand = 2;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = false;
				strcpy(Display.value_str_equalizer_overview[1], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = true;
				strcpy(Display.value_str_equalizer_overview[1], "ON");
			}
		}
		break;
	case 4:
		// Band 3 ON/OFF
		Display.currentBand = 3;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = false;
				strcpy(Display.value_str_equalizer_overview[2], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = true;
				strcpy(Display.value_str_equalizer_overview[2], "ON");
			}
		}
		break;
	case 5:
		// Band 4 ON/OFF
		Display.currentBand = 4;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = false;
				strcpy(Display.value_str_equalizer_overview[3], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = true;
				strcpy(Display.value_str_equalizer_overview[3], "ON");
			}
		}
		break;
	case 6:
		// Band 5 ON/OFF
		Display.currentBand = 5;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = false;
				strcpy(Display.value_str_equalizer_overview[4], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.Filter_ONOFF[Display.currentBand-1] = true;
				strcpy(Display.value_str_equalizer_overview[4], "ON");
			}
		}
		break;
	case 7:
		// TODO: Equalizer Reset..
		// EQUALIZER Reset ON/OFF

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH , UNCOLORED);

			if(potVal < 50) {	// smaller than 50 %
				strcpy(Display.value_str_equalizer_overview[5], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				strcpy(Display.value_str_equalizer_overview[5], "ON");
			}
		}
		break;
	default:
		break;
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_equalizer_overview[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_equalizer_overview[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE4, Display.value_str_equalizer_overview[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE5, Display.value_str_equalizer_overview[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE6, Display.value_str_equalizer_overview[4], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE7, Display.value_str_equalizer_overview[5], &Font12, COLORED);
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

	// as big as the number of parameters
	Display.max_parameter = 6;

	uint8_t mode_number = 0;

	if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:
			// Q-Factor
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Filter_Q[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * EQ_BAND1.maximum_Q);
			if(Display.Filter_Q[Display.currentBand-1] < 0.01)	// guard for Q-factor, so it is never 0
				Display.Filter_Q[Display.currentBand-1] = 0.01;
			sprintf(Display.value_str_equalizer_settings[Display.currentBand-1][0], "%.3f", Display.Filter_Q[Display.currentBand-1]);

			// BAND 1: Low-Shelf filter
			if(Display.currentBand == 1) {
				EQ_BAND1.Q = Display.Filter_Q[Display.currentBand-1];
				SetupLowShelf(&EQ_BAND1, EQ_BAND1.cutoff, EQ_BAND1.Q, EQ_BAND1.dBGain);
			}
			// BAND 2: Peaking-EQ
			else if(Display.currentBand == 2) {
				EQ_BAND2.Q = Display.Filter_Q[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND2, EQ_BAND2.cutoff, EQ_BAND2.Q, EQ_BAND2.dBGain);
			}
			// BAND 3: Peaking-EQ
			else if(Display.currentBand == 3) {
				EQ_BAND3.Q = Display.Filter_Q[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND3, EQ_BAND3.cutoff, EQ_BAND3.Q, EQ_BAND3.dBGain);
			}
			// BAND 4: Peaking-EQ
			else if(Display.currentBand == 4) {
				EQ_BAND4.Q = Display.Filter_Q[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND4, EQ_BAND4.cutoff, EQ_BAND4.Q, EQ_BAND4.dBGain);
			}
			// BAND 5: High-Shelf filter
			else if(Display.currentBand == 5) {
				EQ_BAND5.Q = Display.Filter_Q[Display.currentBand-1];
				SetupHighShelf(&EQ_BAND5, EQ_BAND5.cutoff, EQ_BAND5.Q, EQ_BAND5.dBGain);
			}
			break;
		case 2:
			// Cutoff
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Filter_Cutoff[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * EQ_BAND1.maximum_cutoff);
			if(Display.Filter_Cutoff[Display.currentBand-1] < LUT_FMIN)
				Display.Filter_Cutoff[Display.currentBand-1] = LUT_FMIN;
			sprintf(Display.value_str_equalizer_settings[Display.currentBand-1][1], "%.0f", Display.Filter_Cutoff[Display.currentBand-1]);

			// BAND 1: Low-Shelf filter
			if(Display.currentBand == 1) {
				EQ_BAND1.cutoff = Display.Filter_Cutoff[Display.currentBand-1];
				SetupLowShelf(&EQ_BAND1, EQ_BAND1.cutoff, EQ_BAND1.Q, EQ_BAND1.dBGain);
			}
			// BAND 2: Peaking-EQ
			else if(Display.currentBand == 2) {
				EQ_BAND2.cutoff = Display.Filter_Cutoff[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND2, EQ_BAND2.cutoff, EQ_BAND2.Q, EQ_BAND2.dBGain);
			}
			// BAND 3: Peaking-EQ
			else if(Display.currentBand == 3) {
				EQ_BAND3.cutoff = Display.Filter_Cutoff[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND3, EQ_BAND3.cutoff, EQ_BAND3.Q, EQ_BAND3.dBGain);
			}
			// BAND 4: Peaking-EQ
			else if(Display.currentBand == 4) {
				EQ_BAND4.cutoff = Display.Filter_Cutoff[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND4, EQ_BAND4.cutoff, EQ_BAND4.Q, EQ_BAND4.dBGain);
			}
			// BAND 5: High-Shelf filter
			else if(Display.currentBand == 5) {
				EQ_BAND5.cutoff = Display.Filter_Cutoff[Display.currentBand-1];
				SetupHighShelf(&EQ_BAND5, EQ_BAND5.cutoff, EQ_BAND5.Q, EQ_BAND5.dBGain);
			}
			break;
		case 3:
			// Gain
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Filter_Gain[Display.currentBand-1] = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * EQ_BAND1.maximum_dBGain);	// same maximum gain for every band

			Display.Filter_Gain[Display.currentBand-1] = 2*Display.Filter_Gain[Display.currentBand-1]-EQ_BAND1.maximum_dBGain;	// same maximum gain for every band

			sprintf(Display.value_str_equalizer_settings[Display.currentBand-1][2], "%.0f", Display.Filter_Gain[Display.currentBand-1]);

			// BAND 1: Low-Shelf filter
			if(Display.currentBand == 1) {
				EQ_BAND1.dBGain = Display.Filter_Gain[Display.currentBand-1];
				SetupLowShelf(&EQ_BAND1, EQ_BAND1.cutoff, EQ_BAND1.Q, EQ_BAND1.dBGain);
			}
			// BAND 2: Peaking-EQ
			else if(Display.currentBand == 2) {
				EQ_BAND2.dBGain = Display.Filter_Gain[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND2, EQ_BAND2.cutoff, EQ_BAND2.Q, EQ_BAND2.dBGain);
			}
			// BAND 3: Peaking-EQ
			else if(Display.currentBand == 3) {
				EQ_BAND3.dBGain = Display.Filter_Gain[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND3, EQ_BAND3.cutoff, EQ_BAND3.Q, EQ_BAND3.dBGain);
			}
			// BAND 4: Peaking-EQ
			else if(Display.currentBand == 4) {
				EQ_BAND4.dBGain = Display.Filter_Gain[Display.currentBand-1];
				SetupPeakingEQ(&EQ_BAND4, EQ_BAND4.cutoff, EQ_BAND4.Q, EQ_BAND4.dBGain);
			}
			// BAND 5: High-Shelf filter
			else if(Display.currentBand == 5) {
				EQ_BAND5.dBGain = Display.Filter_Gain[Display.currentBand-1];
				SetupHighShelf(&EQ_BAND5, EQ_BAND5.cutoff, EQ_BAND5.Q, EQ_BAND5.dBGain);
			}
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
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE1, Display.value_str_equalizer_settings[Display.currentBand-1][0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE2, Display.value_str_equalizer_settings[Display.currentBand-1][1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE3, Display.value_str_equalizer_settings[Display.currentBand-1][2], &Font12, COLORED);
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

	// as big as the number of parameters
	Display.max_parameter = 3;

	// Potentiometer Input in %
	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;

	switch(Display.JoystickParameterPosition) {
	case 1:
		// Next Effect
		Display.currentWahWah = 0;
		break;
	case 2:	// WahWah ON/OFF
		Display.currentWahWah = 1;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.WahWah_ONOFF = false;
				strcpy(Display.value_str_wahwah[0], "OFF");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.WahWah_ONOFF = true;
				strcpy(Display.value_str_wahwah[0], "ON");
			}
		}
		break;
	case 3:	// WahWah Mode
		Display.currentWahWah = 2;

		if(Display.poti_moved == true) {
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-50, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH , UNCOLORED);
			if(potVal < 50) {	// smaller than 50 %
				Display.WahWah_Mode = 0;
				strcpy(Display.value_str_wahwah[1], "WahWah");
			}
			else if(potVal >= 50) {	// greater than 50 %
				Display.WahWah_Mode = 1;
				strcpy(Display.value_str_wahwah[1], "AutoWahWah");
			}
		}
		break;
	default:
		break;
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_wahwah[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-50, CASE3, Display.value_str_wahwah[1], &Font12, COLORED);
}

void p_WahWah_Settings(struct WahWah_t *WahWah) {

	uint8_t mode_number = 0;
	//	uint16_t index = 0;

	if(Display.WahWah_Mode == 0) {	// Normal WahWah
		// Header line
		char headerstring[] = "NORMAL WAHWAH";
		Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);

		char str_1[] = "Mid Freq.";
		char str_2[] = "Q-factor";
		char str_3[] = "Mid Freq. Source";
		char str_4[] = "Q Source";

		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);

		// as big as the number of parameters
		Display.max_parameter = 4;

		//		if(Display.poti_moved == true) {

		switch(Display.JoystickParameterPosition) {
		case 1:	// WahWah Mid Frequency
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			if(Display.poti_moved == true) {
				Display.WahWah_MidFreq = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * WahWah->max_mid_freq;
				if(Display.WahWah_MidFreq < 50)	// WahWah_MidFreq should be minimum 50 Hz
					Display.WahWah_MidFreq = 50;
				WahWah->mid_freq = Display.WahWah_MidFreq;
			}
			sprintf(Display.value_str_wahwah[2], "%.2f", Display.WahWah_MidFreq);
			break;
		case 2:	// WahWah Q-factor
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			if(Display.poti_moved == true) {
				Display.WahWah_Q = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * WahWah->max_Q) + 0.5;
				WahWah->bandpass->Q = Display.WahWah_Q;
			}
			sprintf(Display.value_str_wahwah[3], "%.3f", Display.WahWah_Q);
			break;
		case 3:	// WahWah Mid Frequency Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			if(Display.poti_moved == true) {
				mode_number = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				Display.WahWah_Sources[0] = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
			}
			strcpy(Display.value_str_wahwah[4], Display.source_names[mode_number]);
			break;
		case 4:	// Q-factor Source
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			if(Display.poti_moved == true) {
				mode_number = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				Display.WahWah_Sources[1] = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
			}
			strcpy(Display.value_str_wahwah[5], Display.source_names[mode_number]);
			break;
		default:
			break;
		}
		//		}
		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE1, Display.value_str_wahwah[2], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE2, Display.value_str_wahwah[3], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE3, Display.value_str_wahwah[4], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE4, Display.value_str_wahwah[5], &Font12, COLORED);
	}
	else if(Display.WahWah_Mode == 1) {	// Auto-WahWah
		// Header line
		char headerstring[] = "AUTO-WAHWAH";
		Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);

		char str_1[] = "Mid Freq.";
		char str_2[] = "Q-factor";
		char str_3[] = "Range";
		char str_4[] = "LFO Freq.";
		char str_5[] = "Mid Freq. Source";
		char str_6[] = "Q Source";
		char str_7[] = "Range Source";
		char str_8[] = "LFO Freq. Source";

		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE5, str_5, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE6, str_6, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE7, str_7, &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE8, str_8, &Font12, COLORED);

		// as big as the number of parameters
		Display.max_parameter = 8;

		switch(Display.JoystickParameterPosition) {
		case 1:	// Auto-WahWah Mid Frequency
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
			if(Display.poti_moved == true) {
				Display.WahWah_MidFreq = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * WahWah->max_mid_freq;
				if(Display.WahWah_MidFreq < 50)	// WahWah_MidFreq should be minimum 50 Hz
					Display.WahWah_MidFreq = 50;
				WahWah->mid_freq = Display.WahWah_MidFreq;
				WahWah->max_range = (Display.WahWah_MidFreq - 50) * 2;	// max range calculated depending on the current mid freq value
				Display.WahWah_Range = ((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * WahWah->max_range;
				WahWah->range = Display.WahWah_Range;
			}
			sprintf(Display.value_str_wahwah[6], "%.2f", Display.WahWah_MidFreq);
			break;
		case 2:	// Auto-WahWah Q-factor
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			if(Display.poti_moved == true) {
				Display.WahWah_Q = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * WahWah->max_Q) + 0.5;
				WahWah->bandpass->Q = Display.WahWah_Q;
			}
			sprintf(Display.value_str_wahwah[7], "%.2f", Display.WahWah_Q);
			break;
		case 3:	// Auto-WahWah Range
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			if(Display.poti_moved == true) {
				Display.WahWah_Range = ((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * WahWah->max_range;
				WahWah->range = Display.WahWah_Range;
			}
			sprintf(Display.value_str_wahwah[8], "%.2f", Display.WahWah_Range);
			break;
		case 4:	// Auto-WahWah LFO Frequency
			if(WahWah->lfo->lfo_done_flag == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
				//				index = (uint16_t)(((float)Display.ADC2inputs[2]/((float)Display.ADC_FullRange-100)) * (sizeof(LFO_FREQUENCYS)/sizeof(LFO_FREQUENCYS[0])-1));
				//				Display.WahWah_LFOfreq = LFO_FREQUENCYS[index];
				//				WahWah->lfo->lfo_frequency = Display.WahWah_LFOfreq;
				//				WahWah->lfo->lfo_index = 0;
				//				WahWah->lfo->lfo_quarter = 0;
				//				sprintf(Display.value_str_wahwah[5], "%.3f", Display.WahWah_LFOfreq);
				sprintf(Display.value_str_wahwah[9], "%.3f", Display.WahWah_LFOfreq);
			}
			break;
		case 5:	// Auto-WahWah Mid Frequency Source
			if(Display.poti_moved == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE5, Display.value_end_x_position, CASE5+VALUE_ROW_LENGTH, UNCOLORED);
				mode_number = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				Display.WahWah_Sources[0] = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				strcpy(Display.value_str_wahwah[10], Display.source_names[mode_number]);
			}
			break;
		case 6:	// Auto-WahWah Q Source
			if(Display.poti_moved == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE6, Display.value_end_x_position, CASE6+VALUE_ROW_LENGTH, UNCOLORED);
				mode_number = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				Display.WahWah_Sources[1] = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				strcpy(Display.value_str_wahwah[11], Display.source_names[mode_number]);
			}
			break;
		case 7:	// Auto-WahWah Range Source
			if(Display.poti_moved == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE7, Display.value_end_x_position, CASE7+VALUE_ROW_LENGTH, UNCOLORED);
				mode_number = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				Display.WahWah_Sources[2] = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				strcpy(Display.value_str_wahwah[12], Display.source_names[mode_number]);
			}
			break;
		case 8:	// Auto-WahWah LFO Frequency Source
			if(Display.poti_moved == true) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE8, Display.value_end_x_position, CASE8+VALUE_ROW_LENGTH, UNCOLORED);
				mode_number = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				Display.WahWah_Sources[3] = (uint8_t)(((float)Display.ADC2inputs[2] / (float)Display.ADC_FullRange) * (NUMBER_OF_SOURCES));
				strcpy(Display.value_str_wahwah[13], Display.source_names[mode_number]);
			}
			break;
		default:
			break;
		}

		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE1, Display.value_str_wahwah[6], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE2, Display.value_str_wahwah[7], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE3, Display.value_str_wahwah[8], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE4, Display.value_str_wahwah[9], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE5, Display.value_str_wahwah[10], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE6, Display.value_str_wahwah[11], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE7, Display.value_str_wahwah[12], &Font12, COLORED);
		Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE8, Display.value_str_wahwah[13], &Font12, COLORED);
	}
}

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

	// as big as the number of parameters
	Display.max_parameter = 4;

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

	// as big as the number of parameters
	Display.max_parameter = 6;

	// Potentiometer Input in %
	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;
	uint8_t mode_number = 0;
	//	char write_str[10];

	if(Display.poti_moved == true || Tremolo->lfo->lfo_done_flag == true) {
		//	if(Display.poti_moved == true) {

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
			//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			//			Display.Tremolo_Rate_Index = (uint16_t)(((float)Display.ADC2inputs[2]/((float)Display.ADC_FullRange-100)) * ((sizeof(LFO_FREQUENCYS)/sizeof(LFO_FREQUENCYS[0])-1)));
			//			if(Tremolo->lfo->lfo_done_flag == true) {
			////				Display.Tremolo_Rate = LFO_FREQUENCYS[Display.Tremolo_Rate_Index];
			////				sprintf(Display.value_str_tremolo[1], "%.3f", Display.Tremolo_Rate);
			//				Tremolo->lfo->lfo_done_flag = false;
			//			}
			break;
		case 3:
			// Tremolo Depth
			//			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);
			Display.Tremolo_Depth = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * Tremolo->tremolo_maximum_depth);
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

	// delete display tremolo rate content to make sure that the content is not overwritten when the arrow is not on position 2 (tremolo rate)
	Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
	// delete display tremolo depth content to make sure that the content is not overwritten when the arrow is not on position 3 (tremolo depth)
	Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-30, CASE3, Display.value_end_x_position, CASE3+VALUE_ROW_LENGTH, UNCOLORED);

	sprintf(Display.value_str_tremolo[1], "%.3f", Display.Tremolo_Rate);
	sprintf(Display.value_str_tremolo[2], "%.2f", Display.Tremolo_Depth);
	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_tremolo[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE2, Display.value_str_tremolo[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE3, Display.value_str_tremolo[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE4, Display.value_str_tremolo[3], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-30, CASE5, Display.value_str_tremolo[4], &Font12, COLORED);
}

/** @brief this function prints the Tremolo submenu and edits its values
 * @param Tremolo struct
 */
void p_Volume(void) {

	//Header line
	char headerstring[] = "VOLUME";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Voices Vol.";
	char str_2[] = "Drumcomputer Vol.";
	char str_3[] = "Sequencer Vol.";
	char str_4[] = "Keyboard Vol.";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);

	// as big as the number of parameters
	Display.max_parameter = 4;

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
		case 4:
			// Volume Keyboard
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-25, CASE4, Display.value_end_x_position, CASE4+VALUE_ROW_LENGTH, UNCOLORED);
			volume[3] = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange;
			sprintf(Display.value_str_volume[3], "%.2f", volume[3]);
			break;
		default:
			break;
		}
	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE1, Display.value_str_volume[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE2, Display.value_str_volume[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE3, Display.value_str_volume[2], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position-25, CASE4, Display.value_str_volume[3], &Font12, COLORED);
}

//void p_Presets(void) {
//
//	Paint_DrawStringAt(&paint, 1, CASE0, "PRESETS", &Font16, COLORED);
//	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, "Preset:", &Font12, COLORED);
//
//	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;
//
//	switch(Display.JoystickParameterPosition) {
//	case 1:
//		if(potVal < 50) {
//			if(Display.GyroResetPreset[0] == false) {
//
//				Display.Drumcomputer_ONOFF = true;
//				Display.Drumfilter_ONOFF = true;
//				Display.Drumfilter_Cutoff_Source = GYRO_FB;
//
//				Display.Filter_ONOFF[0] = true;
//				Display.EQ_Cutoff_Sources[0] = GYRO_LR;
//				Display.currentBand = 0;
//				NewSignal(&signals1,SIN, 'C',2,16);
//				NewSignal(&signals1,SIN, 'E',2,17);
//				NewSignal(&signals1,SIN, 'G',1,18);
//				NewSignal(&signals1,SIN, 'C',2,8);
//				NewSignal(&signals1,SIN, 'E',2,9);
//				NewSignal(&signals1,SIN, 'G',2,10);
//				NewSignal(&signals1,SIN, 'C',3,11);
//				NewSignal(&signals1,SIN, 'E',3,12);
//				NewSignal(&signals1,SIN, 'G',3,13);
//				NewSignal(&signals1,SIN, 'C',4,14);
//				Display.GyroResetPreset[0] = true;
//				Display.GyroResetPreset[1] = false;
//			}
//		}
//		else if(potVal >= 50) {
//			if(Display.GyroResetPreset[1] == true) {
//				// TODO
//				Display.GyroResetPreset[0] = false;
//				Display.GyroResetPreset[1] = true;
//			}
//		}
//		break;
//	default:
//		break;
//	}
//}

void p_Presets(void) {

	//Header line
	char headerstring[] = "PRESETS";
	Paint_DrawStringAt(&paint, 1, CASE0, headerstring, &Font16, COLORED);
	//row cases
	char str_1[] = "Drums Preset";
	char str_2[] = "Seq. Preset";
	char str_3[] = "Gyro Preset";
	char str_4[] = "EMG Preset";
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE1, str_1, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE2, str_2, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE3, str_3, &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.row_start_x_position, CASE4, str_4, &Font12, COLORED);

	// as big as the number of parameters
	Display.max_parameter = 4;


	NewSignal(&signals1,SIN, 'C',1,8);
	NewSignal(&signals1,SIN, 'E',1,9);
	NewSignal(&signals1,SIN, 'G',1,10);
	NewSignal(&signals1,SIN, 'C',2,11);
	NewSignal(&signals1,SIN, 'E',2,12);
	NewSignal(&signals1,SIN, 'G',2,13);
	NewSignal(&signals1,SIN, 'C',3,14);
	NewSignal(&signals1,SIN, 'E',3,15);
	NewSignal(&signals1,SIN, 'G',3,16);
	NewSignal(&signals1,SIN, 'C',4,17);
	NewSignal(&signals1,SIN, 'E',4,18);
	NewSignal(&signals1,SIN, 'G',4,19);
	NewSignal(&signals1,SIN, 'C',5,20);
	NewSignal(&signals1,SIN, 'E',5,21);
	NewSignal(&signals1,SIN, 'G',5,22);

	Display.WahWah_ONOFF = true;

	//		Display.Tremolo_ONOFF = true;
	//		Display.Tremolo_Sources[1] = GYRO_LR;

	//	Display.Filter_ONOFF[0] = true;
	//	Display.EQ_Cutoff_Sources[0] = GYRO_FB;
	//	Display.currentBand = 0;

	//	Display.Voices_Note[0] = 'C';
	//	Display.Voices_ONOFF[0] = true;
	//	Display.Voices_Octave[0] = 3;
	//	Display.Voice_Note_Sources[0] = EKG;

	//	float potVal = (float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange * 100;
	//
	//	switch(Display.JoystickParameterPosition) {
	//	case 1:	// Drums Preset
	//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE1, Display.value_end_x_position, CASE1+VALUE_ROW_LENGTH, UNCOLORED);
	//		if(potVal < 50) {
	//			sprintf(Display.value_str_presets[0], "%d", 1);
	//			Display.DrumMatrix[0][0] = true;	// Sample 1
	//			Display.DrumMatrix[0][1] = false;
	//			Display.DrumMatrix[0][2] = false;
	//			Display.DrumMatrix[0][3] = false;
	//			Display.DrumMatrix[0][4] = true;
	//			Display.DrumMatrix[0][5] = false;
	//			Display.DrumMatrix[0][6] = false;
	//			Display.DrumMatrix[0][7] = false;
	//			Display.DrumMatrix[1][0] = false;	// Sample 2
	//			Display.DrumMatrix[1][1] = false;
	//			Display.DrumMatrix[1][2] = true;
	//			Display.DrumMatrix[1][3] = false;
	//			Display.DrumMatrix[1][4] = false;
	//			Display.DrumMatrix[1][5] = false;
	//			Display.DrumMatrix[1][6] = true;
	//			Display.DrumMatrix[1][7] = false;
	//			Display.DrumMatrix[2][0] = false;	// Sample 3
	//			Display.DrumMatrix[2][1] = false;
	//			Display.DrumMatrix[2][2] = false;
	//			Display.DrumMatrix[2][3] = false;
	//			Display.DrumMatrix[2][4] = true;
	//			Display.DrumMatrix[2][5] = false;
	//			Display.DrumMatrix[2][6] = false;
	//			Display.DrumMatrix[2][7] = false;
	//			Display.DrumMatrix[3][0] = false;	// Sample 4
	//			Display.DrumMatrix[3][1] = false;
	//			Display.DrumMatrix[3][2] = false;
	//			Display.DrumMatrix[3][3] = false;
	//			Display.DrumMatrix[3][4] = false;
	//			Display.DrumMatrix[3][5] = false;
	//			Display.DrumMatrix[3][6] = false;
	//			Display.DrumMatrix[3][7] = false;
	//
	//			timing_DS1[0] = 1;
	//			timing_DS1[1] = 0;
	//			timing_DS1[2] = 0;
	//			timing_DS1[3] = 0;
	//			timing_DS1[4] = 1;
	//			timing_DS1[5] = 0;
	//			timing_DS1[6] = 0;
	//			timing_DS1[7] = 0;
	//			timing_DS2[0] = 0;
	//			timing_DS2[1] = 0;
	//			timing_DS2[2] = 1;
	//			timing_DS2[3] = 0;
	//			timing_DS2[4] = 0;
	//			timing_DS2[5] = 0;
	//			timing_DS2[6] = 1;
	//			timing_DS2[7] = 0;
	//			timing_DS3[0] = 0;
	//			timing_DS3[1] = 0;
	//			timing_DS3[2] = 0;
	//			timing_DS3[3] = 0;
	//			timing_DS3[4] = 1;
	//			timing_DS3[5] = 0;
	//			timing_DS3[6] = 0;
	//			timing_DS3[7] = 0;
	//			timing_DS4[0] = 0;
	//			timing_DS4[1] = 0;
	//			timing_DS4[2] = 0;
	//			timing_DS4[3] = 0;
	//			timing_DS4[4] = 0;
	//			timing_DS4[5] = 0;
	//			timing_DS4[6] = 0;
	//			timing_DS4[7] = 0;
	//		}
	//		else if(potVal >= 50) {
	//			sprintf(Display.value_str_presets[0], "%d", 2);
	//			//			timing_DS1[0] = 1;	// Advanced Techno Beat
	//			//			timing_DS1[1] = 0;
	//			//			timing_DS1[2] = 1;
	//			//			timing_DS1[3] = 0;
	//			//			timing_DS1[4] = 1;
	//			//			timing_DS1[5] = 0;
	//			//			timing_DS1[6] = 0;
	//			//			timing_DS1[7] = 0;
	//			//			timing_DS2[0] = 0;
	//			//			timing_DS2[1] = 0;
	//			//			timing_DS2[2] = 1;
	//			//			timing_DS2[3] = 0;
	//			//			timing_DS2[4] = 0;
	//			//			timing_DS2[5] = 0;
	//			//			timing_DS2[6] = 1;
	//			//			timing_DS2[7] = 0;
	//			//			timing_DS3[0] = 0;
	//			//			timing_DS3[1] = 0;
	//			//			timing_DS3[2] = 0;
	//			//			timing_DS3[3] = 0;
	//			//			timing_DS3[4] = 1;
	//			//			timing_DS3[5] = 0;
	//			//			timing_DS3[6] = 0;
	//			//			timing_DS3[7] = 1;
	//			//			timing_DS4[0] = 0;
	//			//			timing_DS4[1] = 0;
	//			//			timing_DS4[2] = 1;
	//			//			timing_DS4[3] = 1;
	//			//			timing_DS4[4] = 0;
	//			//			timing_DS4[5] = 0;
	//			//			timing_DS4[6] = 0;
	//			//			timing_DS4[7] = 1;
	//		}
	//		break;
	//	case 2:	// Sequencer Preset
	//		Paint_DrawFilledRectangle(&paint, Display.value_start_x_position, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
	//		if(potVal < 50) {
	//			sprintf(Display.value_str_presets[1], "%d", 1);
	//			freq_index_SN1 = Get_Note_Index('C', 1);	// load notes
	//			for(int i=0; i<FourFour; i++) {
	//				current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
	//			}
	//			freq_index_SN2 = Get_Note_Index('D', 1);
	//			for(int i=0; i<FourFour; i++) {
	//				current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
	//			}
	//			freq_index_SN3 = Get_Note_Index('d', 1);
	//			for(int i=0; i<FourFour; i++) {
	//				current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
	//			}
	//			timing_SN1[0] = 1;	// Sequence Pattern
	//			timing_SN1[1] = 0;
	//			timing_SN1[2] = 0;
	//			timing_SN1[3] = 0;
	//			timing_SN1[4] = 0;
	//			timing_SN1[5] = 0;
	//			timing_SN1[6] = 0;
	//			timing_SN1[7] = 0;
	//			timing_SN2[0] = 0;
	//			timing_SN2[1] = 0;
	//			timing_SN2[2] = 0;
	//			timing_SN2[3] = 1;
	//			timing_SN2[4] = 0;
	//			timing_SN2[5] = 0;
	//			timing_SN2[6] = 0;
	//			timing_SN2[7] = 0;
	//			timing_SN3[0] = 0;
	//			timing_SN3[1] = 0;
	//			timing_SN3[2] = 0;
	//			timing_SN3[3] = 0;
	//			timing_SN3[4] = 0;
	//			timing_SN3[5] = 0;
	//			timing_SN3[6] = 1;
	//			timing_SN3[7] = 0;
	//		}
	//		else if(potVal >= 50) {
	//			sprintf(Display.value_str_presets[1], "%d", 2);
	//		}
	//		break;
	//	case 3:
	//		if(potVal < 50) {
	//			if(Display.GyroResetPreset[0] == false) {
	//
	//				Display.Drumcomputer_ONOFF = true;
	//				Display.Drumfilter_ONOFF = true;
	//				Display.Drumfilter_Cutoff_Source = GYRO_FB;
	//
	//				Display.Filter_ONOFF[0] = true;
	//				Display.EQ_Cutoff_Sources[0] = GYRO_LR;
	//				Display.currentBand = 0;
	//				NewSignal(&signals1,SIN, 'C',2,16);
	//				NewSignal(&signals1,SIN, 'E',2,17);
	//				NewSignal(&signals1,SIN, 'G',1,18);
	//				NewSignal(&signals1,SIN, 'C',2,8);
	//				NewSignal(&signals1,SIN, 'E',2,9);
	//				NewSignal(&signals1,SIN, 'G',2,10);
	//				NewSignal(&signals1,SIN, 'C',3,11);
	//				NewSignal(&signals1,SIN, 'E',3,12);
	//				NewSignal(&signals1,SIN, 'G',3,13);
	//				NewSignal(&signals1,SIN, 'C',4,14);
	//				Display.GyroResetPreset[0] = true;
	//				Display.GyroResetPreset[1] = false;
	//			}
	//		}
	//		else if(potVal >= 50) {
	//			if(Display.GyroResetPreset[1] == true) {
	//				// TODO
	//				Display.GyroResetPreset[0] = false;
	//				Display.GyroResetPreset[1] = true;
	//			}
	//		}
	//		break;
	//	default:
	//		break;
	//	}

	// print value row
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE1, Display.value_str_presets[0], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE2, Display.value_str_presets[1], &Font12, COLORED);
	Paint_DrawStringAt(&paint, Display.value_start_x_position, CASE3, Display.value_str_presets[2], &Font12, COLORED);
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

	if(Display.poti_moved == true) {

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
