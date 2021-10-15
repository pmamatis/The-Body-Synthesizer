#include "signal_synthesis.h"

/** @brief maximal binary value which is used by the DAC, can be adjusted by AMPLITUDE in signal_sythesis.h and will be set in the Init function*/
double maxValueDAC;


/**@brief Init funtion for the signal_synthesis, must be used in order to use any other funtion of this .c
 * @param htim: timer-handler which controls the DAC, timer have to be connected with DAC
 * @param hdac: is the DAC handler
 *@return gives HAL-Status of started timer back
 */
HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac){

	// Sets the maximal digital value which the DAC converts into analog voltage
	maxValueDAC = (double)DAC_MAXVALUE_TO_AMPLITUDE_RATIO * (double)AMPLITUDE;
	outputBuffer_position = HALF_BLOCK;
	output_Channel = 1;
	signals1.count = 0;
	signals1.max = 1;

	//set volume
	Master_Volume = 1;
	for(int i =0 ;i<4;i++){
		volume[i] = 1;
	}

	//Sets all taken ID to zero
	for(int Signal_Synthesis_Init_count = 0; Signal_Synthesis_Init_count < MAX_SIGNAL_KOMBINATION;Signal_Synthesis_Init_count++)
		ID_array[Signal_Synthesis_Init_count]=0;

	for (int i = 0; i >BLOCKSIZE/2; i++)
		*((uint32_t *)(&calculate_vector1[i] )) = (uint32_t)((i/(BLOCKSIZE/2)) * maxValueDAC/2); // TODO muss noch angepasst werden




	//Inits and starts timer connected with DAC
	SetTimerSettings(&htim, LUT_SR);

	return HAL_TIM_Base_Start(&htim);
}


/**@brief Init funtion for the Timer which triggers the DAC, this function sets the timerperiode and presacaler
 * @param htim: timer-handler which controls the DAC, timer have to be connected with DAC
 * @param SR: Sample Rate
 */
void SetTimerSettings(TIM_HandleTypeDef* htim, uint32_t SR) {

	// Clock Sources of all 14 timers: 1 = APB1, 2 = APB2
	uint8_t APBTimerCases[] = {2,1,1,1,1,1,1,2,2,2,2,1,1,1};
	uint8_t Timer = 0;
	uint32_t Clock = 0;

	if(htim->Instance == TIM1) Timer = 1;
	else if(htim->Instance == TIM2) Timer = 2;
	else if(htim->Instance == TIM3) Timer = 3;
	else if(htim->Instance == TIM4) Timer = 4;
	else if(htim->Instance == TIM5) Timer = 5;
	else if(htim->Instance == TIM6) Timer = 6;
	else if(htim->Instance == TIM7) Timer = 7;
	else if(htim->Instance == TIM8) Timer = 8;
	else if(htim->Instance == TIM9) Timer = 9;
	else if(htim->Instance == TIM10) Timer = 10;
	else if(htim->Instance == TIM11) Timer = 11;
	else if(htim->Instance == TIM12) Timer = 12;
	else if(htim->Instance == TIM13) Timer = 13;
	else if(htim->Instance == TIM14) Timer = 14;


	if(APBTimerCases[Timer-1] == 1)
		Clock = 2 * HAL_RCC_GetPCLK1Freq();	// APB1 Timer Clock

	if(APBTimerCases[Timer-1] == 2)
		Clock = 2 * HAL_RCC_GetPCLK2Freq();	// APB2 Timer Clock

	uint32_t values_length = 65536;
	uint16_t prescaler;
	uint32_t timerperiod = 0;

	for(int i=1; i<values_length; i++) {

		prescaler = fmod(Clock, i);	// modulo-operation
		if(prescaler == 0) {// find possible prescaler Values
			prescaler = i;
			timerperiod = Clock/( prescaler * SR );//set timerperiod
			if (timerperiod < values_length){
				break;
			}
		}
	}//end for-loop

	__HAL_TIM_SET_AUTORELOAD(htim, timerperiod-1);	// update timer settings
	__HAL_TIM_SET_PRESCALER(htim, prescaler-1);
	//TIM6->ARR = period-1;
	//TIM6->PSC = prescaler-1;
}



/** @brief Constructor for a signal, adds a signal into the signals1 struct
 *  @param kind: kind of the signal, use signal_kind_enum
 *  @param key:  is string which is a note key from C to b
 *  @param octave: defines in which octave the key is settled.
 *  @attention the combination of key and octave defines the frequency
 */
void LFO_SingleValueProcess(struct effects_lfo_t* lfo) {

	lfo->lfo_data = 0;

	// CASE 1: 0.125 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[0]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[0] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[0]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[0] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[0]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[0] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
	// CASE 2: 0.25 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[1]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[1] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[1]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[1] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[1]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[1] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
	// CASE 3: 0.5 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[2]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[2] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[2]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[2] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[2]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[2] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
	// CASE 4: 1 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[3]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[3] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[3]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[3] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[3]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[3] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
	// CASE 5: 2 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[4]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[4] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[4]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[4] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[4]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[4] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
	// CASE 6: 4 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[5]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[5] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[5]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[5] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[5]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[5] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
	// CASE 7: 8 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[6]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[6] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[6]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[6] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[6]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[6] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
	// CASE 8: 16 Hz
	if(lfo->lfo_frequency == LFO_FREQUENCYS[7]){

		// CHECK: if end of quarter is reached, if yes then increment quarter and set index to zero
		if(lfo->lfo_index == LFO_SUPPORTPOINTS[7] - 1) {

			lfo->lfo_index = 0;
			lfo->lfo_quarter++;
			if (lfo->lfo_quarter > 3)
				lfo->lfo_quarter = 0;
		}

		switch(lfo->lfo_quarter) {
		case 0:
			lfo->lfo_data = LFO[lfo->lfo_index + LFO_STARTINDEX[7]];
			break;
		case 1:
			lfo->lfo_data = LFO[LFO_ENDINDEX[7] - lfo->lfo_index];
			break;
		case 2:
			lfo->lfo_data = -LFO[lfo->lfo_index + LFO_STARTINDEX[7]];
			break;
		case 3:
			lfo->lfo_data = -LFO[LFO_ENDINDEX[7] - lfo->lfo_index];
			break;
		default:
			break;
		}
		lfo->lfo_index++;
	}
}

void NewSignal(struct signal_t* signals, uint8_t kind, uint8_t key, uint8_t octave, uint8_t ID){

	if (signals -> count <= MAX_SIGNAL_KOMBINATION){
		signals -> count += 1;
		uint8_t index = (signals-> count)-1;
		signals -> ID[index]= ID;
		signals -> kind[index] = kind;
		switch (kind){

		case SIN:

			signals -> freq[index] = Get_Note_Frequency(Get_Keyindex(key), octave);
			signals -> freqIndex[index] = Get_Note_Index(key,octave);
			signals -> current_LUT_Index[index] = LUT_STARTINDEX[signals -> freqIndex[index]];
			// signals -> current_LUT_Index[index] = LUT_STARTINDEX[signals1.freqIndex[index]];


			break;
		case NOISE:
			signals -> freq[index] = 0;
			signals -> freqIndex[index] = 0;
			signals -> current_LUT_Index[index] = 0;
			break;
		}
	}
	signals -> max = 1;

	//	for (int NewSignal_count = 0; NewSignal_count < MAX_SIGNAL_KOMBINATION;NewSignal_count++){
	//		if(!ID_array[NewSignal_count]){
	//			signals -> ID[NewSignal_count] = NewSignal_count;
	//			ID_array[NewSignal_count] = 1;
	//		}
	//
	//	}

	//	printf("New Signal counter = %i\r\n", signals->count);
	//	printf("ID's:");
	//		for (int i = 0;i<signals->count;i++)
	//			printf("%i ,",signals->ID[i]);
	//		printf("\r\n");
}

/** @brief deletes a signal inside the signals1 struct, and shifts all other signals behind the deleted signal to the left. The shift is for having no empty spaces inside the signals1 struct
 * @param: signal_index: index of the signals which should be seleted
 * @attention if you wnat to delete two signals in a row, beware that the index of the second signal could have changed, e.g. signals1 contains three signals, you want to delete signals1[0] and signals1[1]. After using DeleteSignal(0) you need to use DeleteSignal(0) again, because signals1[1] became signals1[0] after first use
 * @return None
 *  */
void DeleteSignal(struct signal_t* signals,int16_t signal_index){

	if (signals->count > 0 && signal_index > -1){
		//shift signals too left
		for (int delete_counter=signal_index; delete_counter < signals->count; delete_counter++ ){
			signals -> current_LUT_Index[delete_counter] = signals -> current_LUT_Index[delete_counter+1] ;
			signals -> freq[delete_counter] = signals -> freq[delete_counter+1];
			signals -> freqIndex[delete_counter] = signals -> freqIndex[delete_counter+1];
			signals -> kind[delete_counter] = signals -> kind[delete_counter+1];
			signals -> ID[delete_counter] = signals -> ID[delete_counter+1];
		}
		signals -> count-=1;
		signals -> max = 1;
		//	signals -> max = 0;

		//	printf("ID's:");
		//	for (int i = 0;i<signals->count;i++)
		//		printf("%i ,",signals->ID[i]);
		//	printf("\r\n");
		//	printf("delete: signals left = %i;\r\n",signals->count);
	}
	else {
		printf("delete ERROR\r\n");
	}
}
/** converts an signal ID into its Index
 * @param : ID of the wanted signal
 * @retval: Index of the signal with the given ID, or -1 when ID was not found
 */
int16_t IDtoIndex(int16_t id){

	for(int i =0; i < MAX_SIGNAL_KOMBINATION;i++){
		if (signals1.ID[i] == id){
			return i;
		}
	}
	return -1;
}

/** @brief generates a signal in the calculate_vector, depending on the signals inside the struct signals1. To add signals use NewSignal and to delete signals use DeleteSignal
 *	@param signal: is a signal_t struct which contains the tones to be played
 *	@param  output_Channel: decides if the Array connected to the DAC Channel one is filled or the array connected with the DAC channel two is filled
 *  @note Channel 1 is connected to calculate_vector1 and Channel 2 connected to calculate_vector2
 *  @return None
 */
void Signal_Synthesis(struct signal_t* signals,uint8_t output_Channel){

	//Variables
	float addValue=0;
	uint8_t count = signals -> count;

	// decide if Channel 1 or Channel 2
	float* calculate_vector_tmp = 0; // working aray

	if (output_Channel == 1){
		calculate_vector_tmp = calculate_vector1;
	}
	else if (output_Channel == 2){
		calculate_vector_tmp = calculate_vector2;
	}


	//decide if first half of BLOCKSIZE or second half
	uint16_t BLOOCKSIZE_startIndex=0, BLOOCKSIZE_endIndex=0;
	if (outputBuffer_position == HALF_BLOCK){
		BLOOCKSIZE_startIndex = 0; // nur für lesbarkeit
		BLOOCKSIZE_endIndex = (BLOCKSIZE/2);
	}
	else if(outputBuffer_position == FULL_BLOCK){
		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
		BLOOCKSIZE_endIndex  = BLOCKSIZE;

	}

	//Loop for signal synthesis
	for (int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex; BLOCKSIZE_counter++){
		addValue = 0;
		calculate_keyboard[0] = 0;
		calculate_keyboard[1] = 0;
		calculate_keyboard[2] = 0;
		calculate_keyboard[3] = 0;
		calculate_keyboard[4] = 0;

		// Loop to reach all Signals
		for(int j=0; j<count; j++) {
			switch (signals->kind[j]) {
			case SIN:

				// keyboard signals
				if(signals->ID[j] == KEYBOARD_VOICE_ID){
					calculate_keyboard[0] = LUT[signals -> current_LUT_Index[j]];
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+1){
					calculate_keyboard[1] = LUT[signals -> current_LUT_Index[j]];
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+2){
					calculate_keyboard[2] = LUT[signals -> current_LUT_Index[j]];
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+3){
					calculate_keyboard[3] = LUT[signals -> current_LUT_Index[j]];
				}
				else if(signals->ID[j] == KEYBOARD_VOICE_ID+4){
					calculate_keyboard[4] = LUT[signals -> current_LUT_Index[j]];
				}
				else{
					// adds all SIN values from the signals to addValue
					addValue = addValue + LUT[signals -> current_LUT_Index[j]];
				}
				// get index for the next sin value
				signals -> current_LUT_Index[j]++;

				if (signals -> current_LUT_Index[j] > LUT_ENDINDEX[signals -> freqIndex[j]]) {

					signals -> current_LUT_Index[j] = LUT_STARTINDEX[ signals -> freqIndex[j]];


					/* NEUER ANSATZ
					 * LAST_INDEX_FLAG[j] = true;
					 */


					/* MUSS NOCHMAL ÜBERARBEITET WERDEN
					 * während der Count schleife an der Count-Schleife rumzumachen wird irgendwann zu Bugs führen
					 *
					// create voice signals (maximum 3) to avoid plop sound if note or octave is varied
					if(signals->ID[j] == VOICES_ID) {	//ID taucht nur auf wenn  voice auch ON ist...
						if(Display.Voices_ONOFF[VOICES_ID] == true ) { //Sinnlos!!!!
							if(Display.last_Voices_Note[VOICES_ID] != Display.Voices_Note[VOICES_ID]) {
								DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
								NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
								Display.last_Voices_Note[VOICES_ID] = Display.Voices_Note[VOICES_ID];
							}
							//Wieso 2 mal?????
							if(Display.last_Voices_Octave[VOICES_ID] != Display.Voices_Octave[VOICES_ID]) {
								DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
								NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID], Display.Voices_Octave[VOICES_ID],VOICES_ID);
								Display.last_Voices_Octave[VOICES_ID] = Display.Voices_Octave[VOICES_ID];
							}
						}
					}
					else if(signals->ID[j] == VOICES_ID+1) { //ID taucht nur auf wenn  voice auch ON ist...
						if(Display.Voices_ONOFF[VOICES_ID+1] == true ) { //Sinnlos!!!!
							if(Display.last_Voices_Note[VOICES_ID+1] != Display.Voices_Note[VOICES_ID+1]) {
								DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
								NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
								Display.last_Voices_Note[VOICES_ID+1] = Display.Voices_Note[VOICES_ID+1];
							}
							//Wieso 2 mal?????
							if(Display.last_Voices_Octave[VOICES_ID+1] != Display.Voices_Octave[VOICES_ID+1]) {
								DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
								NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+1], Display.Voices_Octave[VOICES_ID+1],VOICES_ID+1);
								Display.last_Voices_Octave[VOICES_ID+1] = Display.Voices_Octave[VOICES_ID+1];
							}
						}
					}
					else if(signals->ID[j] == VOICES_ID+2) {	//ID taucht nur auf wenn  voice auch ON ist...
						if(Display.Voices_ONOFF[VOICES_ID+2] == true ) { //Sinnlos!!!!
							if(Display.last_Voices_Note[VOICES_ID+2] != Display.Voices_Note[VOICES_ID+2]) {
								DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
								NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
								Display.last_Voices_Note[VOICES_ID+2] = Display.Voices_Note[VOICES_ID+2];
							}
							//Wieso 2 mal?????
							if(Display.last_Voices_Octave[VOICES_ID+2] != Display.Voices_Octave[VOICES_ID+2]) {
								DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
								NewSignal(&signals1, SIN, Display.Voices_Note[VOICES_ID+2], Display.Voices_Octave[VOICES_ID+2],VOICES_ID+2);
								Display.last_Voices_Octave[VOICES_ID+2] = Display.Voices_Octave[VOICES_ID+2];
							}
						}
					}
					// delete signal if voice off
					if(Display.Voices_ONOFF[VOICES_ID]==false && Display.Voices_Created[VOICES_ID] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID));
						Display.Voices_Created[VOICES_ID] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+1]==false && Display.Voices_Created[VOICES_ID+1] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+1));
						Display.Voices_Created[VOICES_ID+1] = false;
					}
					else if(Display.Voices_ONOFF[VOICES_ID+2]==false && Display.Voices_Created[VOICES_ID+2] == true) {
						DeleteSignal(&signals1, IDtoIndex(VOICES_ID+2));
						Display.Voices_Created[VOICES_ID+2] = false;
					}
				*/
				}
				break;

			case NOISE:
				//addValue += AWGN_generator();
				addValue += (2*(float)rand()/sizeof(int))-1;
				break;
			}// Switch-Case



		}// Signal counter for-loop


		/* NEUER ANSATZ ,
		// Delete Signal change Note
		for(int j=0; j<count; j++) {
			if (signals->deleteME[j]){
				DeleteSignal(signals,j );
			}
		}
		*/
		/*limiter function*/
		//norm the signal to -1...1
		//		calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter]/signals -> max;

		// NORM: Volume by signal count
		if(signals->count - active_keyboard_notes == 0) {}	// division by zero for addValue possible -> fuckup!
		else
			addValue = addValue/(signals->count - active_keyboard_notes);


		//write into calculate vector
		calculate_vector_tmp[BLOCKSIZE_counter] = volume[0] * addValue;

		//				// maximum
		//				if (signals -> max < fabs((double)addValue)){
		//					signals -> max = fabs((double)addValue);
		//				}

		// Drummachine
		if ((volume[1]>0)||(volume[2]>0)){
			Drum_Computer_Process();
			drums_filtered = drums;
			if(Display.Drumfilter_ONOFF)
				ProcessFilter(&LS_DRUMS, &drums_filtered);
		}
		else{
			drums = 0;
			sequencer = 0;
		}

		// Keyboard processing
		keyboard_adsr_process();
		// summing up all played keyboard notes
		for (int k= 0; k < 5;k++)
			calculate_vector_tmp[BLOCKSIZE_counter] += volume[3] * calculate_keyboard[k];

		// Play single sample
		if(play_single_sample_flag) {
			PlaySingleSample();
			calculate_vector_tmp[BLOCKSIZE_counter] += single_sample;
		}

		effects_process_fast(&calculate_vector_tmp[BLOCKSIZE_counter]);

		// Add all values
		calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter] + volume[1] * drums_filtered + volume[2] * sequencer;

		//		// maximum
		//		if (signals -> max < fabs((double)addValue)){
		//			signals -> max = fabs((double)addValue);
		//		}

		//		//scale output signal depending on amount of voices
		//		switch (signals -> count){
		//		case 1:
		//			calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter] /((float)2.37);// -7.5 dB, for 0dB: *((float)sqrt((double)2))
		//			break;
		//		case 2:
		//			calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter] /((float)2);// -6 dB
		//			break;
		//		case 3:
		//			calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter] /((float)1.679);// -4.5 dB
		//			break;
		//		case 4:
		//			calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter] /((float)sqrt((double)2));// -3 dB
		//			break;
		//		case 5:
		//			calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter] /((float)1.1885);// -1.5 dB
		//			break;
		//		default:
		//			calculate_vector_tmp[BLOCKSIZE_counter] = calculate_vector_tmp[BLOCKSIZE_counter];
		//			break;
		//		}

		//Signal adjustment to DAC
		//*((uint32_t *)(&calculate_vector_tmp[BLOCKSIZE_counter] )) = (uint32_t)((((float)emg_buffer[BLOCKSIZE_counter]+1)/2) * maxValueDAC + OFFSET ); // +1.5 fir middle of 0-3V3 (with OFFSET of 145)

		//		if ((Display.Sequencer_ONOFF==false) && (Display.Drumcomputer_ONOFF==false) && (signals->count==0)){
		//			calculate_vector_tmp[BLOCKSIZE_counter]  = noPlopOffset ; // +1.5 fir middle of 0-3V3
		//		}

		*((uint32_t *)(&calculate_vector_tmp[BLOCKSIZE_counter] )) = (uint32_t)((1.0 * calculate_vector_tmp[BLOCKSIZE_counter]+1.65) * maxValueDAC); // +1.65 is the middle of 0-3V3
	}//End for-Loop

	// save current LUT index into signals1,
	for (int tmp_count = 0 ; tmp_count < signals -> count; tmp_count++){
		signals -> current_LUT_Index[tmp_count] = signals -> current_LUT_Index[tmp_count];
	}
}

///** @brief generates a low frequency sine to be used for effects
// *  @param effect: struct which contains the parameter for the effect which want to use the LFO
// *
// */
//void Signal_Synthesis_LFO(struct effects_lfo_t* effect) {
//
//	float frequency = effect->lfo_frequency;
//	uint8_t quarter = effect->lfo_quarter;
//	uint32_t index = effect->lfo_index;
//	uint32_t LFO_blocksizecounter = effect->lfo_blocksizecounter;
//
//	// calculate ratio between LFO frequency and minimum processable frequency
//	float frequency_ratio = frequency / LFO_FMIN;
//
//	if(LFO_blocksizecounter == BLOCKSIZE/2) {
//		LFO_blocksizecounter = 0;
//	}
//
//	// check if end of LFO_LUT is reached, if yes then increment quarter and set index to zero
//	if(index  > LFO_ENDINDEX[0]) {
//		index = 0;
//		quarter++;
//		if (quarter > 3)
//			quarter = 0;
//	}
//
//	switch(quarter) {
//	case 0:
//		effect_LFO[LFO_blocksizecounter] = LFO[index];
//		break;
//	case 1:
//		effect_LFO[LFO_blocksizecounter] = LFO[LFO_ENDINDEX[0] - index];
//		break;
//	case 2:
//		effect_LFO[LFO_blocksizecounter] = -LFO[index];
//		break;
//	case 3:
//		effect_LFO[LFO_blocksizecounter] = -LFO[LFO_ENDINDEX[0] - index];
//		break;
//	default:
//		break;
//	}
//	index = round((double)(index + frequency_ratio));
//
//	//save current state into given effect struct
//	effect->lfo_blocksizecounter = LFO_blocksizecounter;
//	effect->lfo_index = index;
//	effect->lfo_quarter = quarter;
//}


//float LFO_SingleValueProcess(struct effects_lfo_t* lfo) {
//
//	float effect_LFO = 0;
//
//	// calculate ratio between LFO_LUT frequency and desired frequency
//	float frequency_ratio = lfo->lfo_frequency / LFO_FMIN;
//
//	// check if end of LFO_LUT is reached, if yes then increment quarter and set index to zero
//	if(lfo->lfo_index  > LFO_ENDINDEX[0]) {
//		lfo->lfo_index = 0;
//		lfo->lfo_quarter++;
//		if (lfo->lfo_quarter > 3)
//			lfo->lfo_quarter = 0;
//	}
//
//	switch(lfo->lfo_quarter) {
//	case 0:
//		effect_LFO = LFO[lfo->lfo_index];
//		break;
//	case 1:
//		effect_LFO = LFO[LFO_ENDINDEX[0] - lfo->lfo_index];
//		break;
//	case 2:
//		effect_LFO = -LFO[lfo->lfo_index];
//		break;
//	case 3:
//		effect_LFO = -LFO[LFO_ENDINDEX[0] - lfo->lfo_index];
//		break;
//	default:
//		break;
//	}
//	lfo->lfo_index = round((double)(lfo->lfo_index + frequency_ratio));
//
//	return effect_LFO;
//}


/* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */
float AWGN_generator()
{

	float temp1;
	float temp2;
	float result;
	int p;

	p = 1;

	while( p > 0 )
	{
		temp2 = ( rand() / ( (float)RAND_MAX ) ); /*  rand() function generates an
                                                       integer between 0 and  RAND_MAX,
                                                       which is defined in stdlib.h.
		 */

		if ( temp2 == 0 )
		{// temp2 is >= (RAND_MAX / 2)
			p = 1;
		}// end if
		else
		{// temp2 is < (RAND_MAX / 2)
			p = -1;
		}// end else

	}// end while()

	temp1 = cos( ( 2.0 * (float)PI ) * rand() / ( (float)RAND_MAX ) );
	result = sqrt( -2.0 * log( temp2 ) ) * temp1;

	return result;	// return the generated random sample to the caller

}// end AWGN_generator()
