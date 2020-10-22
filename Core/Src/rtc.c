/**
  ******************************************************************************
  * File Name          : rtc.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _RTCREG_ = 0;










////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  RTC Initialisation
  * @param  None
  * @retval None
  */
void RTC_Init(void) {
  /* unlock write to Backup Registers */
  // PREG_SET(PWR->CR, PWR_CR_DBP_Pos);
  /* unlock RTC protection */
  // WRITE_REG(RTC->WPR, 0xca);
  // WRITE_REG(RTC->WPR, 0x53);

  /* Enable RTC on LSI */
  // PREG_CLR(RCC->BDCR, RCC_BDCR_RTCEN_Pos);
  // PREG_SET(RCC->BDCR, RCC_BDCR_BDRST_Pos);
  // PREG_CLR(RCC->BDCR, RCC_BDCR_BDRST_Pos);
  // MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_1);
  // PREG_SET(RCC->BDCR, RCC_BDCR_RTCEN_Pos);

  /* lock RTC protection */
  // WRITE_REG(RTC->WPR, 0x00);
  /* lock write to Backup Registers */
  // PREG_CLR(PWR->CR, PWR_CR_DBP_Pos);

  /* EXTI channel to catch an interrupt */
  SET_BIT(EXTI->IMR, EXTI_IMR_IM17);     /* set interrupts */
  SET_BIT(EXTI->RTSR, EXTI_IMR_IM17);    /* set rising edge */
  /* RTC interrupt Init */
  NVIC_SetPriority(RTC_Alarm_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 14, 0));
  NVIC_EnableIRQ(RTC_Alarm_IRQn);


  /* Configure Date and Time */
  struct tm timeStruct = {
    .tm_year = 2020, 
    .tm_mon = 9,
    .tm_mday = 30,
    .tm_wday = 5,
    .tm_hour = 22,
    .tm_min = 12,
    .tm_sec = 59
  };
  RTC_SetDateTime(timeStruct);


  /* Configure alarms */
  RTC_SetAlarm('A', 0);
  RTC_SetAlarm('B', 0);
  // RTC_DisableAlarm('A');
  // RTC_DisableAlarm('B');

 
}






/**
  * @brief  Sets date and time into RTC register
  * @param  timestamp: time.h datetime struct
  * @retval None
  */
void RTC_SetDateTime(struct tm timeStruct) {
  /* unlock write to Backup Registers */
  // PREG_SET(PWR->CR, PWR_CR_DBP_Pos);
  /* unlock RTC protection */
  WRITE_REG(RTC->WPR, 0xca);
  WRITE_REG(RTC->WPR, 0x53); 

  PREG_SET(RTC->ISR, RTC_ISR_INIT_Pos);
  while (!(PREG_CHECK(RTC->ISR, RTC_ISR_INITF_Pos)));
  
  static __IO uint32_t _reg = 0;

  _reg = (
      ((timeStruct.tm_hour / 10) << RTC_TR_HT_Pos)  | ((timeStruct.tm_hour % 10) << RTC_TR_HU_Pos)
    | ((timeStruct.tm_min / 10) << RTC_TR_MNT_Pos) | ((timeStruct.tm_min % 10) << RTC_TR_MNU_Pos)
    | ((timeStruct.tm_sec / 10) << RTC_TR_ST_Pos)  | ((timeStruct.tm_sec % 10) << RTC_TR_SU_Pos)
  );
  RTC->TR = _reg;

  _reg = (
      (((timeStruct.tm_year - 2000) / 10) << RTC_DR_YT_Pos) | (((timeStruct.tm_year - 2000) % 10) << RTC_DR_YU_Pos)
    | ((timeStruct.tm_mon / 10) << RTC_DR_MT_Pos)  | ((timeStruct.tm_mon % 10) << RTC_DR_MU_Pos)
    | ((timeStruct.tm_mday / 10) << RTC_DR_DT_Pos)  | ((timeStruct.tm_mday % 10) << RTC_DR_DU_Pos)
    | (timeStruct.tm_wday << RTC_DR_WDU_Pos)
  );
  RTC->DR = _reg;

  PREG_CLR(RTC->ISR, RTC_ISR_INIT_Pos);
  while (PREG_CHECK(RTC->ISR, RTC_ISR_INITF_Pos));

  /* lock RTC protection */
  WRITE_REG(RTC->WPR, 0x00);
  /* lock write to Backup Registers */
  // PREG_CLR(PWR->CR, PWR_CR_DBP_Pos);
}



/**
  * @brief  Gets date and time from RTC register into buffer
  * @param  buf: a link to save date and time
  * @retval None
  */
void RTC_GetDateTime(uint8_t *buf) {

}



/**
  * @brief  RTC Alarm Handler called from interrupt via flags
  * @param  alarm: alarm A or B
  * @retval None
  */
void RTC_Alarm_Handler(char alarm) {
  if (alarm == 'A') {
    LED_Blink(LED_Port, RED_LED);
  }

  if (alarm == 'B') {
    LED_Blink(LED_Port, GREEN_LED);
  }
}




/**
  * @brief  RTC WakeUp Handler called from interrupt via flags
  * @param  None:
  * @retval None
  */
void RTC_WakeUp_Handler(void) {
  //
}




/*
 * RTC Alarm Handler called from interrupt via flags
 */
/**
  * @brief  Sets RTC Alarm value
  * @param  alarm: an alarm channel
  * @param  alarmVal: an alarm value
  * @retval None
  */
void RTC_SetAlarm(char alarm, uint32_t alarmVal) {
  /* unlock write to Backup Registers */
  // PREG_SET(PWR->CR, PWR_CR_DBP_Pos);
  /* unlock RTC protection */
  WRITE_REG(RTC->WPR, 0xca);
  WRITE_REG(RTC->WPR, 0x53);

  /* Set alarms A */
  if (alarm == 'A') {
    PREG_CLR(RTC->CR, RTC_CR_ALRAIE_Pos);
    PREG_CLR(RTC->CR, RTC_CR_ALRAE_Pos);
    while (!(PREG_CHECK(RTC->ISR, RTC_ISR_ALRAWF_Pos)));
    /* ~0.5s */
    RTC->ALRMAR = (RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1);
    RTC->ALRMASSR = (6 << RTC_ALRMASSR_MASKSS_Pos) | (0x0000 << RTC_ALRMASSR_SS_Pos);
    PREG_CLR(RTC->ISR, RTC_ISR_ALRAF_Pos);
    PREG_SET(RTC->CR, RTC_CR_ALRAIE_Pos);
    PREG_SET(RTC->CR, RTC_CR_ALRAE_Pos);
  }

  /* Set alarms B */
  if (alarm == 'B') {
    PREG_CLR(RTC->CR, RTC_CR_ALRBIE_Pos);
    PREG_CLR(RTC->CR, RTC_CR_ALRBE_Pos);
    while (!(PREG_CHECK(RTC->ISR, RTC_ISR_ALRBWF_Pos)));
    /* ~1s */
    RTC->ALRMBR = (RTC_ALRMBR_MSK4 | RTC_ALRMBR_MSK3 | RTC_ALRMBR_MSK2 | RTC_ALRMBR_MSK1);
    RTC->ALRMBSSR = (8 << RTC_ALRMBSSR_MASKSS_Pos) | (0x0000 << RTC_ALRMBSSR_SS_Pos);
    PREG_CLR(RTC->ISR, RTC_ISR_ALRBF_Pos);
    // __NOP();
    PREG_SET(RTC->CR, RTC_CR_ALRBIE_Pos);
    PREG_SET(RTC->CR, RTC_CR_ALRBE_Pos);
  }

  /* lock RTC protection */
  WRITE_REG(RTC->WPR, 0x00);
  /* lock write to Backup Registers */
  // PREG_CLR(PWR->CR, PWR_CR_DBP_Pos);
}



/**
  * @brief  Disables RTC Alarm
  * @param  alarm: an alarm channel
  * @retval None
  */
void RTC_DisableAlarm(char alarm) {
  if (alarm == 'A') {
    PREG_CLR(RTC->CR, RTC_CR_ALRAIE_Pos);
    PREG_CLR(RTC->CR, RTC_CR_ALRAE_Pos);
    while (!(PREG_CHECK(RTC->ISR, RTC_ISR_ALRAWF_Pos)));
  }

  if (alarm == 'B') {
    PREG_CLR(RTC->CR, RTC_CR_ALRBIE_Pos);
    PREG_CLR(RTC->CR, RTC_CR_ALRBE_Pos);
    while (!(PREG_CHECK(RTC->ISR, RTC_ISR_ALRBWF_Pos)));
  }
}
