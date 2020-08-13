



#include "signal_synthesis.h"





/** @brief maximal binary value which is used by the DAC, can be adjusted by AMPLITUDE in signal_sythesis.h and will be set in the Init function*/
double maxValueDAC = DAC_MAX;



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

	//Sets all taken ID to zero
	for(int Signal_Synthesis_Init_count = 0; Signal_Synthesis_Init_count < MAX_SIGNAL_KOMBINATION;Signal_Synthesis_Init_count++){
		ID_array[Signal_Synthesis_Init_count]=0;
	}
	//Inits and starts timer connected with DAC
	SetTimerSettings(&htim, LUT_SR);
	return HAL_TIM_Base_Start(&htim);
}


/**@brief Init funtion for the Timer which triggers the DAC, this function sets the timerperiode and presacaler
 * @param htim: timer-handler which controls the DAC, timer have to be connected with DAC
 * @param SR: Sample Rate
 */
void SetTimerSettings(TIM_HandleTypeDef* htim, uint32_t SR) {

	uint32_t Clock = HAL_RCC_GetHCLKFreq();	// system core clock HCLK
	uint32_t values_length = 65536;
	uint16_t prescaler;
	uint32_t timerperiod;

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
void NewSignal(uint8_t kind, uint8_t key, uint8_t octave){

	if (signals1.count <= MAX_SIGNAL_KOMBINATION){
		signals1.count += 1;
		uint8_t index = signals1.count-1;

		signals1.kind[index] = kind;
		signals1.freq[index] = Get_Note_Frequency(Get_Keyindex(key), octave);
		signals1.freqIndex[index] = Get_Note_Index(key,octave);
		signals1.current_LUT_Index[index] = LUT_STARTINDEX[signals1.freqIndex[index]];
		signals1.max = 0;
		for (int NewSignal_count = 0; NewSignal_count < MAX_SIGNAL_KOMBINATION;NewSignal_count++){
			if(!ID_array[NewSignal_count]){
				signals1.ID[NewSignal_count] = NewSignal_count;
				ID_array[NewSignal_count] = 1;
			}


		}

	}

}

/** @brief deletes a signal inside the signals1 struct, and shifts all other signals behind the deleted signal to the left. The shift is for having no empty spaces inside the signals1 struct
 * @param: signal_index: index of the signals which should be seleted
 * @attention if you wnat to delete two signals in a row, beware that the index of the second signal could have changed, e.g. signals1 contains three signals, you want to delete signals1[0] and signals1[1]. After using DeleteSignal(0) you need to use DeleteSignal(0) again, because signals1[1] became signals1[0] after first use  */
void DeleteSignal(uint8_t signal_index){
	//free the signal ID
	uint8_t tmp = signals1.ID[signal_index];
	ID_array[tmp] = 0;

	//shift signals too left
	for (int delete_counter=signal_index; delete_counter < signals1.count;delete_counter++ ){
		signals1.current_LUT_Index[delete_counter] = signals1.current_LUT_Index[delete_counter+1] ;
		signals1.freq[delete_counter] = signals1.freq[delete_counter+1];
		signals1.freqIndex[delete_counter] = signals1.freqIndex[delete_counter+1];
		signals1.kind[delete_counter] = signals1.kind[delete_counter+1];
		signals1.ID[delete_counter] = signals1.ID[delete_counter+1];

	}
	signals1.count-=1;
	signals1.max = 0;
}



/** @brief generates a signal in the outputvector, depending on the signals inside the struct signals1. To add signals use NewSignal and to delete signals use DeleteSignal
 */
void Signal_Synthesis(){

	//Variables
	float addValue=0;
	uint8_t count;
	struct signal signals;
	// decide if Channel 1 or Channel 2
	/**@TODO */
	if (output_Channel == 1){
		count = signals1.count;
		signals = signals1;
	}
	//		else if (output_Channel == 2){
	//			count = signals2.count;
	//			signals = signals2;
	//		}


	//decide if first half of BLOCKSIZE or second half
	uint16_t BLOOCKSIZE_startIndex, BLOOCKSIZE_endIndex;
	if(outputBuffer_position == HALF_BLOCK) {
		BLOOCKSIZE_startIndex = 0;
		BLOOCKSIZE_endIndex = BLOCKSIZE/2;
	}
	else if(outputBuffer_position == FULL_BLOCK) {
		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
		BLOOCKSIZE_endIndex  = BLOCKSIZE;
	}

	//Loop to for first signal synthesis and find maximum
	for(int BLOCKSIZE_counter=BLOOCKSIZE_startIndex; BLOCKSIZE_counter<BLOOCKSIZE_endIndex; BLOCKSIZE_counter++) {
		addValue = 0;
		//Loop to reach all Signals
		for (int j = 0; j < count;j++){
			switch (signals.kind[j]) {
			case SIN:
				//adds all SIN values from the signals to addValue
				addValue = addValue + LUT[signals.current_LUT_Index[j]];

				//get index for the next sin value
				signals.current_LUT_Index[j]++;
				if (signals.current_LUT_Index[j] > LUT_ENDINDEX[signals.freqIndex[j]])
				{
					signals.current_LUT_Index[j] = LUT_STARTINDEX[signals1.freqIndex[j]];
				}
				break;
			} // Switch-Case
		} // Signal counter for-loop

		// maximum
		if (signals.max < fabs((double)addValue)){
			signals.max = fabs((double)addValue);
		}

		// write into calculate vector
		calculate_vector1[BLOCKSIZE_counter] = addValue;


	} //BLOCKSIZE for-Loop I


	//Loop to adjust the signal
	for(int BLOCKSIZE_counter=BLOOCKSIZE_startIndex; BLOCKSIZE_counter<BLOOCKSIZE_endIndex; BLOCKSIZE_counter++) {

		//norm the signal to -1...1
		// addValue = addValue/count;
		calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter]/signals.max;

		// BEGIN EFFECTS----------------------------------------------------------------------------------------------

		// Tremolo
		Signal_Synthesis_LFO(&tremollo);
		calculate_vector1[BLOCKSIZE_counter] = (0.5 + 0.5 * effect_LFO[tremollo.lfo_blocksizecounter]) * calculate_vector1[BLOCKSIZE_counter];
		tremollo.lfo_blocksizecounter++;
		//tremollo.index = round((double)(tremollo.index + (tremollo.frequency / LFO_FMIN)));

		/*// Basic Delay
		// User-adjustable effect parameters:
		dryMix = 0.5;
		wetMix = 0.5;
		feedback_level = 0;

		delay_out = (dryMix * calculate_vector1[BLOCKSIZE_counter] + wetMix * delayData[dpr]);

		delayData[dpw] = calculate_vector1[BLOCKSIZE_counter] + (delayData[dpr] * feedback_level);
		if (++dpr >= delayBufLength)
			dpr = 0;
		if (++dpw >= delayBufLength)
			dpw = 0;

		calculate_vector1[BLOCKSIZE_counter] = delay_out;*/

		/*// Feedback-Echo
		uint8_t BPM = 120;	// beats per minute
		float BPS = BPM/60;	// beats per second
		float SPB = 1/BPS;	// seconds per beat
		// note duration = 1-quarter, 0.5-8th, 2-half note
		float note_duration = 0.5;
		uint32_t delay_samples = floor(note_duration * SPB * LUT_SR);  // floor is rounding the number
		float gain = -0.5;
		// Array-Indexing-method
		if((BLOCKSIZE_counter-delay_samples) < 1)
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter] + 0;
		else
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter] + gain * calculate_vector1[BLOCKSIZE_counter-delay_samples];*/

		/*// Hard Clipping Distortion
		double DistortionGain = 1.5;	// value between 1 and 20 (sine to squarewave)
		calculate_vector1[BLOCKSIZE_counter] = DistortionGain * calculate_vector1[BLOCKSIZE_counter];
		if(calculate_vector1[BLOCKSIZE_counter] >= signals.max)
			calculate_vector1[BLOCKSIZE_counter] = signals.max;
		else if(calculate_vector1[BLOCKSIZE_counter] <= -signals.max)
			calculate_vector1[BLOCKSIZE_counter] = -signals.max;*/
		// tanh-Distortion
		//calculate_vector1[BLOCKSIZE_counter] = tanh(3 * calculate_vector1[BLOCKSIZE_counter]);

		// END EFFECTS------------------------------------------------------------------------------------------------

		/*//scale output signal depeding on amount of voices
		switch (signals.count){
		case 1:
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter]/((float)2.37);// -7.5 dB
			break;
		case 2:
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter] /((float)2);// -6 dB
			break;
		case 3:
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter] /((float)1.679);// -4.5 dB
			break;
		case 4:
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter] /((float)sqrt((double)2));// -3 dB
			break;
		case 5:
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter] /((float)1.1885);// -1.5 dB
			break;
		default:
			calculate_vector1[BLOCKSIZE_counter] = calculate_vector1[BLOCKSIZE_counter];
			break;
		}*/

		//if-clause to control the distance between two vector entrys
		//			if (abs(output_vector1[BLOCKSIZE_counter]-output_vector1[BLOCKSIZE_counter-1]) > 20){
		//				tmp[index_tmp] = BLOCKSIZE_counter;
		//				index_tmp++;
		//			}


		//Signal adjustment to DAC
		//output_vector1[BLOCKSIZE_counter] = (calculate_vector1[BLOCKSIZE_counter] - (-signals.max)) * (4095 - 0) / (signals.max - (-signals.max)) + 0;
		output_vector1[BLOCKSIZE_counter] = (uint32_t)((calculate_vector1[BLOCKSIZE_counter]+1)/2 * maxValueDAC + OFFSET );

	} //BLOCKSIZE for-Loop II



	// save current LUT index into signals1,
	for (int tmp_count = 0 ; tmp_count < signals.count; tmp_count++){
		signals1.current_LUT_Index[tmp_count] = signals.current_LUT_Index[tmp_count];
	}

}//Signal Synthesis


/** @brief generates a low frequency sine to be used for effects
 *  @param effect: struct which contains the parameter for the effect which want to use the LFO
 *
 */
void Signal_Synthesis_LFO(struct effects_LFO* effect) {

	float frequency = effect->frequency;
	uint8_t quarter = effect->quarter;
	uint32_t index = effect->index;
	uint32_t LFO_blocksizecounter = effect->lfo_blocksizecounter;

	// calculate ratio between LFO_LUT frequency and disired frequency
	float frequency_ratio = frequency / LFO_FMIN;

	//if(LFO_blocksizecounter == BLOCKSIZE) {
	if(LFO_blocksizecounter == BLOCKSIZE/2) {
		LFO_blocksizecounter = 0;
	}
	/*//DEBUG
	uint16_t BLOOCKSIZE_startIndex, BLOOCKSIZE_endIndex;
	if (outputBuffer_position == HALF_BLOCK){
		BLOOCKSIZE_startIndex = 0;
		BLOOCKSIZE_endIndex = (BLOCKSIZE/2);
	}
	else if(outputBuffer_position == FULL_BLOCK){
		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
		BLOOCKSIZE_endIndex  = BLOCKSIZE;
	}
	for(int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex; BLOCKSIZE_counter++) {	// DEBUG*/

		//for (int LFO_counter = 0; LFO_counter <BLOCKSIZE/2; LFO_counter++) {
		// check if end of LFO_LUT is reached, if yes then increment quarter and set index to zero
		if(index  > LFO_ENDINDEX[0]) {
			index = 0;
			quarter++;
			if (quarter > 3)
				quarter = 0;
		}

		switch(quarter) {
		case 0:
			//effect_LFO[LFO_counter] = LFO[index];
			effect_LFO[LFO_blocksizecounter] = LFO[index];	// DEBUG
			break;
		case 1:
			//effect_LFO[LFO_counter] = LFO[LFO_ENDINDEX[0] - index];
			effect_LFO[LFO_blocksizecounter] = LFO[LFO_ENDINDEX[0] - index];	// DEBUG
			break;
		case 2:
			//effect_LFO[LFO_counter] = -LFO[index];
			effect_LFO[LFO_blocksizecounter] = -LFO[index];	// DEBUG
			break;
		case 3:
			//effect_LFO[LFO_counter] = -LFO[LFO_ENDINDEX[0] - index];
			effect_LFO[LFO_blocksizecounter] = -LFO[LFO_ENDINDEX[0] - index];	// DEBUG
			break;
		default:
			break;
		} // end switch-case
		index = round((double)(index + frequency_ratio));

		//DEBUG
		//effect_LFO_output[BLOCKSIZE_counter] = (uint32_t)((effect_LFO[BLOCKSIZE_counter]+1)/2 * 3000 + 145);

	//} //BLOCKSIZE for-Loop I

	//LFO_blocksizecounter++;

	//save current state into given effect struct
	effect->lfo_blocksizecounter = LFO_blocksizecounter;
	effect->index = index;
	effect->quarter = quarter;
}


/** @brief generates a low frequency sine to be used for effects
 *  @param effect: struct which contains the parameter for the effect which want to use the LFO
 *
 */
/*void Signal_Synthesis_LFO(struct effects_LFO* effect) {

	float frequency = effect->frequency;
	uint8_t quarter = effect->quarter;
	uint32_t index = effect->index;

	// calculate ratio between LFO_LUT frequency and disired frequency
	float frequency_ratio = frequency /LFO_FMIN;

	//DEBUG
	uint16_t BLOOCKSIZE_startIndex, BLOOCKSIZE_endIndex;
	if (outputBuffer_position == HALF_BLOCK){
		BLOOCKSIZE_startIndex = 0;
		BLOOCKSIZE_endIndex = (BLOCKSIZE/2);
	}
	else if(outputBuffer_position == FULL_BLOCK){
		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
		BLOOCKSIZE_endIndex  = BLOCKSIZE;
	}
	for (int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex; BLOCKSIZE_counter++) {	// DEBUG

		//for (int LFO_counter = 0; LFO_counter <BLOCKSIZE/2; LFO_counter++){
		// check if end of LFO_LUT is reached, when yes increment qurter and set index to zero
		if ( index  > LFO_ENDINDEX[0]){
			index = 0;
			quarter++;
			if (quarter > 3)
				quarter = 0;
		}

		switch(quarter){
		case 0:
			//effect_LFO[LFO_counter] = LFO[index];
			effect_LFO[BLOCKSIZE_counter] = LFO[index];	// DEBUG
			break;
		case 1:
			//effect_LFO[LFO_counter] = LFO[(LFO_ENDINDEX[0] - index)];
			effect_LFO[BLOCKSIZE_counter] = LFO[(LFO_ENDINDEX[0] - index )];	// DEBUG
			break;
		case 2:
			//effect_LFO[LFO_counter] = -LFO[index];
			effect_LFO[BLOCKSIZE_counter] = -LFO[index];	// DEBUG
			break;
		case 3:
			//effect_LFO[LFO_counter] = -LFO[(LFO_ENDINDEX[0] - index)];
			effect_LFO[BLOCKSIZE_counter] = -LFO[(LFO_ENDINDEX[0] - index)];	// DEBUG
			break;
		default:
			break;
		} // end switch-case
		index = round((double)(index + frequency_ratio));

		//DEBUG
		effect_LFO_output[BLOCKSIZE_counter] = (uint32_t)((effect_LFO[BLOCKSIZE_counter]+1)/2 * 3000 + 145);

	} //BLOCKSIZE for-Loop I

	//save current state into given effect struct
	effect -> index = index;
	effect -> quarter = quarter;
}*/
