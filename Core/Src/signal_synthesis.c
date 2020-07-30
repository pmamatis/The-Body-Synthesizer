



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
	//Inits and starts timer connected with DAC
	SetTimerSettings(&htim, LUT_SR);
	return HAL_TIM_Base_Start(&htim);
}


/**@brief Init funtion for the Timer which triggers the DAC
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




void NewSignal(uint8_t kind, uint8_t key, uint8_t octave){

			if (signals1.count <= MAX_SIGNAL_KOMBINATION){
				signals1.count += 1;
				uint8_t index = signals1.count-1;

				signals1.kind[index] = kind;
				signals1.freq[index] = Get_Note_Frequency(Get_Keyindex(key), octave);
				signals1.freqIndex[index] = Get_Note_Index(key,octave);
				signals1.current_LUT_Index[index] = LUT_STARTINDEX[signals1.freqIndex[index]];
			}

}

void DeleteSignal(uint8_t signal_index){
	for (int delete_counter=signal_index; delete_counter < signals1.count;delete_counter++ ){
		signals1.current_LUT_Index[delete_counter] = signals1.current_LUT_Index[delete_counter+1] ;
		signals1.freq[delete_counter] = signals1.freq[delete_counter+1];
		signals1.freqIndex[delete_counter] = signals1.freqIndex[delete_counter+1];
		signals1.kind[delete_counter] = signals1.kind[delete_counter+1];
	}
	signals1.count-=1;
}

void Signal_Synthesis(){

	//Variables
		float addValue=0;
		float min = 1;
		float max = -1;
		uint8_t count;
		struct signal signals;
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

		if (outputBuffer_position == HALF_BLOCK){
			BLOOCKSIZE_startIndex = 0;
			BLOOCKSIZE_endIndex = (BLOCKSIZE/2)-1;
		}
		else if(outputBuffer_position == FULL_BLOCK){
			BLOOCKSIZE_startIndex = BLOCKSIZE/2;
			BLOOCKSIZE_endIndex  = BLOCKSIZE-1;
		}


		//Loop to reach every array entry of calculate vector
		for (int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex ;BLOCKSIZE_counter++){
				addValue = 0;
		//Loop to reach all Signals
//				uint32_t tmp_index = 0;
				for (int j = 0; j < count;j++){
					switch (signals.kind[j]) {
					case SIN:
//							tmp_index = LUT_STARTINDEX[signals.freqIndex[j]] + signals.current_LUT_Index[j];
							addValue = addValue + LUT[signals.current_LUT_Index[j]];
							//get index for the next sin value
							signals.current_LUT_Index[j]++;
							if (signals.current_LUT_Index[j] > LUT_ENDINDEX[signals.freqIndex[j]])
							{
								signals.current_LUT_Index[j] = LUT_STARTINDEX[signals1.freqIndex[j]];
							}
					break;
					}//Switch-Case
				}// SIgnal counter for-loop

				//Signal adjustment to DAC

				//maximum
				if (max < addValue)
					max = addValue;
				//minimum

				if (min > addValue)
					min = addValue;

//			//norm the signal to -1...1
			addValue = addValue/count;
//			addValue = addValue*(2/(max-min)); //vllt logarithmisch
			//Effekte


			//write into output vector
			output_vector1[BLOCKSIZE_counter] = (addValue+1) * maxValueDAC/2 + OFFSET ;
			} //BLOCKSIZE for-Loop


}//Signal Synthesis






/** @brief adds up to two signals and writes the result into calculate_vector
 *  	   @attention the signals have to be written in following order  Signal_Synthesis(count, kind of signal 1,(double)frequency_1, kind of signal 2,(double)frequency_2)
 * @param count: number of signals
 * @param kind of signal:@arg SIN
 * 		  			 	 @arg SAWTOOTH
 * 		  				 @arg TRIANGLE
 * 		  				 @arg PWM
 * @param  frequency: Frequency of the signal, have to be a double type
 *@return gives the lowest frequency back
 */
//void Signal_Synthesis(uint8_t count,uint8_t signal_composition,...){
//
//
////	lastIndex = 0;
////	//Init for variable number of function input arguments
//
//	va_list argumentlist;
//	va_start(argumentlist, signal_composition);
//	float addValue=0;
//	float min = 1;
//	float max = -1;
//
//
//	//minimal frequency of the given signals, initialized with F_MAX
//	double freqMin = F_MAX;
////
////	uint8_t indexMin;
////	//used to save the minimum and maximum of the caculate array
////	float min=0;
////	float max=0;
////
//	//calculates the lowest frequency and saves the given signals in a struct
//	uint8_t tmpCount = count;
//	while(tmpCount--){ //first frequency is stored in signals[count]
//
//		//Fetch information
//		if(signal_composition == note_key){
//			char key = va_arg(argumentlist, unsigned int);
//			uint8_t octave = va_arg(argumentlist, unsigned int);
//			signals.kind[tmpCount] = SIN;
//			signals.freq[tmpCount] = Get_Note_Frequency(Get_Keyindex(key), octave);
//			signals.freqIndex[tmpCount] = Get_Note_Index(key,octave);
//			signals.current_LUT_Index[tmpCount] = LUT_STARTINDEX[signals.freqIndex[tmpCount]];
//		}
//		else if(signal_composition == mixed){
//			signals.kind[tmpCount] = va_arg(argumentlist, unsigned int);
//			signals.freq[tmpCount] = va_arg(argumentlist, int);
////		signals.maxIndex[tmpCount] = LUT_SUPPORTPOINTS[signals.freq[tmpCount]];
//		}
//
//
//		if (signals.freq[tmpCount] > F_MAX)
//			signals.freq[tmpCount] = F_MAX;
//
//		if(signals.freq[tmpCount] < freqMin){
//			freqMin = signals.freq[tmpCount];
////			indexMin = tmpCount;
//		}
//	}
////
////	float wt,addValue;
////	uint16_t wt_max[count];
////
//	va_end(argumentlist);
//	//decide if first half of BLOCKSIZE or second half
//	uint16_t BLOOCKSIZE_startIndex, BLOOCKSIZE_endIndex;
//
//	if (outputBuffer_position == HALF_BLOCK){
//		BLOOCKSIZE_startIndex = 0;
//		BLOOCKSIZE_endIndex = (BLOCKSIZE/2)-1;
//
//	}
//	else if(outputBuffer_position == FULL_BLOCK){
//		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
//		BLOOCKSIZE_endIndex  = BLOCKSIZE-1;
//	}
//
////Loop to reach every array entry of calculate vector
//	for (int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex ;BLOCKSIZE_counter++){
//		addValue = 0;
//	//Loop to reach all Signals
//		for (int j = 0; j < count;j++){
//			switch (signals.kind[j]) {
//			case SIN:
//					//get current sin value
//					addValue = addValue + LUT[signals.current_LUT_Index[j]];
//
//					//get index for the next sin value
//					if (signals.current_LUT_Index[j] > LUT_ENDINDEX[signals.freqIndex[j]])
//					{
//						signals.current_LUT_Index[j] = LUT_STARTINDEX[signals.freqIndex[j]];
//					}
//					else
//					{
//						signals.current_LUT_Index[j]++;
//					}
//					//v. 1.3
//					// calculate the input argument for the sin-funktion
//					//wt = (int)(signals.freq[j]/ F_MIN*i) % (BLOCKSIZE);
//					//Get sin value
//					//addValue = GetSin((int)(wt));
//					break;
//			case SAWTOOTH:
//				//tmp = (int)(signals.freq[j]/SAMPLE_FREQ)*i;
//
//			case TRIANGLE:
//
//				break;
//			case PWM:
//
//				break;
//
//			default:
////				return -1;
//				break;
//
//
//			}
//
//
//
//		}// SIgnal counter for-loop
//
//
//		//Signal adjustment to DAC
//
//		//maximum
//		if (max < addValue)
//			max = addValue;
//		//minimum
//		if (min > addValue)
//			min = addValue;
//
////norm the signal to -1...1
//	addValue = addValue*(2/(max-min));
//
//	//write into output vector
//	output_vector1[BLOCKSIZE_counter] = (addValue+1) * maxValueDAC/2 + OFFSET ;
//	} //BLOCKSIZE for-Loop
//
//
//}

// v.1.3

//	//calculate the end of one periode of the combined signal by finding the least common multiplier(LCM)
//	uint16_t LCM = wt_max[indexMin];
//	uint8_t isLCM = 0;
//	int k = LCM;
//	for (k; k < BLOCKSIZE;k++){
//		isLCM = 0;
//
//		for (int j = 0; j < count ;j++){
//			if ((k % wt_max[j])==0){
//				isLCM = isLCM + 1;
//			}
//		}
//
//		// check if i is a LCM
//		if (isLCM==count){
//			LCM = k;
//			break;
//		}
//	}
//
//	//set lastIndex for the OutputSignal function
//	if ( k == BLOCKSIZE && isLCM == 0 ){
//		int i = BLOCKSIZE;
//		while(i--){
//			if ((calculate_vector[i-1]<= 0) && (calculate_vector[i]>=0)){
//				lastIndex = i-1;
//				break;
//			}
//		}
//	}
//	else{
//		lastIndex = BLOCKSIZE - (BLOCKSIZE % LCM);
//	}
//
//	//BUG-Fix
//	if ((count == 1) && ((freqMin==5 )||(freqMin==4800))){
//		lastIndex = BLOCKSIZE;
//	}

//	va_end(argumentlist);
////	return freqMin;
//	}


	/** @brief converts the calculate_vector into DAC friendly value and gives the signal via DAC out by using the Array output_vector1 and output_vector2
	 * @param hdac: handler of the DAC
	 * @param channel: DAC output channel
	 * 		@arg 1 ,Channel 1
	 * 		@arg 2 ,Channel 2
	 * @return gives back the status of the DAC
	 */
//	HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac, uint8_t channel){
//
//		for (int i = 0; i < BLOCKSIZE; i++){
//
//			if (channel == 1){
//			output_vector1[i] = (calculate_vector[i]+1) * maxValueDAC/2 + OFFSET ;
//			}
//			else if (channel == 2){
//			output_vector2[i] = (calculate_vector[i]+1) * maxValueDAC/2 + OFFSET ;
//			}
//		}
//		if (channel == 1){
//
//		return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, output_vector1,lastIndex, DAC_ALIGN_12B_R);
//		}
//		else if (channel == 2){
//				return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, output_vector2,lastIndex, DAC_ALIGN_12B_R);
//		}
//		else{
//				return HAL_ERROR;
//		}
//
//	}



//	void TEST(DAC_HandleTypeDef hdac){
//		//10 ... 20 Hz
//		for (int z=10; z < 20; z++){
//			Signal_Synthesis(1,SIN,(float)z);
////			Output_Signal(hdac);
//			HAL_Delay(10000);
//		}
//		//20 ...100
//		for (int z=20; z < 100; z=z+10){
//			Signal_Synthesis(1,SIN,(float)z);
////			Output_Signal(hdac);
//			HAL_Delay(1000);
//		}
//		// 100... 1000
//		for (int z=100; z < 1000; z=z+100){
//			Signal_Synthesis(1,SIN,(double)z);
////			Output_Signal(hdac,1);
//			HAL_Delay(1000);
//		}
//		// 1000... 4800
//		for (int z=1000; z < 4800; z=z+500){
//			Signal_Synthesis(1,SIN,(double)z);
////			Output_Signal(hdac);
//			HAL_Delay(1000);
//		}
//		Signal_Synthesis(1,SIN,(double)4800);
////		Output_Signal(hdac);
//		HAL_Delay(1000);
//	}

