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

/** @brief lookuptable for respective note keys*/
const char keys[26] = {'C','c','D','d','E','F','f','G','g','A','B','H','C','c','D','d','E','F','f','G','g','A','B','H','C','c'};
//                      C#      D#		        F#	    G#				    C#	    D#		    F#	    G#				    C#



uint8_t Get_Keyindex(char key);
void Play_Note(char note, uint8_t octave, uint8_t channel);
double Get_Note_Frequency(uint8_t index,uint8_t octave);
void Play_Chord(char root_note,uint8_t sex, uint8_t octave, uint8_t chordtype);
uint16_t Get_Note_Index(char key,uint8_t octave);


#endif /* INC_MUSIC_NOTES_H_ */
