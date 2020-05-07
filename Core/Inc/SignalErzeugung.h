/**
  ******************************************************************************
  * @file    SignalErzeugung.c
  * @author  Paul Mamatis
  * @date 	27 Apr 2020
  * @brief	Funktionsgenerator für HAL-Libary auf Nucleo-144 F4.....
  *
  *         Diese H-Datei beinhaltet die wichtige voreinstellungen zur Signalerzeugung von 1Hz bis 8000Hz.
  *
  *@todo SIgnaladdierung testen, bzw fehler berechnen
  *
  *
*/


#ifndef INC_SIGNALERZEUGUNG_H_
#define INC_SIGNALERZEUGUNG_H_

#include <math.h>
#include "main.h"
#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>



//defines
/**@brief number of support points for the signal tables, needs to set also in the table arrays below*/
#define SUPPORT_POINTS  136
/**@brief number of support points for the add-signal tables, needs to set also in the table array below*/
#define SUPPORT_POINTS_ADD_SIG 2160
/**@brief maximale Amplitude der Signale in milli Volt*/
#define AMPLITUDE 	2000
/**@brief DAC wert für maximale Spannung(3,3V) */
#define DAC_MAX 	4095
 /** @brief 100mV */
#define OFFSET 		145
/**@brief 4096/3300 */
#define DACmax_maxAmplitude_verhaeltnis  1.24121212121212
/**@brief normiert die Stützsetellen auf 2*Pi */
#define normierung(stuetzstellen) 2*M_PI/stuetzstellen


/**@brief Signalarten zur eingabe in Funktionen*/
enum signalArt{
	SIN = 0,
	SAEGEZAHN,
	DREIECK,
	PWM,
	ADDSIG
};

/**@brief wird zur Signal addierung gebraucht*/
struct Signal{
	unsigned int art[10];
	double frequenz[10];
};

//Variables
/** @brief signal support point arrays*/
uint32_t sinTable[136];		  //Sinus
double sinTable_origin[136];	  //untouched Sinus
uint32_t saegezahnTable[136]; //Sägezhan
uint32_t dreieckTable[136];	  //Dreieck
uint32_t PWMTable[136];		  //PWM
/** @brief Array für addierte SIgnale*/
uint32_t addierterVektor[2160];



//Funktionen
HAL_StatusTypeDef SignalErzeugung_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac);
HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac, TIM_HandleTypeDef htim, double frequenz, uint8_t Signalart);
void ChangePWMArray(float alpha);
double SignaleAddieren(uint8_t count, ...);
uint8_t Test();



#endif /* INC_SIGNALERZEUGUNG_H_ */
