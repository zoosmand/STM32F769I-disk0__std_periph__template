/**
  ******************************************************************************
  * File Name          : fmc.c
  * Description        : This file provides code for the configuration
  *                      of the FMC instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fmc.h"

/* Global variables ---------------------------------------------------------*/
uint32_t _FMCREG_ = 0;

/* Private function prototypes -----------------------------------------------*/
static void SDRAM_Init();








////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Initializes FMC peripheral 
  * @param  mode: FMC memory mode (NAND, SDRAM, etc.)
  * @return None
  */
 void FMC_Init(FMC_MemoryMode mode) {
  /** FMC GPIO Configuration  
  PF0   ------> FMC_A0
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PF5   ------> FMC_A5
  PF12  ------> FMC_A6
  PF13  ------> FMC_A7
  PF14  ------> FMC_A8
  PF15  ------> FMC_A9
  PG0   ------> FMC_A10
  PG1   ------> FMC_A11
  PD14  ------> FMC_D0
  PD15  ------> FMC_D1
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10  ------> FMC_D7
  PE11  ------> FMC_D8
  PE12  ------> FMC_D9
  PE13  ------> FMC_D10
  PE14  ------> FMC_D11
  PE15  ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10  ------> FMC_D15
  PG4   ------> FMC_BA0
  PG5   ------> FMC_BA1
  PG8   ------> FMC_SDCLK
  PC0   ------> FMC_SDNWE
  PF11  ------> FMC_SDNRAS
  PG15  ------> FMC_SDNCAS
  PB5   ------> FMC_SDCKE1
  PB6   ------> FMC_SDNE1
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  */
  /* ----------------------------------------------------------------------------- */
#define F_MASK     (FMC_A0_Pin_Mask | FMC_A1_Pin_Mask | FMC_A2_Pin_Mask | FMC_A3_Pin_Mask | FMC_A4_Pin_Mask | FMC_A5_Pin_Mask | \
    FMC_A6_Pin_Mask | FMC_A7_Pin_Mask | FMC_A8_Pin_Mask | FMC_A9_Pin_Mask | FMC_SDNRAS_Pin_Mask)

  /* Mode */
  MODIFY_REG(GPIOF->MODER, F_MASK,
    (   (_MODE_AF << FMC_A0_Pin_Pos * 2)
      | (_MODE_AF << FMC_A1_Pin_Pos * 2)
      | (_MODE_AF << FMC_A2_Pin_Pos * 2)
      | (_MODE_AF << FMC_A3_Pin_Pos * 2)
      | (_MODE_AF << FMC_A4_Pin_Pos * 2)
      | (_MODE_AF << FMC_A5_Pin_Pos * 2)
      | (_MODE_AF << FMC_A6_Pin_Pos * 2)
      | (_MODE_AF << FMC_A7_Pin_Pos * 2)
      | (_MODE_AF << FMC_A8_Pin_Pos * 2)
      | (_MODE_AF << FMC_A9_Pin_Pos * 2)
      | (_MODE_AF << FMC_SDNRAS_Pin_Pos * 2)
    )
  );
  /* Speed */
  MODIFY_REG(GPIOF->OSPEEDR, F_MASK, 
    (   (_SPEED_V << FMC_A0_Pin_Pos * 2)
      | (_SPEED_V << FMC_A1_Pin_Pos * 2)
      | (_SPEED_V << FMC_A2_Pin_Pos * 2)
      | (_SPEED_V << FMC_A3_Pin_Pos * 2)
      | (_SPEED_V << FMC_A4_Pin_Pos * 2)
      | (_SPEED_V << FMC_A5_Pin_Pos * 2)
      | (_SPEED_V << FMC_A6_Pin_Pos * 2)
      | (_SPEED_V << FMC_A7_Pin_Pos * 2)
      | (_SPEED_V << FMC_A8_Pin_Pos * 2)
      | (_SPEED_V << FMC_A9_Pin_Pos * 2)
      | (_SPEED_V << FMC_SDNRAS_Pin_Pos * 2)
    )
  );
  /* Output type */
  /* Push mode */
  /* Alternate function */
  MODIFY_REG(GPIOF->AFR[0], 0x00ffffff, 
    (   (GPIO_AF_12 << FMC_A0_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_A1_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_A2_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_A3_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_A4_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_A5_Pin_Pos * 4)
    )
  );
  MODIFY_REG(GPIOF->AFR[1], 0xfffff000, 
    (   (GPIO_AF_12 << (FMC_A6_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_A7_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_A8_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_A9_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_SDNRAS_Pin_Pos - 8) * 4)
    )
  );




  /* ----------------------------------------------------------------------------- */
#define G_MASK     (FMC_A10_Pin_Mask | FMC_A11_Pin_Mask | FMC_BA0_Pin_Mask | FMC_BA1_Pin_Mask | FMC_SDCLK_Pin_Mask | FMC_SDNCAS_Pin_Mask)

  /* Mode */
  MODIFY_REG(GPIOG->MODER, G_MASK,
    (   (_MODE_AF << FMC_A10_Pin_Pos * 2)
      | (_MODE_AF << FMC_A11_Pin_Pos * 2)
      | (_MODE_AF << FMC_BA0_Pin_Pos * 2)
      | (_MODE_AF << FMC_BA1_Pin_Pos * 2)
      | (_MODE_AF << FMC_SDCLK_Pin_Pos * 2)
      | (_MODE_AF << FMC_SDNCAS_Pin_Pos * 2)
    )
  );
  /* Speed */
  MODIFY_REG(GPIOG->OSPEEDR, G_MASK, 
    (   (_SPEED_V << FMC_A10_Pin_Pos * 2)
      | (_SPEED_V << FMC_A11_Pin_Pos * 2)
      | (_SPEED_V << FMC_BA0_Pin_Pos * 2)
      | (_SPEED_V << FMC_BA1_Pin_Pos * 2)
      | (_SPEED_V << FMC_SDCLK_Pin_Pos * 2)
      | (_SPEED_V << FMC_SDNCAS_Pin_Pos * 2)
    )
  );
  /* Output type */
  /* Push mode */
  /* Alternate function */
  MODIFY_REG(GPIOG->AFR[0], 0x00ff00ff, 
    (   (GPIO_AF_12 << FMC_A10_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_A11_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_BA0_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_BA1_Pin_Pos * 4)
    )
  );
  MODIFY_REG(GPIOG->AFR[1], 0xf000000f, 
    (   (GPIO_AF_12 << (FMC_SDCLK_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_SDNCAS_Pin_Pos - 8) * 4)
    )
  );




  /* ----------------------------------------------------------------------------- */
#define E_MASK     (FMC_NBL0_Pin_Mask | FMC_NBL1_Pin_Mask | FMC_D4_Pin_Mask | FMC_D5_Pin_Mask | FMC_D6_Pin_Mask | FMC_D7_Pin_Mask | \
  FMC_D8_Pin_Mask | FMC_D9_Pin_Mask | FMC_D10_Pin_Mask | FMC_D11_Pin_Mask | FMC_D12_Pin_Mask)

  /* Mode */
  MODIFY_REG(GPIOE->MODER, E_MASK,
    (   (_MODE_AF << FMC_NBL0_Pin_Pos * 2)
      | (_MODE_AF << FMC_NBL1_Pin_Pos * 2)
      | (_MODE_AF << FMC_D4_Pin_Pos * 2)
      | (_MODE_AF << FMC_D5_Pin_Pos * 2)
      | (_MODE_AF << FMC_D6_Pin_Pos * 2)
      | (_MODE_AF << FMC_D7_Pin_Pos * 2)
      | (_MODE_AF << FMC_D8_Pin_Pos * 2)
      | (_MODE_AF << FMC_D9_Pin_Pos * 2)
      | (_MODE_AF << FMC_D10_Pin_Pos * 2)
      | (_MODE_AF << FMC_D11_Pin_Pos * 2)
      | (_MODE_AF << FMC_D12_Pin_Pos * 2)
    )
  );
  /* Speed */
  MODIFY_REG(GPIOE->OSPEEDR, E_MASK, 
    (   (_SPEED_V << FMC_NBL0_Pin_Pos * 2)
      | (_SPEED_V << FMC_NBL1_Pin_Pos * 2)
      | (_SPEED_V << FMC_D4_Pin_Pos * 2)
      | (_SPEED_V << FMC_D5_Pin_Pos * 2)
      | (_SPEED_V << FMC_D6_Pin_Pos * 2)
      | (_SPEED_V << FMC_D7_Pin_Pos * 2)
      | (_SPEED_V << FMC_D8_Pin_Pos * 2)
      | (_SPEED_V << FMC_D9_Pin_Pos * 2)
      | (_SPEED_V << FMC_D10_Pin_Pos * 2)
      | (_SPEED_V << FMC_D11_Pin_Pos * 2)
      | (_SPEED_V << FMC_D12_Pin_Pos * 2)
    )
  );
  /* Output type */
  /* Push mode */
  /* Alternate function */
  MODIFY_REG(GPIOE->AFR[0], 0xf00000ff, 
    (   (GPIO_AF_12 << FMC_NBL0_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_NBL1_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_D4_Pin_Pos * 4)
    )
  );
  MODIFY_REG(GPIOE->AFR[1], 0xffffffff, 
    (   (GPIO_AF_12 << (FMC_D5_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D6_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D7_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D8_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D9_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D10_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D11_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D12_Pin_Pos - 8) * 4)
    )
  );





  /* ----------------------------------------------------------------------------- */
#define D_MASK     (FMC_D0_Pin_Mask | FMC_D1_Pin_Mask | FMC_D2_Pin_Mask | FMC_D3_Pin_Mask | FMC_D13_Pin_Mask | FMC_D14_Pin_Mask | \
  FMC_D15_Pin_Mask)

  /* Mode */
  MODIFY_REG(GPIOD->MODER, D_MASK,
    (   (_MODE_AF << FMC_D0_Pin_Pos * 2)
      | (_MODE_AF << FMC_D1_Pin_Pos * 2)
      | (_MODE_AF << FMC_D2_Pin_Pos * 2)
      | (_MODE_AF << FMC_D3_Pin_Pos * 2)
      | (_MODE_AF << FMC_D13_Pin_Pos * 2)
      | (_MODE_AF << FMC_D14_Pin_Pos * 2)
      | (_MODE_AF << FMC_D15_Pin_Pos * 2)
    )
  );
  /* Speed */
  MODIFY_REG(GPIOD->OSPEEDR, D_MASK, 
    (   (_SPEED_V << FMC_D0_Pin_Pos * 2)
      | (_SPEED_V << FMC_D1_Pin_Pos * 2)
      | (_SPEED_V << FMC_D2_Pin_Pos * 2)
      | (_SPEED_V << FMC_D3_Pin_Pos * 2)
      | (_SPEED_V << FMC_D13_Pin_Pos * 2)
      | (_SPEED_V << FMC_D14_Pin_Pos * 2)
      | (_SPEED_V << FMC_D15_Pin_Pos * 2)
    )
  );
  /* Output type */
  /* Push mode */
  /* Alternate function */
  MODIFY_REG(GPIOD->AFR[0], 0x000000ff, 
    (   (GPIO_AF_12 << FMC_D2_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_D3_Pin_Pos * 4)
    )
  );
  MODIFY_REG(GPIOD->AFR[1], 0xff000fff, 
    (   (GPIO_AF_12 << (FMC_D13_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D14_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D15_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D0_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D1_Pin_Pos - 8) * 4)
    )
  );





  /* ----------------------------------------------------------------------------- */
#define H_MASK     (FMC_SDCKE0_Pin_Mask | FMC_SDNE0_Pin_Mask | FMC_SDNWE_Pin_Mask | FMC_D16_Pin_Mask | FMC_D17_Pin_Mask | FMC_D18_Pin_Mask | \
  FMC_D19_Pin_Mask | FMC_D20_Pin_Mask | FMC_D21_Pin_Mask | FMC_D22_Pin_Mask | FMC_D23_Pin_Mask)

  /* Mode */
  MODIFY_REG(GPIOH->MODER, H_MASK,
    (   (_MODE_AF << FMC_SDCKE0_Pin_Pos * 2)
      | (_MODE_AF << FMC_SDNE0_Pin_Pos * 2)
      | (_MODE_AF << FMC_SDNWE_Pin_Pos * 2)
      | (_MODE_AF << FMC_D16_Pin_Pos * 2)
      | (_MODE_AF << FMC_D17_Pin_Pos * 2)
      | (_MODE_AF << FMC_D18_Pin_Pos * 2)
      | (_MODE_AF << FMC_D19_Pin_Pos * 2)
      | (_MODE_AF << FMC_D20_Pin_Pos * 2)
      | (_MODE_AF << FMC_D21_Pin_Pos * 2)
      | (_MODE_AF << FMC_D22_Pin_Pos * 2)
      | (_MODE_AF << FMC_D23_Pin_Pos * 2)
    )
  );
  /* Speed */
  MODIFY_REG(GPIOH->OSPEEDR, H_MASK, 
    (   (_SPEED_V << FMC_SDCKE0_Pin_Pos * 2)
      | (_SPEED_V << FMC_SDNE0_Pin_Pos * 2)
      | (_SPEED_V << FMC_SDNWE_Pin_Pos * 2)
      | (_SPEED_V << FMC_D16_Pin_Pos * 2)
      | (_SPEED_V << FMC_D17_Pin_Pos * 2)
      | (_SPEED_V << FMC_D18_Pin_Pos * 2)
      | (_SPEED_V << FMC_D19_Pin_Pos * 2)
      | (_SPEED_V << FMC_D20_Pin_Pos * 2)
      | (_SPEED_V << FMC_D21_Pin_Pos * 2)
      | (_SPEED_V << FMC_D22_Pin_Pos * 2)
      | (_SPEED_V << FMC_D23_Pin_Pos * 2)
    )
  );
  /* Output type */
  /* Push mode */
  /* Alternate function */
  MODIFY_REG(GPIOH->AFR[0], 0x00f0ff00, 
    (   (GPIO_AF_12 << FMC_SDCKE0_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_SDNE0_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_SDNWE_Pin_Pos * 4)
    )
  );
  MODIFY_REG(GPIOH->AFR[1], 0xffffffff, 
    (   (GPIO_AF_12 << (FMC_D16_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D17_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D18_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D19_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D20_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D21_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D22_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D23_Pin_Pos - 8) * 4)
    )
  );





  /* ----------------------------------------------------------------------------- */
#define I_MASK     (FMC_D24_Pin_Mask | FMC_D25_Pin_Mask | FMC_D26_Pin_Mask | FMC_D27_Pin_Mask | FMC_D28_Pin_Mask | FMC_D29_Pin_Mask | \
  FMC_D30_Pin_Mask | FMC_D31_Pin_Mask | FMC_NBL2_Pin_Mask | FMC_NBL3_Pin_Mask)

  /* Mode */
  MODIFY_REG(GPIOI->MODER, I_MASK,
    (   (_MODE_AF << FMC_D24_Pin_Pos * 2)
      | (_MODE_AF << FMC_D25_Pin_Pos * 2)
      | (_MODE_AF << FMC_D26_Pin_Pos * 2)
      | (_MODE_AF << FMC_D27_Pin_Pos * 2)
      | (_MODE_AF << FMC_D28_Pin_Pos * 2)
      | (_MODE_AF << FMC_D29_Pin_Pos * 2)
      | (_MODE_AF << FMC_D30_Pin_Pos * 2)
      | (_MODE_AF << FMC_D31_Pin_Pos * 2)
      | (_MODE_AF << FMC_NBL2_Pin_Pos * 2)
      | (_MODE_AF << FMC_NBL3_Pin_Pos * 2)
    )
  );
  /* Speed */
  MODIFY_REG(GPIOI->OSPEEDR, I_MASK, 
    (   (_SPEED_V << FMC_D24_Pin_Pos * 2)
      | (_SPEED_V << FMC_D25_Pin_Pos * 2)
      | (_SPEED_V << FMC_D26_Pin_Pos * 2)
      | (_SPEED_V << FMC_D27_Pin_Pos * 2)
      | (_SPEED_V << FMC_D28_Pin_Pos * 2)
      | (_SPEED_V << FMC_D29_Pin_Pos * 2)
      | (_SPEED_V << FMC_D30_Pin_Pos * 2)
      | (_SPEED_V << FMC_D31_Pin_Pos * 2)
      | (_SPEED_V << FMC_NBL2_Pin_Pos * 2)
      | (_SPEED_V << FMC_NBL3_Pin_Pos * 2)
    )
  );
  /* Output type */
  /* Push mode */
  /* Alternate function */
  MODIFY_REG(GPIOI->AFR[0], 0xffffffff, 
    (   (GPIO_AF_12 << FMC_D24_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_D25_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_D26_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_D27_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_D28_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_D29_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_NBL2_Pin_Pos * 4)
      | (GPIO_AF_12 << FMC_NBL3_Pin_Pos * 4)
    )
  );
  MODIFY_REG(GPIOI->AFR[1], 0x00000ff0, 
    (   (GPIO_AF_12 << (FMC_D30_Pin_Pos - 8) * 4)
      | (GPIO_AF_12 << (FMC_D31_Pin_Pos - 8) * 4)
    )
  );


  if (mode == _SDRAM) {
    SDRAM_Init();
  }
}




/**
  * @brief  Initializes the FMC_SDRAM device according to the specified
  *         control parameters in the FMC_SDRAM_InitTypeDef
  * @param  None
  * @return None
  */
static void SDRAM_Init() {
    /* SDRAM controller registers */
    FMC_Bank5_6->SDCR[SDRAM_BANK1] = (__IO uint32_t)(
        FMC_SDCR_CLK_PER_2
      | FMC_SDCR_RBURST_EN
      | FMC_SDCR_RPIPE_0
      | FMC_SDCR_COL_BITS_8
      | FMC_SDCR_ROW_BITS_12
      | FMC_SDCR_BUS_32
      | FMC_SDCR_BANKS_NUM_4
      | FMC_SDCR_CAS_3
      | FMC_SDCR_WP_DIS
    );

    FMC_Bank5_6->SDTR[SDRAM_BANK1] = (__IO uint32_t)(
        (1 << FMC_SDTR1_TMRD_Pos)
      | (6 << FMC_SDTR1_TXSR_Pos)
      | (3 << FMC_SDTR1_TRAS_Pos)
      | (6 << FMC_SDTR1_TRC_Pos)
      | (1 << FMC_SDTR1_TWR_Pos)
      | (1 << FMC_SDTR1_TRP_Pos)
      | (1 << FMC_SDTR1_TRCD_Pos)
    );

  SDRAM_CommandTypeDef SdramCommand       = {0};

  SdramCommand.CommandMode                = SDRAM_CMD_CLK_ENABLE;
  SdramCommand.CommandTarget              = SDRAM_CMD_TARGET_BANK1;
  SdramCommand.AutoRefreshNumber          = 1;
  SdramCommand.ModeRegisterDefinition     = 0;
  SDRAM_SendCommand(&SdramCommand);
  Delay(30);

  SdramCommand.CommandMode                = SDRAM_CMD_PALL;
  SDRAM_SendCommand(&SdramCommand);

  SdramCommand.CommandMode                = SDRAM_CMD_AUTOREFRESH_MODE;
  SdramCommand.AutoRefreshNumber          = 8;
  SDRAM_SendCommand(&SdramCommand);

  SdramCommand.CommandMode                = SDRAM_CMD_LOAD_MODE;
  SdramCommand.AutoRefreshNumber          = 1;
  SdramCommand.ModeRegisterDefinition     = (
      SDRAM_MODEREG_BURST_LENGTH_1
    | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL
    | SDRAM_MODEREG_CAS_LATENCY_3
    | SDRAM_MODEREG_OPERATING_MODE_STANDARD
    | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE
  );
  SDRAM_SendCommand(&SdramCommand);

  SDRAM_ProgramRefreshRate(1539);
}









/**
  * @brief  Program the SDRAM Memory Refresh rate.
  * @param  RefreshRate: The SDRAM refresh rate value.
  * @return None
  */
void SDRAM_ProgramRefreshRate(uint32_t RefreshRate) {
  /* Set the refresh rate in command register */
  FMC_Bank5_6->SDRTR |= (__IO uint32_t)(RefreshRate << FMC_SDRTR_COUNT_Pos);
}




/**
  * @brief  Set the Number of consecutive SDRAM Memory auto Refresh commands.
  * @param  AutoRefreshNumber: Specifies the auto Refresh number.       
  * @return None
  */
void SDRAM_SetAutoRefreshNumber(uint32_t AutoRefreshNumber) {
  /* Set the Auto-refresh number in command register */
  FMC_Bank5_6->SDCMR |= (__IO uint32_t)(AutoRefreshNumber << FMC_SDCMR_NRFS_Pos); 
}




/**
  * @brief  Send Command to the FMC SDRAM bank
  * @param  Command: Pointer to SDRAM command structure   
  * @return send status
  */  
void SDRAM_SendCommand(SDRAM_CommandTypeDef *cmd) {
  FMC_Bank5_6->SDCMR = (__IO uint32_t)(
      cmd->CommandMode
    | cmd->CommandTarget
    | (cmd->AutoRefreshNumber << FMC_SDCMR_NRFS_Pos)
    | (cmd->ModeRegisterDefinition << FMC_SDCMR_MRD_Pos)
  );
  while (SDRAM_BUSY_STATUS_CHECK);
}












////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  Writes a byte into SDRAM's certain address
  * @param  addr: SDRAM address
  * @param  data: a byte   
  * @return none
  */
void SDRAM_Write8b(uint32_t addr, uint8_t data) {
  *(__IO uint8_t*) (SDRAM_START_ADDR + addr) = data;
}




/**
  * @brief  Reads a byte from SDRAM's certain address
  * @param  addr: SDRAM address
  * @return a byte
  */
uint8_t SDRAM_Read8b(uint32_t addr) {
  return (*(__IO uint8_t*)(SDRAM_START_ADDR + addr));
}




/**
  * @brief  Writes a halfword into SDRAM's certain address
  * @param  addr: SDRAM address
  * @param  data: a halfword
  * @return none
  */
void SDRAM_Write16b(uint32_t addr, uint16_t data) {
  *(__IO uint16_t*) (SDRAM_START_ADDR + addr) = data;
}




/**
  * @brief  Reads a halfword from SDRAM's certain address
  * @param  addr: SDRAM address
  * @return a halfword
  */
uint16_t SDRAM_Read16b(uint32_t addr) {
  return (*(__IO uint16_t*)(SDRAM_START_ADDR + addr));
}




/**
  * @brief  Writes a word into SDRAM's certain address
  * @param  addr: SDRAM address
  * @param  data: a word
  * @return none
  */
void SDRAM_Write32b(uint32_t addr, uint32_t data) {
  *(__IO uint32_t*)(SDRAM_START_ADDR + addr) = data;
}




/**
  * @brief  Reads a word from SDRAM's certain address
  * @param  addr SDRAM address
  * @return a word
  */
uint32_t SDRAM_Read32b(uint32_t addr) {
  return (*(__IO uint32_t*)(SDRAM_START_ADDR + addr));
}




/**
  * @brief  Reads a buffer from SDRAM's certain address
  * @param  addr SDRAM address
  * @param  cnt count of bytes
  * @param  buf pointer of a buffer
  * @return status of reading
  */
uint8_t SDRAM_ReadBuffer8b(uint32_t addr, uint32_t cnt, uint8_t *buf) {
  if ((addr + cnt) > SDRAM_MAX_ADDR_Offset) return (0);
  uint32_t ptr = addr;

  while (SDRAM_BUSY_STATUS_CHECK);

  while (cnt--) {
    *buf++ = *(__IO uint8_t*)(SDRAM_START_ADDR + ptr);
    ptr++;
  }
  return (1);
}




/**
  * @brief  Writes a buffer into SDRAM's certain address
  * @param  addr SDRAM address
  * @param  cnt count of bytes
  * @param  buf pointer of a buffer
  * @return status of writing
  */
uint8_t SDRAM_WriteBuffer8b(uint32_t addr, uint32_t cnt, uint8_t *buf) {
  if ((addr + cnt) > SDRAM_MAX_ADDR_Offset) return (0);
  uint32_t ptr = addr;

  while (SDRAM_BUSY_STATUS_CHECK);

  while (cnt--) {
    *(__IO uint8_t*)(SDRAM_START_ADDR + ptr) = *buf++;
    ptr++;
  }
  return (1);
}




/**
  * @brief  Reads a buffer from SDRAM's certain address
  * @param  addr SDRAM address
  * @param  cnt count of words
  * @param  buf pointer of a buffer
  * @return status of reading
  */
uint8_t SDRAM_ReadBuffer(uint32_t addr, uint32_t cnt, uint32_t *buf) {
  if ((addr + cnt) > SDRAM_MAX_ADDR_Offset) return (0);
  uint32_t ptr = addr;

  while (SDRAM_BUSY_STATUS_CHECK);

  while (cnt--) {
    *buf++ = *(__IO uint32_t*)(SDRAM_START_ADDR + ptr);
    ptr += 4;
  }
  return (1);
}




/**
  * @brief  Writes a buffer into SDRAM's certain address
  * @param  addr SDRAM address
  * @param  cnt count of words
  * @param  buf pointer of a buffer
  * @return status of writing
  */
uint8_t SDRAM_WriteBuffer(uint32_t addr, uint32_t cnt, uint32_t *buf) {
  if ((addr + cnt) > SDRAM_MAX_ADDR_Offset) return (0);
  uint32_t ptr = addr;

  while (SDRAM_BUSY_STATUS_CHECK);

  while (cnt--) {
    *(__IO uint32_t*)(SDRAM_START_ADDR + ptr) = *buf++;
    ptr += 4;
  }
  return (1);
}
