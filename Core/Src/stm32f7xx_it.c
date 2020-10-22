/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
  //
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
  while (1) {
    //
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
  while (1) {
    //
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void) {
  while (1) {
    //
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
  while (1) {
    //
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {
  //
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
  //
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void) {
  //
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
  //
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles RCC global interrupt.
  */
void RCC_IRQHandler(void) {
  //
}

/**
  * @brief This function handles EXTI0 global interrupt.
  */
void EXTI0_IRQHandler(void) {
  /* clear pending bit */
  PREG_SET(EXTI->PR, EXTI_IMR_MR0_Pos);
  __NOP();
  FLAG_SET(_EXTIREG_, _WUBAF_);
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void) {
  /* Clear RXNE bit */
  PREG_SET(USART1->RQR, USART_RQR_RXFRQ_Pos);
  __NOP();
  FLAG_SET(_USARTREG_, _USART1_RXAF_);
}

/**
  * @brief This function handles RTC alarms A and B interrupt through EXTI line 17.
  */
void RTC_Alarm_IRQHandler(void) {
  /* Clear penfing bit */
  PREG_SET(EXTI->PR, EXTI_IMR_MR17_Pos); 
  /* Alarm A */
  if (PREG_CHECK(RTC->ISR, RTC_ISR_ALRAF_Pos)) {
    PREG_CLR(RTC->ISR, RTC_ISR_ALRAF_Pos);
    PREG_CLR(RTC->ISR, RTC_ISR_INIT_Pos);
    // WRITE_REG(RTC->ISR, (~((RTC_ISR_ALRAF | RTC_ISR_INIT) & 0x0000FFFFU) | (RTC->ISR & RTC_ISR_INIT)));
    FLAG_SET(_RTCREG_, _ALAF_);
  }
  /* Alarm B */
  if (PREG_CHECK(RTC->ISR, RTC_ISR_ALRBF_Pos)) {
    PREG_CLR(RTC->ISR, RTC_ISR_ALRBF_Pos);
    PREG_CLR(RTC->ISR, RTC_ISR_INIT_Pos);
    FLAG_SET(_RTCREG_, _ALBF_);
  }
  /* Wake Up */
  if (PREG_CHECK(RTC->ISR, RTC_ISR_WUTF_Pos)) {
    PREG_CLR(RTC->ISR, RTC_ISR_WUTF_Pos);
    PREG_CLR(RTC->ISR, RTC_ISR_INIT_Pos);
    FLAG_SET(_RTCREG_, _WUTF_);
  }
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM6_DAC_IRQHandler(void) {
  PREG_CLR(TIM6->SR, TIM_SR_UIF_Pos);
  FLAG_SET(_TIMREG_, _BT6F_);
}

/**
  * @brief This function handles LTDC global interrupt.
  */
void LTDC_IRQHandler(void) {

}

/**
  * @brief This function handles DMA2D global interrupt.
  */
void DMA2D_IRQHandler(void) {

}

/**
  * @brief This function handles DSI global interrupt.
  */
void DSI_IRQHandler(void) {

}

