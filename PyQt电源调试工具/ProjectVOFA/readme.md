# ProjectTemplate 示例工程

> ProjectTemplate 模板工程展示了TAE32F53xx SDK的最小系统配置;
>
> 本工程中简要说明如下：
>
> 1. 本工程提供最小系统配置示例，不提供模块接口使用示例;
> 2. 本工程包含了TAE32F53xx的所有模块驱动，在实际使用过程中可根据需要进行删减；

---

## 适用平台

> 本工程适用以下芯片类型：
>
> 1. TAE32F53xx系列：TAE32F5300;

> 本工程适用以下评估板类型：
>
> 1. TAE32F5300_EVAL_BOARD;

---

## 工程配置
> 本工程在tae32f53xx_ll_conf.h文件中默认打开了所有模块的使能宏定义，如下所示：
```
	/* Internal Class Peripheral */
	#define LL_MODULE_ENABLED           /*!< LL Module Enable       */
	#define LL_CORTEX_MODULE_ENABLED    /*!< Cortex Module Enable   */
	#define LL_FPLL_MODULE_ENABLED      /*!< FPLL Module Enable     */
	#define LL_LVD_MODULE_ENABLED       /*!< LVD Module Enable      */
	#define LL_DMA_MODULE_ENABLED       /*!< DMA Module Enable      */
	#define LL_FLASH_MODULE_ENABLED     /*!< FLASH Module Enable    */
	#define LL_DFLASH_MODULE_ENABLED    /*!< DFLASH Module Enable   */
	#define LL_WWDG_MODULE_ENABLED      /*!< WWDG Module Enable     */
	#define LL_IWDG_MODULE_ENABLED      /*!< IWDG Module Enable     */
	#define LL_TMR_MODULE_ENABLED       /*!< TMR Module Enable      */
	#define LL_IIR_MODULE_ENABLED       /*!< IIR Module Enable      */

	/* Interface Class Peripheral */
	#define LL_GPIO_MODULE_ENABLED      /*!< GPIO Module Enable     */
	#define LL_UART_MODULE_ENABLED      /*!< UART Module Enable     */
	#define LL_I2C_MODULE_ENABLED       /*!< I2C Module Enable      */
	#define LL_CAN_MODULE_ENABLED       /*!< CAN Module Enable      */
	#define LL_DALI_MODULE_ENABLED      /*!< DALI Module Enable     */
	#define LL_USB_MODULE_ENABLED       /*!< USB Module Enable      */

	/* Analog Class Peripheral */
	#define LL_ADC_MODULE_ENABLED       /*!< ADC Module Enable      */
	#define LL_DAC_MODULE_ENABLED       /*!< DAC Module Enable      */
	#define LL_CMP_MODULE_ENABLED       /*!< CMP Module Enable      */
	#define LL_ECU_MODULE_ENABLED       /*!< ECU Module Enable      */
	#define LL_HRPWM_MODULE_ENABLED     /*!< HRPWM Module Enable    */
```
> 如果需要用到打印功能，需要在tae32f53xx_dbg_conf.h文件中打开以下的宏定义<此宏定义本工程默认打开>:
```
    #define TAE_USING_DBG
```
> 如果需要用到UART打印功能，还需要在tae32f53xx_ll_conf.h文件中打开下面的宏定义<此宏定义本工程默认打开>：
```
    #define LL_UART_MODULE_ENABLED		/*!< UART Module Enable     */
```
## 模块依赖

> N/A

## 调试接口配置

> ***1. UART0/1:*** 

>>  **软件配置** :
>>> a. 在tae32f53xx_ll_msp.c文件中进行串口MSP配置，如串口引脚等信息;
>>> b. 在main.c里调用User_Debug_Init接口初始化为UART0/1;

>>  **硬件配置** :
>>
>>  > a. 按照所选引脚，连接串口线打印;
***
> ***2. ITM:***

>>  **软件配置** :
>>> a. 在main.c里调用User_Debug_Init接口初始化为ITM;
>>> b. 在keil工程里，打开"Options for Target->Debug->Setting->Trace",确保Core Clock为工程系统时钟,
>>>     ITM Stimulus Ports 的Enable通道0打开，然后勾选"Trace Settings"的“Enable”即可；
>>> c. 进入调试模式后，在Keil软件中打开"View->Serial Windows->Debug(printf)Viewer";

>>  **硬件配置** :
>>
>>  > a. 确保SWO引脚和PB3用跳线帽短接，并通过Jlink连接电脑端;

## 工程说明

> 本工程作为最小系统配置示例，不演示具体模块使用，系统启动后仅打印相关Platform Information，如下所示:
```
======================== Platform Information =======================
Tai-Action TAE32F53xx SDK Release V1.1.0 Jun  9 2021 10:03:46

CPU  clock  90000000 Hz
AHB  clock  90000000 Hz
APB0 clock  90000000 Hz
APB1 clock  90000000 Hz
HSE  clock   8000000 Hz
HSI  clock   8000000 Hz
LSI  clock     32000 Hz
=====================================================================

[D@APP] App start
```

### 操作说明：

> 1. 编译工程，烧录镜像，启动即可;
> 2. 系统启动后，可以看到相关的打印信息;

### 代码结构
```
.
├── ProjectTemplate/User
│   ├── main.c                      # 本工程的入口
│   ├── tae32f53xx_it.c             # 本工程的中断入口
│   └── tae32f53xx_ll_msp.c         # 本工程的模块初始化
├── Documentation
│   └── readme.md                   # 本工程readme md文档
├── Drivers/TAE_Driver
│   ├── tae32f53xx_ll.c             # LL module driver
│   ├── tae32f53xx_ll_adc.c         # ADC LL Module Driver
│   ├── tae32f53xx_ll_can.c         # CAN LL Module Driver
│   ├── tae32f53xx_ll_cmp.c         # CMP LL Module Driver
│   ├── tae32f53xx_ll_cortex.c      # CORTEX LL module driver
│   ├── tae32f53xx_ll_dac.c         # DAC LL Module Driver
│   ├── tae32f53xx_ll_dali.c        # DALI LL module driver
│   ├── tae32f53xx_ll_dflash.c      # DFLASH LL Module Driver
│   ├── tae32f53xx_ll_dma.c         # DMA LL Module Driver
│   ├── tae32f53xx_ll_ecu.c         # ECU LL Module Driver
│   ├── tae32f53xx_ll_flash.c       # FLASH LL Module Driver
│   ├── tae32f53xx_ll_fpll.c        # FPLL LL Module Driver
│   ├── tae32f53xx_ll_gpio.c        # GPIO LL module driver
│   ├── tae32f53xx_ll_hrpwm.c       # HRPWM LL Module Driver
│   ├── tae32f53xx_ll_i2c.c         # I2C LL Module Driver
│   ├── tae32f53xx_ll_iir.c         # IIR LL Module Driver
│   ├── tae32f53xx_ll_iwdg.c        # IWDG LL Module Driver
│   ├── tae32f53xx_ll_lvdctrl.c     # LVDCTRL LL Module Driver
│   ├── tae32f53xx_ll_sysctrl.c     # SYSCTRL LL Module Driver
│   ├── tae32f53xx_ll_tmr.c         # TMR LL Module Driver
│   ├── tae32f53xx_ll_uart.c        # UART LL Module Driver
│   ├── tae32f53xx_ll_usb.c         # USB LL Module Driver
│   └── tae32f53xx_ll_wwdg.c        # WWDG LL Module Driver
├── Drivers/TAE_Device
│   ├── startup_tae32f53xx.c        # CMSIS-Core(M) Device Startup File for a tae32f53xx(Cortex-M3) Device
│   └── system_tae32f53xx.c         # CMSIS Cortex-M3 Device Peripheral Access Layer System Source File
└── Utilities/Debug
    └── user_debug.c                # This file provides the Debug User Config Method
```

### 代码流程

> 1. main()入口;
> 2. 系统时钟配置;
> 3. 打印相关Platform Information;

---

## 常见问题

> N/A
