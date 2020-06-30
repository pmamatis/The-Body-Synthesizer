



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

	// init calculate Vector with 0
//	for(int i = 0; i<BLOCKSIZE;i++){
//		calculate_vector[i] = 0;
//	}
	//Inits and starts timer connected with DAC
	__HAL_TIM_SET_AUTORELOAD(&htim,COUNTER_PERIOD);
	return HAL_TIM_Base_Start(&htim);
}





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
float Signal_Synthesis(uint8_t count, ...){


	lastIndex = 0;
	//Init for variable number of function input arguments
	struct signal signals;
	va_list argumentlist;
	va_start(argumentlist, count);

	//minimal frequency of the given signals, initialized with F_MAX
	double freqMin = F_MAX;

	uint8_t indexMin;
	//used to save the minimum and maximum of the caculate array
	float min=0;
	float max=0;

	//calculates the lowest frequency and saves the given signals in a struct
	uint8_t tmpCount = count;
	while(tmpCount--){ //first frequency is stored in signals[count]
		signals.kind[tmpCount] = va_arg(argumentlist, unsigned int);
		signals.freq[tmpCount] = va_arg(argumentlist, double);
//		signals.maxIndex[tmpCount] =LUT_Supportpoints[signals.freq[tmpCount]];

		if (signals.freq[tmpCount] > F_MAX)
			signals.freq[tmpCount] = F_MAX;

		if(signals.freq[tmpCount] < freqMin){
			freqMin = signals.freq[tmpCount];
			indexMin = tmpCount;
		}
	}

	float wt,addValue;
	uint16_t wt_max[count];


	//decide if first half of BLOCKSIZE or second half
	uint16_t BLOOCKSIZE_startIndex, BLOOCKSIZE_endIndex;

	if (outputBuffer_position == HALF_BLOCK){
		BLOOCKSIZE_startIndex = 0;
		BLOOCKSIZE_endIndex = BLOCKSIZE/2;

	}
	else if(outputBuffer_position == FULL_BLOCK){
		BLOOCKSIZE_startIndex = BLOCKSIZE/2;
		BLOOCKSIZE_endIndex  = BLOCKSIZE;
	}

//Loop to reach every array entry of calculate vector
	for (int BLOCKSIZE_counter = BLOOCKSIZE_startIndex; BLOCKSIZE_counter < BLOOCKSIZE_endIndex ;BLOCKSIZE_counter++){
	//Loop to reach all Signals
		for (int j = 0; j < count;j++){
			uint32_t index;
			switch (signals.kind[j]) {
			case SIN:
//					addValue = LUT[index];
					//v. 1.3
					// calculate the input argument for the sin-funktion
					//wt = (int)(signals.freq[j]/ F_MIN*i) % (BLOCKSIZE);
					//Get sin value
					//addValue = GetSin((int)(wt));
					break;
			case SAWTOOTH:
				//tmp = (int)(signals.freq[j]/SAMPLE_FREQ)*i;

			case TRIANGLE:

				break;
			case PWM:

				break;

			default:
				return -1;
				break;


			}

//			//write into calculate_vector
//			calculate_vector[i] = (calculate_vector[i]+ addValue);


//			//maximum
//			if (max < calculate_vector[i])
//				max = calculate_vector[i];
//			//minimum
//			if (min > calculate_vector[i])
//				min = calculate_vector[i];

		}

//	wt_max[j] = floor(BLOCKSIZE/(signals.freq[j]/ F_MIN));
	}
	//norm the signal to -1...1
//	for (int i = 0; i< BLOCKSIZE;i++){
//		calculate_vector[i] = calculate_vector[i]*(2/(max-min));
//	}

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

	va_end(argumentlist);
	return freqMin;
	}


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

