/**
 ******************************************************************************
 * @file    user_tmr.c
 * @author  MCD Application Team
 * @brief   This file provides the TMR Config Method.
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
#include "tae32f53xx_ll.h"
#include <string.h>

#define DBG_TAG "User TMR"
#define DBG_LVL DBG_LOG
#include "dbg/tae32f53xx_dbg.h"

/** @addtogroup TAE32F53xx_Examples
 * @{
 */

/** @addtogroup TAE32F53xx_TMR_InputCapture_Example
 * @{
 */

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup User_TMR_InputCapture_Private_Variables User TMR_InputCapture Private Variables
 * @brief    User TMR_InputCapture Private Variables
 * @{
 */

static uint32_t ICIndex;                  /*!< IC Index               */
static __IO uint32_t uwMeasuredFrequency; /*!< uw Measured Frequency  */
static __IO double uwMeasuredDuty;        /*!< uw Measured Duty       */
static uint32_t uwICValue1;               /*!< uw IC Value1           */
static uint32_t uwICValue2;               /*!< uw IC Value2           */
static uint32_t uwICValue3;               /*!< uw IC Value3           */
static double uwDutyDiffCapture;          /*!< uw Duty Diff Capture   */
static uint32_t uwFreqDiffCapture;        /*!< uw Freq Diff Capture   */

/**
 * @}
 */

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup User_TMR_InputCapture_Private_Functions User TMR_InputCapture Private Functions
 * @brief    User TMR_InputCapture Private Functions
 * @{
 */
void User_TMR_IC_Init(TMR_TypeDef *Instance);
void User_TMR_DeInit(TMR_TypeDef *Instance);
void User_TMR_TestLoop(TMR_TypeDef *Instance);
/**
 * @}
 */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup User_TMR_InputCapture_Private_Functions
 * @{
 */

/**
 * @brief  User TMR IC Init
 * @param  Instance Specifies TMR peripheral
 * @note   Configure TMR0 in input capture mode
 * @return None
 */
void User_TMR_IC_Init(TMR_TypeDef *Instance)
{
  TMR_InitTypeDef TMR_IC_Init;

  memset(&TMR_IC_Init, 0, sizeof(TMR_IC_Init));

  TMR_IC_Init.TBInit.ClockSource = TMR_CLKSOURCE_INTERNAL;
  TMR_IC_Init.TBInit.ContinuousMode = TMR_CONTINUOUS_MODE_ENABLE;
  TMR_IC_Init.TBInit.StartValue = 0;
  TMR_IC_Init.TBInit.EndValue = 0xFFF - 1;
  TMR_IC_Init.TBInit.Prescaler = 0xF - 1;
  TMR_IC_Init.TBInit.AutoReloadPreload = TMR_AUTORELOAD_PRELOAD_ENABLE;
  TMR_IC_Init.TBInit.UpdateEnable = TMR_UPDATE_ENABLE;
  TMR_IC_Init.TBInit.UpdateSource = TMR_UPDATE_SOURCE_COUNTER;

  TMR_IC_Init.ICInit.ICEnable = ENABLE;
  TMR_IC_Init.ICInit.ICFilter = 0;
  TMR_IC_Init.ICInit.ICPolarity = TMR_ICPOLARITY_FALLING;
  TMR_IC_Init.ICInit.ICSelection = TMR_ICSELECTION_TMR0;

  TMR_IC_Init.OCInit.OCEnable = DISABLE;

  TMR_IC_Init.ExtInit.ExtEnable = DISABLE;
  TMR_IC_Init.ExtInit.ExtTRGOTrigger = TMR_EXT_TRGO_TRIGGER_DISABLE;
  TMR_IC_Init.ExtInit.ExtPWMWave = TMR_EXT_PWM_WAVE_DISABLE;
  TMR_IC_Init.ExtInit.ExtCCTrigger = TMR_EXT_CC_TRIGGER_DISABLE;

  LL_TMR_Init(Instance, &TMR_IC_Init);
  // __LL_TMR_CC_IT_ENABLE(Instance, TMR_IT_ICIE);
  __LL_TMR_IT_ENABLE(Instance, TMR_IT_OVIE);
}

/**
 * @brief  User TMR DeInit
 * @param  Instance Specifies TMR peripheral
 * @return None
 */
void User_TMR_DeInit(TMR_TypeDef *Instance)
{
  LL_TMR_DeInit(Instance);

  LL_TMR_DeInit(TMR1);
}

/**
 * @brief  User TMR test loop
 * @param  Instance Specifies TMR peripheral
 * @return None
 */
void User_TMR_TestLoop(TMR_TypeDef *Instance)
{

  /* Enable counter */
  LL_TMR_Start(Instance);

  /* Enable counter */
  LL_TMR_Start(TMR1);

  LL_Delay(100);

  while (1)
    ;
}

/**
 * @brief  TMR LL Capture Interrupt Callback
 * @param  Instance Specifies TMR peripheral
 * @return None
 */
void LL_TMR_IC_CaptureCallback(TMR_TypeDef *Instance)
{
  static uint32_t tick = 0;
  static uint32_t minDelay = 0xFFFFFFFF;
  static uint8_t count = 0;

  minDelay = Instance->CCR - tick < minDelay ? Instance->CCR - tick : minDelay;
  tick = Instance->CCR;

  if (Instance->CCCR & TMR_CCCR_CCP)
    __LL_TMR_POLARITY_SET(Instance, TMR_ICPOLARITY_RISING);
  else
    __LL_TMR_POLARITY_SET(Instance, TMR_ICPOLARITY_FALLING);
  count++;

  if (count == 8)
  {
    uint32_t baudRate = SystemCoreClock / (Instance->PSCR + 1) / minDelay;
    LOG_D("baudRate:%d\n", baudRate);
    count = 0;
		minDelay=0xFFFFFFFF;
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
