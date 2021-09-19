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
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;
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
 * @brief This function handles TIM5 global interrupt.
 */
void TIM5_IRQHandler(void)
{
	/* USER CODE BEGIN TIM5_IRQn 0 */

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

	//printf("******\r\n");
	//
	//
	//for (int i = 0; i<sizeof(sensor_data_t);i++){
	//	printf("%i,",pRxData[i]);
	//}
	//
	//printf("\r\n");
	//	printf("gyro init: %i\r\n",sensorData.gyro_initilized);
	//	printf("tilt: %i\r\n",sensorData.tilt_detecded);
	//printf("\r\n");
	//printf("\r\n");

	/* USER CODE END TIM7_IRQn 1 */
}

/**
 * @brief This function handles DMA2 stream0 global interrupt.
 */
void DMA2_Stream0_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

	Filters_Reinit();
	//OnePress_keyboard_process(keyboard_adc_value, &signals1, &envelope);
	//if(Display.mode == KEYBOARD)
	//OnePress_keyboard_process(Display.ADC1input, &signals1, &envelope, &Display);

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

	// Start Drumcomputer Processing
	if(Display.EditDrums == true) {
		//if(Display.EditDrums == true && Display.Drumcomputer_ONOFF == true) {	// diese if-Abfrage überarbeiten, da sonst der Joystick spinnt (Warum???) ?

		if(Display.UpdateDisplay == true) {	// this variable is set true in GPIO EXTI Callback
			DISPLAY_Update();
			Display.UpdateDisplay = false;
		}

		if(Display.ADC2inputs[1] < Display.LowerLimit) {	// joystick down
			DISPLAY_DeleteDrumcomputerStepCursor();
			if(Display.CurrentSampleRow < MAX_NUMBER_OF_SAMPLES)	// Display.CurrentSampleRow should be maximum the number of loaded samples
				Display.CurrentSampleRow++;
			DISPLAY_SetDrumcomputerStepCursor();
		}
		else if(Display.ADC2inputs[1] > Display.UpperLimit) {	// joystick up
			DISPLAY_DeleteDrumcomputerStepCursor();
			if(Display.CurrentSampleRow > 1)	// Display.CurrentSampleRow should be minimum 1
				Display.CurrentSampleRow--;
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

		Display.lastCurrentDrumstep = Display.CurrentDrumstep;
		Display.lastCurrentSampleRow = Display.CurrentSampleRow;
	}
	// END Drumcomputer Processing

	else if(Display.EditDrums == false) {
		// arrow up or down
		if (Display.arrow_flag == true) {	// just in case we would not use the arrow, this flag should be false
			if (Display.ADC2inputs[1] < Display.LowerLimit) {	// joystick-y goes down
				DISPLAY_ArrowDown(&(Display.JoystickParameterPosition));
				DISPLAY_processing();
				DISPLAY_Update();
			}
			else if (Display.ADC2inputs[1] > Display.UpperLimit) {	// joystick-y goes up
				DISPLAY_ArrowUp(&(Display.JoystickParameterPosition));
				DISPLAY_processing();
				DISPLAY_Update();
			}
		}
		// switch page left or right
		if(Display.ADC2inputs[0] > Display.UpperLimit) {	// switch to the left page
			DISPLAY_SwitchPageLeft();
			//		Display.JoystickParameterPosition = 1;
			DISPLAY_processing();
			Display.JoystickParameterPosition = 1;
			DISPLAY_DrawArrow(1);
			DISPLAY_Update();
		}
		else if(Display.ADC2inputs[0] < Display.LowerLimit) {	// switch to the right page
			DISPLAY_SwitchPageRight();
			//		Display.JoystickParameterPosition = 1;
			DISPLAY_processing();
			Display.JoystickParameterPosition = 1;
			DISPLAY_DrawArrow(1);
			DISPLAY_Update();
		}
	}

	if(Display.pagePosition == 2 && Display.currentDrumcomputer > 0 && Display.JoystickParameterPosition == 2) {	// BPM setting

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

				// SEQUENCER
				//				// RESET: ADSR for being ready in next cycle
				//				adsr_SN1[drum_index].adsr_done = false;
				//				adsr_SN2[drum_index].adsr_done = false;
				//				adsr_SN3[drum_index].adsr_done = false;
				//				adsr_SN4[drum_index].adsr_done = false;

				//				// INIT: Timing positions
				//				timing_DS1[i] = 0;
				//				timing_DS2[i] = 0;
				//				timing_DS3[i] = 0;
				//				timing_DS4[i] = 0;

				//				// INIT: Sequencer timing positions
				//				timing_SN1[i] = 0;
				//				timing_SN2[i] = 0;
				//				timing_SN3[i] = 0;
				//				timing_SN4[i] = 0;
				//
				//				// INIT: Sequencer start index
				//				current_LUT_index_SN1[i] = LUT_STARTINDEX[freq_index_SN1];
				//				current_LUT_index_SN2[i] = LUT_STARTINDEX[freq_index_SN2];
				//				current_LUT_index_SN3[i] = LUT_STARTINDEX[freq_index_SN3];
				//				current_LUT_index_SN4[i] = LUT_STARTINDEX[freq_index_SN4];
				//
				//				// INIT: ADSR structs
				//				Sequencer_ADSR_Init(&adsr_SN1[i]);
				//				Sequencer_ADSR_Init(&adsr_SN2[i]);
				//				Sequencer_ADSR_Init(&adsr_SN3[i]);
				//				Sequencer_ADSR_Init(&adsr_SN4[i]);
				timing_position_in_samples[i] = (FourFour / 4 ) * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
			}
			char bpm_str[10];
			sprintf(bpm_str, "%.1f", BPM);
			last_BPM = BPM;
			Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-20, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
			Paint_DrawStringAt(&paint, Display.value_start_x_position-20, CASE2, bpm_str, &Font12, COLORED);
		}
	}

	//	printf("%i\r\n", Display.ADC2inputs[2]);
	Display.Poti_Threshold = 50;
	if(abs(Display.last_Poti - Display.ADC2inputs[2]) > Display.Poti_Threshold) {
		//printf("Poti triggered\r\n");
		Display.poti_moved = true;
		DISPLAY_processing();
		DISPLAY_Update();
		Display.last_Poti = Display.ADC2inputs[2];
		II_Display_Effects();
		II_Display_Voices();
	}
	else {
		Display.poti_moved = false;
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
