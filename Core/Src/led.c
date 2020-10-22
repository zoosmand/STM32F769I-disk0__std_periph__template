/**
  ******************************************************************************
  * File Name          : LED.c
  * Description        : This file provides code for the configuration
  *                      of the GPIO instances for LED's indication.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _LEDREG_ = 0;


void LED_Init(void) {
    /* GPIO LED -  PJ13, PJ5 */
  /* Mode */
  MODIFY_REG(LED_Port->MODER, (LED0_Pin_Mask | LED1_Pin_Mask), ((_MODE_OUT << LED0_Pin_Pos * 2) | (_MODE_OUT << LED1_Pin_Pos * 2)));
  /* Speed */
  // MODIFY_REG(GPIOG->OSPEEDR, (GPIO_PIN_13_Mask | GPIO_PIN_14_Mask), ((_SPEED_L << GPIO_PIN_13_Pos * 2) | (_SPEED_L << GPIO_PIN_14_Pos * 2)));
  /* Output type */
  // MODIFY_REG(GPIOG->OTYPER, ((_OTYPE_PP << GPIO_PIN_13_Pos) | (_OTYPE_PP << GPIO_PIN_14_Pos)), ((_OTYPE_PP << GPIO_PIN_13_Pos) | (_OTYPE_PP << GPIO_PIN_14_Pos)));
  /* Push mode */
  // MODIFY_REG(GPIOG->PUPDR, (GPIO_PIN_13_Mask | GPIO_PIN_14_Mask), ((_PUPD_NO << GPIO_PIN_13_Pos * 2) | (_PUPD_NO << GPIO_PIN_14_Pos * 2)));
}


/**
  * @brief  This function blink a LED.
  * @param  port: a pointer to a GPIO port
  * @param  pinSource: a number of pin in a port
  * @retval None
  */
void LED_Blink(GPIO_TypeDef* port, uint16_t pinSource) {
  (PIN_LEVEL(port, pinSource)) ? PIN_L(port, pinSource) : PIN_H(port, pinSource);
}