/*
 * sd_card.h
 *
 *  Created on: Jun 11, 2020
 *      Author: Marc Bielen
 */

#ifndef INC_SD_CARD_H_
#define INC_SD_CARD_H_

#include "fatfs.h"
#include "string.h"
#include <stdio.h>

// MOSI -> DI
// MISO -> DO

FATFS fs;  // file system
FIL fil; // File
FILINFO fno;
FRESULT fresult;  // result
char txtfile_array[40000];	// could be also higher if necessary
UINT br, bw;  // File read/write count
DIR dj;	// directory object

//**** capacity related
FATFS *pfs;
DWORD fre_clust;
uint32_t total, free_space;

#define BUFFER_SIZE 10	// should be bigger for even bigger files
char buffer[BUFFER_SIZE];  // to store strings..

int bufsize (char *buf);

void clear_buffer (void);	// clearing buffer to show that result obtained is from the file

void send_uart (char *string, UART_HandleTypeDef huart);

char* find_text_file (UART_HandleTypeDef huart);

void sd_card_mount(UART_HandleTypeDef huart);

void sd_card_unmount(UART_HandleTypeDef huart);

void sd_card_free_space(UART_HandleTypeDef huart);

void sd_card_write_newfile(char *filename, char *filecontent, UART_HandleTypeDef huart);

void sd_card_write_appendfile(char *filename, char *filecontent, UART_HandleTypeDef huart);

void sd_card_read(char *filename, float *LUT, UART_HandleTypeDef huart);

float sd_card_read_sample(char *filename);

void sd_card_remove_file(char *filename, UART_HandleTypeDef huart);

#endif /* INC_SD_CARD_H_ */
