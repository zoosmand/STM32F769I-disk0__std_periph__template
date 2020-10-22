/**
  ******************************************************************************
  * File Name          : i2c.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _I2CREG_;


/* -------------------------------------------------------------------------- */
/* Private function prototypes -----------------------------------------------*/
/* -------------------------------------------------------------------------- */
static uint8_t I2C_GenerateStart(I2C_TypeDef *I2Cx);
static void I2C_GenerateStop(I2C_TypeDef *I2Cx);
static void I2C_SendAddress(I2C_TypeDef *I2Cx, uint16_t slaveAddr, I2C_AddressMode addrMode, I2C_Direction dir);









////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Initializes I2C3 peripheral
  * @param  None
  * @return None
  */
void I2C_Init(I2C_TypeDef *I2Cx) {

  if (I2Cx == I2C1) {
    /** I2C4 GPIO Configuration    
        PB9      ------> I2C1_SDA
        PB8     ------> I2C1_SCL 
    */
    /* ----------------------------------------------------------------------------- */
    /* Mode */
    #define I2C_1_MASK  (I2C_1_SDA_Pin_Mask | I2C_1_SCL_Pin_Mask)
    MODIFY_REG(I2C_1_Port->MODER, I2C_1_MASK, (
        (_MODE_AF << (I2C_1_SDA_Pin_Pos * 2))
      | (_MODE_AF << (I2C_1_SCL_Pin_Pos * 2))
    ));
    /* Speed */
    MODIFY_REG(I2C_1_Port->OSPEEDR, I2C_1_MASK, (
        (_SPEED_V << (I2C_1_SDA_Pin_Pos * 2))
      | (_SPEED_V << (I2C_1_SCL_Pin_Pos * 2))
    ));
    // /* Output type */
    MODIFY_REG(I2C_1_Port->OTYPER, (I2C_1_SDA_Pin | I2C_1_SCL_Pin), (
        (_OTYPE_OD << I2C_1_SDA_Pin_Pos)
      | (_OTYPE_OD << I2C_1_SCL_Pin_Pos)
    ));
    // MODIFY_REG(I2C_4_SCL_Port->OTYPER, I2C_4_SCL_Pin, (_OTYPE_OD << I2C_4_SCL_Pin_Pos));
    /* Push mode */
    MODIFY_REG(I2C_1_Port->PUPDR, I2C_1_MASK, (
        (_PUPD_PU << (I2C_1_SDA_Pin_Pos * 2))
      | (_PUPD_PU << (I2C_1_SCL_Pin_Pos * 2))
    ));
    /* Alternate function */
    MODIFY_REG(I2C_1_Port->AFR[1], 0x000000ff, (
        (GPIO_AF_4 << ((I2C_1_SDA_Pin_Pos - 8) * 4))
      | (GPIO_AF_4 << ((I2C_1_SCL_Pin_Pos - 8) * 4))
    ));

    /* Due to a undocumented bug, the source clock should be start after the GPIO initialization */
    Delay(1);
    // PREG_SET(RCC->APB1ENR, RCC_APB1ENR_I2C3EN_Pos);


    // I2C
    /* ----------------------------------------------------------------------------- */
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_PE);
    I2Cx->TIMINGR = (0x40912732 & 0xf0ffffff);
    SET_BIT(I2Cx->OAR1, I2C_OAR1_OA1EN);
    SET_BIT(I2Cx->CR2, (I2C_CR2_AUTOEND | I2C_CR2_NACK));
    I2Cx->OAR2 = 0;
    MODIFY_REG(I2Cx->CR1, (I2C_CR1_GCEN_Msk | I2C_CR1_NOSTRETCH_Msk), 0);
    SET_BIT(I2Cx->CR1, I2C_CR1_PE);
  }



  if (I2Cx == I2C4) {
    /** I2C4 GPIO Configuration    
        PB7      ------> I2C4_SDA
        PD12     ------> I2C4_SCL 
    */
    /* ----------------------------------------------------------------------------- */
    /* Mode */
    MODIFY_REG(I2C_4_SDA_Port->MODER, I2C_4_SDA_Pin_Mask, (_MODE_AF << (I2C_4_SDA_Pin_Pos * 2)));
    MODIFY_REG(I2C_4_SCL_Port->MODER, I2C_4_SCL_Pin_Mask, (_MODE_AF << (I2C_4_SCL_Pin_Pos * 2)));
    /* Speed */
    MODIFY_REG(I2C_4_SDA_Port->OSPEEDR, I2C_4_SDA_Pin_Mask, (_SPEED_V << (I2C_4_SDA_Pin_Pos * 2)));
    MODIFY_REG(I2C_4_SCL_Port->OSPEEDR, I2C_4_SCL_Pin_Mask, (_SPEED_V << (I2C_4_SCL_Pin_Pos * 2)));
    // /* Output type */
    // MODIFY_REG(I2C_4_SDA_Port->OTYPER, I2C_4_SDA_Pin, (_OTYPE_OD << I2C_4_SDA_Pin_Pos));
    MODIFY_REG(I2C_4_SCL_Port->OTYPER, I2C_4_SCL_Pin, (_OTYPE_OD << I2C_4_SCL_Pin_Pos));
    // /* Push mode */
    // MODIFY_REG(I2C_4_SDA_Port->PUPDR, I2C_4_SDA_Pin_Mask, (_PUPD_PU << (I2C_4_SDA_Pin_Pos * 2)));
    // MODIFY_REG(I2C_4_SCL_Port->PUPDR, I2C_4_SCL_Pin_Mask, (_PUPD_PU << (I2C_4_SCL_Pin_Pos * 2)));
    /* Alternate function */
    MODIFY_REG(I2C_4_SDA_Port->AFR[0], 0xf0000000, (GPIO_AF_11 << (I2C_4_SDA_Pin_Pos * 4)));
    MODIFY_REG(I2C_4_SCL_Port->AFR[1], 0x000f0000, (GPIO_AF_4 << ((I2C_4_SCL_Pin_Pos - 8) * 4)));

    /* Due to a undocumented bug, the source clock should be start after the GPIO initialization */
    Delay(1);
    // PREG_SET(RCC->APB1ENR, RCC_APB1ENR_I2C3EN_Pos);


    // I2C
    /* ----------------------------------------------------------------------------- */
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_PE);
    I2Cx->TIMINGR = (0x40912732 & 0xf0ffffff);
    SET_BIT(I2Cx->OAR1, I2C_OAR1_OA1EN);
    SET_BIT(I2Cx->CR2, (I2C_CR2_AUTOEND | I2C_CR2_NACK));
    I2Cx->OAR2 = 0;
    MODIFY_REG(I2Cx->CR1, (I2C_CR1_GCEN_Msk | I2C_CR1_NOSTRETCH_Msk), 0);
    SET_BIT(I2Cx->CR1, I2C_CR1_PE);
  }
}






/**
  * @brief  Writes 8 bit data via I2C
  * @param  I2Cx: pointer to an I2C instance
  * @param  data: a byte to send
  * @return None
  */
uint8_t I2C_Write(I2C_TypeDef *I2Cx, uint8_t slaveAddress, uint8_t *buf, uint16_t len) {
  uint8_t status = 0;

  if (I2C_GenerateStart(I2Cx)) {
    // if (I2C_Master_Transmit(I2Cx, slaveAddress, &reg, 1)) {
      status = I2C_Master_Transmit(I2Cx, slaveAddress, buf, len);
    // }
    I2C_GenerateStop(I2Cx);
  }

 return (status);
}




/**
  * @brief  Reads 8 bit data via I2C
  * @param  I2Cx: pointer to an I2C instance
  * @return  a received byte
  */
uint8_t I2C_Read(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t reg, uint8_t *buf, uint16_t len) {
  uint8_t status = 0;

  // if (I2C_GenerateStart(I2Cx)) {
  //   if (I2C_Master_Transmit(I2Cx, slaveAddress, &reg, 1)) {
  //     if (I2C_GenerateStart(I2Cx)) {
  //       status = I2C_Master_Receive(I2Cx, slaveAddress, buf, len);
  //     }
  //   }
  //   I2C_GenerateStop(I2Cx);
  // }

  I2C_Master_Transmit(I2Cx, slaveAddr, &reg, 1);

  I2C_Master_Receive(I2Cx, slaveAddr, buf, len);

  return (status);
}




// /**
//   * @brief  Transfers 8 bit data via I2C (read and write in one iteraction)
//   * @param  I2Cx: pointer to an I2C instance
//   * @param  data: a byte to send
//   * @return a received byte
//   */
// uint8_t I2C_Transfer8b(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t data) {

//   return (data);
// }




/**
  * @brief  Transmits in master mode an amount of data.
  * @param  I2Cx Pointer to a I2C_TypeDef I2Cx.
  * @param  slaveAddress Target I2Cx address: The I2Cx 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  buf Pointer to data buffer
  * @param  len Amount of data to be sent
  * @return transmit status
  */
uint8_t I2C_Master_Transmit(I2C_TypeDef *I2Cx, uint16_t slaveAddr, uint8_t *buf, uint32_t len) {
  uint8_t status = 0;
  uint32_t timeout = 5000000;

  if (len > 0xff) return (status);

  //  I2Cx->CR2 |= ((slaveAddress << I2C_CR2_SADD_Pos) | (I2C_TX << I2C_CR2_RD_WRN_Pos));

  // /* Generate Start or ReStart */
  // PREG_SET(I2Cx->CR2, I2C_CR2_START_Pos);

  // while (!(PREG_CHECK(I2Cx->ISR, I2C_ISR_BUSY_Pos))) {
  //   timeout--;
  //   if (!timeout) {
  //     status = 0;
  //     return (status);
  //   }
  // }
  
  /* Disable Pos */
  // PREG_CLR(I2Cx->CR1, I2C_CR1);
  // /* Disable Ack */
  // PREG_CLR(I2Cx->CR1, I2C_CR1_ACK_Pos);


  // if (I2C_SendAddress(I2Cx, slaveAddress, mode_7bit, transmit)) {
  //   while (len--) {
  //     I2Cx->DR = *buf++;
  //     while (!(PREG_CHECK(I2Cx->SR1, I2C_SR1_TXE_Pos))) {
  //       timeout--;
  //       if (!timeout) {
  //         status = 0;
  //         return (status);
  //       }
  //     }

  //     if ((PREG_CHECK(I2Cx->SR1, I2C_SR1_AF_Pos)) || (PREG_CHECK(I2Cx->SR1, I2C_SR1_ARLO_Pos)) || (PREG_CHECK(I2Cx->SR1, I2C_SR1_BERR_Pos))) {
  //       status = 0;
  //     } else {
  //       status = 1;
  //     }
  //   }
  // }

  if ((slaveAddr & 0x7f) == slaveAddr) {
    I2C_SendAddress(I2Cx, slaveAddr, I2C_7bit, I2C_TX);
  } else {
    I2C_SendAddress(I2Cx, slaveAddr, I2C_10bit, I2C_TX);
  }
  I2Cx->CR2 |= (len << I2C_CR2_NBYTES_Pos);
  status = I2C_GenerateStart(I2Cx);
  status = I2C_GenerateStart(I2Cx);

  while (len--) {
    I2Cx->TXDR = *buf++;
    while (!(PREG_CHECK(I2Cx->ISR, I2C_ISR_TXE_Pos))) {
      timeout--;
      if (!timeout) {
        status = 0;
        return (status);
      }
    }
  }

  I2C_GenerateStop(I2Cx);

  return (status);
}






/**
  * @brief  Receives in master mode an amount of data.
  * @param  I2Cx Pointer to a I2C_TypeDef I2Cx.
  * @param  slaveAddress Target I2Cx address: The I2Cx 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  buf Pointer to data buffer
  * @param  len Amount of data to be sent
  * @return receive status
  */
uint8_t I2C_Master_Receive(I2C_TypeDef *I2Cx, uint16_t slaveAddr, uint8_t *buf, uint16_t len) {
  uint8_t status = 0;
  uint32_t timeout = 5000000;
  
  // /* Enable Ack */
  // // PREG_SET(I2Cx->CR2, I2C_CR2_ACK_Pos);
  // // CLR_I2C_BIT(&I2Cx->CR1, I2C_CR1_ACK_Pos);

  // if (I2C_SendAddress(I2Cx, slaveAddress, mode_7bit, receive)) {
  //   while (len--) {
  //     // last byte without Acking
  //     if (len == 0) {
  //       // PREG_CLR(I2Cx->CR1, I2C_CR1_ACK_Pos);
  //     }

  //     while (!(PREG_CHECK(I2Cx->SR1, I2C_SR1_RXNE_Pos))) {
  //       timeout--;
  //       if (!timeout) {
  //         status = 0;
  //         return (status);
  //       }
  //     }
  //     *buf++ = I2Cx->DR;

  //     if ((PREG_CHECK(I2Cx->SR1, I2C_SR1_AF_Pos)) || (PREG_CHECK(I2Cx->SR1, I2C_SR1_ARLO_Pos)) || (PREG_CHECK(I2Cx->SR1, I2C_SR1_BERR_Pos))) {
  //       status = 0;
  //     } else {
  //       status = 1;
  //     }
  //   }
  // }

  if ((slaveAddr & 0x7f) == slaveAddr) {
    I2C_SendAddress(I2Cx, slaveAddr, I2C_7bit, I2C_RX);
  } else {
    I2C_SendAddress(I2Cx, slaveAddr, I2C_10bit, I2C_RX);
  }
  I2Cx->CR2 |= (len << I2C_CR2_NBYTES_Pos);
  status = I2C_GenerateStart(I2Cx);
  while (len--) {

    *buf++ = I2Cx->RXDR;
    while (!(PREG_CHECK(I2Cx->ISR, I2C_ISR_RXNE_Pos))) {
      timeout--;
      if (!timeout) {
        status = 0;
        return (status);
      }
    }
  }

  I2C_GenerateStop(I2Cx);

  return (status);
}






static void I2C_SendAddress(I2C_TypeDef *I2Cx, uint16_t slaveAddr, I2C_AddressMode addrMode, I2C_Direction dir) {

  // if (addressMode == mode_7bit) {
  //   I2Cx->CR2 |= ((slaveAddress << I2C_CR2_SADD_Pos) | (dir << I2C_CR2_RD_WRN_Pos));
  //   while (!(PREG_CHECK(I2Cx->ISR, I2C_ISR_ADDR_Pos))) {
  //     timeout--;
  //     if (!timeout) {
  //       status = 0;
  //       return (status);
  //     }
  //   }
  // } else {
  //   // ToDo. 10-bit address handler
  // }

  switch (addrMode) {
    case I2C_7bit:
      I2Cx->CR2 |= ((slaveAddr << I2C_CR2_SADD_Pos) | (dir << I2C_CR2_RD_WRN_Pos));
      I2Cx->CR2 &= ~(1 << I2C_CR2_AUTOEND_Pos);
      break;
    
    case I2C_10bit:
      /* ToDo. 10-bit address handler */
      break;
    
    default:
      break;
  }
}





uint8_t I2C_GenerateStart(I2C_TypeDef *I2Cx) {
  uint8_t status = 1;
  uint32_t timeout = 5000000;


  // while (PREG_CHECK(I2Cx->ISR, I2C_ISR_BUSY_Pos)) {
  //   timeout--;
  //   if (!timeout) {
  //     status = 0;
  //     return (status);
  //   }
  // }
   /* Generate Start or ReStart */
  PREG_SET(I2Cx->CR2, I2C_CR2_START_Pos);
  
  while (PREG_CHECK(I2Cx->ISR, I2C_ISR_TXIS_Pos)) {
    timeout--;
    if (!timeout) {
      status = 0;
      return (status);
    }
  }
  return (status);
}





void I2C_GenerateStop(I2C_TypeDef *I2Cx) {
  PREG_SET(I2Cx->CR2, I2C_CR2_STOP_Pos);
}




void FT6206_Init(void) {
  Delay(50);

  uint8_t buf[8]; 
  // I2C_Read(I2C4, I2C_ADDR, FT6206_CHIP_ID_REG, buf, 1);

  buf[0] = FT6206_CHIP_ID_REG;

  I2C_Master_Transmit(I2C4, I2C_ADDR, buf, 1);
  I2C_Master_Receive(I2C4, I2C_ADDR, buf, 1);
}