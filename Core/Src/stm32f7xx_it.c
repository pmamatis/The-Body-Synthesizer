/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f7xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

//extern ADC_HandleTypeDef hadc3;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

volatile uint8_t FatFsCnt = 0;
volatile uint8_t Timer1, Timer2;

void SDTimer_Handler(void) {
	if(Timer1 > 0)
		Timer1--;

	if(Timer2 > 0)
		Timer2--;
}

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_dac1;
extern DMA_HandleTypeDef hdma_dac2;
extern DMA_HandleTypeDef hdma_spi4_rx;
extern DMA_HandleTypeDef hdma_spi4_tx;
extern SPI_HandleTypeDef hspi4;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void)
{
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
		/* USER CODE END W1_MemoryManagement_IRQn 0 */
	}
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void)
{
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_BusFault_IRQn 0 */
		/* USER CODE END W1_BusFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void)
{
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_UsageFault_IRQn 0 */
		/* USER CODE END W1_UsageFault_IRQn 0 */
	}
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/*FatFsCnt++;
	if(FatFsCnt >= 10) {
		FatFsCnt = 0;
		SDTimer_Handler();
	}*/

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles DMA1 stream5 global interrupt.
 */
void DMA1_Stream5_IRQHandler(void)
{
	/* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

	/* USER CODE END DMA1_Stream5_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_dac1);
	/* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

	/* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
 * @brief This function handles DMA1 stream6 global interrupt.
 */
void DMA1_Stream6_IRQHandler(void)
{
	/* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

	/* USER CODE END DMA1_Stream6_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_dac2);
	/* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

	/* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
 * @brief This function handles ADC1, ADC2 and ADC3 global interrupts.
 */
void ADC_IRQHandler(void)
{
	/* USER CODE BEGIN ADC_IRQn 0 */

	/* USER CODE END ADC_IRQn 0 */
	HAL_ADC_IRQHandler(&hadc1);
	HAL_ADC_IRQHandler(&hadc2);
	HAL_ADC_IRQHandler(&hadc3);
	/* USER CODE BEGIN ADC_IRQn 1 */

	/* USER CODE END ADC_IRQn 1 */
}

/**
 * @brief This function handles EXTI line[9:5] interrupts.
 */
void EXTI9_5_IRQHandler(void)
{
	/* USER CODE BEGIN EXTI9_5_IRQn 0 */

	/* USER CODE END EXTI9_5_IRQn 0 */
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
	/* USER CODE BEGIN EXTI9_5_IRQn 1 */

	/* USER CODE END EXTI9_5_IRQn 1 */
}

/**
 * @brief This function handles TIM1 break interrupt and TIM9 global interrupt.
 */
void TIM1_BRK_TIM9_IRQHandler(void)
{
	/* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 0 */

	/* USER CODE END TIM1_BRK_TIM9_IRQn 0 */
	HAL_TIM_IRQHandler(&htim1);
	/* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 1 */

	/* USER CODE END TIM1_BRK_TIM9_IRQn 1 */
}

/**
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler(void)
{
	/* USER CODE BEGIN TIM2_IRQn 0 */

	/* USER CODE END TIM2_IRQn 0 */
	HAL_TIM_IRQHandler(&htim2);
	/* USER CODE BEGIN TIM2_IRQn 1 */

	/* USER CODE END TIM2_IRQn 1 */
}

/**
 * @brief This function handles TIM3 global interrupt.
 */
void TIM3_IRQHandler(void)
{
	/* USER CODE BEGIN TIM3_IRQn 0 */
	II_Display_Voices();
	II_Display_Effects();

	/* USER CODE END TIM3_IRQn 0 */
	HAL_TIM_IRQHandler(&htim3);
	/* USER CODE BEGIN TIM3_IRQn 1 */

	/* USER CODE END TIM3_IRQn 1 */
}

/**
 * @brief This function handles TIM4 global interrupt.
 */
void TIM4_IRQHandler(void)
{
	/* USER CODE BEGIN TIM4_IRQn 0 */

	/* USER CODE END TIM4_IRQn 0 */
	HAL_TIM_IRQHandler(&htim4);
	/* USER CODE BEGIN TIM4_IRQn 1 */

	/* USER CODE END TIM4_IRQn 1 */
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
void EXTI15_10_IRQHandler(void)
{
	/* USER CODE BEGIN EXTI15_10_IRQn 0 */

	/* USER CODE END EXTI15_10_IRQn 0 */
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	/* USER CODE BEGIN EXTI15_10_IRQn 1 */

	/* USER CODE END EXTI15_10_IRQn 1 */
}

/**
 * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
 */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	/* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */

	/* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
	HAL_TIM_IRQHandler(&htim8);
	/* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

	/* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/**
 * @brief This function handles TIM5 global interrupt.
 */
void TIM5_IRQHandler(void)
{
	/* USER CODE BEGIN TIM5_IRQn 0 */
	//	tim5_counter++;
	//	if(tim5_counter == 500){
	//			printf("%i\r\n",HAL_GetTick());
	//			time = HAL_GetTick();
	//			tim5_counter = 0;
	//	}

	/* USER CODE END TIM5_IRQn 0 */
	HAL_TIM_IRQHandler(&htim5);
	/* USER CODE BEGIN TIM5_IRQn 1 */

	//HAL_ADC_Start_DMA(KEYBOARD_ADC, &keyboard_adc_value, 1);
	HAL_ADC_Start_DMA(KEYBOARD_ADC, &Display.ADC1input, 1);

	/* USER CODE END TIM5_IRQn 1 */
}

/**
 * @brief This function handles TIM7 global interrupt.
 */
void TIM7_IRQHandler(void)
{
	/* USER CODE BEGIN TIM7_IRQn 0 */

	/* USER CODE END TIM7_IRQn 0 */
	HAL_TIM_IRQHandler(&htim7);
	/* USER CODE BEGIN TIM7_IRQn 1 */
	//  HAL_SPI_TransmitReceive_IT(&SensorSPI, pTxData, pRxData, sizeof(sensor_data_t));
	//  HAL_SPI_Receive(&hspi4, pRxData, sizeof(sensor_data_t), 100);
	HAL_SPI_TransmitReceive(hSensorSPI, pTxData, pRxData, sizeof(sensor_data_t),100);

	__disable_irq();
	memcpy(&sensorData,&pRxData, sizeof(sensor_data_t));
	__enable_irq();

	if (sensorData.gyro_initilized == 1)
		HAL_GPIO_WritePin(Blue_User_LED_GPIO_Port, Blue_User_LED_Pin, GPIO_PIN_SET);
	else if(sensorData.gyro_initilized != 1)
		HAL_GPIO_WritePin(Blue_User_LED_GPIO_Port, Blue_User_LED_Pin, GPIO_PIN_RESET);

	//	printf("******\r\n");
	//
	//
	//	for (int i = 0; i<sizeof(sensor_data_t);i++){
	//		printf("%i,",pRxData[i]);
	//	}
	//
	//	printf("\r\n");
	//		printf("gyro init: %i\r\n",sensorData.gyro_initilized);
	//		printf("tilt: %i\r\n",sensorData.tilt_detected);
	//	printf("\r\n");
	//	printf("\r\n");

	/* USER CODE END TIM7_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream0 global interrupt.
 */
void DMA2_Stream0_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

	//OnePress_keyboard_process(keyboard_adc_value, &signals1, &envelope);
	//	if(Display.mode == KEYBOARD)


	// Key Release Sensing
	if(Display.ADC1input <= NO_KEY_ADC_VALUE) {

		if(keyboard_pressed_counter%2==0)
			keyboard_pressed_counter++;
	}
	// Key Press Sensing
	else if (Display.ADC1input > NO_KEY_ADC_VALUE){

		if(keyboard_pressed_counter%2==1)
			keyboard_pressed_counter++;
	}

	// Reset counter
	if (keyboard_pressed_counter == 11)
		keyboard_pressed_counter = 1;

	// Activate Processing
	if (keyboard_pressed_counter == 2)
		activate_processing[0] = true;
	if (keyboard_pressed_counter == 4)
		activate_processing[1] = true;
	if(keyboard_pressed_counter == 6)
		activate_processing[2] = true;
	if(keyboard_pressed_counter == 8)
		activate_processing[3] = true;
	if(keyboard_pressed_counter == 10)
		activate_processing[4] = true;

	// Process
	OnePress_keyboard_process(Display.ADC1input, &signals1, &Display);

	/* USER CODE END DMA2_Stream0_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc1);
	/* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

	/* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream1 global interrupt.
 */
void DMA2_Stream1_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream1_IRQn 0 */

	/* USER CODE END DMA2_Stream1_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc3);
	/* USER CODE BEGIN DMA2_Stream1_IRQn 1 */
	/* USER CODE END DMA2_Stream1_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream2 global interrupt.
 */
void DMA2_Stream2_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

	// START Drumcomputer Processing
	if(Display.EditDrums == true) {

		//		if(Display.UpdateDisplay == true) {	// this variable is set true in GPIO EXTI Callback
		//			DISPLAY_Update();
		//			Display.UpdateDisplay = false;
		//		}

		if(Display.ADC2inputs[1] < Display.LowerLimit) {	// joystick down
			DISPLAY_DeleteDrumcomputerStepCursor();
			if(Display.CurrentSampleRow < MAX_NUMBER_OF_SAMPLES)	// Display.CurrentSampleRow should be maximum the number of loaded samples
				Display.CurrentSampleRow++;

			//			Display.CurrentSampleRow++;
			//			if(Display.CurrentSampleRow == MAX_NUMBER_OF_SAMPLES)	// set cursor to the most left step, when cursor exceeds the most right step
			//				Display.CurrentSampleRow = 1;

			DISPLAY_SetDrumcomputerStepCursor();
		}
		else if(Display.ADC2inputs[1] > Display.UpperLimit) {	// joystick up
			DISPLAY_DeleteDrumcomputerStepCursor();
			if(Display.CurrentSampleRow > 1)	// Display.CurrentSampleRow should be minimum 1
				Display.CurrentSampleRow--;

			//			Display.CurrentSampleRow--;
			//			if(Display.CurrentSampleRow == 1)	// set cursor to the most right step, when cursor exceeds the most left step
			//				Display.CurrentSampleRow = MAX_NUMBER_OF_SAMPLES;

			DISPLAY_SetDrumcomputerStepCursor();
		}
		if(Display.ADC2inputs[0] > Display.UpperLimit) {	// joystick left
			DISPLAY_DeleteDrumcomputerStepCursor();
			if(Display.CurrentDrumstep > 1)	// Display.CurrentDrumstep should be minimum 1
				Display.CurrentDrumstep--;
			DISPLAY_SetDrumcomputerStepCursor();
		}
		else if(Display.ADC2inputs[0] < Display.LowerLimit) {	// joystick right
			DISPLAY_DeleteDrumcomputerStepCursor();
			if(Display.CurrentDrumstep < NUMBER_OF_DRUMSTEPS)	// Display.CurrentDrumStep should be maximum the number of drumsteps
				Display.CurrentDrumstep++;
			DISPLAY_SetDrumcomputerStepCursor();
		}
	}
	// END Drumcomputer Processing

	// START Sequencer Processing
	if(Display.EditSteps == true) {
		//if(Display.EditSteps == true && Display.Sequencer_ONOFF == true) {	// diese if-Abfrage überarbeiten, da sonst der Joystick spinnt (Warum???) ?

		//		if(Display.UpdateDisplay == true) {	// this variable is set true in GPIO EXTI Callback
		//			DISPLAY_Update();
		//			Display.UpdateDisplay = false;
		//		}

		if(Display.ADC2inputs[1] < Display.LowerLimit) {	// joystick down
			DISPLAY_DeleteSequencerStepCursor();
			if(Display.CurrentNoteRow < MAX_NUMBER_OF_NOTES)	// Display.CurrentNoteRow should be maximum the number of notes
				Display.CurrentNoteRow++;
			DISPLAY_SetSequencerStepCursor();
		}
		else if(Display.ADC2inputs[1] > Display.UpperLimit) {	// joystick up
			DISPLAY_DeleteSequencerStepCursor();
			if(Display.CurrentNoteRow > 1)	// Display.CurrentNoteRow should be minimum 1
				Display.CurrentNoteRow--;
			DISPLAY_SetSequencerStepCursor();
		}
		if(Display.ADC2inputs[0] > Display.UpperLimit) {	// joystick left
			DISPLAY_DeleteSequencerStepCursor();
			if(Display.CurrentSequencestep > 1)	// Display.CurrentSequencestep should be minimum 1
				Display.CurrentSequencestep--;
			DISPLAY_SetSequencerStepCursor();
		}
		else if(Display.ADC2inputs[0] < Display.LowerLimit) {	// joystick right
			DISPLAY_DeleteSequencerStepCursor();
			if(Display.CurrentSequencestep < NUMBER_OF_SEQUENCERSTEPS)	// Display.CurrentSequencestep should be maximum the number of sequencer steps
				Display.CurrentSequencestep++;
			DISPLAY_SetSequencerStepCursor();
		}
	}
	// END Sequencer Processing

	// joystick usable if sequencer steps and drums not edited at the moment
	if( !(Display.EditDrums || Display.EditSteps) ) {
		//	else if(Display.EditSteps == false) {
		//else if(Display.EditDrums == false) {
		// arrow up or down
		if (Display.arrow_flag == true) {	// just in case we would not use the arrow, this flag should be false
			if(Display.ADC2inputs[1] < Display.LowerLimit) {	// joystick-y goes down
				DISPLAY_ArrowDown(&(Display.JoystickParameterPosition));
				DISPLAY_processing();
				//				DISPLAY_Update();
				Display.UpdateDisplay = true;
			}
			else if(Display.ADC2inputs[1] > Display.UpperLimit) {	// joystick-y goes up
				DISPLAY_ArrowUp(&(Display.JoystickParameterPosition));
				DISPLAY_processing();
				//				DISPLAY_Update();
				Display.UpdateDisplay = true;
			}
		}
		// switch page left or right
		if(Display.ADC2inputs[0] > Display.UpperLimit) {	// switch to the left page
			DISPLAY_SwitchPageLeft();
			//		Display.JoystickParameterPosition = 1;
			DISPLAY_processing();
			Display.JoystickParameterPosition = 1;
			DISPLAY_DrawArrow(1);
			//			DISPLAY_Update();
			Display.UpdateDisplay = true;
		}
		else if(Display.ADC2inputs[0] < Display.LowerLimit) {	// switch to the right page
			DISPLAY_SwitchPageRight();
			//		Display.JoystickParameterPosition = 1;
			DISPLAY_processing();
			Display.JoystickParameterPosition = 1;
			DISPLAY_DrawArrow(1);
			//			DISPLAY_Update();
			Display.UpdateDisplay = true;
		}
	}

	// BPM setting
	// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
	if(Display.poti_moved == true) {
		if(Display.pagePosition == 3 && Display.currentDrumcomputer > 0 && Display.JoystickParameterPosition == 2) {

			BPM = (((float)Display.ADC2inputs[2]/(float)Display.ADC_FullRange) * (BPM_MAX-60)) + 60;	// minimum BPM of 60, cause at low BPMs cause fuckups
			BPM = roundf(BPM);

			if(abs(last_BPM - BPM) > 3) {
				for(int i=0; i<FourFour; i++) {

					// INIT: Counter
					counter_DS1[i] = 0;
					counter_DS2[i] = 0;
					counter_DS3[i] = 0;
					counter_DS4[i] = 0;

					drum_index = 0;
					counter_master = 0;

					// RESET: Drum sound bins
					DS1s = 0;
					DS2s = 0;
					DS3s = 0;
					DS4s = 0;

					drums = 0;

					timing_position_in_samples[i] = (FourFour / 4 ) * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
				}
				char bpm_str[10];
				sprintf(bpm_str, "%.1f", BPM);
				last_BPM = BPM;
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
				Paint_DrawStringAt(&paint, Display.value_start_x_position-20, CASE2, bpm_str, &Font12, COLORED);
			}
		}
	}

	// calculate mean value of the potentiometer value
	Display.PotiMean_tmp += Display.ADC2inputs[2];
	if(Display.PotiMean_counter == 10) {
		Display.PotiMean = Display.PotiMean_tmp / Display.PotiMean_counter;
		Display.PotiMean_counter = 0;
		Display.PotiMean_tmp = 0;
		printf("PotiMean = %u\r\n", Display.PotiMean);
	}
	Display.PotiMean_counter++;

	//	printf("Poti diff = %u\r\n", abs(Display.last_Poti - Display.PotiMean));

	// do not process the poti change if joystick is moved in x- or y-direction
	if(abs(Display.ADC2inputs[0]-Display.JoystickMiddle)<100 && abs(Display.ADC2inputs[1]-Display.JoystickMiddle)<100) {
//		Display.Poti_Threshold = 10;
		if(abs(Display.last_Poti - Display.PotiMean) > Display.Poti_Threshold) {
			//			printf("moved\r\n");
			//			printf("Poti diff = %u\r\n", abs(Display.last_Poti - Display.PotiMean));
			Display.poti_moved = true;
			Display.last_Poti = Display.PotiMean;
			DISPLAY_processing();
			//			DISPLAY_Update();
			Display.UpdateDisplay = true;
		}
		else {
			Display.poti_moved = false;
			Display.last_Poti = Display.PotiMean;
		}
	}

	// necessary to update the display when the rate is changed in the LFO_SingleValueProcess function
	if(Tremolo.lfo->lfo_done_flag) {
		DISPLAY_processing();
		Display.UpdateDisplay = true;
		Tremolo.lfo->lfo_done_flag = false;
	}
	if(WahWah.lfo->lfo_done_flag) {
		DISPLAY_processing();
		Display.UpdateDisplay = true;
		WahWah.lfo->lfo_done_flag = false;
	}

	// process the display and and update it when one of the buttons is pressed, because otherwise the voices and sequencer notes and octaves are not updated
	if(Display.button_pressed_flag == true) {
		DISPLAY_processing();
		Display.UpdateDisplay = true;
		Display.button_pressed_flag = false;
	}

	if(Display.UpdateDisplay == true) {
		DISPLAY_Update();
		Display.UpdateDisplay = false;
	}

	/* USER CODE END DMA2_Stream2_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc2);
	/* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

	/* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream3 global interrupt.
 */
void DMA2_Stream3_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream3_IRQn 0 */

	/* USER CODE END DMA2_Stream3_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_spi4_rx);
	/* USER CODE BEGIN DMA2_Stream3_IRQn 1 */

	/* USER CODE END DMA2_Stream3_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream4 global interrupt.
 */
void DMA2_Stream4_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream4_IRQn 0 */

	/* USER CODE END DMA2_Stream4_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_spi4_tx);
	/* USER CODE BEGIN DMA2_Stream4_IRQn 1 */

	/* USER CODE END DMA2_Stream4_IRQn 1 */
}

/**
 * @brief This function handles SPI4 global interrupt.
 */
void SPI4_IRQHandler(void)
{
	/* USER CODE BEGIN SPI4_IRQn 0 */

	/* USER CODE END SPI4_IRQn 0 */
	HAL_SPI_IRQHandler(&hspi4);
	/* USER CODE BEGIN SPI4_IRQn 1 */
	/* USER CODE END SPI4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
