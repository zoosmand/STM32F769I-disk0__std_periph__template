/**
  ******************************************************************************
  * File Name          : EXTI.c
  * Description        : This file provides code for the configuration
  *                      of the EXTI instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "exti.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _EXTIREG_ = 0;









void EXTI_Init(void) {
  /* GPIO Wake-Up PA0, Touch Screen PA15 */
  /* Mode */
  // MODIFY_REG(GPIOA->MODER, (GPIO_PIN_1_Mask | GPIO_PIN_15_Mask), ((_MODE_IN << GPIO_PIN_1_Pos * 2) | (_MODE_IN << GPIO_PIN_15_Pos * 2)));
  /* Speed */
  // MODIFY_REG(GPIOA->OSPEEDR, (GPIO_PIN_1_Mask | GPIO_PIN_15_Mask), ((_SPEED_L << GPIO_PIN_1_Pos * 2) | (_SPEED_L << GPIO_PIN_15_Pos * 2)));
  /* Output type */
  // MODIFY_REG(GPIOA->OTYPER, ((_OTYPE_PP << GPIO_PIN_1_Pos) | (_OTYPE_PP << GPIO_PIN_15_Pos)), ((_OTYPE_PP << GPIO_PIN_1_Pos) | (_OTYPE_PP << GPIO_PIN_15_Pos)));
  /* Push mode */
  // MODIFY_REG(GPIOA->PUPDR, (GPIO_PIN_1_Mask | GPIO_PIN_15_Mask), ((_PUPD_NO << GPIO_PIN_1_Pos * 2) | (_PUPD_NO << GPIO_PIN_15_Pos * 2)));

  /* EXTI channel to catch an interrupt */
  // CLEAR_BIT(EXTI->EMR, (EXTI_IMR_IM0 | EXTI_IMR_IM15));   /* clear events */
  SET_BIT(EXTI->IMR, EXTI_IMR_IM0);     /* set interrupts */
  // CLEAR_BIT(EXTI->FTSR, (EXTI_IMR_IM0 | EXTI_IMR_IM15));  /* clear fallng egde */
  SET_BIT(EXTI->RTSR, EXTI_IMR_IM0);    /* set rising edge */

  /* Wake-Up PA0, interrupt Init */
  NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
  NVIC_EnableIRQ(EXTI0_IRQn);

}
