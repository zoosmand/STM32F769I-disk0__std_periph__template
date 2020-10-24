/**
  ******************************************************************************
  * File Name          : ft6206.h
  * Description        : This file provides headers for the code of the
  *                      configuration of the FT6206 capacitive touchscreen.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT6206_H
#define __FT6206_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _FT6206REG_;


/* Private defines -----------------------------------------------------------*/
#define FT6206_I2C_ADDR           0x54

/* FT6206 Chip identification register */
#define FT6206_CHIP_ID_REG        0xa8


/* FT6206 Registry Flags */



/* Exported functions prototypes ---------------------------------------------*/
void FT6206_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__FT6206_H */
