/**
  ******************************************************************************
  * File Name          : dma2d.c
  * Description        : This file provides code for the configuration
  *                      of the GPIO instances for DMA2D's indication.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "dma2d.h"

/* Global variables ---------------------------------------------------------*/


void DMA2D_Init(void) {
  /* DMA2D register to memory transfer mode */
  MODIFY_REG(DMA2D->CR, DMA2D_CR_MODE_Msk, 3);
  /* ARGB8888 DMA2D color mode */
  MODIFY_REG(DMA2D->OPFCCR, DMA2D_OPFCCR_CM_Msk, 0);
  /* Set output offset */
  MODIFY_REG(DMA2D->OOR, DMA2D_OOR_LO_Msk, 0);
  /* DMA2D OPFCCR AI and RBS fields setting (Output Alpha Inversion)*/
  /* No modification of the alpha channel value */
  /* Select regular mode (RGB or ARGB) */
  MODIFY_REG(DMA2D->OPFCCR, (DMA2D_OPFCCR_AI_Msk | DMA2D_OPFCCR_RBS_Msk), ((0 << DMA2D_OPFCCR_AI_Pos) | (0 << DMA2D_OPFCCR_RBS_Pos)));
  /* Set memeory address*/
  DMA2D->OMAR = SDRAM_START_ADDR;
  /* Set output color */
  DMA2D->OCOLR = 0xff000000;
  /* Set lines and pixel per line */
  #ifdef _LANDSCAPE_
    MODIFY_REG(DMA2D->NLR, (DMA2D_NLR_NL_Msk | DMA2D_NLR_PL_Msk), ((DISPLAY_HEIGHT << DMA2D_NLR_NL_Pos) | (DISPLAY_WIDTH << DMA2D_NLR_PL_Pos)));
  #else
    MODIFY_REG(DMA2D->NLR, (DMA2D_NLR_NL_Msk | DMA2D_NLR_PL_Msk), ((DISPLAY_HEIGHT << DMA2D_NLR_NL_Pos) | (DISPLAY_WIDTH << DMA2D_NLR_PL_Pos)));
  #endif
  
  DMA2D_ForegroundLayer_Init();
  DMA2D_BackgroundLayer_Init();

  /** @brief NVIC configuration for DMA2D interrupt that is now enabled */
  NVIC_SetPriority(DMA2D_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 7, 0));
  NVIC_EnableIRQ(DMA2D_IRQn);


}




void DMA2D_ForegroundLayer_Init(void) {
  MODIFY_REG(DMA2D->FGPFCCR, (DMA2D_FGPFCCR_CM | DMA2D_FGPFCCR_AM | DMA2D_FGPFCCR_ALPHA | DMA2D_FGPFCCR_AI | DMA2D_FGPFCCR_RBS),
      (0 << DMA2D_FGPFCCR_CM_Pos) /* ARGB8888 color mode */
    | (0 << DMA2D_FGPFCCR_ALPHA_Pos) /* A4 or A8 Alpa offset*/
    | (0 << DMA2D_FGPFCCR_AM_Pos) /* No modification of the alpha channel value */
    | (0 << DMA2D_FGPFCCR_AI_Pos) /* No modification of the alpha channel value */
    | (0 << DMA2D_FGPFCCR_RBS_Pos) /* Select regular mode (RGB or ARGB) */
  );

  WRITE_REG(DMA2D->FGOR, 0); /* Set no offset */
}




void DMA2D_BackgroundLayer_Init(void) {
  MODIFY_REG(DMA2D->FGPFCCR, (DMA2D_BGPFCCR_CM | DMA2D_BGPFCCR_AM | DMA2D_BGPFCCR_ALPHA | DMA2D_BGPFCCR_AI | DMA2D_BGPFCCR_RBS),
      (0 << DMA2D_BGPFCCR_CM_Pos) /* ARGB8888 color mode */
    | (0 << DMA2D_BGPFCCR_ALPHA_Pos) /* A4 or A8 Alpa offset*/
    | (0 << DMA2D_BGPFCCR_AM_Pos) /* No modification of the alpha channel value */
    | (0 << DMA2D_BGPFCCR_AI_Pos) /* No modification of the alpha channel value */
    | (0 << DMA2D_BGPFCCR_RBS_Pos) /* Select regular mode (RGB or ARGB) */
  );

  WRITE_REG(DMA2D->BGOR, 0); /* Set no offset */
}




