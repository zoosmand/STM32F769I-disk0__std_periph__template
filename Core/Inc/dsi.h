/**
  ******************************************************************************
  * File Name          : DSI.h
  * Description        : This file provides code for the configuration
  *                      of the DSI instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DSI_H
#define __DSI_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _DSIREG_;


/* Private defines -----------------------------------------------------------*/
#define LCD_CLOCK                         (uint16_t)27429 // 27429 kHz
#define LANE_BYTE_CLOCK                   (uint16_t)62500 // 500 MHz / 8 = 62.5 MHz = 62500 kHz

#define DSI_RGB565                        0x00000000U /*The values 0x00000001 and 0x00000002 can also be used for the RGB565 color mode configuration */
#define DSI_RGB666                        0x00000003U /*The value 0x00000004 can also be used for the RGB666 color mode configuration                 */
#define DSI_RGB888                        0x00000005U

#define DSI_DCS_SHORT_PKT_WRITE_P0        0x05 /* DCS short write, no parameters */
#define DSI_DCS_SHORT_PKT_WRITE_P1        0x15 /* DCS short write, one parameter */
#define DSI_GEN_SHORT_PKT_WRITE_P0        0x03 /* Generic short write, no parameters */
#define DSI_GEN_SHORT_PKT_WRITE_P1        0x13 /* Generic short write, one parameter */
#define DSI_GEN_SHORT_PKT_WRITE_P2        0x23 /* Generic short write, two parameters */
#define DSI_DCS_LONG_PKT_WRITE            0x39 /* DCS long write */
#define DSI_GEN_LONG_PKT_WRITE            0x29 /* Generic long write */
#define DSI_DCS_SHORT_PKT_READ            0x06 /* DCS short read */
#define DSI_GEN_SHORT_PKT_READ_P0         0x04 /* Generic short read, no parameters */
#define DSI_GEN_SHORT_PKT_READ_P1         0x14 /* Generic short read, one parameter */
#define DSI_GEN_SHORT_PKT_READ_P2         0x24 /* Generic short read, two parameters */

// PJ2
#define DSI_TE_Pin          GPIO_PIN_2
#define DSI_TE_Pin_Pos      GPIO_PIN_2_Pos
#define DSI_TE_Pin_Mask     GPIO_PIN_2_Mask
#define DSI_TE_Port         GPIOJ
// PJ15
#define DSI_RESET_Pin       GPIO_PIN_15
#define DSI_RESET_Pin_Pos   GPIO_PIN_15_Pos
#define DSI_RESET_Pin_Mask  GPIO_PIN_15_Mask
#define DSI_RESET_Port      GPIOJ


/* Exported functions prototypes ---------------------------------------------*/
void DSI_Init(void);
void DSI_Run(void);
void DSI_ShortWrite(uint8_t ch, uint8_t mode, uint8_t p1, uint8_t p2);
void DSI_LongWrite(uint8_t ch, uint8_t mode, uint32_t cnt, uint8_t p1, uint8_t *p2);
void DSI_Write(uint32_t cnt, uint8_t *buf);

#ifdef __cplusplus
}
#endif
#endif /*__DSI_H */
