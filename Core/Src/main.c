/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Global variables ---------------------------------------------------------*/
uint32_t sysQuantum           = 0;
uint32_t millis               = 0;
uint32_t seconds              = 0;
uint32_t minutes              = 0;
uint32_t _GLOBALREG_          = 0;
uint32_t delay_tmp            = 0;
uint32_t SystemCoreClock      = 16000000;
RCC_ClocksTypeDef RccClocks;

/* Private variables ---------------------------------------------------------*/
static uint32_t millis_tmp    = 100;
static uint32_t seconds_tmp   = 1000;
static uint32_t minutes_tmp   = 60;

// static uint32_t delay_ts = 0;

/* Private function prototypes -----------------------------------------------*/
static void CronSysQuantum_Handler(void);
static void CronMillis_Handler(void);
static void CronSeconds_Handler(void);
static void CronMinutes_Handler(void);
static void Flags_Handler(void);









////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {

  // Delay(500);

  while (1) {
    Delay_Handler(0);
    Cron_Handler();
    Flags_Handler();
  }
}








/********************************************************************************/
/*                                     CRON                                     */
/********************************************************************************/
void Cron_Handler(void) {
  $CronStart:
  if (SysTick->CTRL & (1 << SysTick_CTRL_COUNTFLAG_Pos)) { 
    sysQuantum++;
    CronSysQuantum_Handler();
  }

  if (sysQuantum >= millis_tmp) {
    millis++;
    millis_tmp = sysQuantum + 100;
    CronMillis_Handler();
  }
  
  if (millis >= seconds_tmp) {
    seconds++;
    seconds_tmp += 1000;
    CronSeconds_Handler();
  }
  
  if (seconds >= minutes_tmp) {
    minutes++;
    minutes_tmp += 60;
    CronMinutes_Handler();
  }

  while (sysQuantum < delay_tmp) {
    goto $CronStart;
  }
  // !!!!!!!!! The bug!!!!!!!!
  delay_tmp = 0;
  FLAG_CLR(_GLOBALREG_, _DELAYF_);
}






/********************************************************************************/
/*                             CRON EVENTS HANDLERS                             */
/********************************************************************************/
// ---- System Quantum ---- //
static void CronSysQuantum_Handler(void) {
  //
}

// ---- Milliseconds ---- //
static void CronMillis_Handler(void) {
  //
}

// ---- Seconds ---- //
static void CronSeconds_Handler(void) {
  /* Refresh independent watchdog */
  IWDG->KR = IWDG_KEY_RELOAD;
  /* Let secondly running procedures to run */
  FLAG_SET(_GLOBALREG_, _SECF_);
}

// ---- Minutes ---- //
static void CronMinutes_Handler(void) {
  //
}






/********************************************************************************/
/*                                     FLAGS                                    */
/********************************************************************************/
void Flags_Handler(void){
  /* TIM7 IT event */
  if (FLAG_CHECK(_TIMREG_, _BT6F_)) {
    Timer_Handler(TIM6);
    FLAG_CLR(_TIMREG_, _BT6F_);
  }

  /* USART1 IT event  */
  if (FLAG_CHECK(_USARTREG_, _USART1_RXAF_)) {
    USART1_RX_Handler();
    FLAG_CLR(_USARTREG_, _USART1_RXAF_);
  }

  /* USART1 Local Buffer event */
  if (FLAG_CHECK(_USARTREG_, _USART1_LBNEF_)) {
    // uint8_t bbb[4];
    // USART1_RxBufferRead(bbb, 4);
    FLAG_CLR(_USARTREG_, _USART1_LBNEF_);
  }

  /* RTC Alarm A IT event */
  if (FLAG_CHECK(_RTCREG_, _ALAF_)) {
    RTC_Alarm_Handler('A');
    FLAG_CLR(_RTCREG_, _ALAF_);
  }

  /* RTC Alarm B IT event */
  if (FLAG_CHECK(_RTCREG_, _ALBF_)) {
    RTC_Alarm_Handler('B');
    FLAG_CLR(_RTCREG_, _ALBF_);
  }

  /* The set of procedures runs every second */
  if (FLAG_CHECK(_GLOBALREG_, _SECF_)) {
    // LED_Blink(LED_Port, LED0_Pin);
    printf("test\n");
    // PrintDateTime(_printf);
    // SDRAM_Write8b(0, 'A');
    // SDRAM_Write8b(1, 'B');

    // uint8_t aaa = SDRAM_Read8b(0);
    // uint8_t bbb = SDRAM_Read8b(1);
    // printf("%c%c\n", aaa, bbb);


    DisplayDateAndTime_Handler();

    DrawHLine(L1, 2, 100, 100, _YELLOW);
    DrawVLine(L1, 1, 100, 100, _WHITE);


    FillRectangle(L1, 100, 200, 100, 200, _GREEN);


    // SDRAM_Write32b(0, 0xffffffff);

    // if (truner) {
    //   IO_WriteCmd(0, (uint8_t *){OTM8009A_CMD_MADCTR, 0xa0});
    //   truner = 0;
    // } else {
    //   IO_WriteCmd(0, (uint8_t *){OTM8009A_CMD_MADCTR, 0x60});
    //   truner = 1;
    // }

    // FT6206_Init();

    FLAG_CLR(_GLOBALREG_, _SECF_);
  }
}










void Delay(uint32_t delay) {
  __IO uint64_t tmp = 43200 * delay;
  while (tmp--);
}











/**
  * @brief  Reset of all peripherals, Initializes the Flash interface and the Systick.
  * @retval None
  */
void SystemInit(void) {
  /* Vector Table Relocation in Internal FLASH */
  SCB->VTOR = FLASH_BASE | 0x00;

 /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* Enable the FLASH Adaptive Real-Time memory accelerator */
  SET_BIT(FLASH->ACR, FLASH_ACR_ARTEN);

  /* Enable the FLASH prefetch buffer */
  FLASH->ACR |= FLASH_ACR_PRFTEN;

  /* Set Interrupt Group Priority */
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Conficure SysTick */
  // SysTick->CTRL     = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
  // SysTick->LOAD     = 2160U - 1U;
  // SysTick->VAL      = 0;
  // SysTick->CTRL     |= SysTick_CTRL_ENABLE_Msk;
  SET_BIT(SysTick->CTRL, (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk));
  SysTick->LOAD = 2160U - 1U;
  SysTick->VAL = 0;
  SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);

  /* SysTick interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(SysTick_IRQn);

  /* SysCfg */
  PREG_SET(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN_Pos);
  while (!(PREG_CHECK(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN_Pos)));
   
  /* PWR */
  PREG_SET(RCC->APB1ENR, RCC_APB1ENR_PWREN_Pos);
  while (!(PREG_CHECK(RCC->APB1ENR, RCC_APB1ENR_PWREN_Pos)));
  PREG_SET(RCC->APB1ENR, RCC_APB2ENR_SYSCFGEN_Pos);
  while (!(PREG_CHECK(RCC->APB1ENR, RCC_APB2ENR_SYSCFGEN_Pos)));

  /* FLASH_IRQn interrupt configuration */
  NVIC_SetPriority(FLASH_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(FLASH_IRQn);

  /* RCC_IRQn interrupt configuration */
  NVIC_SetPriority(RCC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(RCC_IRQn);

  /* Set the FLASH Latency */
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_7WS);
  if (READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_7WS) {
    Error_Handler();
  }

  /* Configure the main internal regulator output voltage */
  PREG_SET(PWR->CR1, PWR_CR1_VOS_Pos);
  while (!(PREG_CHECK(PWR->CR1, PWR_CR1_VOS_Pos)));
  /* Enable Over drive Mode */
  PREG_SET(PWR->CR1, PWR_CR1_ODEN_Pos);

  /* HSE enable and wait till it's ready */
  PREG_SET(RCC->CR, RCC_CR_HSEON_Pos);
  while(!(PREG_CHECK(RCC->CR, RCC_CR_HSERDY_Pos)));

  /* LSI enable and wait till it's ready */
  PREG_SET(RCC->CSR, RCC_CSR_LSION_Pos);
  while(!(PREG_CHECK(RCC->CSR, RCC_CSR_LSIRDY_Pos)));

  /* Backup registers enable access */
  PREG_SET(PWR->CR1, PWR_CR1_DBP_Pos);

  /* force backup domain reset */
  PREG_SET(RCC->BDCR, RCC_BDCR_BDRST_Pos);
  PREG_CLR(RCC->BDCR, RCC_BDCR_BDRST_Pos);

  /* Confugure LSE drive */
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, 0U);

  /* LSE enable and wait till it's ready */
  PREG_SET(RCC->BDCR, RCC_BDCR_LSEON_Pos);
  while(!(PREG_CHECK(RCC->BDCR, RCC_BDCR_LSERDY_Pos)));

  /* RTC source is LSE */
  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, RCC_BDCR_RTCSEL_0);

  /* Enable RTC */
  PREG_SET(RCC->BDCR, RCC_BDCR_RTCEN_Pos);

  /* Configure PLL domain end prescaller */
  MODIFY_REG(RCC->PLLCFGR, (RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP), ((RCC_PLLCFGR_PLLSRC_HSE | RCC_PLLCFGR_PLLM_4 | RCC_PLLCFGR_PLLM_3 | RCC_PLLCFGR_PLLM_0) | 432 << RCC_PLLCFGR_PLLN_Pos));
  /* PLL enable and wait till it's ready */
  PREG_SET(RCC->CR, RCC_CR_PLLON_Pos);
  while (!(PREG_CHECK(RCC->CR, RCC_CR_PLLRDY_Pos)));

  /* AHB isn't divided */
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);

  /* APB1 divided by 4 */
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4);
  /* APB2 divided by 2 */
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2);

  /* Enable PLL as sysclock and wait till it's ready */
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
  while(!(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL));

  SystemCoreClock = 216000000U;
  RccClocks.HCLK_Freq = SystemCoreClock;
  RccClocks.PCLK1_Freq = 54000000U;
  RccClocks.PCLK1_Freq_Tim = 108000000U;
  RccClocks.PCLK2_Freq = 108000000U;
  RccClocks.PCLK2_Freq_Tim = 216000000U;


  // MODIFY_REG(RCC->DCKCFGR2, (((RCC_DCKCFGR2_USART1SEL << 16U) | RCC_DCKCFGR2_USART1SEL_0) >> 16U), (((RCC_DCKCFGR2_USART1SEL << 16U) | RCC_DCKCFGR2_USART1SEL_0) & 0x0000FFFFU));

  /* Set timers prescaler */
  MODIFY_REG(RCC->DCKCFGR1, RCC_DCKCFGR1_TIMPRE_Msk, (0 << RCC_DCKCFGR1_TIMPRE_Pos));

  /* Enable PLL SAI Domain */
  RCC->PLLSAICFGR = (
      384 << RCC_PLLSAICFGR_PLLSAIN_Pos
    | 0 << RCC_PLLSAICFGR_PLLSAIP_Pos
    | 4 << RCC_PLLSAICFGR_PLLSAIQ_Pos
    | 7 << RCC_PLLSAICFGR_PLLSAIR_Pos
  );
  MODIFY_REG(RCC->DCKCFGR1, RCC_DCKCFGR1_PLLSAIDIVR_Msk, (0 << RCC_DCKCFGR1_PLLSAIDIVR_Pos));

  /* Enable PLL SAI wait till it's ready */
  PREG_SET(RCC->CR, RCC_CR_PLLSAION_Pos);
  while (!(PREG_CHECK(RCC->CR, RCC_CR_PLLSAIRDY_Pos)));



  /*****************************************************************************************/
  /*****************************************************************************************/
  /*****************************************************************************************/
  /* Freeze some peripherals for the debug purpose */
  #ifdef DEBUG
  SET_BIT(DBGMCU->APB1FZ, (
      DBGMCU_APB1_FZ_DBG_TIM7_STOP
    | DBGMCU_APB1_FZ_DBG_TIM6_STOP
    | DBGMCU_APB1_FZ_DBG_IWDG_STOP
    | DBGMCU_APB1_FZ_DBG_WWDG_STOP
  ));
  #endif

  /* Set SWO trace output */
  // PREG_SET(CoreDebug->DEMCR, CoreDebug_DEMCR_TRCENA_Pos); 
  // TPI->CSPSR = 0x1;
  // TPI->FFCR = 0x101;
  // TPI->SPPR = 0x1;
  // PREG_SET(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN_Pos);
  // ITM->LAR = 0xc5acce55;
  // ITM->TCR = (ITM_TCR_ITMENA_Msk | ITM_TCR_SYNCENA_Msk | (1 << ITM_TCR_TraceBusID_Pos));
  // ITM->TER = 0x1;
  // ITM->TPR = 0x1;


  /*****************************************************************************************/
  /* IWDG */
  IWDG->KR = IWDG_KEY_ENABLE;
  IWDG->KR = IWDG_KEY_WR_ACCESS_ENABLE;
  IWDG->PR =  IWDG_PR_PR & (IWDG_PR_PR_2 | IWDG_PR_PR_0); /*!< Divider by 128 */
  IWDG->RLR = IWDG_RLR_RL & 624;
  while (!(PREG_CHECK(IWDG->SR, IWDG_SR_PVU_Pos)));
  IWDG->KR = IWDG_KEY_RELOAD;

  /*****************************************************************************************/
  /* Peripheral clock */
  /* APB1 */
  SET_BIT(RCC->APB1ENR, (
      RCC_APB1ENR_TIM6EN
    | RCC_APB1ENR_I2C1EN
    | RCC_APB1ENR_I2C4EN
  ));
  CLEAR_BIT(RCC->APB1ENR, (
      RCC_APB1ENR_SPI2EN
  ));

  /* AHB1 */
  SET_BIT(RCC->AHB1ENR, ( 
      RCC_AHB1ENR_GPIOAEN
    | RCC_AHB1ENR_GPIOBEN
    | RCC_AHB1ENR_GPIOCEN
    | RCC_AHB1ENR_GPIODEN
    | RCC_AHB1ENR_GPIOEEN
    | RCC_AHB1ENR_GPIOFEN
    | RCC_AHB1ENR_GPIOJEN
    | RCC_AHB1ENR_GPIOGEN
    | RCC_AHB1ENR_GPIOHEN
    | RCC_AHB1ENR_GPIOIEN
    | RCC_AHB1ENR_GPIOKEN
    | RCC_AHB1ENR_CRCEN
    | RCC_AHB1ENR_DMA2DEN
  ));

  /* APB2 */
  SET_BIT(RCC->APB2ENR, (
      RCC_APB2ENR_USART1EN
    // | RCC_APB2ENR_SPI5EN
    | RCC_APB2ENR_LTDCEN
    | RCC_APB2ENR_DSIEN
  ));

  /* AHB3 */
  SET_BIT(RCC->AHB3ENR, (
      RCC_AHB3ENR_FMCEN
  ));
  /* Wait for FMC starts */
  while (!(PREG_CHECK(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN_Pos)));



  /************************************************************************************************/
  /************************************************************************************************/
  /************************************************************************************************/
  Delay(500);

  /* LED */
  LED_Init();

  /* EXTI */
  EXTI_Init();

  /* USART1 */ 
  USART1_Init();

  /* CRC */ 
  CRC_Init();

  /* SPI5 */
  // SPI5_Init();

  // /* I2C3 */
  // I2C3_Init();

  /* Basic Timer6 */
  BasicTimer6_Init();

  /* RTC */
  RTC_Init();

  /* I2C */
  // I2C_Init(I2C4);
  I2C_Init(I2C1);

  /* Sensors */
  BMx280_Init(BME280);

  /* Touchscreen STMPE811 */
  // PE811_Init();

  /* On-board display */
  Display_Init();

}


