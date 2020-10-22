/**
  ******************************************************************************
  * File Name          : RTC.h
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H
#define __RTC_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _RTCREG_;


/* Private defines -----------------------------------------------------------*/
// SPI Registry Flags
#define _ALAF_        0 // Alarm A Flag
#define _ALBF_        1 // Alarm B Flag
#define _WUTF_        2 // Wake Up Timer Flag



#define RTC_GetYear     (uint16_t)(((READ_BIT(RTC->DR, (RTC_DR_YT | RTC_DR_YU))) >> RTC_DR_YU_Pos) + 0x2000)
#define RTC_GetMonth    (uint16_t)((READ_BIT(RTC->DR, (RTC_DR_MT | RTC_DR_MU)))>> RTC_DR_MU_Pos)
#define RTC_GetDay      (uint16_t)((READ_BIT(RTC->DR, (RTC_DR_DT | RTC_DR_DU))) >> RTC_DR_DU_Pos)
#define RTC_GetWeekDay  (uint16_t)(READ_BIT(RTC->DR, RTC_DR_WDU) >> RTC_DR_WDU_Pos)
#define RTC_GetHour     (uint16_t)((READ_BIT(RTC->TR, (RTC_TR_HT | RTC_TR_HU))) >> RTC_TR_HU_Pos)
#define RTC_GetMinute   (uint16_t)(READ_BIT(RTC->TR, (RTC_TR_MNT | RTC_TR_MNU))>> RTC_TR_MNU_Pos)
#define RTC_GetSecond   (uint16_t)(READ_BIT(RTC->TR, (RTC_TR_ST | RTC_TR_SU)) >> RTC_TR_SU_Pos)



/* Exported functions prototypes ---------------------------------------------*/
void RTC_Init(void);
void RTC_SetDateTime(struct tm timeStruct);
void RTC_GetDateTime(uint8_t *buf);
void RTC_Alarm_Handler(char alarm);
void RTC_WakeUp_Handler(void);
void RTC_SetAlarm(char alarm, uint32_t alarmVal);
void RTC_DisableAlarm(char alarm);



#ifdef __cplusplus
}
#endif
#endif /*__RTC_H */
