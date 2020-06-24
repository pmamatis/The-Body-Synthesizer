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


/** @brief lookuptable for note frequencies*/
const float notes[108] = {
16.35,		// C0
17.32,
18.35,
19.45,
20.6,
21.83,
23.12,
24.5,
25.96,
27.5,
29.14,
30.87,
32.7,		// C1
34.65,
36.71,
38.89,
41.2,
43.65,
46.25,
49,
51.91,
55,
58.27,
61.74,
65.41,		// C2
69.3,
73.42,
77.78,
82.41,
87.31,
92.5,
98,
103.83,
110,
116.54,
123.47,
130.81,		// C3
138.59,
146.83,
155.56,
164.81,
174.61,
185,
196,
207.65,
220,
233.08,
246.94,
261.63,		// C4
277.18,
293.66,
311.13,
329.63,
349.23,
369.99,
392,
415.3,
440,
466.16,
493.88,
523.25,		// C5
554.37,
587.33,
622.25,
659.25,
698.46,
739.99,
783.99,
830.61,
880,
932.33,
987.77,
1046.5,		// C6
1108.73,
1174.66,
1244.51,
1318.51,
1396.91,
1479.98,
1567.98,
1661.22,
1760,
1864.66,
1975.53,
2093,		// C7
2217.46,
2349.32,
2489.02,
2637.02,
2793.83,
2959.96,
3135.96,
3322.44,
3520,
3729.31,
3951.07,
4186.01,	// C8
4434.92,
4698.63,
4978.03,
5274.04,
5587.65,
5919.91,
6271.93,
6644.88,
7040,
7458.62,
7902.13};

/** @brief lookuptable for respective note keys*/
const char keys[26] = {'C','c','D','d','E','F','f','G','g','A','B','H','C','c','D','d','E','F','f','G','g','A','B','H','C','c'};
//                      C#      D#		        F#	    G#				    C#	    D#		    F#	    G#				    C#



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
	double note_freq =notes[tmp_octave+index];
	return note_freq;
}

/**@brief returns the frequency of a music note listed in the
 */
double Get_Note_Index(uint8_t index,uint8_t octave){
	int tmp_octave = 12*octave; //DEBUG
	double note_freq =notes[tmp_octave+index];
	return note_freq;
}

void Play_Note(char note, uint8_t octave,uint8_t channel){
	double freq = Get_Note_Frequency(Get_Keyindex(note), octave);
	Signal_Synthesis(1,SIN,freq);
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

	Signal_Synthesis(count-2,SIN,note_frequency[0],SIN,note_frequency[1]);
	Output_Signal(hdac, 1);
	count = count -2;
	Signal_Synthesis(count,SIN,note_frequency[2],SIN,note_frequency[3]);
	Output_Signal(hdac, 2);
}


