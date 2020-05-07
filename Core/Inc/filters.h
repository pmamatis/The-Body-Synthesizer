/**
  ******************************************************************************
  * @file    filters.h
  * @author  Max Lehmer
  * @date 	 07 May 2020
  * @brief	 Filter-Library
*/

#ifndef INC_FILTERS_H_
#define INC_FILTERS_H_

#include "main.h"

/*********************************
 * @parameter	Overall Blocksize
 *********************************/
#define BUFFERSIZE	2160
#define BLOCKSIZE 	32
#define NUM_TAPS	27

/***************************
 * Input and output buffers
 ***************************/
extern float32_t Input[BUFFERSIZE];
extern float32_t Output[BUFFERSIZE];

// your code here

#endif /* INC_MUSIC_NOTES_H_ */
