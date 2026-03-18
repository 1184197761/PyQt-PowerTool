/**
  ******************************************************************************
  * @file    user_uart.h
  * @author  MCD Application Team
  * @brief   Head file for user UART module test.
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
#ifndef _USER_UART_H_
#define _USER_UART_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_Examples
  * @{
  */

/** @addtogroup TAE32F53xx_UART_TxPolling_RxIT_Example
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup User_UART_TxPolling_RxIT_Exported_Functions
  * @{
  */
void User_UART_Example(UART_TypeDef *Instance);
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


#endif /* _USER_UART_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

