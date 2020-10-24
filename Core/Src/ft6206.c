/**
  ******************************************************************************
  * File Name          : ft6206.c
  * Description        : This file provides headers for the code of the
  *                      configuration of the FT6206 capacitive touchscreen.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "ft6206.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _FT6206REG_ = 0;








////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Initializes and checks FT2606 
  * @param  None
  * @return None
  */
void FT6206_Init(void) {
  uint8_t buf[8]; 
  I2C_Read(I2C4, FT6206_I2C_ADDR, FT6206_CHIP_ID_REG, buf, 4);

  printf("%x, %x, %x, %x \n", buf[0], buf[1], buf[2], buf[3]);
}


