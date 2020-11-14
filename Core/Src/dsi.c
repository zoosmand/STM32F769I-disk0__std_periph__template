/**
  ******************************************************************************
  * File Name          : DSI.c
  * Description        : This file provides code for the configuration
  *                      of the GPIO instances for DSI's indication.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
  
/* Includes ------------------------------------------------------------------*/
#include "dsi.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _DSIREG_ = 0;


void DSI_Init(void) {
  /* GPIO DSI TE - PJ2 */
  /* Mode */
  MODIFY_REG(DSI_TE_Port->MODER, DSI_TE_Pin_Mask, (_MODE_AF << DSI_TE_Pin_Pos * 2));
  /* Speed */
  MODIFY_REG(DSI_TE_Port->OSPEEDR, DSI_TE_Pin_Mask, (_SPEED_V << DSI_TE_Pin_Pos * 2));
  /* Output type */
  /* Push mode */
  /* Alternate function */
  MODIFY_REG(DSI_TE_Port->AFR[0], 0x00000f00, (GPIO_AF_13 << DSI_TE_Pin_Pos * 4));


  /* GPIO DSI Reset -  PJ15 */
  /* Mode */
  MODIFY_REG(DSI_RESET_Port->MODER, DSI_RESET_Pin_Mask, (_MODE_OUT << DSI_RESET_Pin_Pos * 2));
  /* Speed */
  // MODIFY_REG(DSI_RESET_Port->OSPEEDR, DSI_RESET_Pin_Mask, (_SPEED_L << DSI_RESET_Pin_Mask * 2));
  /* Output type */
  // MODIFY_REG(DSI_RESET_Port->OTYPER, DSI_RESET_Pin, (_OTYPE_PP << DSI_RESET_Pin_Pos));
  /* Push mode */
  MODIFY_REG(DSI_RESET_Port->PUPDR, DSI_RESET_Pin_Mask, (_PUPD_PU << DSI_RESET_Pin_Pos * 2));
  /* Alternate function */

  // Delay(10);

  // DSI_Reset();
  /* Reset */
  PIN_L(DSI_RESET_Port, DSI_RESET_Pin);
  Delay(10);
  PIN_H(DSI_RESET_Port, DSI_RESET_Pin);


  /* Enable DSI regulator */
  PREG_SET(DSI->WRPCR, DSI_WRPCR_REGEN_Pos);
  __NOP();
  __NOP();
  Delay(10);

  MODIFY_REG(DSI->WRPCR, (DSI_WRPCR_PLL_NDIV_Msk | DSI_WRPCR_PLL_IDF_Msk | DSI_WRPCR_PLL_ODF), (
      (100 << DSI_WRPCR_PLL_NDIV_Pos)
    | (5 << DSI_WRPCR_PLL_IDF_Pos)
    | (0 << DSI_WRPCR_PLL_ODF_Pos)
  ));

  /* Enable DSI PLL and wait it starts */
  PREG_SET(DSI->WRPCR, DSI_WRPCR_PLLEN_Pos);
  while(!(PREG_CHECK(DSI->WISR, DSI_WISR_PLLLS_Pos)));

  /* D-PHY clock and digital enable*/
  DSI->PCTLR |= (DSI_PCTLR_CKE | DSI_PCTLR_DEN);
  /* Clock lane configuration */
  MODIFY_REG(DSI->CLCR, (DSI_CLCR_DPCC_Msk | DSI_CLCR_ACR_Msk), DSI_CLCR_DPCC); /* Clock lane control disabled */
  /* Configure the number of active data lanes */
  MODIFY_REG(DSI->PCONFR, DSI_PCONFR_NL_Msk, 1); /* Two data lanes */

  /* Set the TX escape clock division factor */
  MODIFY_REG(DSI->CCR, DSI_CCR_TXECKDIV_Msk, 4);

  /* Calculate the bit period in high-speed mode in unit of 0.25 ns (UIX4) */
  /* The equation is : UIX4 = IntegerPart( (1000/F_PHY_Mhz) * 4 )          */
  /* Where : F_PHY_Mhz = (NDIV * HSE_Mhz) / (IDF * ODF)                    */
  /* Set the bit period in high-speed mode */
  MODIFY_REG(DSI->WPCR[0], DSI_WPCR0_UIX4_Msk, ((4000000 * 5) / ((HSE_VALUE / 1000) * 100)));

   /* Disable all error interrupts and reset the Error Mask */
  DSI->IER[0] = 0;
  DSI->IER[1] = 0;










/* ------------------------------------------------------------------------------------------------- */
  /* Select video mode by resetting CMDM and DSIM bits */
  DSI->MCR &= ~DSI_MCR_CMDM;
  DSI->WCFGR &= ~DSI_WCFGR_DSIM;

  /* Select command mode by setting CMDM and DSIM bits */
  // PREG_SET(DSI->MCR, DSI_MCR_CMDM_Pos);
  // PREG_SET(DSI->WCFGR, DSI_WCFGR_DSIM_Pos);

  /* Configure the video mode transmission type */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_VMT_Msk, (2 << DSI_VMCR_VMT_Pos)); /* Mode Video burst ie : one LgP per line */

  /* Configure the video packet size */
  #ifdef _LANDSCAPE_
    MODIFY_REG(DSI->VPCR, DSI_VPCR_VPSIZE_Msk, (DISPLAY_HEIGHT << DSI_VPCR_VPSIZE_Pos)); /* Value depending on display orientation choice portrait/landscape */
  #else
    MODIFY_REG(DSI->VPCR, DSI_VPCR_VPSIZE_Msk, (DISPLAY_WIDTH << DSI_VPCR_VPSIZE_Pos)); /* Value depending on display orientation choice portrait/landscape */
  #endif

  /* Set the chunks number to be transmitted through the DSI link */
  MODIFY_REG(DSI->VCCR, DSI_VCCR_NUMC_Msk, (0 << DSI_VCCR_NUMC_Pos));

  /* Set the size of the null packet */
  MODIFY_REG(DSI->VNPCR, DSI_VNPCR_NPSIZE_Msk, (0xfff << DSI_VNPCR_NPSIZE_Pos));

  /* Select the virtual channel for the LTDC interface traffic */
  MODIFY_REG(DSI->LVCIDR, DSI_LVCIDR_VCID_Msk, (0 << DSI_LVCIDR_VCID_Pos)); /* Channel ID*/

  /* Configure the polarity of control signals */
  MODIFY_REG(DSI->LPCR, (DSI_LPCR_DEP_Msk | DSI_LPCR_VSP_Msk | DSI_LPCR_HSP_Msk), ((0 << DSI_LPCR_DEP_Pos) | (0 << DSI_LPCR_VSP_Pos) | (0 << DSI_LPCR_HSP_Pos)));

  /* Select the color coding for the host */
  MODIFY_REG(DSI->LCOLCR, DSI_LCOLCR_COLC_Msk, (DSI_RGB888 << DSI_LCOLCR_COLC_Pos));

  /* Select the color coding for the wrapper */
  MODIFY_REG(DSI->WCFGR, DSI_WCFGR_COLMUX_Msk, (DSI_RGB888 << DSI_WCFGR_COLMUX_Pos));

  /* Enable/disable the loosely packed variant to 18-bit configuration */
  // if DSI_RGB565
  // MODIFY_REG(DSI->LCOLCR, DSI_LCOLCR_LPE_Msk, (0 << DSI_LCOLCR_LPE_Pos));

  /* Set the Horizontal Synchronization Active (_HSA_) in lane byte clock cycles */
  MODIFY_REG(DSI->VHSACR, DSI_VHSACR_HSA_Msk, (((_HSA_ * LANE_BYTE_CLOCK)/LCD_CLOCK) << DSI_VHSACR_HSA_Pos));

  /* Set the Horizontal Back Porch (_HBP_) in lane byte clock cycles */
  MODIFY_REG(DSI->VHBPCR, DSI_VHBPCR_HBP_Msk, (((_HBP_ * LANE_BYTE_CLOCK)/LCD_CLOCK) << DSI_VHBPCR_HBP_Pos));

  /* Set the total line time (HLINE=DISPLAY_HEIGHT+_HSA_+_HBP_+_HFP_) in lane byte clock cycles */
  #ifdef _LANDSCAPE_
    MODIFY_REG(DSI->VLCR, DSI_VLCR_HLINE_Msk, ((((DISPLAY_HEIGHT + _HSA_ + _HBP_ + _HFP_) * LANE_BYTE_CLOCK)/LCD_CLOCK) << DSI_VLCR_HLINE_Pos));
  #else
    MODIFY_REG(DSI->VLCR, DSI_VLCR_HLINE_Msk, ((((DISPLAY_WIDTH + _HSA_ + _HBP_ + _HFP_ + 0) * LANE_BYTE_CLOCK)/LCD_CLOCK) << DSI_VLCR_HLINE_Pos));
  #endif

  /* Set the Vertical Synchronization Active (_VSA_) */
  MODIFY_REG(DSI->VVSACR, DSI_VVSACR_VSA_Msk, (_VSA_ << DSI_VVSACR_VSA_Pos));

  /* Set the Vertical Back Porch (_VBP_)*/
  MODIFY_REG(DSI->VVBPCR, DSI_VVBPCR_VBP_Msk, (_VBP_ << DSI_VVBPCR_VBP_Pos));

  /* Set the Vertical Front Porch (_VFP_)*/
  MODIFY_REG(DSI->VVFPCR, DSI_VVFPCR_VFP_Msk, (_VFP_ << DSI_VVFPCR_VFP_Pos));

  /* Set the Vertical Active period*/
  #ifdef _LANDSCAPE_
    MODIFY_REG(DSI->VVACR, DSI_VVACR_VA_Msk, (DISPLAY_WIDTH << DSI_VVACR_VA_Pos));
  #else
    MODIFY_REG(DSI->VVACR, DSI_VVACR_VA_Msk, (DISPLAY_HEIGHT << DSI_VVACR_VA_Pos));
  #endif

  /* Configure the command transmission mode */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_LPCE_Msk, DSI_VMCR_LPCE);

  /* Low power largest packet size */
  MODIFY_REG(DSI->LPMCR, DSI_LPMCR_LPSIZE_Msk, (16 << DSI_LPMCR_LPSIZE_Pos));

  /* Low power DISPLAY_WIDTH largest packet size */
  MODIFY_REG(DSI->LPMCR, DSI_LPMCR_VLPSIZE_Msk, (0 << DSI_LPMCR_VLPSIZE_Pos));

  /* Enable LP transition in HFP period */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_LPHFPE_Msk, DSI_VMCR_LPHFPE);

  /* Enable LP transition in HBP period */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_LPHBPE_Msk, DSI_VMCR_LPHBPE);

  /* Enable LP transition in DISPLAY_WIDTH period */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_LPVAE_Msk, DSI_VMCR_LPVAE);

  /* Enable LP transition in VFP period */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_LPVFPE_Msk, DSI_VMCR_LPVFPE);

  /* Enable LP transition in VBP period */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_LPVBPE_Msk, DSI_VMCR_LPVBPE);

  /* Enable LP transition in vertical sync period */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_LPVSAE_Msk, DSI_VMCR_LPVSAE);

  /* Enable the request for an acknowledge response at the end of a frame */
  MODIFY_REG(DSI->VMCR, DSI_VMCR_FBTAAE_Msk, (0 << DSI_VMCR_FBTAAE_Pos));

/* ------------------------------------------------------------------------------------------------- */










  //   /* Set the timeout clock division factor */
  // MODIFY_REG(DSI->CCR, DSI_CCR_TOCKDIV_Msk, (1 << DSI_CCR_TOCKDIV_Pos));

  // /* High-speed transmission timeout */
  // MODIFY_REG(DSI->TCCR[0], DSI_TCCR0_HSTX_TOCNT_Msk, (0 << DSI_TCCR0_HSTX_TOCNT_Pos));

  // /* Low-power reception timeout */
  // MODIFY_REG(DSI->TCCR[0], DSI_TCCR0_LPRX_TOCNT_Msk, (0 << DSI_TCCR0_LPRX_TOCNT_Pos));

  // /* High-speed read timeout */
  // MODIFY_REG(DSI->TCCR[1], DSI_TCCR1_HSRD_TOCNT_Msk, (0 << DSI_TCCR1_HSRD_TOCNT_Pos));

  // /* Low-power read timeout */
  // MODIFY_REG(DSI->TCCR[2], DSI_TCCR2_LPRD_TOCNT_Msk, (0 << DSI_TCCR2_LPRD_TOCNT_Pos));

  // /* High-speed write timeout */
  // MODIFY_REG(DSI->TCCR[3], DSI_TCCR3_HSWR_TOCNT_Msk, (0 << DSI_TCCR3_HSWR_TOCNT_Pos));

  // /* High-speed write presp mode */
  // MODIFY_REG(DSI->TCCR[3], DSI_TCCR3_PM_Msk, (0 << DSI_TCCR3_PM_Pos));

  // /* Low-speed write timeout */
  // MODIFY_REG(DSI->TCCR[4], DSI_TCCR4_LPWR_TOCNT_Msk, (0 << DSI_TCCR4_LPWR_TOCNT_Pos));

  // /* BTA timeout */
  // MODIFY_REG(DSI->TCCR[5], DSI_TCCR5_BTA_TOCNT_Msk, (0 << DSI_TCCR5_BTA_TOCNT_Pos));






  // /* Clock lane timer configuration */
  // /* In Automatic Clock Lane control mode, the DSI Host can turn off the clock lane between two
  //    High-Speed transmission.
  //    To do so, the DSI Host calculates the time required for the clock lane to change from HighSpeed
  //    to Low-Power and from Low-Power to High-Speed.
  //    This timings are configured by the HS2LP_TIME and LP2HS_TIME in the DSI Host Clock Lane Timer Configuration Register (DSI_CLTCR).
  //    But the DSI Host is not calculating LP2HS_TIME + HS2LP_TIME but 2 x HS2LP_TIME.

  //    Workaround : Configure HS2LP_TIME and LP2HS_TIME with the same value being the max of HS2LP_TIME or LP2HS_TIME.
  //   */
  // uint16_t maxTime = 33;
  // MODIFY_REG(DSI->CLTCR, (DSI_CLTCR_LP2HS_TIME_Msk | DSI_CLTCR_HS2LP_TIME_Msk), (maxTime | ((maxTime) << 16U)));

  // /* Data lane timer configuration */
  // MODIFY_REG(DSI->DLTCR, (DSI_DLTCR_MRD_TIME_Msk | DSI_DLTCR_LP2HS_TIME_Msk | DSI_DLTCR_HS2LP_TIME_Msk), (
  //     (0 << DSI_DLTCR_MRD_TIME_Pos)
  //   | (25 << DSI_DLTCR_LP2HS_TIME_Pos)
  //   | (15 << DSI_DLTCR_HS2LP_TIME_Pos)
  // ));

  // /* Configure the wait period to request HS transmission after a stop state */
  // MODIFY_REG(DSI->PCONFR, DSI_PCONFR_SW_TIME_Msk, (0 << DSI_PCONFR_SW_TIME_Pos));






  // /* Bus Turn Around Enable */
  // MODIFY_REG(DSI->PCR, (DSI_PCR_CRCRXE_Msk | DSI_PCR_ECCRXE_Msk | DSI_PCR_BTAE_Msk | DSI_PCR_ETRXE_Msk | DSI_PCR_ETTXE_Msk), DSI_PCR_BTAE);




  // /* Low-Power RX low-pass Filtering Tuning */
  // // MODIFY_REG(DSI->WPCR[1], DSI_WPCR1_LPRXFT_Msk, (0b10000 << DSI_WPCR1_LPRXFT_Pos));




  // /* Disable all error interrupts and reset the Error Mask */
  // DSI->IER[0] = 0;
  // DSI->IER[1] = 0;






  // /* Select High-speed or Low-power for command transmission */
  // MODIFY_REG(DSI->CMCR, 0xfffffffc, (
  //     (0 << DSI_CMCR_GSW0TX_Pos) // Generic short write zero (High speed)
  //   | (0 << DSI_CMCR_GSW1TX_Pos) // Generic short write one (High speed)
  //   | (0 << DSI_CMCR_GSW2TX_Pos) // Generic short write two (High speed)
  //   | (0 << DSI_CMCR_GSR0TX_Pos) // Generic short read zero (High speed)
  //   | (0 << DSI_CMCR_GSR1TX_Pos) // Generic short read one (High speed)
  //   | (0 << DSI_CMCR_GSR2TX_Pos) // Generic short read two (High speed)
  //   | (0 << DSI_CMCR_GLWTX_Pos) // Generic long write (High speed)
  //   | (0 << DSI_CMCR_DSW0TX_Pos) // DCS short write zero (High speed)
  //   | (0 << DSI_CMCR_DSW1TX_Pos) // DCS short write one (High speed)
  //   | (0 << DSI_CMCR_DSR0TX_Pos) // DCS short read zero (High speed)
  //   | (0 << DSI_CMCR_DLWTX_Pos) // DCS long write (High speed)
  //   | (0 << DSI_CMCR_MRDPS_Pos) // Maximim read packet size (High speed)
  // ));

  // /* Configure the acknowledge request after each packet transmission */
  // PREG_SET(DSI->CMCR, DSI_CMCR_ARE_Pos);





  // /* Select command mode by setting CMDM and DSIM bits */
  // PREG_SET(DSI->MCR, DSI_MCR_CMDM_Pos);
  // PREG_SET(DSI->WCFGR, DSI_WCFGR_DSIM_Pos);

  // // /* Select the virtual channel for the LTDC interface traffic */
  // // MODIFY_REG(DSI->LVCIDR, DSI_LVCIDR_VCID_Msk, 0);

  // /* Configure the polarity of control signals */
  // MODIFY_REG(DSI->LPCR, (DSI_LPCR_DEP_Msk | DSI_LPCR_VSP_Msk | DSI_LPCR_HSP_Msk), (
  //     (0 << DSI_LPCR_DEP_Pos)
  //   | (1 << DSI_LPCR_VSP_Pos)
  //   | (1 << DSI_LPCR_HSP_Pos)
  // ));

  // /* Select the color coding for the host (DSI_RGB888) */
  // MODIFY_REG(DSI->LCOLCR, DSI_LCOLCR_COLC_Msk, (5 << DSI_LCOLCR_COLC_Pos));

  // /* Select the color coding for the wrapper (DSI_RGB888) */
  // MODIFY_REG(DSI->WCFGR, DSI_WCFGR_COLMUX_Msk, (5 << DSI_WCFGR_COLMUX_Pos));

  // /* Configure the maximum allowed size for write memory command */
  // MODIFY_REG(DSI->LCCR, DSI_LCCR_CMDSIZE_Msk, (800 << DSI_LCCR_CMDSIZE_Pos));

  // /* Configure the tearing effect source and polarity and select the refresh mode */
  // MODIFY_REG(DSI->WCFGR, (DSI_WCFGR_TESRC_Msk | DSI_WCFGR_TEPOL_Msk | DSI_WCFGR_AR_Msk | DSI_WCFGR_VSPOL_Msk), (
  //     (1 << DSI_WCFGR_TESRC_Pos) /* External source*/
  //   | (0 << DSI_WCFGR_TEPOL_Pos) /* Rising edge */
  //   | (1 << DSI_WCFGR_AR_Pos) /* Automal refresh enabled */
  //   | (0 << DSI_WCFGR_VSPOL_Pos) /* Falling */
  // ));

  // /* Configure the tearing effect acknowledge request */
  // PREG_CLR(DSI->CMCR, DSI_CMCR_TEARE_Pos); /* Disabled */

  // /* Enable the Tearing Effect interrupt */
  // PREG_SET(DSI->WIER, DSI_WIER_TEIE_Pos);

  // /* Enable the End of Refresh interrupt */
  // PREG_SET(DSI->WIER, DSI_WIER_ERIE_Pos);


  // SET_BIT(DSI->CR, DSI_CR_EN);
  // __NOP();
  // __NOP();

  // SET_BIT(DSI->WCR, DSI_WCR_DSIEN);
  // __NOP();
  // __NOP();


  /** @brief NVIC configuration for DSI interrupt that is now enabled */
  NVIC_SetPriority(DSI_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 7, 0));
  NVIC_EnableIRQ(DSI_IRQn);
}






void DSI_ShortWrite(uint8_t ch, uint8_t mode, uint8_t p1, uint8_t p2) {
  /* Wait for Command FIFO Empty */
  while(!(PREG_CHECK(DSI->GPSR, DSI_GPSR_CMDFE_Pos)));
  /* Update the DSI packet header with new information */
  DSI->GHCR = (
      (mode << DSI_GHCR_DT_Pos)
    | (ch << DSI_GHCR_VCID_Pos)
    | (p1 << DSI_GHCR_WCLSB_Pos)
    | (p2 << DSI_GHCR_WCMSB_Pos)
  );
}





void DSI_LongWrite(uint8_t ch, uint8_t mode, uint32_t cnt, uint8_t p1, uint8_t *p2) {
	uint32_t uicounter, nbBytes, count;
	uint32_t fifoword;
	uint8_t *pparams = p2;

  /* Wait for Command FIFO Empty */
  while (!(PREG_CHECK(DSI->GPSR, DSI_GPSR_CMDFE_Pos))) {
  }

	/* Set the DCS code on payload byte 1, and the other parameters on the write FIFO command*/
	fifoword = p1;
	nbBytes = (cnt < 3) ? cnt : 3;

	for (count = 0; count < nbBytes; count++) {
		fifoword |= (((uint32_t)(*(pparams + count))) << (8 + (8 * count)));
	}
	DSI->GPDR = fifoword;

	uicounter = cnt - nbBytes;
	pparams += nbBytes;
	/* Set the Next parameters on the write FIFO command*/
	while (uicounter != 0) {
		nbBytes = (uicounter < 4) ? uicounter : 4;
		fifoword = 0;

		for (count = 0; count < nbBytes; count++) {
		  fifoword |= (((uint32_t)(*(pparams + count))) << (8 * count));
		}

		DSI->GPDR = fifoword;
		uicounter -= nbBytes;
		pparams += nbBytes;
	}

	/* Configure the packet to send a long DCS command */
	DSI_ShortWrite(ch, mode, ((cnt + 1) & 0x00ff), (((cnt + 1) & 0xff00) >> 8));
}





void DSI_Write(uint32_t cnt, uint8_t *buf) {
	if(cnt <= 1) {
		DSI_ShortWrite(0, DSI_DCS_SHORT_PKT_WRITE_P1, buf[0], buf[1]);
	} else {
		DSI_LongWrite(0, DSI_DCS_LONG_PKT_WRITE, cnt, buf[cnt], buf);
	}
}




void DSI_Run(void) {
  SET_BIT(DSI->CR, DSI_CR_EN);
  SET_BIT(DSI->WCR, DSI_WCR_DSIEN);
}

