/**
  ******************************************************************************
  * @file    user_tmr.h
  * @author  MCD Application Team
  * @brief   Head file for user TMR module test.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USER_TMR_H_
#define _USER_TMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_Examples
  * @{
  */

/** @addtogroup TAE32F53xx_TMR_TimeBase_Example
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup User_TMR_TimeBase_Exported_Functions
  * @{
  */
void User_TMR_Example(TMR_TypeDef *Instance) ;
void User_TMR_Init(TMR_TypeDef *Instance);
void User_TMR_DeInit(TMR_TypeDef *Instance);
void User_TMR_TestLoop(TMR_TypeDef *Instance);
void User_TMR_IC_Init(TMR_TypeDef *Instance);
/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _USER_TMR_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

