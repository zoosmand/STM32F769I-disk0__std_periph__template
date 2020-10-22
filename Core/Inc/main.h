/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Define debug output to SWO */
#define SWO_ITM
#define SWO_USART

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "stm32f7xx.h"

/* Private includes ----------------------------------------------------------*/
#include "common.h"
#include "stm32f7xx_it.h"
#include "led.h"
#include "crc.h"
#include "exti.h"
#include "usart.h"
#include "tim.h"
#include "rtc.h"
#include "dma2d.h"
#include "fmc.h"
#include "dsi.h"
#include "ltdc.h"
#include "display.h"
#include "fonts.h"
#include "otm8009a.h"
#include "i2c.h"
#include "bmx280.h"

/* Global typedef ------------------------------------------------------------*/
struct __FILE {
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct
{
  uint32_t HCLK_Freq;          /*!< HCLK clock frequency */
  uint32_t PCLK1_Freq;         /*!< PCLK1 clock frequency */
  uint32_t PCLK1_Freq_Tim;     /*!< PCLK1 clock frequency for timers */
  uint32_t PCLK2_Freq;         /*!< PCLK2 clock frequency */
  uint32_t PCLK2_Freq_Tim;     /*!< PCLK2 clock frequency for timers */
} RCC_ClocksTypeDef;


/* Exported types ------------------------------------------------------------*/

/* Exported varables ---------------------------------------------------------*/
extern uint32_t sysQuantum;
extern uint32_t millis;
extern uint32_t seconds;
extern uint32_t minutes;
extern uint32_t _GLOBALREG_;
extern uint32_t SystemCoreClock;
extern RCC_ClocksTypeDef RccClocks;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/
// _GLOBALREG_ Flags    
#define _DELAYF_  0 // Delay handler Flag
#define _SECF_    1 // Second handler Flag



#define CCMRAM  __attribute__((section(".ccmram")))

/* Exported functions prototypes ---------------------------------------------*/
extern void Delay_Handler(uint32_t delay);
extern void Delay(uint32_t delay);
extern void Cron_Handler(void);
extern void Set_BitBandVal(uint32_t addr, uint32_t key);
extern uint32_t Get_BitBandVal(uint32_t addr);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

