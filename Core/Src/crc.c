/**
  ******************************************************************************
  * File Name          : crc.c
  * Description        : This file provides code for the configuration
  *                      of the GPIO instances for CRC's indication.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "crc.h"

/* Global variables ---------------------------------------------------------*/


void CRC_Init(void) {
  /* X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 +X^8 + X^7 + X^5 + X^4 + X^2+ X +1 */
  WRITE_REG(CRC->POL, 0x04c11db7);
  /* 32-bit long generating polynomial */
  MODIFY_REG(CRC->CR, CRC_CR_POLYSIZE, 0);
  /* Default init value*/
  WRITE_REG(CRC->INIT, 0xffffffff);
  /* Set input data inversion mode */
  /* Set output data inversion mode */
  MODIFY_REG(CRC->CR, (CRC_CR_REV_IN_Msk | CRC_CR_REV_OUT_Msk), 0);
  /* Reser the CRC calculation */
  PREG_SET(CRC->CR, CRC_CR_RESET_Pos);
}


