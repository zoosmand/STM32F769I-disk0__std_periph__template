/**
  ******************************************************************************
  * File Name          : DMA2D.h
  * Description        : This file provides code for the configuration
  *                      of the DMA2D instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMA2D_H
#define __DMA2D_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/


/* Private defines -----------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void DMA2D_Init(void);
void DMA2D_ForegroundLayer_Init(void);
void DMA2D_BackgroundLayer_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__DMA2D_H */
