



#include "signal_synthesis.h"





/** @brief Maximaler binärer Wert die der DAC darstellen soll, wird über AMPLITUDE eingestellt*/
double maximalwert_DAC = DAC_MAX;




/**@brief starts the timer
 * @param htim: timer-handler which controls the DAC, timer have to be connected with DAC
 * @param hdac: is the DAC handler
 *@return gives HAL-Status of startet timer back
 */
HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac){

	// Berechnung der DAC Werte abhängig von der gewünschten Amplitude

	maximalwert_DAC = (double)DAC_MAXVALUE_TO_AMPLITUDE_RATIO * (double)AMPLITUDE;
	// Create Sin Table
//	float wt;
//	for(int i = 0; i<BLOCKSIZE;i++){
//		wt = i/(float)BLOCKSIZE* 2*M_PI;
//		sinTable[i] = sin(wt);
//	}
//	sinTable[BLOCKSIZE+1] = 0;
	// init calculate Vector with 0
	for(int i = 0; i<BLOCKSIZE;i++){
		calculate_vector[i] = 0;
	}
	//Starte Timer 8, ist verbunden mit DAC
	__HAL_TIM_SET_AUTORELOAD(&htim,COUNTER_PERIOD);
	return HAL_TIM_Base_Start(&htim);
}





/** @brief Addiert beliebig viele Signale und schreibt das Ergebnis in das Array addierterVektor,
 *  	   @attention die Signale müssen wie folgt aufgelistet werden  SignaleAddieren(count,Signalart_1,Frequenz_1,Signalart_2,Frequenz_2,...)
 * @param count: Anzahl zu addierender Signale
 * @param Signalart: @arg SIN
 * 		  			 @arg SAWTOOTH
 * 		  			 @arg TRIANGLE
 * 		  			 @arg PWM, standard ist alpha = 0.5. Wenn alpha etwas anderes betragen soll, muss zuerst ChangePWMArray(float alpha) ausgeführt werden
 * @param frequenz: Frequency of the Signal, have to be a double type
 *@return Die Funktion gibt den HAL Status des gestarteten DAC zurück

 */
float Signal_Synthesis(uint8_t count, ...){


	// init calculate Vector with 0
	lastIndex = 0;
	for(int i = 0; i<BLOCKSIZE+1;i++){
		calculate_vector[i] = 0;
	}

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

		if (signals.freq[tmpCount] > F_MAX)
			signals.freq[tmpCount] = F_MAX;

		if(signals.freq[tmpCount] < freqMin){
			freqMin = signals.freq[tmpCount];
			indexMin = tmpCount;
		}
	}

	//
	float wt,addValue
	uint16_t wt_max[count];

	//Loop to reach all Signals
	for (int j = 0; j < count;j++){

		//Loop to reach every array entry
		for (int i = 0; i < BLOCKSIZE+1;i++){

			switch (signals.kind[j]) {
			case SIN:
					// calculate the input argument for the sin-funktion
					wt = (int)(signals.freq[j]/ F_MIN*i) % (BLOCKSIZE);
					//Get sin value
					addValue = GetSin((int)(wt));
					break;
			case SAWTOOTH:
				tmp = (int)(signals.freq[j]/SAMPLE_FREQ)*i;

			case TRIANGLE:

				break;
			case PWM:

				break;

			default:
				return -1;
				break;


			}

			//write into calculate_vector
			calculate_vector[i] = (calculate_vector[i]+ addValue);


			//maximum
			if (max < calculate_vector[i])
				max = calculate_vector[i];
			//minimum
			if (min > calculate_vector[i])
				min = calculate_vector[i];

		}


	}
	//norm the signal to -1...1
	for (int i = 0; i< BLOCKSIZE;i++){
		calculate_vector[i] = calculate_vector[i]*(2/(max-min));
		watch = calculate_vector[i];

	}


	//calculate the end of one periode of the combined signal by finding the least common multiplier(LCM)
	uint16_t LCM = wt_max[indexMin];
	uint8_t isLCM = 0;
	int k = LCM;
	for (k; k < BLOCKSIZE;k++){
		isLCM = 0;

		for (int j = 0; j < count ;j++){
			if ((k % wt_max[j])==0){
				isLCM = isLCM + 1;
			}
		}

		// check if i is a LCM
		if (isLCM==count){
			LCM = k;
			break;
		}
	}

	//set lastIndex for the OutputSignal function
	if ( k == BLOCKSIZE && isLCM == 0 ){
		int i = BLOCKSIZE;
		while(i--){
			if ((calculate_vector[i-1]<= 0) && (calculate_vector[i]>=0)){
				lastIndex = i-1;
				break;
			}
		}
	}
	else{
		lastIndex = BLOCKSIZE - (BLOCKSIZE % LCM);
	}

	va_end(argumentlist);
	return freqMin;
	}


	/** @brief converts the calculate_vector into DAC friendly value and gives the signal via DAC out by using the Array output_vector1 and output_vector2
	 * @param hdac: handler of the DAC
	 * @param channel: DAC output channel
	 * 		@arg 1...Channel 1
	 * 		@arg 2...Channel 2
	 * @return gives back the status of the DAC
	 */
	HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac, uint8_t channel){

		for (int i = 0; i < BLOCKSIZE; i++){

			if (channel == 1){
			output_vector1[i] = (calculate_vector[i]+1) * maximalwert_DAC/2 + OFFSET ;
			}
			else if (channel == 2){
			output_vector2[i] = (calculate_vector[i]+1) * maximalwert_DAC/2 + OFFSET ;
			}
		}
		if (channel == 1){

		return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, output_vector1,lastIndex, DAC_ALIGN_12B_R);
		}
		else if (channel == 2){
				return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, output_vector2,lastIndex, DAC_ALIGN_12B_R);
		}
		else{
				return HAL_ERROR;
		}

	}



	void TEST(DAC_HandleTypeDef hdac){
		//10 ... 20 Hz
		for (int z=10; z < 20; z++){
			Signal_Synthesis(1,SIN,(float)z);
//			Output_Signal(hdac);
			HAL_Delay(10000);
		}
		//20 ...100
		for (int z=20; z < 100; z=z+10){
			Signal_Synthesis(1,SIN,(float)z);
//			Output_Signal(hdac);
			HAL_Delay(1000);
		}
		// 100... 1000
		for (int z=100; z < 1000; z=z+100){
			Signal_Synthesis(1,SIN,(double)z);
//			Output_Signal(hdac,1);
			HAL_Delay(1000);
		}
		// 1000... 4800
		for (int z=1000; z < 4800; z=z+500){
			Signal_Synthesis(1,SIN,(double)z);
//			Output_Signal(hdac);
			HAL_Delay(1000);
		}
		Signal_Synthesis(1,SIN,(double)4800);
//		Output_Signal(hdac);
		HAL_Delay(1000);
	}

