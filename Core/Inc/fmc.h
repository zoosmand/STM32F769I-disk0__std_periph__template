/**
  ******************************************************************************
  * File Name          : fmc.h
  * Description        : This file provides code for the configuration
  *                      of the FMC instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FMC_H
#define __FMC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Global variables ----------------------------------------------------------*/
extern uint32_t _FMCREG_;


/* Private defines -----------------------------------------------------------*/
typedef enum {
  _NAND = 0,
  _PCCARD,
  _NORSRAM,
  _NORSRAM_EXT,
  _SDRAM
} FMC_MemoryMode;

#define SDRAM_START_ADDR                          (uint32_t)0xc0000000 // SDRAM Bank 1 adress
// #define SDRAM_START_ADDR                          (uint32_t)0xd0000000 // SDRAM Bank 2 address
#define SDRAM_MAX_ADDR_Offset                     (uint32_t)(0x01000000 - 1) // 16MB

#define SDRAM_MODEREG_BURST_LENGTH_1              (uint16_t)0x0000
#define SDRAM_MODEREG_BURST_LENGTH_2              (uint16_t)0x0001
#define SDRAM_MODEREG_BURST_LENGTH_4              (uint16_t)0x0002
#define SDRAM_MODEREG_BURST_LENGTH_8              (uint16_t)0x0004
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL       (uint16_t)0x0000
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED      (uint16_t)0x0008
#define SDRAM_MODEREG_CAS_LATENCY_1               (uint16_t)0x0000
#define SDRAM_MODEREG_CAS_LATENCY_2               (uint16_t)0x0020
#define SDRAM_MODEREG_CAS_LATENCY_3               (uint16_t)0x0030
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD     (uint16_t)0x0000
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED  (uint16_t)0x0000
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE      (uint16_t)0x0200

#define SDRAM_BANK1                               0
#define SDRAM_BANK2                               1

/* SDCRx bits definition */
// NC[1:0]: Number of column address bits
// #define FMC_SDCR_COL_BITS_8                       0b00
// #define FMC_SDCR_COL_BITS_9                       0b01
// #define FMC_SDCR_COL_BITS_10                      0b10
// #define FMC_SDCR_COL_BITS_11                      0b11
// #define FMC_SDCR_COL_BITS_Pos                     0
#define FMC_SDCR_COL_BITS_8                       0x00000000
#define FMC_SDCR_COL_BITS_9                       FMC_SDCR1_NC_0 //0x00000001
#define FMC_SDCR_COL_BITS_10                      FMC_SDCR1_NC_1 //0x00000002
#define FMC_SDCR_COL_BITS_11                      FMC_SDCR1_NC //0x00000003


// NR[1:0]: Number of row address bits
// #define FMC_SDCR_ROW_BITS_11                      0b00
// #define FMC_SDCR_ROW_BITS_12                      0b01
// #define FMC_SDCR_ROW_BITS_13                      0b10
// #define FMC_SDCR_ROW_BITS_Pos                     2
#define FMC_SDCR_ROW_BITS_11                      0x00000000
#define FMC_SDCR_ROW_BITS_12                      FMC_SDCR1_NR_0 //0x00000004
#define FMC_SDCR_ROW_BITS_13                      FMC_SDCR1_NR_1 //0x00000008

// MWID[1:0]: Memory data bus width
// #define FMC_SDCR_BUS_8                            0b00
// #define FMC_SDCR_BUS_16                           0b01
// #define FMC_SDCR_BUS_32                           0b10
// #define FMC_SDCR_BUS_Pos                          4
#define FMC_SDCR_BUS_8                            0x00000000
#define FMC_SDCR_BUS_16                           FMC_SDCR1_MWID_0 //0x00000010
#define FMC_SDCR_BUS_32                           FMC_SDCR1_MWID_1 //0x00000020

// NB: Number of internal banks
// #define FMC_SDCR_BANKS_NUM_2                      0b0
// #define FMC_SDCR_BANKS_NUM_4                      0b1
// #define FMC_SDCR_BANKS_NUM_Pos                    6
#define FMC_SDCR_BANKS_NUM_2                      0x00000000
#define FMC_SDCR_BANKS_NUM_4                      FMC_SDCR1_NB //0x00000040

// CAS[1:0]: CAS Latency, 1-2-3 cycles
// #define FMC_SDCR_CAS_1                            0b01
// #define FMC_SDCR_CAS_2                            0b10
// #define FMC_SDCR_CAS_3                            0b11
// #define FMC_SDCR_CAS_Pos                          7
#define FMC_SDCR_CAS_1                            FMC_SDCR1_CAS_0 //0x00000080
#define FMC_SDCR_CAS_2                            FMC_SDCR1_CAS_1 //0x00000100
#define FMC_SDCR_CAS_3                            FMC_SDCR1_CAS //0x00000180

// WP: Write protection
// #define FMC_SDCR_WP_DIS                           0b0
// #define FMC_SDCR_WP_EN                            0b1
// #define FMC_SDCR_WP_Pos                           9
#define FMC_SDCR_WP_DIS                           0x00000000
#define FMC_SDCR_WP_EN                            FMC_SDCR1_WP //0x00000200

// SDCLK[1:0]: SDRAM clock configuration
// #define FMC_SDCR_CLK_DIS                          0b00
// #define FMC_SDCR_CLK_PER_2                        0b10
// #define FMC_SDCR_CLK_PER_3                        0b11
// #define FMC_SDCR_CLK_Pos                          10
#define FMC_SDCR_CLK_DIS                          0x00000000
#define FMC_SDCR_CLK_PER_2                        FMC_SDCR1_SDCLK_1 //0x00000800
#define FMC_SDCR_CLK_PER_3                        FMC_SDCR1_SDCLK //0x00000c00

// RBURST: Burst read
// #define FMC_SDCR_RBURST_DIS                       0b0
// #define FMC_SDCR_RBURST_EN                        0b1
// #define FMC_SDCR_RBURST_Pos                       12
#define FMC_SDCR_RBURST_DIS                       0x00000000
#define FMC_SDCR_RBURST_EN                        FMC_SDCR1_RBURST //0x00001000

// RPIPE[1:0]: Read pipe delay 0-1-2 clock cycle
// #define FMC_SDCR_RPIPE_0                          0b00
// #define FMC_SDCR_RPIPE_1                          0b01
// #define FMC_SDCR_RPIPE_2                          0b10
// #define FMC_SDCR_RPIPE_Pos                        13
#define FMC_SDCR_RPIPE_0                          0x00000000
#define FMC_SDCR_RPIPE_1                          FMC_SDCR1_RPIPE_0 //0x00002000
#define FMC_SDCR_RPIPE_2                          FMC_SDCR1_RPIPE_1 //0x00004000



// #define FMC_SDTR_TMRD_Pos                         0 // TMRD[3:0]: Load Mode Register to Active
// #define FMC_SDTR_TXSR_Pos                         4 // TXSR[3:0]: Exit Self-refresh delay
// #define FMC_SDTR_TRAS_Pos                         8 // TRAS[3:0]: Self refresh time
// #define FMC_SDTR_TRC_Pos                          12 // TRC[3:0]: Row cycle delay
// #define FMC_SDTR_TWR_Pos                          16 // TWR[3:0]: Recovery delay
// #define FMC_SDTR_TRP_Pos                          20 // TRP[3:0]: Row precharge delay
// #define FMC_SDTR_TRCD_Pos                         24 // TRCD[3:0]: Row to column delay


#define SDRAM_CMD_NORMAL_MODE                     0x00000000
#define SDRAM_CMD_CLK_ENABLE                      0x00000001
#define SDRAM_CMD_PALL                            0x00000002
#define SDRAM_CMD_AUTOREFRESH_MODE                0x00000003
#define SDRAM_CMD_LOAD_MODE                       0x00000004
#define SDRAM_CMD_SELFREFRESH_MODE                0x00000004
#define SDRAM_CMD_POWERDOWN_MODE                  0x00000006

#define SDRAM_CMD_TARGET_BANK2                    FMC_SDCMR_CTB2
#define SDRAM_CMD_TARGET_BANK1                    FMC_SDCMR_CTB1
#define SDRAM_CMD_TARGET_BANK1_2                  (FMC_SDCMR_CTB2 | FMC_SDCMR_CTB1)

#define SDRAM_NORMAL_MODE                         0x00000000
#define SDRAM_SELF_REFRESH_MODE                   FMC_SDSR_MODES1_0
#define SDRAM_POWER_DOWN_MODE                     FMC_SDSR_MODES1_1

// #define SDRAM_AUTO_REFRESH_NUM_Pos                FMC_SDCMR_NRFS_Pos
// #define SDRAM_MODE_REG_Pos                        FMC_SDCMR_MRD_Pos




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


// PF0
#define FMC_A0_Pin          GPIO_PIN_0
#define FMC_A0_Pin_Pos      GPIO_PIN_0_Pos
#define FMC_A0_Pin_Mask     GPIO_PIN_0_Mask
// PF1
#define FMC_A1_Pin          GPIO_PIN_1
#define FMC_A1_Pin_Pos      GPIO_PIN_1_Pos
#define FMC_A1_Pin_Mask     GPIO_PIN_1_Mask
// PF2
#define FMC_A2_Pin          GPIO_PIN_2
#define FMC_A2_Pin_Pos      GPIO_PIN_2_Pos
#define FMC_A2_Pin_Mask     GPIO_PIN_2_Mask
// PF3
#define FMC_A3_Pin          GPIO_PIN_3
#define FMC_A3_Pin_Pos      GPIO_PIN_3_Pos
#define FMC_A3_Pin_Mask     GPIO_PIN_3_Mask
// PF4
#define FMC_A4_Pin          GPIO_PIN_4
#define FMC_A4_Pin_Pos      GPIO_PIN_4_Pos
#define FMC_A4_Pin_Mask     GPIO_PIN_4_Mask
// PF5
#define FMC_A5_Pin          GPIO_PIN_5
#define FMC_A5_Pin_Pos      GPIO_PIN_5_Pos
#define FMC_A5_Pin_Mask     GPIO_PIN_5_Mask
// PF12
#define FMC_A6_Pin          GPIO_PIN_12
#define FMC_A6_Pin_Pos      GPIO_PIN_12_Pos
#define FMC_A6_Pin_Mask     GPIO_PIN_12_Mask
// PF13
#define FMC_A7_Pin          GPIO_PIN_13
#define FMC_A7_Pin_Pos      GPIO_PIN_13_Pos
#define FMC_A7_Pin_Mask     GPIO_PIN_13_Mask
// PF14
#define FMC_A8_Pin          GPIO_PIN_14
#define FMC_A8_Pin_Pos      GPIO_PIN_14_Pos
#define FMC_A8_Pin_Mask     GPIO_PIN_14_Mask
// PF15
#define FMC_A9_Pin          GPIO_PIN_15
#define FMC_A9_Pin_Pos      GPIO_PIN_15_Pos
#define FMC_A9_Pin_Mask     GPIO_PIN_15_Mask
// PG0
#define FMC_A10_Pin         GPIO_PIN_0
#define FMC_A10_Pin_Pos     GPIO_PIN_0_Pos
#define FMC_A10_Pin_Mask    GPIO_PIN_0_Mask
// PG1
#define FMC_A11_Pin         GPIO_PIN_1
#define FMC_A11_Pin_Pos     GPIO_PIN_1_Pos
#define FMC_A11_Pin_Mask    GPIO_PIN_1_Mask
// PD14
#define FMC_D0_Pin          GPIO_PIN_14
#define FMC_D0_Pin_Pos      GPIO_PIN_14_Pos
#define FMC_D0_Pin_Mask     GPIO_PIN_14_Mask
// PD15
#define FMC_D1_Pin          GPIO_PIN_15
#define FMC_D1_Pin_Pos      GPIO_PIN_15_Pos
#define FMC_D1_Pin_Mask     GPIO_PIN_15_Mask
// PD0
#define FMC_D2_Pin          GPIO_PIN_0
#define FMC_D2_Pin_Pos      GPIO_PIN_0_Pos
#define FMC_D2_Pin_Mask     GPIO_PIN_0_Mask
// PD1
#define FMC_D3_Pin          GPIO_PIN_1
#define FMC_D3_Pin_Pos      GPIO_PIN_1_Pos
#define FMC_D3_Pin_Mask     GPIO_PIN_1_Mask
// PE7
#define FMC_D4_Pin          GPIO_PIN_7
#define FMC_D4_Pin_Pos      GPIO_PIN_7_Pos
#define FMC_D4_Pin_Mask     GPIO_PIN_7_Mask
// PE8
#define FMC_D5_Pin          GPIO_PIN_8
#define FMC_D5_Pin_Pos      GPIO_PIN_8_Pos
#define FMC_D5_Pin_Mask     GPIO_PIN_8_Mask
// PE9
#define FMC_D6_Pin          GPIO_PIN_9
#define FMC_D6_Pin_Pos      GPIO_PIN_9_Pos
#define FMC_D6_Pin_Mask     GPIO_PIN_9_Mask
// PE10
#define FMC_D7_Pin          GPIO_PIN_10
#define FMC_D7_Pin_Pos      GPIO_PIN_10_Pos
#define FMC_D7_Pin_Mask     GPIO_PIN_10_Mask
// PE11
#define FMC_D8_Pin          GPIO_PIN_11
#define FMC_D8_Pin_Pos      GPIO_PIN_11_Pos
#define FMC_D8_Pin_Mask     GPIO_PIN_11_Mask
// PE12
#define FMC_D9_Pin          GPIO_PIN_12
#define FMC_D9_Pin_Pos      GPIO_PIN_12_Pos
#define FMC_D9_Pin_Mask     GPIO_PIN_12_Mask
// PE13
#define FMC_D10_Pin         GPIO_PIN_13
#define FMC_D10_Pin_Pos     GPIO_PIN_13_Pos
#define FMC_D10_Pin_Mask    GPIO_PIN_13_Mask
// PE14
#define FMC_D11_Pin         GPIO_PIN_14
#define FMC_D11_Pin_Pos     GPIO_PIN_14_Pos
#define FMC_D11_Pin_Mask    GPIO_PIN_14_Mask
// PE15
#define FMC_D12_Pin         GPIO_PIN_15
#define FMC_D12_Pin_Pos     GPIO_PIN_15_Pos
#define FMC_D12_Pin_Mask    GPIO_PIN_15_Mask
// PD8
#define FMC_D13_Pin         GPIO_PIN_8
#define FMC_D13_Pin_Pos     GPIO_PIN_8_Pos
#define FMC_D13_Pin_Mask    GPIO_PIN_8_Mask
// PD9
#define FMC_D14_Pin         GPIO_PIN_9
#define FMC_D14_Pin_Pos     GPIO_PIN_9_Pos
#define FMC_D14_Pin_Mask    GPIO_PIN_9_Mask
// PD10
#define FMC_D15_Pin         GPIO_PIN_10
#define FMC_D15_Pin_Pos     GPIO_PIN_10_Pos
#define FMC_D15_Pin_Mask    GPIO_PIN_10_Mask
// PH8
#define FMC_D16_Pin         GPIO_PIN_8
#define FMC_D16_Pin_Pos     GPIO_PIN_8_Pos
#define FMC_D16_Pin_Mask    GPIO_PIN_8_Mask
// PH9
#define FMC_D17_Pin         GPIO_PIN_9
#define FMC_D17_Pin_Pos     GPIO_PIN_9_Pos
#define FMC_D17_Pin_Mask    GPIO_PIN_9_Mask
// PH10
#define FMC_D18_Pin         GPIO_PIN_10
#define FMC_D18_Pin_Pos     GPIO_PIN_10_Pos
#define FMC_D18_Pin_Mask    GPIO_PIN_10_Mask
// PH11
#define FMC_D19_Pin         GPIO_PIN_11
#define FMC_D19_Pin_Pos     GPIO_PIN_11_Pos
#define FMC_D19_Pin_Mask    GPIO_PIN_11_Mask
// PH12
#define FMC_D20_Pin         GPIO_PIN_12
#define FMC_D20_Pin_Pos     GPIO_PIN_12_Pos
#define FMC_D20_Pin_Mask    GPIO_PIN_12_Mask
// PH13
#define FMC_D21_Pin         GPIO_PIN_13
#define FMC_D21_Pin_Pos     GPIO_PIN_13_Pos
#define FMC_D21_Pin_Mask    GPIO_PIN_13_Mask
// PH14
#define FMC_D22_Pin         GPIO_PIN_14
#define FMC_D22_Pin_Pos     GPIO_PIN_14_Pos
#define FMC_D22_Pin_Mask    GPIO_PIN_14_Mask
// PH15
#define FMC_D23_Pin         GPIO_PIN_15
#define FMC_D23_Pin_Pos     GPIO_PIN_15_Pos
#define FMC_D23_Pin_Mask    GPIO_PIN_15_Mask
// PI0
#define FMC_D24_Pin         GPIO_PIN_0
#define FMC_D24_Pin_Pos     GPIO_PIN_0_Pos
#define FMC_D24_Pin_Mask    GPIO_PIN_0_Mask
// PI1
#define FMC_D25_Pin         GPIO_PIN_1
#define FMC_D25_Pin_Pos     GPIO_PIN_1_Pos
#define FMC_D25_Pin_Mask    GPIO_PIN_1_Mask
// PI2
#define FMC_D26_Pin         GPIO_PIN_2
#define FMC_D26_Pin_Pos     GPIO_PIN_2_Pos
#define FMC_D26_Pin_Mask    GPIO_PIN_2_Mask
// PI3
#define FMC_D27_Pin         GPIO_PIN_3
#define FMC_D27_Pin_Pos     GPIO_PIN_3_Pos
#define FMC_D27_Pin_Mask    GPIO_PIN_3_Mask
// PI6
#define FMC_D28_Pin         GPIO_PIN_6
#define FMC_D28_Pin_Pos     GPIO_PIN_6_Pos
#define FMC_D28_Pin_Mask    GPIO_PIN_6_Mask
// PI7
#define FMC_D29_Pin         GPIO_PIN_7
#define FMC_D29_Pin_Pos     GPIO_PIN_7_Pos
#define FMC_D29_Pin_Mask    GPIO_PIN_7_Mask
// PI9
#define FMC_D30_Pin         GPIO_PIN_9
#define FMC_D30_Pin_Pos     GPIO_PIN_9_Pos
#define FMC_D30_Pin_Mask    GPIO_PIN_9_Mask
// PI10
#define FMC_D31_Pin         GPIO_PIN_10
#define FMC_D31_Pin_Pos     GPIO_PIN_10_Pos
#define FMC_D31_Pin_Mask    GPIO_PIN_10_Mask



// PH5
#define FMC_SDNWE_Pin       GPIO_PIN_5
#define FMC_SDNWE_Pin_Pos   GPIO_PIN_5_Pos
#define FMC_SDNWE_Pin_Mask  GPIO_PIN_5_Mask
// PF11
#define FMC_SDNRAS_Pin      GPIO_PIN_11
#define FMC_SDNRAS_Pin_Pos  GPIO_PIN_11_Pos
#define FMC_SDNRAS_Pin_Mask GPIO_PIN_11_Mask



// PG4
#define FMC_BA0_Pin         GPIO_PIN_4
#define FMC_BA0_Pin_Pos     GPIO_PIN_4_Pos
#define FMC_BA0_Pin_Mask    GPIO_PIN_4_Mask
// PG5
#define FMC_BA1_Pin         GPIO_PIN_5
#define FMC_BA1_Pin_Pos     GPIO_PIN_5_Pos
#define FMC_BA1_Pin_Mask    GPIO_PIN_5_Mask



// PG8
#define FMC_SDCLK_Pin       GPIO_PIN_8
#define FMC_SDCLK_Pin_Pos   GPIO_PIN_8_Pos
#define FMC_SDCLK_Pin_Mask  GPIO_PIN_8_Mask
// PG15
#define FMC_SDNCAS_Pin      GPIO_PIN_15
#define FMC_SDNCAS_Pin_Pos  GPIO_PIN_15_Pos
#define FMC_SDNCAS_Pin_Mask GPIO_PIN_15_Mask


// PH2
#define FMC_SDCKE0_Pin      GPIO_PIN_2
#define FMC_SDCKE0_Pin_Pos  GPIO_PIN_2_Pos
#define FMC_SDCKE0_Pin_Mask GPIO_PIN_2_Mask
// PH3
#define FMC_SDNE0_Pin       GPIO_PIN_3
#define FMC_SDNE0_Pin_Pos   GPIO_PIN_3_Pos
#define FMC_SDNE0_Pin_Mask  GPIO_PIN_3_Mask




// PE0
#define FMC_NBL0_Pin        GPIO_PIN_0
#define FMC_NBL0_Pin_Pos    GPIO_PIN_0_Pos
#define FMC_NBL0_Pin_Mask   GPIO_PIN_0_Mask
// PE1
#define FMC_NBL1_Pin        GPIO_PIN_1
#define FMC_NBL1_Pin_Pos    GPIO_PIN_1_Pos
#define FMC_NBL1_Pin_Mask   GPIO_PIN_1_Mask
// PI4
#define FMC_NBL2_Pin        GPIO_PIN_4
#define FMC_NBL2_Pin_Pos    GPIO_PIN_4_Pos
#define FMC_NBL2_Pin_Mask   GPIO_PIN_4_Mask
// PI5
#define FMC_NBL3_Pin        GPIO_PIN_4
#define FMC_NBL3_Pin_Pos    GPIO_PIN_4_Pos
#define FMC_NBL3_Pin_Mask   GPIO_PIN_4_Mask



typedef struct {
  uint32_t CommandMode;                  /*!< Defines the command issued to the SDRAM device. */
  uint32_t CommandTarget;                /*!< Defines which device (1 or 2) the command will be issued to. */
  uint32_t AutoRefreshNumber;            /*!< Defines the number of consecutive auto refresh command issued. */
  uint32_t ModeRegisterDefinition;       /*!< Defines the SDRAM Mode register content. */
} SDRAM_CommandTypeDef;



// FMC Registry Flags



/* Exported macro ------------------------------------------------------------*/
#define SDRAM_BUSY_STATUS_CHECK                   (PREG_CHECK(FMC_Bank5_6->SDSR, FMC_SDSR_BUSY_Pos))


/* Exported functions prototypes ---------------------------------------------*/
void FMC_Init(FMC_MemoryMode mode);
////// SDRAM //////
void SDRAM_SendCommand(SDRAM_CommandTypeDef *cmd);
void SDRAM_ProgramRefreshRate(uint32_t RefreshRate);
void SDRAM_SetAutoRefreshNumber(uint32_t AutoRefreshNumber);
void SDRAM_Write8b(uint32_t addr, uint8_t data);
uint8_t SDRAM_Read8b(uint32_t addr);
void SDRAM_Write16b(uint32_t addr, uint16_t data);
uint16_t SDRAM_Read16b(uint32_t addr);
void SDRAM_Write32b(uint32_t addr, uint32_t data);
uint32_t SDRAM_Read32b(uint32_t addr);
uint8_t SDRAM_ReadBuffer8b(uint32_t addr, uint32_t cnt, uint8_t *buf);
uint8_t SDRAM_WriteBuffer8b(uint32_t addr, uint32_t cnt, uint8_t *buf);
uint8_t SDRAM_ReadBuffer(uint32_t addr, uint32_t cnt, uint32_t *buf);
uint8_t SDRAM_WriteBuffer(uint32_t addr, uint32_t cnt, uint32_t *buf);




#ifdef __cplusplus
}
#endif
#endif /*__FMC_H */
