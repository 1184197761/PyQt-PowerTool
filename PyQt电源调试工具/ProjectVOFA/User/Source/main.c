/**
 ******************************************************************************
 * @file    main.c
 * @author  MCD Application Team
 * @brief   main source file for template project
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

#include "main.h"
#include "dbg/tae32f53xx_dbg.h"

void SystemClock_Config(); // 系统时钟配置


/**
 * @brief  主函数
 * @param  无
 * @return 状态
 */
int main(void)
{
	SystemClock_Config();								 // 系统时钟设置
	LL_Init();													 // 底层驱动初始化
	User_Debug_Init(USER_DBG_IFC_UART0); // 调试串口初始化
	User_VOFA_Example();
	while (true)
		;
}

/**
 * @brief  系统时钟配置
 * @param  无
 * @return 无
 */
void SystemClock_Config()
{
	LL_StatusETypeDef ret;
	SYSCTRL_SysclkUserCfgTypeDef sysclk_cfg;

	// FPLL0初始化
	LL_FPLL_Init(FPLL0);

	// SYSCLK时钟配置
	sysclk_cfg.sysclk_src = SYSCLK_SRC_PLL0DivClk;
	sysclk_cfg.sysclk_freq = 90000000UL;
	sysclk_cfg.pll0clk_src = PLLCLK_SRC_XOSC;
	sysclk_cfg.pll0clk_src_freq = HSE_VALUE;
	sysclk_cfg.apb0_clk_div = SYSCTRL_CLK_DIV_1;
	sysclk_cfg.apb1_clk_div = SYSCTRL_CLK_DIV_1;
	ret = LL_SYSCTRL_SysclkInit(SYSCTRL, &sysclk_cfg);

	if (ret == LL_OK)
	{
		SystemCoreClockUpdate(sysclk_cfg.sysclk_freq);
	}
                
	// eFlash存储器CLK源和分区配置
	LL_SYSCTRL_EFLASH_ClkCfg(EFLASH_CLK_SRC_PLL0DivClk, SYSCTRL_CLK_DIV_9);
}


#ifdef USE_FULL_ASSERT
/**
 * @brief  报告源文件的名称和源行号
 *         发生ASSERT_PARAM错误的位置。
 * @param  file：指向源文件名的指针
 * @param  line：ASSERT_PARAM错误行源编号
 * @retval 无
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	LOG_E("在%s行%d中断言失败", file, line);

	/*无限循环*/
	while (1)
		;
}
#endif

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
