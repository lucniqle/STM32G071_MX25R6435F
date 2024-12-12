/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g0xx_hal.h"

#include "custom.h"
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IRQ_Pin GPIO_PIN_13
#define IRQ_GPIO_Port GPIOC
#define IRQ_EXTI_IRQn EXTI4_15_IRQn
#define CSMX_Pin GPIO_PIN_4
#define CSMX_GPIO_Port GPIOA
#define RSTMX_Pin GPIO_PIN_6
#define RSTMX_GPIO_Port GPIOC
#define WP_Pin GPIO_PIN_7
#define WP_GPIO_Port GPIOC
#define D_INPT_Pin GPIO_PIN_11
#define D_INPT_GPIO_Port GPIOA
#define D_OUT_Pin GPIO_PIN_12
#define D_OUT_GPIO_Port GPIOA
#define RSTBT_Pin GPIO_PIN_0
#define RSTBT_GPIO_Port GPIOD
#define ANATEST_Pin GPIO_PIN_5
#define ANATEST_GPIO_Port GPIOB
#define CSBT_Pin GPIO_PIN_9
#define CSBT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern SPI_HandleTypeDef hspi1;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
