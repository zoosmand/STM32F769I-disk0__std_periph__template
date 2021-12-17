/**
  ******************************************************************************
  * File Name          : usart.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _USARTREG_;


/* Private defines -----------------------------------------------------------*/
#define USART_1_TX_Pin              GPIO_PIN_9
#define USART_1_TX_Pin_Pos          GPIO_PIN_9_Pos
#define USART_1_TX_Pin_Mask         GPIO_PIN_9_Mask
#define USART_1_RX_Pin              GPIO_PIN_10
#define USART_1_RX_Pin_Pos          GPIO_PIN_10_Pos
#define USART_1_RX_Pin_Mask         GPIO_PIN_10_Mask
#define USART_1_Port                GPIOA
/* RX Buffer definition */
#define RXBUF_LEN           64
#define RXBUF_MASK          (RXBUF_LEN - 1)
/* USART Registry Flags */
#define _USART1_LBNEF_      0 // Local Buffer Not Empty Flag
#define _USART1_RXAF_       1 // RX Action Flag


/* Private macros ------------------------------------------------------------*/
#define BAUDRATE        115200
#define BRR_Value       (RccClocks.PCLK2_Freq / BAUDRATE)


/* Exported functions prototypes ---------------------------------------------*/
void USART1_Init(void);
void USART1_RX_Handler(void);
uint8_t USART1_RxBufferRead(uint8_t *buf, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif /*__ USART_H */

