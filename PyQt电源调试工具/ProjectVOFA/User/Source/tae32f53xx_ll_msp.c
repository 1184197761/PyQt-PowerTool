/**
 ******************************************************************************
 * @file    tae32f53xx_ll_msp.c
 * @author  MCD Application Team
 * @brief   LL MSP module.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
 * All rights reserved.</center></h2>
 *
 * This software is licensed by Tai-Action under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dbg/tae32f53xx_dbg.h"

/** @addtogroup TAE32F53xx_Examples
 * @{
 */

/** @addtogroup TAE32F53xx_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup MSP_LL_Private_Functions MSP LL Private Functions
 * @brief    MSP LL Private Functions
 * @{
 */

/**
 * @brief  Initializes the Global MSP.
 * @param  None
 * @retval None
 */
void LL_MspInit(void)
{
  // SYSCTRL PMU Config
  LL_SYSCTRL_PMUCfg();

#ifdef LL_GPIO_MODULE_ENABLED
  // GPIO Msp Init
  LL_SYSCTRL_GPIOA_ClkEnRstRelease();
  LL_SYSCTRL_GPIOB_ClkEnRstRelease();
  LL_SYSCTRL_GPIOC_ClkEnRstRelease();
  LL_SYSCTRL_GPIOD_ClkEnRstRelease();
#endif

#ifdef LL_DMA_MODULE_ENABLED
  // DMA Msp Init
  LL_SYSCTRL_DMA_ClkEnRstRelease();

  // NVIC DMA Interrupt Enable
  LL_NVIC_EnableIRQ(DMA_IRQn);
#endif

#ifdef LL_FLASH_MODULE_ENABLED
  // FLASH Msp Init
  LL_SYSCTRL_EFLASH_ClkEnRstRelease();
#endif
}

/**
 * @brief  DeInitializes the Global MSP.
 * @param  None
 * @retval None
 */
void LL_MspDeInit(void)
{
#ifdef LL_GPIO_MODULE_ENABLED
  // GPIO Msp DeInit
  LL_SYSCTRL_GPIOA_ClkDisRstAssert();
  LL_SYSCTRL_GPIOB_ClkDisRstAssert();
  LL_SYSCTRL_GPIOC_ClkDisRstAssert();
  LL_SYSCTRL_GPIOD_ClkDisRstAssert();
#endif

#ifdef LL_DMA_MODULE_ENABLED
  // DMA Msp DeInit
  LL_SYSCTRL_DMA_ClkDisRstAssert();

  // NVIC DMA Interrupt Disable
  LL_NVIC_DisableIRQ(DMA_IRQn);
#endif

#ifdef LL_FLASH_MODULE_ENABLED
  // FLASH Msp DeInit
  LL_SYSCTRL_EFLASH_ClkDisRstAssert();
#endif
}

/**
 * @brief  Initializes the FPLL MSP.
 * @param  Instance Specifies FPLL peripheral
 * @retval None
 */
void LL_FPLL_MspInit(FPLL_TypeDef *Instance)
{
  // Check FPLL Instance to be Valid
  if (!IS_FPLL_ALL_INSTANCE(Instance))
  {
    return;
  }

  // FPLL Soft Reset Release
  if (Instance == FPLL0)
  {
    LL_SYSCTRL_FPLL0_RstRelease();
  }
  else if (Instance == FPLL1)
  {
    LL_SYSCTRL_FPLL1_RstRelease();
  }
  else if (Instance == FPLL2)
  {
    LL_SYSCTRL_FPLL2_RstRelease();
  }
}

/**
 * @brief  DeInitializes the FPLL MSP.
 * @param  Instance Specifies FPLL peripheral
 * @retval None
 */
void LL_FPLL_MspDeInit(FPLL_TypeDef *Instance)
{
  // Check FPLL Instance to be Valid
  if (!IS_FPLL_ALL_INSTANCE(Instance))
  {
    return;
  }

  // FPLL Soft Reset Assert
  if (Instance == FPLL0)
  {
    LL_SYSCTRL_FPLL0_RstAssert();
  }
  else if (Instance == FPLL1)
  {
    LL_SYSCTRL_FPLL1_RstAssert();
  }
  else if (Instance == FPLL2)
  {
    LL_SYSCTRL_FPLL2_RstAssert();
  }
}

/**
 * @brief  Initializes the UART MSP.
 * @param  Instance Specifies UART peripheral
 * @retval None
 */
void LL_UART_MspInit(UART_TypeDef *Instance)
{
  GPIO_InitTypeDef UART_GPIO_Init;

  // Check UART Instance to be Valid
  if (!IS_UART_ALL_INSTANCE(Instance))
  {
    return;
  }

  if (Instance == UART0)
  {
    // UART0 Pinmux Config: PC10 & PC11
    //        UART_GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    //        UART_GPIO_Init.Mode = GPIO_MODE_AF;
    //        UART_GPIO_Init.OType = GPIO_OTYPE_PP;
    //        UART_GPIO_Init.Pull = GPIO_NOPULL;
    //        UART_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    //        UART_GPIO_Init.Alternate = GPIO_AF10_UART0;
    //        LL_GPIO_Init(GPIOC, &UART_GPIO_Init);
    UART_GPIO_Init.Pin = GPIO_PIN_7;
    UART_GPIO_Init.Mode = GPIO_MODE_AF;
    UART_GPIO_Init.Alternate = GPIO_AF10_UART0;
    LL_GPIO_Init(GPIOC, &UART_GPIO_Init);

    UART_GPIO_Init.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    UART_GPIO_Init.Mode = GPIO_MODE_AF;
    UART_GPIO_Init.OType = GPIO_OTYPE_PP;
    UART_GPIO_Init.Pull = GPIO_NOPULL;
    UART_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    UART_GPIO_Init.Alternate = GPIO_AF10_UART0;
    LL_GPIO_Init(GPIOA, &UART_GPIO_Init);

    // UART0 Bus Clock Enable and Soft Reset Release
    LL_SYSCTRL_UART0_ClkEnRstRelease();

    // NVIC UART0 Interrupt Enable
    LL_NVIC_EnableIRQ(UART0_IRQn);
  }
  else if (Instance == UART1)
  {
    // UART1 Pinmux Config: PB8 & PB9
    UART_GPIO_Init.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    UART_GPIO_Init.Mode = GPIO_MODE_AF;
    UART_GPIO_Init.OType = GPIO_OTYPE_PP;
    UART_GPIO_Init.Pull = GPIO_NOPULL;
    UART_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    UART_GPIO_Init.Alternate = GPIO_AF10_UART1;
    LL_GPIO_Init(GPIOB, &UART_GPIO_Init);

    // UART1 Bus Clock Enable and Soft Reset Release
    LL_SYSCTRL_UART1_ClkEnRstRelease();

    // NVIC UART1 Interrupt Enable
    LL_NVIC_EnableIRQ(UART1_IRQn);
  }
}

/**
 * @brief  DeInitializes the UART MSP.
 * @param  Instance Specifies UART peripheral
 * @retval None
 */
void LL_UART_MspDeInit(UART_TypeDef *Instance)
{
  // Check UART Instance to be Valid
  if (!IS_UART_ALL_INSTANCE(Instance))
  {
    return;
  }

  if (Instance == UART0)
  {
    // NVIC UART0 Interrupt Disable
    LL_NVIC_DisableIRQ(UART0_IRQn);

    // UART0 Bus Clock Disable and Soft Reset Assert
    LL_SYSCTRL_UART0_ClkDisRstAssert();

    // UART0 Pinmux DeInit
    LL_GPIO_DeInit(GPIOC, GPIO_PIN_10 | GPIO_PIN_11);
  }
  else if (Instance == UART1)
  {
    // NVIC UART1 Interrupt Disable
    LL_NVIC_DisableIRQ(UART1_IRQn);

    // UART1 Bus Clock Disable and Soft Reset Assert
    LL_SYSCTRL_UART1_ClkDisRstAssert();

    // UART1 Pinmux DeInit
    LL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);
  }
}

/**
 * @brief  Initializes the TMR MSP.
 * @param  Instance Specifies TMR peripheral
 * @retval None
 */
void LL_TMR_MspInit(TMR_TypeDef *Instance)
{
  GPIO_InitTypeDef TMR_GPIO_Init;

  // Check TMR Instance to be Valid
  if (!IS_TMR_ALL_INSTANCE(Instance))
  {
    return;
  }

  // Pinmux Common Config
  TMR_GPIO_Init.Mode = GPIO_MODE_AF;
  TMR_GPIO_Init.OType = GPIO_OTYPE_PP;
  TMR_GPIO_Init.Pull = GPIO_NOPULL;
  TMR_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;

  if (Instance == TMR0)
  {
    // TMR0 Pinmux Config: PA0
    TMR_GPIO_Init.Pin = GPIO_PIN_1;
    TMR_GPIO_Init.Alternate = GPIO_AF4_TMR0;
    LL_GPIO_Init(GPIOA, &TMR_GPIO_Init);

    // TMR Bus Clock Enable and Soft Reset Release
    LL_SYSCTRL_LSTMR_ClkEnRstRelease();

    // NVIC TMR0 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR0_IRQn);
  }
  else if (Instance == TMR1)
  {

    // TMR1 Pinmux Config: PA3
    TMR_GPIO_Init.Pin = GPIO_PIN_3;
    TMR_GPIO_Init.Alternate = GPIO_AF4_TMR1;
    LL_GPIO_Init(GPIOA, &TMR_GPIO_Init);

    // TMR Bus Clock Enable and Soft Reset Release
    LL_SYSCTRL_LSTMR_ClkEnRstRelease();

    // NVIC TMR1 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR1_IRQn);
  }
  else if (Instance == TMR2)
  {

    // TMR2 Pinmux Config: PA6
    TMR_GPIO_Init.Pin = GPIO_PIN_6;
    TMR_GPIO_Init.Alternate = GPIO_AF4_TMR2;
    LL_GPIO_Init(GPIOA, &TMR_GPIO_Init);

    // TMR Bus Clock Enable and Soft Reset Release
    LL_SYSCTRL_LSTMR_ClkEnRstRelease();

    // NVIC TMR2 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR2_IRQn);
  }
  else if (Instance == TMR3)
  {

    // TMR3 Pinmux Config: PA7
    TMR_GPIO_Init.Pin = GPIO_PIN_7;
    TMR_GPIO_Init.Alternate = GPIO_AF4_TMR3;
    LL_GPIO_Init(GPIOA, &TMR_GPIO_Init);

    // TMR Bus Clock Enable and Soft Reset Release
    LL_SYSCTRL_LSTMR_ClkEnRstRelease();

    // NVIC TMR3 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR3_IRQn);
  }
  else if (Instance == TMR4)
  {

    // TMR4 Pinmux Config: PA5
    TMR_GPIO_Init.Pin = GPIO_PIN_5;
    TMR_GPIO_Init.Alternate = GPIO_AF5_TMR4;
    LL_GPIO_Init(GPIOA, &TMR_GPIO_Init);

    // SYSCTRL HSTMR Bus Clock Enable and Reset Release
    LL_SYSCTRL_HSTMR_ClkEnRstRelease();

    // NVIC TMR4 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR4_IRQn);
  }
  else if (Instance == TMR5)
  {

    // TMR5 Pinmux Config: PB0
    TMR_GPIO_Init.Pin = GPIO_PIN_0;
    TMR_GPIO_Init.Alternate = GPIO_AF6_TMR5;
    LL_GPIO_Init(GPIOB, &TMR_GPIO_Init);

    // SYSCTRL HSTMR Bus Clock Enable and Reset Release
    LL_SYSCTRL_HSTMR_ClkEnRstRelease();

    // NVIC TMR5 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR5_IRQn);
  }
  else if (Instance == TMR6)
  {

    // TMR6 Pinmux Config: PB1
    TMR_GPIO_Init.Pin = GPIO_PIN_1;
    TMR_GPIO_Init.Alternate = GPIO_AF6_TMR6;
    LL_GPIO_Init(GPIOB, &TMR_GPIO_Init);

    // SYSCTRL HSTMR Bus Clock Enable and Reset Release
    LL_SYSCTRL_HSTMR_ClkEnRstRelease();

    // NVIC TMR6 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR6_IRQn);
  }
  else if (Instance == TMR7)
  {

    // TMR7 Pinmux Config: PC3
    TMR_GPIO_Init.Pin = GPIO_PIN_3;
    TMR_GPIO_Init.Alternate = GPIO_AF6_TMR7;
    LL_GPIO_Init(GPIOC, &TMR_GPIO_Init);

    // SYSCTRL HSTMR Bus Clock Enable and Reset Release
    LL_SYSCTRL_HSTMR_ClkEnRstRelease();

    // NVIC TMR7 Interrupt Enable
    LL_NVIC_EnableIRQ(TMR7_IRQn);
  }
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
