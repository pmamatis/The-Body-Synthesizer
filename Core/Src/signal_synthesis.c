



#include "signal_synthesis.h"





/** @briefMaximaler binärer Wert die der DAC darstellen soll, wird über AMPLITUDE eingestellt*/
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
	float wt;
	for(int i = 0; i<BLOCKSIZE;i++){
		wt = i/(float)BLOCKSIZE* 2*M_PI;
		sinTable[i] = sin(wt);
	}
	sinTable[BLOCKSIZE+1] = 0;
	// init calculate Vector with 0
	for(int i = 0; i<BLOCKSIZE;i++){
		calculate_vector[i] = 0;
	}
	//Starte Timer 8, ist verbunden mit DAC
	__HAL_TIM_SET_AUTORELOAD(&htim,COUNTER_PERIOD);
	return 1;
}





/** @brief Addiert beliebig viele Signale und schreibt das Ergebnis in das Array addierterVektor,
 *  	   @attention die Signale müssen wie folgt aufgelistet werden  SignaleAddieren(count,Signalart_1,Frequenz_1,Signalart_2,Frequenz_2,...)
 * @param count: Anzahl zu addierender Signale
 * @param Signalart: @li SIN
 * 		  			 @li SAEGEZAHN
 * 		  			 @li DREIECK
 * 		  			 @li PWM, standard ist alpha = 0.5. Wenn alpha etwas anderes betragen soll, muss zuerst ChangePWMArray(float alpha) ausgeführt werden
 * @param frequenz: Frequency of the Signal, have to be a double type
 *@return Die Funktion gibt den HAL Status des gestarteten DAC zurück

 */
float Signal_Synthesis(uint8_t count, ...){


	// init calculate Vector with 0
	lastIndex = 0;
	for(int i = 0; i<BLOCKSIZE+1;i++){
		calculate_vector[i] = 0;
	}

	float freqMin = 8000;
	struct signal signals;
	va_list argumentlist;
	va_start(argumentlist, count);
	uint8_t indexMin;
	//used to save the minimum and maximum of the caculate array
	float min=0;
	float max=0;

	//Bestimmt die kleinste Frequenz und speichert alle Signale im Struct
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
	float wt, sinf0,addValue,tmp, tmp1, tmp2,tmp3,tmp4;//DEBUG
	//	tmp1 = (float)SAMPLE_FREQ; //DEBUG
	uint16_t wt_max[count];

	//Loop to reach all Signals
	for (int j = 0; j < count;j++){


		//		sigFreq_sampleFreq_ratio = signals.freq[j]/tmp1;

		//metode 2
		wt_max[j] = floor(BLOCKSIZE/(signals.freq[j]/ F_MIN));
		//lastIndex = BLOCKSIZE-(BLOCKSIZE % wt_max);
		//Loop for the Array
		for (int i = 0; i < BLOCKSIZE+1;i++){

			switch (signals.kind[j]) {
			case SIN:
				// methode 1
				//				wt = (int)(signals.freq[j]/ F_MIN*i) % (BLOCKSIZE);
				//				addValue = sinTable[(int)(wt)];

				//metode 2
				tmp = (i % wt_max[j]);
				wt = (tmp/wt_max[j]) * 2*M_PI;
				sinf0 = sin(wt); // Erzeugung des Sinus-Wertes abhängig von der kleinsten Frequenz
				addValue = sinf0;

				break;
			case SAWTOOTH:
				tmp = (int)(signals.freq[j]/SAMPLE_FREQ)*i; //Sägezahnwert durch beschleunigen des Counters abhängig von Frequenz bestimmen

				//Wenn der Wert größer als der Maximalwert des Counters ist, wieder bei 0 anfangen
				//									if (tmp > BLOCKSIZE)
				//										tmp = tmp - BLOCKSIZE;
				//
				//									addValueSaegezahn = addValueSaegezahn + maximalwert_DAC/BLOCKSIZE*tmp + OFFSET;// Addierten-Wert auf gewünschte Amplitude bringen
				//									break;
				//								case DREIECK:
				//										addValueDreieck = addValueDreieck + dreieckTable[i*(int)(Signale.frequenz[j]/Signale.frequenz[indexMin])];//bereits erzeugtes Dreieck-Stützstellen-Array frequenzabängig durchgehen
				//									break;
				//								case PWM:
				//									//	wird im gegensatz zu den anderen Signalen nur einmal addiert da es entweder Maximale Amplitude oder null ist
				//									double tmp = PWMTable[i*(int)(Signale.frequenz[j]/Signale.frequenz[indexMin]]);
				//									if (tmp){
				//									addValuePWM = PWMTable[i*(int)(Signale.frequenz[j]/Signale.frequenz[indexMin])];//bereits erzeugtes PWM-Stützstellen-Array frequenzabängig durchgehen
				//									}
				break;
			default:
				return -1;
				break;


			}
			calculate_vector[i] = (calculate_vector[i]+ addValue);// max min auf infinity und -infinity
			//maximum
			if (max < calculate_vector[i])
				max = calculate_vector[i];
			//minimum
			if (min > calculate_vector[i])
				min = calculate_vector[i];



			//methode 1
			//			if (calculate_vector[i] == 0){
			//				lastIndex = i;
			//			}

		}


		//norminate the siganl to -1...1

		//addValue =(addValueDreieck + addValuePWM + addValueSIN + addValueSaegezahn)/count; // auf Eins normieren


	}
	//norm the signal to -1...1
	for (int i = 0; i< BLOCKSIZE;i++){
		calculate_vector[i] = calculate_vector[i]*(2/(max-min));
		//		calculate_vector[i] = calculate_vector[i]*1/count;
	}


	//calculate the end of one periode of the combined signal by finding the least common multiplier(LCM)
	uint16_t LCM = wt_max[indexMin];
	uint8_t isLCM = 0;
	for (int i = LCM; i < BLOCKSIZE;i++){
		isLCM = 0;

		for (int j = 0; j < count ;j++){
			if ((i % wt_max[j])==0){
				isLCM = isLCM + 1;
			}
		}

		// check if i is a LCM
		if (isLCM==count){
			LCM = i;
			break;
		}
	}

	if (LCM > BLOCKSIZE){
		return -1;
	}

	//set lastIndex for the OutputSignal function
	lastIndex = BLOCKSIZE - (BLOCKSIZE % LCM);
	va_end(argumentlist);
	return freqMin;
}


/** @brief lässt den DAC via DMA entweder ein Sinus, Dreieck, oder Saegezahnsiganl asgeben
 * @param hdac: ist der DAC handler
 * @param htim: ist der Timerhandler welcher den DAC steuert
 * @param frequenz: ist die frequenz des Ausgabe Signals
 * @param  Signalart:@li SIN
 * 		  			 @li SAEGEZAHN
 * 		  			 @li DREIECK
 * 		  			 @li PWM, standard ist alpha = 0.5. Wenn alpha etwas anderes betragen soll, muss zuerst ChangePWMArray(float alpha) ausgeführt werden
 *@return Die Funktion gibt den HAL Status des gestarteten DAC zurück

 */
HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac){
	//uint32_t output_vector[BLOCKSIZE+39];
	uint32_t length = lastIndex;
	//	HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
	float tmp, tmp2;
	uint32_t tmp3 ;
	for (int i = 0; i < BLOCKSIZE; i++){


		tmp = calculate_vector[i]+1;
		tmp2 = tmp * maximalwert_DAC/2 ;
		tmp3 = tmp2 +OFFSET;
		output_vector[i] = (calculate_vector[i]+1) * maximalwert_DAC/2 + OFFSET;
	}
	//HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
	return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, output_vector,length, DAC_ALIGN_12B_R);
}

void TEST(DAC_HandleTypeDef hdac){
	//10 ... 20 Hz
	for (int z=10; z < 20; z++){
		Signal_Synthesis(1,SIN,(float)z);
		Output_Signal(hdac);
		HAL_Delay(10000);
	}
	//20 ...100
	for (int z=20; z < 100; z=z+10){
		Signal_Synthesis(1,SIN,(float)z);
		Output_Signal(hdac);
		HAL_Delay(1000);
	}
	// 100... 1000
	for (int z=100; z < 1000; z=z+100){
		Signal_Synthesis(1,SIN,(double)z);
		Output_Signal(hdac);
		HAL_Delay(1000);
	}
	// 1000... 4800
	for (int z=1000; z < 4800; z=z+500){
		Signal_Synthesis(1,SIN,(double)z);
		Output_Signal(hdac);
		HAL_Delay(1000);
	}
	Signal_Synthesis(1,SIN,(double)4800);
	Output_Signal(hdac);
	HAL_Delay(1000);
}

