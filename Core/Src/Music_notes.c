/**
  ******************************************************************************
  * @file    music_notes.c
  * @author  Max Lehmer,Paul Mamatis
  * @date 	27 Apr 2020
  * @brief	Music note synthesis for Nucleo-144 F4.....
  *			This C-file maps music notes to frequencies
  *
  *
  *
  *
*/

#include "music_notes.h"




/** @brief minor/major tone scale in semi tone steps, according to the array keys*/
const uint32_t major_scale[9] =  {0,2,4,5,7,9,11,12, 14}; 	// {2,2,1,2,2,2,1}; Dur
const uint32_t minor_scale[9] =  {0,2,3,5,7,8,10,12, 14};		// {2,1,2,2,1,2,2}; Mol


/** @brief minor/major tone chords in semi tone steps, according to the array keys*/
const uint32_t major_chords[9] = {0,1,1,0,0,1, 2, 0, 1}; 	// 0: major, 1: minor, 2: diminished
const uint32_t minor_chords[9] = {1,2,0,1,1,0, 0, 1, 2};	// 0: major, 1: minor, 2: diminished

/** @brief chords, numbers give information of position in scale array(must be -1 if used directly) */
const uint32_t chord_5[3] = {1,3,5};   //5th-chord
const uint32_t chord_7[4] = {1,3,5,7}; //7th-chord, Jazz
const uint32_t chord_9[4] = {1,3,5,9}; //9th-chord, Math-Rock
const uint32_t chord_dim[3] = {1,3,4};//diminished-chord



/** @brief extern variables */

extern DAC_HandleTypeDef hdac;
extern DMA_HandleTypeDef hdma_dac1;

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;


//variables

/** @brief music key*/
char key = 'C';
/** @brief key mode*/
uint8_t sex = 0;


//functions


/** @brief returns the index of a note-letter depending on the keys-array
 * 	@param key: note-letter e.g. C
 * 	@return key index
 * 	*/

uint8_t Get_Keyindex(char key){

	uint8_t keyindex = 0;

	for(int i = 0; i < 12; i++){
		if(key == keys[i]) keyindex = i;
	}
return keyindex;
}


/**@brief returns the frequency of a music note listed in the
 */
double Get_Note_Frequency(uint8_t index,uint8_t octave){
	int tmp_octave = 12*octave; //DEBUG
	double note_freq =LUT_FREQUENCYS[tmp_octave+index];
	return note_freq;
}

/**@brief returns the frequency of a music note listed in the
 */
uint16_t Get_Note_Index(char key,uint8_t octave){
	return 12*octave + Get_Keyindex(key);
}

void Play_Note(char note, uint8_t octave,uint8_t channel){
	double freq = Get_Note_Frequency(Get_Keyindex(note), octave);
//	Signal_Synthesis(1,SIN,freq);
	Output_Signal(hdac, channel);
}





void Play_Chord(char root_note,uint8_t sex,  uint8_t octave, uint8_t chordtype){

	// number of notes
	uint8_t count = 0;
	if (chordtype == fifth)
		 count = 3;
	else count = 4;

	//sex type
	uint8_t scale[9];
	if (sex == major){
		for (int i=0;i<9;i++)
			scale[i]=major_scale[i];
	}
	else {
		for (int i=0;i<9;i++)
			scale[i]=minor_scale[i];
	}
	double note_frequency[count];
	note_frequency[3] = 0;


	for (int i=0; i < count; i++){
		uint8_t scale_index, freq_index; //DEBUG
			switch(chordtype){
							case fifth:
								scale_index = chord_5[i]-1;
								freq_index = Get_Keyindex(root_note)+scale[scale_index];
								//freq_index = Get_Keyindex(tmp); //DEBUG
								note_frequency[i] = Get_Note_Frequency(freq_index, octave);
								  break;
							case seventh:
								note_frequency[i] = Get_Note_Frequency(Get_Keyindex(root_note+scale[chord_7[i]-1]), octave);
								  break;
							case ninth:
								note_frequency[i] = Get_Note_Frequency(Get_Keyindex(root_note+scale[chord_9[i]-1]), octave);
								  break;
			}
	}

//	Signal_Synthesis(count-2,SIN,note_frequency[0],SIN,note_frequency[1]);
	Output_Signal(hdac, 1);
	count = count -2;
//	Signal_Synthesis(count,SIN,note_frequency[2],SIN,note_frequency[3]);
	Output_Signal(hdac, 2);
}


