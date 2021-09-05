/*
 * sd_card.c
 *
 *  Created on: Jun 11, 2020
 *      Author: Marc Bielen
 */

#include "sd_card.h"

// UART functions for debugging
int bufsize (char *buf) {
	int i=0;
	while (*buf++ != '\0') i++;
	return i;
}

void clear_buffer (void) {
	for (int i=0; i<BUFFER_SIZE; i++) buffer[i] = '\0';
}

void send_uart (char *string, UART_HandleTypeDef huart) {
	uint8_t len = strlen (string);
	HAL_UART_Transmit(&huart, (uint8_t *) string, len, HAL_MAX_DELAY);  // transmit in blocking mode
}

char* find_text_file (UART_HandleTypeDef huart) {

	char txtfile_array_temp[100];

	fresult = f_findfirst(&dj, &fno, "", "*.txt");  // Start to search for text files

	while (fresult == FR_OK && fno.fname[0]) {         	// Repeat while an item is found

		strcpy(txtfile_array_temp, fno.fname);
		strcat(txtfile_array, txtfile_array_temp);
		send_uart (fno.fname, huart);					// Print the object name
		send_uart("\n\r", huart);
		fresult = f_findnext(&dj, &fno);               	// Search for next item
	}

	f_closedir(&dj);

	return txtfile_array;
}

void sd_card_mount(UART_HandleTypeDef huart) {	// Mount SD Card (Einbinden der SD-Karte)

	/*fresult = f_mount(&fs, "/", 1);
	if (fresult != FR_OK) send_uart ("ERROR!!! in mounting SD CARD...\n\r", huart);
	else send_uart("SD CARD MOUNTED successfully...\n\r", huart);

	clear_buffer();*/

	fresult = f_mount(&fs, "", 0);
	if(fresult != FR_OK)
		send_uart ("ERROR!!! in mounting SD CARD...\n\r", huart);
	else
		send_uart("SD CARD MOUNTED successfully...\n\r", huart);

	clear_buffer();
}

void sd_card_unmount(UART_HandleTypeDef huart) {	// Unmount SD Card

	fresult = f_mount(NULL, "/", 1);
	if (fresult == FR_OK) send_uart ("SD CARD UNMOUNTED successfully...\n\n\r", huart);

	clear_buffer();
}

void sd_card_free_space(UART_HandleTypeDef huart) {	// Check free space

	f_getfree("", &fre_clust, &pfs);

	total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	sprintf (buffer, "SD CARD Total Size: \t%lu\n\r",total);
	send_uart(buffer, huart);
	clear_buffer();

	free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
	sprintf (buffer, "SD CARD Free Space: \t%lu\n\r",free_space);
	send_uart(buffer, huart);
	clear_buffer();
}

void sd_card_write_newfile(char *filename, char *filecontent, UART_HandleTypeDef huart) {
	// FA_READ - Specifies read access to the object. Data can be read from the file.
	// FA_WRITE - Specifies write access to the object. Data can be written to the file. Combine with FA_READ for read-write access.
	// FA_OPEN_EXISTING - Opens the file. The function fails if the file is not existing. (Default)
	// FA_CREATE_NEW - Creates a new file. The function fails with FR_EXIST if the file is existing.
	// FA_CREATE_ALWAYS - Creates a new file. If the file is existing, it will be truncated and overwritten.
	// FA_OPEN_ALWAYS - Opens the file if it is existing. If not, a new file will be created.
	// FA_OPEN_APPEND - Same as FA_OPEN_ALWAYS except the read/write pointer is set end of the file.

	// Open file to write/ create a file if it doesn't exist
	fresult = f_open(&fil, filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
	if (fresult == FR_OK)
		send_uart ("File created and the data is written\n\r", huart);
	else
		send_uart ("File can not be created\n\r", huart);

	// Writing text
	f_puts(filecontent, &fil);

	// Close file
	fresult = f_close(&fil);

	if (fresult == FR_OK)
		send_uart ("File created and the data is written\n\r", huart);
	else
		send_uart ("File can not be created\n\r", huart);

	clear_buffer();
}

void sd_card_write_appendfile(char *filename, char *filecontent, UART_HandleTypeDef huart) {
	// FA_READ - Specifies read access to the object. Data can be read from the file.
	// FA_WRITE - Specifies write access to the object. Data can be written to the file. Combine with FA_READ for read-write access.
	// FA_OPEN_EXISTING - Opens the file. The function fails if the file is not existing. (Default)
	// FA_CREATE_NEW - Creates a new file. The function fails with FR_EXIST if the file is existing.
	// FA_CREATE_ALWAYS - Creates a new file. If the file is existing, it will be truncated and overwritten.
	// FA_OPEN_ALWAYS - Opens the file if it is existing. If not, a new file will be created.
	// FA_OPEN_APPEND - Same as FA_OPEN_ALWAYS except the read/write pointer is set end of the file.

	// Open file to write/ append data to end of file
	fresult = f_open(&fil, filename, FA_OPEN_APPEND | FA_READ | FA_WRITE);

	// Writing text
	f_puts(filecontent, &fil);

	// Close file
	fresult = f_close(&fil);

	if (fresult == FR_OK)	send_uart ("File created and the data is written\n\r", huart);

	clear_buffer();
}

void sd_card_read(char *filename, float *LUT, UART_HandleTypeDef huart) {
	// FA_READ - Specifies read access to the object. Data can be read from the file.
	// FA_WRITE - Specifies write access to the object. Data can be written to the file. Combine with FA_READ for read-write access.
	// FA_OPEN_EXISTING - Opens the file. The function fails if the file is not existing. (Default)
	// FA_CREATE_NEW - Creates a new file. The function fails with FR_EXIST if the file is existing.
	// FA_CREATE_ALWAYS - Creates a new file. If the file is existing, it will be truncated and overwritten.
	// FA_OPEN_ALWAYS - Opens the file if it is existing. If not, a new file will be created.
	// FA_OPEN_APPEND - Same as FA_OPEN_ALWAYS except the read/write pointer is set end of the file.

	// Open file to read
	fresult = f_open(&fil, filename, FA_READ);
	if (fresult == FR_OK)
		send_uart ("file is open and the data is shown below\n\r", huart);

	// Read data from the file - Please see the function details for the arguments

	uint32_t Cycles = (uint32_t)f_size(&fil) / BUFFER_SIZE; // 400
	uint32_t NoLength = 10;
	uint32_t NoSamples = 100;

	char SampleTemp[NoLength];

	for(int i = 0; i < Cycles; i++) {

		f_read (&fil, buffer, BUFFER_SIZE, &br);
		br = br + BUFFER_SIZE;

		for(int j = 0; j < NoSamples; j++) {

			for(int k = 0; k < NoLength; k++){

				SampleTemp[k] = buffer[j*NoLength+k];
			}
			LUT[i*NoSamples+j] = atof(SampleTemp)-1;
		}
	}

	// Close file
	f_close(&fil);

	// Clear buffer
	clear_buffer();
}

float sd_card_read_sample(char *filename) {
	// FA_READ - Specifies read access to the object. Data can be read from the file.
	// FA_WRITE - Specifies write access to the object. Data can be written to the file. Combine with FA_READ for read-write access.
	// FA_OPEN_EXISTING - Opens the file. The function fails if the file is not existing. (Default)
	// FA_CREATE_NEW - Creates a new file. The function fails with FR_EXIST if the file is existing.
	// FA_CREATE_ALWAYS - Creates a new file. If the file is existing, it will be truncated and overwritten.
	// FA_OPEN_ALWAYS - Opens the file if it is existing. If not, a new file will be created.
	// FA_OPEN_APPEND - Same as FA_OPEN_ALWAYS except the read/write pointer is set end of the file.

	// Open file to read
	fresult = f_open(&fil, filename, FA_READ);
	//	if (fresult == FR_OK)
	//		send_uart ("file is open and the data is shown below\n\r", huart);

	// Read data from the file - Please see the function details for the arguments
	uint32_t NoLength = 10;

	char SampleTemp[NoLength];

	f_read (&fil, buffer, NoLength, &br);
	br = br + NoLength;

	for(int k = 0; k < NoLength; k++){

		SampleTemp[k] = buffer[k];
	}

	// Close file
	f_close(&fil);

	// Clear buffer
	clear_buffer();

	return atof(SampleTemp)-1;
}

void sd_card_remove_file(char *filename, UART_HandleTypeDef huart) {

	strcat("/",filename);
	fresult = f_unlink(filename);
	if (fresult == FR_OK) {
		send_uart(filename, huart);
		send_uart(" removed successfully...\n\r", huart);
	}

	clear_buffer();
}
