/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#include "gsm.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
gsm_t gsm;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
	// Parity Error
	if((__HAL_UART_GET_IT(huart, UART_IT_PE) != RESET))
	{
		__HAL_UART_CLEAR_IT(huart, UART_CLEAR_PEF);
	}
	// Frame Error
	if((__HAL_UART_GET_IT(huart, UART_IT_FE) != RESET))
	{
		__HAL_UART_CLEAR_IT(huart, UART_CLEAR_FEF);
	}
	// Noise Error
	if((__HAL_UART_GET_IT(huart, UART_IT_NE) != RESET))
	{
		__HAL_UART_CLEAR_IT(huart, UART_CLEAR_NEF);
	}
	// Overrun Error
	if((__HAL_UART_GET_IT(huart, UART_IT_ORE) != RESET))
	{
		__HAL_UART_CLEAR_IT(huart, UART_CLEAR_OREF);
	}

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  quectell_begin();


	//MODUL BILGISI
	gsm= quectell_ATcommand_data(ATI,2);

//	//IMEI
//	HAL_Delay(1000);
//	memset(&gsm, '\0', sizeof(gsm));
//	gsm= quectell_ATcommand_data(imei,2);

//	//GSM DURUM SORGULAMA
//	HAL_Delay(1000);
//	memset(&gsm, '\0', sizeof(gsm));
//	gsm= quectell_ATcommand_data(QueryStateofInitialization,10);

	//GSM DURUM
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_ATcommand_data(QueryGSMNetworkStatus,10);

	//NETWORK SENKRONIZASYON AKTIFLESTIRME
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_ATcommand_data(NetworkTimeSynchronization,10);

	//TARIH SAAT BILGISI
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_ATcommand_data(LatestNetworkTimeSynchronized,10);

//	//SIM OKUMA CALISMIYOR
//	HAL_Delay(1000);
//	memset(&gsm, '\0', sizeof(gsm));
//	gsm= quectell_ATcommand_data(SIMInsertedStatusActive,10);
//
//	HAL_Delay(1000);
//	memset(&gsm, '\0', sizeof(gsm));
//	gsm= quectell_ATcommand_data(SIMInsertedStatusReporting,10);

	//BAGLANTI MODU SECIMI
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_ATcommand_data(NetworkRegistrationL1,10);

	//BAGLANDIMI
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_ATcommand_data(NetworkRegistrationStatus,10);

//	//ARAMA
//	HAL_Delay(1000);
//	memset(&gsm, '\0', sizeof(gsm));
//	gsm= quectell_ATcommand_data(ARAMA,10);
//
//	//KAPATMA
//	HAL_Delay(10000);
//	memset(&gsm, '\0', sizeof(gsm));
//	gsm= quectell_ATcommand_data(KAPATMA,10);

	//OPERATOR NAME
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_ATcommand_data(OperatorSelection,10);

	//OPERATOR SIGNAL
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_ATcommand_data(OperatorSignal,10);

	//MESAJ
	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));
	gsm= quectell_message_data(sendMessageNumber, sendMessageData);

	HAL_Delay(1000);
	memset(&gsm, '\0', sizeof(gsm));

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


//	  gsm= quectell_message_data(sendMessageNumber, sendMessageData);
//
	  HAL_Delay(2000);
	  memset(&gsm, '\0', sizeof(gsm));

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GSM_POWER_GPIO_Port, GSM_POWER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RFTX_MON_Pin SIM_DOOR_Pin */
  GPIO_InitStruct.Pin = RFTX_MON_Pin|SIM_DOOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : GSM_POWER_Pin */
  GPIO_InitStruct.Pin = GSM_POWER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GSM_POWER_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
