/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of timers instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _TIMREG_ = 0;









////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  Initialises Basic Timer7
  * @param  None
  * @retval None
  */
void BasicTimer6_Init(void) {
  /* TIM7 interrupt Init */
  NVIC_SetPriority(TIM6_DAC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
  NVIC_EnableIRQ(TIM6_DAC_IRQn);

  TIM6->PSC = 54000U - 1U; // APB1 runs on max freq of SystemCoreClock/2
  TIM6->ARR = 2000U - 1U;
  /* Autoreload enable */ 
  PREG_SET(TIM6->CR1, TIM_CR1_ARPE_Pos);

  /* Interrupt enabling passes */
  PREG_CLR(TIM6->SR, TIM_SR_UIF_Pos);
  PREG_SET(TIM6->DIER, TIM_DIER_UIE_Pos);
  PREG_SET(TIM6->CR1, TIM_CR1_CEN_Pos);

}



/**
  * @brief  Basic Timer Handler called from interrupt via flag's handler
  * @param  tim: pointer to a basic timer instance
  * @retval None
  */
void Timer_Handler(TIM_TypeDef* tim) {
  if (tim == TIM6) {
    // printf("tim6\n");
  }
}


// void PrintDateTime(PrintDateTimeTypeDef dst) {
//   static char dateStr[12];
//   static char timeStr[12];

//   sprintf(timeStr, "%2x:%02x:%02x ", RTC_GetHour, RTC_GetMinute, RTC_GetSecond);
//   sprintf(dateStr, "%2x/%x/%4x ", RTC_GetDay, RTC_GetMonth, RTC_GetYear);

//   switch (dst) {
//   case _printf:
//     printf("date: %s\n\r", dateStr);
//     printf("time: %s\n\r", timeStr);
//     break;
  
//   default:
//     break;
//   }
// }