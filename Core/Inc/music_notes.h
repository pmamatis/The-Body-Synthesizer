/**
  ******************************************************************************
  * @file    music_notes.c
  * @author  Max Lehmer,Paul Mamatis
  * @date 	27 Apr 2020
  * @brief	Funktionsgenerator für HAL-Libary auf Nucleo-144 F4.....
  *
  *
  *
*/


#ifndef INC_MUSIC_NOTES_H_
#define INC_MUSIC_NOTES_H_

#include "main.h"

enum chord_type{
	fifth= 0,
	seventh,
	ninth,
};

enum sex_type{
	major=0,
	minor,
	diminished
};

const char keys[26];

uint8_t Get_Keyindex(char key);
double Get_Note_Frequency(uint8_t index,uint8_t octave);
uint16_t Get_Note_Index(char key,uint8_t octave);


#endif /* INC_MUSIC_NOTES_H_ */
