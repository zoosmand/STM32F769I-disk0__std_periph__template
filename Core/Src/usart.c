/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _USARTREG_ = 0;

/* Private variables ---------------------------------------------------------*/
static uint8_t usartBuf[RXBUF_LEN];
static uint8_t usartBufPrtIn = 0;
static uint8_t usartBufPrtOut = 0;


/* Private function prototypes -----------------------------------------------*/










////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Initializes USART1 peripheral 
  * @param  None
  * @retval None
  */
void USART1_Init(void) {
  /** USART1 GPIO Configuration  
    PA9    ------> USART1_TX
    PA10   ------> USART1_RX
  */
  #define USART_1_MASK  (USART_1_TX_Pin_Mask | USART_1_RX_Pin_Mask)

  MODIFY_REG(USART_1_Port->MODER, USART_1_MASK, (
      (_MODE_AF << (USART_1_TX_Pin_Pos * 2))
    | (_MODE_AF << (USART_1_RX_Pin_Pos * 2))
  ));
  MODIFY_REG(USART_1_Port->OSPEEDR, USART_1_MASK, (
      (_SPEED_V << (USART_1_TX_Pin_Pos * 2))
    | (_SPEED_V << (USART_1_RX_Pin_Pos * 2))
  ));
  MODIFY_REG(USART_1_Port->AFR[1], 0x00000ff0, (
      (GPIO_AF_7 << ((USART_1_TX_Pin_Pos - 8) * 4))
    | (GPIO_AF_7 << ((USART_1_RX_Pin_Pos - 8) * 4))
  ));

  /* Transmit enable */
  PREG_SET(USART1->CR1, USART_CR1_TE_Pos);
  /* Receive enable */
  PREG_SET(USART1->CR1, USART_CR1_RE_Pos);
  /* Asyncronos mode */
  CLEAR_BIT(USART1->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(USART1->CR3, (USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL));
  /* Set Baudrate */
  USART1->BRR = BRR_Value;
  /* Enable RXNE Interrupt */
  PREG_SET(USART1->CR1, USART_CR1_RXNEIE_Pos);
  /* Enable USART1 */
  PREG_SET(USART1->CR1, USART_CR1_UE_Pos);
  
  /* USART1 interrupt Init */
  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 14, 0));
  NVIC_EnableIRQ(USART1_IRQn);
  /* Clear RXNE  pernding bit */
  PREG_SET(USART1->RQR, USART_RQR_RXFRQ_Pos);
}







void USART1_RX_Handler() {
  uint8_t tmp = USART1->RDR;
  uint8_t preRxPtr = usartBufPrtIn - 1;
  preRxPtr &= RXBUF_MASK;

  usartBuf[(usartBufPrtIn++)] = tmp;
  usartBufPrtIn &= RXBUF_MASK;

  // the end of message
  if ((usartBuf[preRxPtr] == 0x0d) && (tmp == 0x0a)) {
  // if (tmp == '\n') { // 0x0a
    // if (usartBuf[preRxPtr] == '\r') { // 0x0d
      FLAG_SET(_USARTREG_, _USART1_LBNEF_);
    // }
  }
}





uint8_t USART1_RxBufferRead(uint8_t *buf, uint16_t len) {
  uint8_t payloadLen = 0;
  while (usartBufPrtOut != usartBufPrtIn) {
    buf[(payloadLen++)] = usartBuf[(usartBufPrtOut++)];
    usartBufPrtOut &= RXBUF_MASK;
  }
  return payloadLen;
}

