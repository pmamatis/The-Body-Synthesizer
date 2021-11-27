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
const char keys[26];

/** @brief minor/major tone scale in semi tone steps, according to the array keys*/
const uint32_t major_scale[9]; 	// {2,2,1,2,2,2,1}; Dur
const uint32_t minor_scale[9];	// {2,1,2,2,1,2,2}; Mol

/** @brief minor/major tone chords in semi tone steps, according to the array keys*/
const uint32_t major_chords[9];	// 0: major, 1: minor, 2: diminished
const uint32_t minor_chords[9];	// 0: major, 1: minor, 2: diminished

/** @brief chords, numbers give information of position in scale array(must be -1 if used directly) */
const uint32_t chord_5[3];		//5th-chord
const uint32_t chord_7[4];		//7th-chord, Jazz
const uint32_t chord_9[4];		//9th-chord, Math-Rock
const uint32_t chord_dim[3];	//diminished-chord

uint8_t Get_Keyindex(char key);
double Get_Note_Frequency(uint8_t index,uint8_t octave);
uint16_t Get_Note_Index(char key,uint8_t octave);


#endif /* INC_MUSIC_NOTES_H_ */
