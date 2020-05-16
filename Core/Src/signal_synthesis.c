



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

	//Starte Timer 8, ist verbunden mit DAC
	__HAL_TIM_SET_AUTORELOAD(&htim,COUNTER_PERIOD);
	return HAL_TIM_Base_Start(&htim);
}





/** @brief Addiert beliebig viele Signale und schreibt das Ergebnis in das Array addierterVektor,
 *  	   @attention die Signale müssen wie folgt aufgelistet werden  SignaleAddieren(count,Signalart_1,Frequenz_1,Signalart_2,Frequenz_2,...)
 * @param count: Anzahl zu addierender Signale
 * @param Signalart: @li SIN
 * 		  			 @li SAEGEZAHN
 * 		  			 @li DREIECK
 * 		  			 @li PWM, standard ist alpha = 0.5. Wenn alpha etwas anderes betragen soll, muss zuerst ChangePWMArray(float alpha) ausgeführt werden
  * @param frequenz: Frequenz des Signals welches direkt davor steht
 *@return Die Funktion gibt den HAL Status des gestarteten DAC zurück

 */
float Signal_Synthesis(uint8_t count, ...){
		uint16_t freqMin = 8000;
		struct signal signals;
		va_list argumentlist;
		va_start(argumentlist, count);
	    uint8_t indexMin;

		//Bestimmt die kleinste Frequenz und speichert alle Signale im Struct
		uint8_t tmpCount = count;
		while(tmpCount--){
			signals.kind[tmpCount] = va_arg(argumentlist, unsigned int);
			signals.freq[tmpCount] = va_arg(argumentlist, double);

			if (signals.freq[tmpCount] > 8000)
				signals.freq[tmpCount] = 8000;

			if(signals.freq[tmpCount] < freqMin){
				freqMin = signals.freq[tmpCount];
				indexMin = tmpCount;
			}
		}

		//
		float wt, sinf0,addValue,tmp, tmp1;//DEBUG
		tmp1 = (float)SAMPLE_FREQ; //DEBUG
		//Loop to reach all Signals
		for (int j = 0; j < count;j++){
			sigFreq_sampleFreq_ratio = signals.freq[j]/tmp1;
			int wt_max = round(SUPPORT_POINTS/(sigFreq_sampleFreq_ratio));
			lastIndex = wt_max * sigFreq_sampleFreq_ratio;

				//Loop for the Array
				for (int i = 0; i < SUPPORT_POINTS;i++){

								switch (signals.kind[j]) {
										case SIN:
										    tmp = (i % wt_max);
											wt = (tmp/wt_max) * 2*M_PI;
											sinf0 = sin(wt); // Erzeugung des Sinus-Wertes abhängig von der kleinsten Frequenz
											addValue = sinf0;
//											addValueSIN = addValueSIN + (maximalwert_DAC/2 * (sinf0 + 1) + OFFSET); // Addierten-Wert auf gewünschte Amplitude bringen
											break;
										case SAWTOOTH:
											tmp = (int)(signals.freq[j]/SAMPLE_FREQ)*i; //Sägezahnwert durch beschleunigen des Counters abhängig von Frequenz bestimmen

											//Wenn der Wert größer als der Maximalwert des Counters ist, wieder bei 0 anfangen
		//									if (tmp > SUPPORT_POINTS)
		//										tmp = tmp - SUPPORT_POINTS;
		//
		//									addValueSaegezahn = addValueSaegezahn + maximalwert_DAC/SUPPORT_POINTS*tmp + OFFSET;// Addierten-Wert auf gewünschte Amplitude bringen
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
				calculate_vector[i] = addValue;

				 }
		//normierung des Signals
		//addValue =(addValueDreieck + addValuePWM + addValueSIN + addValueSaegezahn)/count; // auf Eins normieren

		}

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
		uint32_t output_vector[SUPPORT_POINTS];
		uint8_t index[1000];
		int j = 0;
		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);

		for (int i = 0; i < SUPPORT_POINTS; i++){
			output_vector[i] = (calculate_vector[i]+1) * maximalwert_DAC/2 + OFFSET ;

			if (output_vector[i] > (maximalwert_DAC + OFFSET) ){
				index[j] = i;
				j++;
		}
		}

		return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, output_vector, lastIndex, DAC_ALIGN_12B_R);



}
