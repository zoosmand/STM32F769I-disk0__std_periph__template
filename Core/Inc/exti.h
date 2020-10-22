/**
  ******************************************************************************
  * File Name          : EXTI.h
  * Description        : This file provides code for the configuration
  *                      of the EXTI instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EXTI_H
#define __EXTI_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _EXTIREG_;


/* Private defines -----------------------------------------------------------*/
// EXTI Registry Flags
#define _WUBAF_       0 // Wake Up Button Action Flag



/* Exported functions prototypes ---------------------------------------------*/
void EXTI_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__EXTI_H */
