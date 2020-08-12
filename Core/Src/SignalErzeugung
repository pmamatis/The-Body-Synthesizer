



/**
  ******************************************************************************
  * @file    SignalErzeugung.c
  * @author  Paul Mamatis
  * @date 	27 Apr 2020
  * @brief	Funktionsgenerator für HAL-Libary auf Nucleo-144 F4.....
  *
  *         Diese C-Datei beinhaltet die Funktionen zur Signalerzeugung von 1Hz bis 8000Hz.
  *         die Signale sind:
  *         * Sinus
  *         * Saegezahn
  *         * Dreieck
  *         * PWM
  *         * Addition sämtlicher aufgeführter Signale
  *
  *
  *
*/

#include "SignalErzeugung.h"

//Variablen



/** @brief Signal-Stützstellen für den oberen Frequenz-Bereich
136 Werte => maximale erreichbare Frequenz von 16 kHz mit Timer-Clock 108 Mhz*/




/** @briefMaximaler binärer Wert die der DAC darstellen soll, wird über AMPLITUDE eingestellt*/
double maximalwert_DAC = DAC_MAX;







/**@brief create the signal-support-points and starts the timer
 * @param htim: timer-handler which controls the DAC, timer have to be connected with DAC
 * @param hdac: is the DAC handler
 *@return gives HAL-Status of startet timer back
 */
HAL_StatusTypeDef SignalErzeugung_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac){

	// Berechnung der DAC Werte abhängig von der gewünschten Amplitude
	double tmp1 = AMPLITUDE; //DEBUG
	double tmp2 = DACmax_maxAmplitude_verhaeltnis; //DEBUG
	maximalwert_DAC = (double)DACmax_maxAmplitude_verhaeltnis * (double)AMPLITUDE;

	double sinf_halbe_offset, wt; //DEBUG

	// Erzeugung der Signal SUPPORT_POINTS

	for (int i =0; i < SUPPORT_POINTS; i++){
		//Sinus
		wt = i * normierung(SUPPORT_POINTS);
		sinTable_origin[i] = sin(wt);
		sinf_halbe_offset = (sinTable_origin[i]+1)*maximalwert_DAC/2; //DEBUG
		sinTable[i] = round(sinf_halbe_offset) + OFFSET;
		//Sägezahn
		saegezahnTable[i] = maximalwert_DAC/SUPPORT_POINTS*i + OFFSET;

		//Dreieck und PWM
		if (i<(SUPPORT_POINTS/2)){
			dreieckTable[i] = 2*i * maximalwert_DAC/SUPPORT_POINTS + OFFSET;
			PWMTable[i]= maximalwert_DAC+OFFSET;
		}
		else{
			dreieckTable[i] = 2*maximalwert_DAC-(2*i * maximalwert_DAC/SUPPORT_POINTS) + OFFSET;
			PWMTable[i]= OFFSET;
		}
	}
	//Starte Timer 8, ist verbunden mit DAC
	return HAL_TIM_Base_Start(&htim);
}



/** @brief Testfunktion, welche alle vier Signalarten über den DAC ausgibt
 * @param htim: ist der Timerhandler welcher den DAC steuert
 * @param hdac: ist der DAC handler
 *@return Die Funktion gibt den HAL Status des gestarteten DAC zurück
 */
uint8_t Test(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac){
	int return_var = -1;
		Output_Signal(hdac, htim, 1000, 0);
		HAL_Delay(2000);
		Output_Signal(hdac, htim, 1000, 1);
		HAL_Delay(2000);
		Output_Signal(hdac, htim, 1000, 2);
		HAL_Delay(2000);
		return_var = Output_Signal(hdac, htim, 1000, 3);
		HAL_Delay(2000);
		return return_var;
}



/**
 @brief erzeugt eine Array mit PWM Signal und gewünschtem Modulationsgrad alpha
 * 		  Muss vor dem Ausgeben oder addieren eines PWM-SIgnals aufgerufen werden,
 * 		   um einen MOdulationsgrad ungleich 0,5 zu erreichen
 * @param alpha: Modulationsgrad,  0 > alpha > 1
 */
void ChangePWMArray(float alpha){
	float modulation = 1-alpha;
	uint32_t modulierte_stuetzstellen = ceil((float)SUPPORT_POINTS*modulation);

	for (int i = 0 ; i < SUPPORT_POINTS ; i++){
		if (i < modulierte_stuetzstellen)
			PWMTable[i] = maximalwert_DAC*OFFSET;
		else
			PWMTable[i] = OFFSET;
	}
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
double SignaleAddieren(uint8_t count, ...){
		uint16_t freqMin = 8000;
		uint8_t  indexMin = 0;
		struct Signal Signale;
		va_list argumentlist;
		va_start(argumentlist, count);

		//Bestimmt die kleinste Frequenz und speichert alle Signale im Struct
		uint8_t tmpCount = count;
		while(tmpCount--){
			Signale.art[tmpCount] = va_arg(argumentlist, unsigned int);
			Signale.frequenz[tmpCount] = va_arg(argumentlist, double);
			if(Signale.frequenz[tmpCount] < freqMin){
				freqMin = Signale.frequenz[tmpCount];
				indexMin = tmpCount;
			}
		}

		double wt, sinf0,addValue,tmp;//DEBUG

		//Schleife um alle Einträge des Ziel-Arrays zu beschreiben
		for (int i = 0; i < SUPPORT_POINTS_ADD_SIG;i++){
			wt = i * normierung(SUPPORT_POINTS_ADD_SIG);
			addierterVektor[i] = 0;
			double addValueSIN = 0;
			double addValueSaegezahn = 0;
			double addValueDreieck = 0;
			double addValuePWM = 0;
				//Schleife um alle Signale an der i-ten Stelle des Ziel-Arrays aufzusummieren,
				for (int j = 0; j < count;j++){
						switch (Signale.art[j]) {
								case SIN:
//									sinf0 = sinTable[Signale.frequenz[j]/Signale.frequenz[indexMin]];
									sinf0 = sin(Signale.frequenz[j]/Signale.frequenz[indexMin]*wt); // Erzeugung des Sinus-Wertes abhängig von der kleinsten Frequenz
									addValueSIN = addValueSIN + (maximalwert_DAC/2 * (sinf0 + 1) + OFFSET); // Addierten-Wert auf gewünschte Amplitude bringen
									break;
								case SAEGEZAHN:
									tmp = (int)(Signale.frequenz[j]/Signale.frequenz[indexMin])*i; //Sägezahnwert durch beschleunigen des Counters abhängig von Frequenz bestimmen

									//Wenn der Wert größer als der Maximalwert des Counters ist, wieder bei 0 anfangen
									if (tmp > SUPPORT_POINTS)
										tmp = tmp - SUPPORT_POINTS;

									addValueSaegezahn = addValueSaegezahn + maximalwert_DAC/SUPPORT_POINTS*tmp + OFFSET;// Addierten-Wert auf gewünschte Amplitude bringen
									break;
								case DREIECK:
										addValueDreieck = addValueDreieck + dreieckTable[i*(int)(Signale.frequenz[j]/Signale.frequenz[indexMin])];//bereits erzeugtes Dreieck-Stützstellen-Array frequenzabängig durchgehen
									break;
								case PWM:
									//wird im gegensatz zu den anderen Signalen nur einmal addiert da es entweder Maximale Amplitude oder null ist
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
		addierterVektor[i] = addValue;
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
HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac, TIM_HandleTypeDef htim, double frequenz, uint8_t Signalart){
		uint16_t TimerIncrements=0;
		if (frequenz > 8000)
			frequenz=8000;
		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);

			//Frequenz über den Timer einstellen
		if (Signalart==ADDSIG)
			TimerIncrements = round(108000000/(SUPPORT_POINTS_ADD_SIG*frequenz));
		else
			TimerIncrements = round(108000000/(SUPPORT_POINTS*frequenz));

		__HAL_TIM_SET_AUTORELOAD(&htim,TimerIncrements);

			switch (Signalart) {
				case SIN:
					return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, sinTable, SUPPORT_POINTS, DAC_ALIGN_12B_R);
					break;
				case SAEGEZAHN:
					return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, saegezahnTable, SUPPORT_POINTS, DAC_ALIGN_12B_R);
					break;
				case DREIECK:
					return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, dreieckTable, SUPPORT_POINTS, DAC_ALIGN_12B_R);
					break;
				case PWM:
					return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, PWMTable, SUPPORT_POINTS, DAC_ALIGN_12B_R);
				case ADDSIG:
					return HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, addierterVektor, SUPPORT_POINTS_ADD_SIG, DAC_ALIGN_12B_R);
					break;
				default:
					return -1;
					break;
			}

}




