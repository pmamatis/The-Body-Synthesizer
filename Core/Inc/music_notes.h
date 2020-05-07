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
uint8_t Get_Keyindex(char key);
void Play_Note(char note, uint8_t octave);
double Get_Note_Frequency(uint8_t index,uint8_t octave);
void Play_Chord(char root_note,uint8_t sex, uint8_t octave, uint8_t chordtype);


#endif /* INC_MUSIC_NOTES_H_ */
