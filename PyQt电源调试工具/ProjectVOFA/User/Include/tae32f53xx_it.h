/**
  ******************************************************************************
  * @file    tae32f53xx_it.h
  * @author  MCD Application Team
  * @brief   Header file for Main Interrupt Service Routines.
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
#ifndef _TAE32F53XX_IT_H_
#define _TAE32F53XX_IT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/


/** @addtogroup TAE32F53xx_Examples
  * @{
  */

/** @addtogroup TAE32F53xx_Template
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @addtogroup TAE32F53xx_IT_Private_Functions
  * @{
  */

/** @addtogroup TAE32F53xx_IT_Private_Functions_Group1
  * @{
  */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
/**
  * @}
  */


/** @addtogroup TAE32F53xx_IT_Private_Functions_Group2
  * @{
  */
void DMA_IRQHandler(void);
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


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_IT_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

