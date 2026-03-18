/**
 ******************************************************************************
 * @file    tae32f53xx_it.c
 * @author  MCD Application Team
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
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
#include "tae32f53xx_it.h"

/** @addtogroup TAE32F53xx_Examples
 * @{
 */

/** @addtogroup TAE32F53xx_UART_TxPolling_RxIT_Example
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup UART_TxPolling_RxIT_IT_Private_Functions UART_TxPolling_RxIT IT Private Functions
 * @brief    UART_TxPolling_RxIT IT Private Functions
 * @{
 */

/** @defgroup UART_TxPolling_RxIT_IT_Private_Functions_Group1 UART_TxPolling_RxIT Cortex-M3 Processor Exceptions Handlers
 * @brief    UART_TxPolling_RxIT Cortex-M3 Processor Exceptions Handlers
 * @{
 */

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles TMR0 Handler.
 * @param  None
 * @return None
 */
void TMR0_IRQHandler(void)
{
#ifdef LL_TMR_MODULE_ENABLED
  LL_TMR_IRQHandler(TMR0);
#endif
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
#ifdef LL_MODULE_ENABLED
  LL_IncTick();
#endif

#ifdef LL_CORTEX_MODULE_ENABLED
  LL_SYSTICK_IRQHandler();
#endif
}

/**
 * @}
 */

/******************************************************************************/
/*                  TAE32F53xx Peripherals Interrupt Handlers                 */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_tae32f53xx.c).                                              */
/******************************************************************************/

/** @defgroup UART_TxPolling_RxIT_IT_Private_Functions_Group2 UART_TxPolling_RxIT UART IRQ Handler
 * @brief    UART_TxPolling_RxIT UART IRQ Handler
 * @{
 */

/**
 * @brief  This function handles UART0 Handler.
 * @param  None
 * @return None
 */
void UART0_IRQHandler(void)
{
#ifdef LL_UART_MODULE_ENABLED
  LL_UART_IRQHandler(UART0);
#endif
}

/**
 * @brief  This function handles UART1 Handler.
 * @param  None
 * @return None
 */
void UART1_IRQHandler(void)
{
#ifdef LL_UART_MODULE_ENABLED
  LL_UART_IRQHandler(UART1);
#endif
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

/**
 * @}
 */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
