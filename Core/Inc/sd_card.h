/** TODO
 * @file sd_card.h
 * @author ??????
 * @brief sd card acces
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @defgroup SDcard SD-Card 
 * @brief SD-Card software
 * @{
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

#define BUFFER_SIZE 1000	// should be bigger for even bigger files
char buffer[BUFFER_SIZE];  // to store strings..

int bufsize (char *buf);

void clear_buffer (void);	// clearing buffer to show that result obtained is from the file

void send_uart (char *string, UART_HandleTypeDef huart);

char* find_text_file (UART_HandleTypeDef huart);

void sd_card_mount(void);

void sd_card_unmount(void);

void sd_card_free_space(UART_HandleTypeDef huart);

void sd_card_write_newfile(char *filename, char *filecontent, UART_HandleTypeDef huart);

void sd_card_write_appendfile(char *filename, char *filecontent, UART_HandleTypeDef huart);

void sd_card_read(char *filename, float *LUT);

void sd_card_remove_file(char *filename, UART_HandleTypeDef huart);

/** @} */
#endif /* INC_SD_CARD_H_ */
