/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEYPAD_OUTPUT_ROW_0_Pin GPIO_PIN_0
#define KEYPAD_OUTPUT_ROW_0_GPIO_Port GPIOC
#define KEYPAD_OUTPUT_ROW_1_Pin GPIO_PIN_1
#define KEYPAD_OUTPUT_ROW_1_GPIO_Port GPIOC
#define KEYPAD_OUTPUT_ROW_2_Pin GPIO_PIN_2
#define KEYPAD_OUTPUT_ROW_2_GPIO_Port GPIOC
#define KEYPAD_OUTPUT_ROW_3_Pin GPIO_PIN_3
#define KEYPAD_OUTPUT_ROW_3_GPIO_Port GPIOC
#define LED_BIN_Pin GPIO_PIN_0
#define LED_BIN_GPIO_Port GPIOA
#define LED_DEC_Pin GPIO_PIN_1
#define LED_DEC_GPIO_Port GPIOA
#define LED_HEX_Pin GPIO_PIN_2
#define LED_HEX_GPIO_Port GPIOA
#define LED_LSB_Pin GPIO_PIN_3
#define LED_LSB_GPIO_Port GPIOA
#define KEYPAD_INPUT_COL_0_Pin GPIO_PIN_4
#define KEYPAD_INPUT_COL_0_GPIO_Port GPIOA
#define KEYPAD_INPUT_COL_1_Pin GPIO_PIN_5
#define KEYPAD_INPUT_COL_1_GPIO_Port GPIOA
#define KEYPAD_INPUT_COL_2_Pin GPIO_PIN_6
#define KEYPAD_INPUT_COL_2_GPIO_Port GPIOA
#define KEYPAD_INPUT_COL_3_Pin GPIO_PIN_7
#define KEYPAD_INPUT_COL_3_GPIO_Port GPIOA
#define KEYPAD_INPUT_COL_4_Pin GPIO_PIN_0
#define KEYPAD_INPUT_COL_4_GPIO_Port GPIOB
#define KEYPAD_INPUT_COL_5_Pin GPIO_PIN_1
#define KEYPAD_INPUT_COL_5_GPIO_Port GPIOB
#define CH423_DEC_SCL_Pin GPIO_PIN_10
#define CH423_DEC_SCL_GPIO_Port GPIOB
#define DEBUG_MCO2_Pin GPIO_PIN_9
#define DEBUG_MCO2_GPIO_Port GPIOC
#define CH423_HEX_SCL_Pin GPIO_PIN_8
#define CH423_HEX_SCL_GPIO_Port GPIOA
#define SWD_SWDIO_Pin GPIO_PIN_13
#define SWD_SWDIO_GPIO_Port GPIOA
#define SWD_SWCLK_Pin GPIO_PIN_14
#define SWD_SWCLK_GPIO_Port GPIOA
#define CH423_DEC_SDA_Pin GPIO_PIN_3
#define CH423_DEC_SDA_GPIO_Port GPIOB
#define CH423_HEX_SDA_Pin GPIO_PIN_4
#define CH423_HEX_SDA_GPIO_Port GPIOB
#define CH423_BIN_SCL_Pin GPIO_PIN_6
#define CH423_BIN_SCL_GPIO_Port GPIOB
#define CH423_BIN_SDA_Pin GPIO_PIN_7
#define CH423_BIN_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
