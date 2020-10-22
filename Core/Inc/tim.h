/**
  ******************************************************************************
  * File Name          : tim.h
  * Description        : This file provides code for the configuration
  *                      of timers instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H
#define __TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Global variables ---------------------------------------------------------*/
extern uint32_t _TIMREG_;

// typedef enum {
//   _printf = 0,
//   _display,
//   _other
// } PrintDateTimeTypeDef;




/* Private defines -----------------------------------------------------------*/
// TIM Registry Flags
#define _BT6F_        0 // Basic Timer6 Action Flag




/* Exported functions prototypes ---------------------------------------------*/
void BasicTimer6_Init(void);
void Timer_Handler(TIM_TypeDef* tim);
// void PrintDateTime(PrintDateTimeTypeDef dst);



#ifdef __cplusplus
}
#endif
#endif /*__TIM_H */

