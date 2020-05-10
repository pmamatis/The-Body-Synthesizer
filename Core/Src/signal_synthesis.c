



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
double Signal_Synthesis(uint8_t count, ...){
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

		double wt, sinf0,addValue,tmp, wt_max;//DEBUG

		//Schleife um alle Einträge des Ziel-Arrays zu beschreiben
		for (int j = 0; j < count;j++){
			wt_max = SUPPORT_POINTS/(signals.freq[j]/SAMPLE_FREQ );
			double overflow = 0;

				for (int i = 0; i < SUPPORT_POINTS;i++){
					wt = i + overflow;
					if ( )
					wt = i * normierung(SUPPORT_POINTS);
//					double addValueSIN = 0;
//					double addValueSaegezahn = 0;
//					double addValueDreieck = 0;
//					double addValuePWM = 0;
						//Schleife um alle Signale an der i-ten Stelle des Ziel-Arrays aufzusummieren,

								switch (signals.kind[j]) {
										case SIN:

											wt = signals.freq[j]/SAMPLE_FREQ * 2*M_PI

											sinf0 = sin(); // Erzeugung des Sinus-Wertes abhängig von der kleinsten Frequenz
											addValueSIN = addValueSIN + (maximalwert_DAC/2 * (sinf0 + 1) + OFFSET); // Addierten-Wert auf gewünschte Amplitude bringen
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

				 }
		//normierung des Signals
		addValue =(addValueDreieck + addValuePWM + addValueSIN + addValueSaegezahn)/count; // auf Eins normieren
		output_vector[i] = addValue;
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

		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);

		return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, output_vector, SUPPORT_POINTS, DAC_ALIGN_12B_R);



}
