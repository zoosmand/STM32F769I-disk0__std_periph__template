/**
  ******************************************************************************
  * File Name          : LTDC.c
  * Description        : This file provides code for the configuration
  *                      of the LTDC instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fmc.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _LTDCREG_ = 0;

/* Private function prototypes -----------------------------------------------*/
static void LTDC_ConfigLayer1(void);
static void LTDC_ConfigLayer2(void);








////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Initializes LTDC peripheral 
  * @param  None
  * @retval None
  */
void LTDC_Init(void) {
  /* Configure the HS, VS, DE and PC polarity */
  MODIFY_REG(LTDC->GCR, (LTDC_GCR_HSPOL_Msk | LTDC_GCR_VSPOL_Msk | LTDC_GCR_DEPOL_Msk | LTDC_GCR_PCPOL_Msk), (
      (1 << LTDC_GCR_HSPOL_Pos)
    | (1 << LTDC_GCR_VSPOL_Pos)
    | (0 << LTDC_GCR_DEPOL_Pos)
    | (0 << LTDC_GCR_PCPOL_Pos)
  ));
  /* Set Synchronization size */
  MODIFY_REG(LTDC->SSCR, (LTDC_SSCR_VSH_Msk | LTDC_SSCR_HSW_Msk), (
      ((_VSA_ - 1) << LTDC_SSCR_VSH_Pos)
    | ((_HSA_ - 1) << LTDC_SSCR_HSW_Pos)
  ));
  /* Set Accumulated Back porch */
  MODIFY_REG(LTDC->BPCR, (LTDC_BPCR_AVBP_Msk | LTDC_BPCR_AHBP_Msk), (
      ((_VSA_ + _VBP_ - 1) << LTDC_BPCR_AVBP_Pos)
    | ((_HSA_ + _HBP_ - 1) << LTDC_BPCR_AHBP_Pos)
  ));

  /* Set Accumulated Active Width and Height */
  #ifdef _LANDSCAPE_
    MODIFY_REG(LTDC->AWCR, (LTDC_AWCR_AAW_Msk | LTDC_AWCR_AAH_Msk), (
        ((DISPLAY_WIDTH + _VSA_ + _VBP_ - 1) << LTDC_AWCR_AAH_Pos)
      | ((DISPLAY_HEIGHT + _HSA_ + _HBP_ - 1) << LTDC_AWCR_AAW_Pos)
    ));
  #else
    MODIFY_REG(LTDC->AWCR, (LTDC_AWCR_AAW_Msk | LTDC_AWCR_AAH_Msk), (
        ((DISPLAY_WIDTH + _HSA_ + _HBP_ - 1) << LTDC_AWCR_AAW_Pos)
      | ((DISPLAY_HEIGHT + _VSA_ + _VBP_ - 1) << LTDC_AWCR_AAH_Pos)
    ));
  #endif

    /* Set Total Width and Height */
  #ifdef _LANDSCAPE_
    MODIFY_REG(LTDC->TWCR, (LTDC_TWCR_TOTALW_Msk | LTDC_TWCR_TOTALH_Msk), (
        ((DISPLAY_WIDTH + _VSA_ + _VBP_ + _VFP_ - 1) << LTDC_TWCR_TOTALH_Pos)
      | ((DISPLAY_HEIGHT + _HSA_ + _HBP_ + _HFP_ - 1) << LTDC_TWCR_TOTALW_Pos)
    ));
  #else
    MODIFY_REG(LTDC->TWCR, (LTDC_TWCR_TOTALW_Msk | LTDC_TWCR_TOTALH_Msk), (
        ((DISPLAY_WIDTH + _HSA_ + _HBP_ + _HFP_ - 1) << LTDC_TWCR_TOTALW_Pos)
      | ((DISPLAY_HEIGHT + _VSA_ + _VBP_ + _VFP_ - 1) << LTDC_TWCR_TOTALH_Pos)
    ));
  #endif
  
  /* Set the background color value */
  LTDC->BCCR = ARGB8888_Lightblue;
  /* Enable the Transfer Error and FIFO underrun interrupts */
  MODIFY_REG(LTDC->IER, (LTDC_IER_TERRIE_Msk | LTDC_IER_FUIE_Msk),  (LTDC_IER_TERRIE | LTDC_IER_FUIE));


  
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  LTDC_ConfigLayer1();
  LTDC_ConfigLayer2();  

  /* Enable Dither by setting DTEN bit */
  PREG_SET(LTDC->GCR, LTDC_GCR_DEN_Pos);

  /* Enable LTDC by setting LTDCEN bit */
  PREG_SET(LTDC->GCR, LTDC_GCR_LTDCEN_Pos);

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /** @brief NVIC configuration for LTDC interrupt that is now enabled */
  NVIC_SetPriority(LTDC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 7, 0));
  NVIC_EnableIRQ(LTDC_IRQn);

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  DSI_Run();

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  FillLayer(L1, _WHITE_0);
  FillLayer(L2, _WHITE_0);

  
}







/**
  * @brief  Setup an LTDC Layer 1.
  * @param  None
  * @retval None
  */
static void LTDC_ConfigLayer1(void) {
  LTDC_Layer_TypeDef* layer = (LTDC_Layer_TypeDef*)LTDC_Layer1_BASE;

  /* Configure the horizontal start and stop position */
  #ifdef _LANDSCAPE_
    layer->WHPCR = (
        ((L1_PADDING_TOP + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U) + 1U) << LTDC_LxWHPCR_WHSTPOS_Pos)
      | (((L1_HEIGHT + L1_PADDING_TOP) + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U)) << LTDC_LxWHPCR_WHSPPOS_Pos)
    );
  #else
    layer->WHPCR = (__IO uint32_t)(
        ((L1_PADDING_TOP + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U) + 1U) << LTDC_LxWHPCR_WHSTPOS_Pos)
      | (((L1_WIDTH + L1_PADDING_TOP) + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U)) << LTDC_LxWHPCR_WHSPPOS_Pos)
    );
  #endif

  /* Configure the vertical start and stop position */
  #ifdef _LANDSCAPE_
    layer->WVPCR = (
        ((L1_PADDING_LEFT + (LTDC->BPCR & LTDC_BPCR_AVBP) + 1U) << LTDC_LxWVPCR_WVSTPOS_Pos)
      | (((L1_WIDTH + L1_PADDING_LEFT) + (LTDC->BPCR & LTDC_BPCR_AVBP)) << LTDC_LxWVPCR_WVSPPOS_Pos)
    );
  #else
    layer->WVPCR = (__IO uint32_t)(
        ((L1_PADDING_LEFT + (LTDC->BPCR & LTDC_BPCR_AVBP) + 1U) << LTDC_LxWVPCR_WVSTPOS_Pos)
      | (((L1_HEIGHT + L1_PADDING_LEFT) + (LTDC->BPCR & LTDC_BPCR_AVBP)) << LTDC_LxWVPCR_WVSPPOS_Pos)
    );
  #endif

  /* Specifies the pixel format */
  layer->PFCR = PIXEL_FORMAT_ARGB8888;
  /* Configure the default color values */
  layer->DCCR = _ORANGE;
  /* Specifies the constant alpha value */
  layer->CACR = 0xff;
  /* Specifies the blending factors */
  layer->BFCR = (
      BLENDING_FACTOR1_PAxCA
    | BLENDING_FACTOR2_PAxCA
  );
  /* Configure the color frame buffer start address */
  layer->CFBAR = L1_ADDR;

  /* Configure the color frame buffer pitch in byte */
  #ifdef _LANDSCAPE_
    layer->CFBLR = (
        (((L1_HEIGHT * 4) + 3) << LTDC_LxCFBLR_CFBLL_Pos)
      | ((L1_HEIGHT * 4) << LTDC_LxCFBLR_CFBP_Pos)
    );
  #else
    layer->CFBLR = (
        (((L1_WIDTH * 4) + 3) << LTDC_LxCFBLR_CFBLL_Pos)
      | ((L1_WIDTH * 4) << LTDC_LxCFBLR_CFBP_Pos)
    );
  #endif

  /* Configure the frame buffer line number */
  #ifdef _LANDSCAPE_
    layer->CFBLNR = L1_WIDTH;
  #else
    layer->CFBLNR = L1_HEIGHT;
  #endif

  /* Enable LTDC_Layer by setting LEN bit */
  PREG_SET(layer->CR, LTDC_LxCR_LEN_Pos);
  PREG_SET(LTDC->SRCR, LTDC_SRCR_IMR_Pos);
}




/**
  * @brief  Setup an LTDC Layer 2.
  * @param  None
  * @retval None
  */
static void LTDC_ConfigLayer2(void) {
  LTDC_Layer_TypeDef* layer = (LTDC_Layer_TypeDef*)LTDC_Layer2_BASE;

  /* Configure the horizontal start and stop position */
  #ifdef _LANDSCAPE_
    layer->WHPCR = (
        ((L2_PADDING_TOP + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U) + 1U) << LTDC_LxWHPCR_WHSTPOS_Pos)
      | (((L2_HEIGHT + L2_PADDING_TOP) + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U)) << LTDC_LxWHPCR_WHSPPOS_Pos)
    );
  #else
    layer->WHPCR = (
        ((L2_PADDING_LEFT + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U) + 1U) << LTDC_LxWHPCR_WHSTPOS_Pos)
      | (((L2_WIDTH + L2_PADDING_LEFT) + ((LTDC->BPCR & LTDC_BPCR_AHBP) >> 16U)) << LTDC_LxWHPCR_WHSPPOS_Pos)
    );
  #endif

  /* Configure the vertical start and stop position */
  #ifdef _LANDSCAPE_
    layer->WVPCR = (
        ((L2_PADDING_LEFT + (LTDC->BPCR & LTDC_BPCR_AVBP) + 1U) << LTDC_LxWVPCR_WVSTPOS_Pos)
      | (((L2_WIDTH + L2_PADDING_LEFT) + (LTDC->BPCR & LTDC_BPCR_AVBP)) << LTDC_LxWVPCR_WVSPPOS_Pos)
    );
  #else
    layer->WVPCR = (
        ((L2_PADDING_TOP + (LTDC->BPCR & LTDC_BPCR_AVBP) + 1U) << LTDC_LxWVPCR_WVSTPOS_Pos)
      | (((L2_HEIGHT + L2_PADDING_TOP) + (LTDC->BPCR & LTDC_BPCR_AVBP)) << LTDC_LxWVPCR_WVSPPOS_Pos)
    );
  #endif

  /* Specifies the pixel format */
  layer->PFCR = PIXEL_FORMAT_ARGB8888;
  /* Configure the default color values */
  layer->DCCR = _WHITE_0;
  /* Specifies the constant alpha value */
  layer->CACR = 0xff;
  /* Specifies the blending factors */
  layer->BFCR = (
      BLENDING_FACTOR1_PAxCA
    | BLENDING_FACTOR2_PAxCA
  );
  /* Configure the color frame buffer start address */
  layer->CFBAR = L2_ADDR;
  
  /* Configure the color frame buffer pitch in byte */
  #ifdef _LANDSCAPE_
    layer->CFBLR = (
        (((L2_HEIGHT * 4) + 3U) << LTDC_LxCFBLR_CFBLL_Pos)
      | ((L2_HEIGHT * 4) << LTDC_LxCFBLR_CFBP_Pos)
    );
  #else
    layer->CFBLR = (
        (((L2_WIDTH * 4) + 3U) << LTDC_LxCFBLR_CFBLL_Pos)
      | ((L2_WIDTH * 4) << LTDC_LxCFBLR_CFBP_Pos)
    );
  #endif

  /* Configure the frame buffer line number */
  #ifdef _LANDSCAPE_
    layer->CFBLNR = L2_WIDTH;
  #else
    layer->CFBLNR = L2_HEIGHT;
  #endif

  /* Enable LTDC_Layer by setting LEN bit */
  PREG_SET(layer->CR, LTDC_LxCR_LEN_Pos);
  PREG_SET(LTDC->SRCR, LTDC_SRCR_IMR_Pos);

}


