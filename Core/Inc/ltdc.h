/**
  ******************************************************************************
  * File Name          : LTDC.h
  * Description        : This file provides code for the configuration
  *                      of the LTDC instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LTDC_H
#define __LTDC_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _LTDCREG_;

/**LTDC GPIO Configuration    
  PC10    ------> LTDC_R2
  PA6     ------> LTDC_G2
  PD6     ------> LTDC_B2
  PB0     ------> LTDC_R3
  PG10    ------> LTDC_G3
  PG11    ------> LTDC_B3
  PA11    ------> LTDC_R4
  PB10    ------> LTDC_G4
  PG12    ------> LTDC_B4
  PA12    ------> LTDC_R5
  PB11    ------> LTDC_G5
  PA3     ------> LTDC_B5
  PB1     ------> LTDC_R6
  PC7     ------> LTDC_G6
  PB8     ------> LTDC_B6
  PG6     ------> LTDC_R7
  PD3     ------> LTDC_G7
  PB9     ------> LTDC_B7
  PC6     ------> LTDC_HSYNC
  PA4     ------> LTDC_VSYNC
  PG7     ------> LTDC_CLK
  PF10    ------> LTDC_DE
  PD11    ------> TE
  PD12    ------> RDX
  PD13    ------> WRX
  PC2     ------> SPI_CS
*/

// PC10
#define R2_Pin                    GPIO_PIN_10
#define R2_Pin_Pos                GPIO_PIN_10_Pos
#define R2_Pin_Mask               GPIO_PIN_10_Mask
// PA6
#define G2_Pin                    GPIO_PIN_6
#define G2_Pin_Pos                GPIO_PIN_6_Pos
#define G2_Pin_Mask               GPIO_PIN_6_Mask
// PD6
#define B2_Pin                    GPIO_PIN_6
#define B2_Pin_Pos                GPIO_PIN_6_Pos
#define B2_Pin_Mask               GPIO_PIN_6_Mask
// PB0
#define R3_Pin                    GPIO_PIN_0
#define R3_Pin_Pos                GPIO_PIN_0_Pos
#define R3_Pin_Mask               GPIO_PIN_0_Mask
// PG10
#define G3_Pin                    GPIO_PIN_10
#define G3_Pin_Pos                GPIO_PIN_10_Pos
#define G3_Pin_Mask               GPIO_PIN_10_Mask
// PG11
#define B3_Pin                    GPIO_PIN_11
#define B3_Pin_Pos                GPIO_PIN_11_Pos
#define B3_Pin_Mask               GPIO_PIN_11_Mask
// PA11
#define R4_Pin                    GPIO_PIN_11
#define R4_Pin_Pos                GPIO_PIN_11_Pos
#define R4_Pin_Mask               GPIO_PIN_11_Mask
// PB10
#define G4_Pin                    GPIO_PIN_10
#define G4_Pin_Pos                GPIO_PIN_10_Pos
#define G4_Pin_Mask               GPIO_PIN_10_Mask
// PG12
#define B4_Pin                    GPIO_PIN_12
#define B4_Pin_Pos                GPIO_PIN_12_Pos
#define B4_Pin_Mask               GPIO_PIN_12_Mask
// PA12
#define R5_Pin                    GPIO_PIN_12
#define R5_Pin_Pos                GPIO_PIN_12_Pos
#define R5_Pin_Mask               GPIO_PIN_12_Mask
// PB11
#define G5_Pin                    GPIO_PIN_11
#define G5_Pin_Pos                GPIO_PIN_11_Pos
#define G5_Pin_Mask               GPIO_PIN_11_Mask
// PA3
#define B5_Pin                    GPIO_PIN_3
#define B5_Pin_Pos                GPIO_PIN_3_Pos
#define B5_Pin_Mask               GPIO_PIN_3_Mask
// PB1
#define R6_Pin                    GPIO_PIN_1
#define R6_Pin_Pos                GPIO_PIN_1_Pos
#define R6_Pin_Mask               GPIO_PIN_1_Mask
// PC7
#define G6_Pin                    GPIO_PIN_7
#define G6_Pin_Pos                GPIO_PIN_7_Pos
#define G6_Pin_Mask               GPIO_PIN_7_Mask
// PB8
#define B6_Pin                    GPIO_PIN_8
#define B6_Pin_Pos                GPIO_PIN_8_Pos
#define B6_Pin_Mask               GPIO_PIN_8_Mask
// PG6
#define R7_Pin                    GPIO_PIN_6
#define R7_Pin_Pos                GPIO_PIN_6_Pos
#define R7_Pin_Mask               GPIO_PIN_6_Mask
// PD3
#define G7_Pin                    GPIO_PIN_3
#define G7_Pin_Pos                GPIO_PIN_3_Pos
#define G7_Pin_Mask               GPIO_PIN_3_Mask
// PB9
#define B7_Pin                    GPIO_PIN_9
#define B7_Pin_Pos                GPIO_PIN_9_Pos
#define B7_Pin_Mask               GPIO_PIN_9_Mask
// PC6
#define HSYNC_Pin                 GPIO_PIN_6
#define HSYNC_Pin_Pos             GPIO_PIN_6_Pos
#define HSYNC_Pin_Mask            GPIO_PIN_6_Mask
// PA4
#define VSYNC_Pin                 GPIO_PIN_4
#define VSYNC_Pin_Pos             GPIO_PIN_4_Pos
#define VSYNC_Pin_Mask            GPIO_PIN_4_Mask
// PG7
#define CLK_Pin                   GPIO_PIN_7
#define CLK_Pin_Pos               GPIO_PIN_7_Pos
#define CLK_Pin_Mask              GPIO_PIN_7_Mask
// PF10
#define DE_Pin                    GPIO_PIN_10
#define DE_Pin_Pos                GPIO_PIN_10_Pos
#define DE_Pin_Mask               GPIO_PIN_10_Mask
// PD11
#define TE_Pin                    GPIO_PIN_11
#define TE_Pin_Pos                GPIO_PIN_11_Pos
#define TE_Pin_Mask               GPIO_PIN_11_Mask
// PD12
#define RDX_Pin                   GPIO_PIN_12
#define RDX_Pin_Pos               GPIO_PIN_12_Pos
#define RDX_Pin_Mask              GPIO_PIN_12_Mask
// PD13
#define WRX_Pin                   GPIO_PIN_13
#define WRX_Pin_Pos               GPIO_PIN_13_Pos
#define WRX_Pin_Mask              GPIO_PIN_13_Mask
// PC2
#define CS_Pin                    GPIO_PIN_2
#define CS_Pin_Pos                GPIO_PIN_2_Pos
#define CS_Pin_Mask               GPIO_PIN_2_Mask



#define HSPOL_AL                  0x00000000        /* Horizontal Synchronization is active low. */
#define HSPOL_AH                  LTDC_GCR_HSPOL    /* Horizontal Synchronization is active high. */
#define VSPOL_AL                  0x00000000        /* Vertical Synchronization is active low. */
#define VSPOL_AH                  LTDC_GCR_VSPOL    /* Vertical Synchronization is active high. */
#define DEPOL_AL                  0x00000000        /* Data Enable, is active low. */
#define DEPOL_AH                  LTDC_GCR_DEPOL    /* Data Enable, is active high. */
#define PCPOL_IPC                 0x00000000        /* input pixel clock. */
#define PCPOL_IIPC                LTDC_GCR_PCPOL    /* inverted input pixel clock. */


#define L1                        1
#define L2                        2
#define ALPHA_Pos                 24


#define PIXEL_FORMAT_ARGB8888     0x00000000   /* ARGB8888 LTDC pixel format */
#define PIXEL_FORMAT_RGB888       0x00000001   /* RGB888 LTDC pixel format */
#define PIXEL_FORMAT_RGB565       0x00000002   /* RGB565 LTDC pixel format */
#define PIXEL_FORMAT_ARGB1555     0x00000003   /* ARGB1555 LTDC pixel format */
#define PIXEL_FORMAT_ARGB4444     0x00000004   /* ARGB4444 LTDC pixel format */
#define PIXEL_FORMAT_L8           0x00000005   /* L8 LTDC pixel format */
#define PIXEL_FORMAT_AL44         0x00000006   /* AL44 LTDC pixel format */
#define PIXEL_FORMAT_AL88         0x00000007   /* AL88 LTDC pixel format */

#define BLENDING_FACTOR1_CA       0x00000400   /* Blending factor : Cte Alpha */
#define BLENDING_FACTOR1_PAxCA    0x00000600   /* Blending factor : Cte Alpha x Pixel Alpha */
#define BLENDING_FACTOR2_CA       0x00000005   /* Blending factor : Cte Alpha */
#define BLENDING_FACTOR2_PAxCA    0x00000007   /* Blending factor : Cte Alpha x Pixel Alpha */




/* Private defines -----------------------------------------------------------*/
// LTDC Registry Flags



/* Exported functions prototypes ---------------------------------------------*/
void LTDC_Init(void);




#ifdef __cplusplus
}
#endif
#endif /*__LTDC_H */
