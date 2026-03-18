#include "user_vofa.h"

#define UART_BAUDRATE 115200  // 串口波特率
#define UART_RXBUFF_LEN 1024  // 串口接收长度
#define UART_TIME_OUT_MS 1    // 串口接收超时
#define WAVE_TIME_DELAY 100    // 波形更新周期
#define DATA_TIME_DELAY 1000  // 数据更新周期
#define DATA_SUM Shutdown + 1 // 数据总量

BoartDatas boardDatas;
uint8_t rxBuff[UART_RXBUFF_LEN]; // DMA接收缓冲区
uint16_t tmrCount = 0;           // 定时器中断计数值
bool rxFlag = false;             // 串口接收中断标记
bool tmrFlag = false;            // 定时器溢出中断标志

void DMA_Init(); // DMA初始化

/**
 * @brief  用户VOFA示例
 * @return 无
 */
void User_VOFA_Example()
{

  DMA_Init();                // DMA初始化
  LL_UART_Receive_IT(UART0); // 串口接收中断配置

//  User_TMR_Init(TMR0);   // 定时器0初始化
	User_TMR_IC_Init(TMR0);
  LL_TMR_Start_IT(TMR0); // 开启定时器中断

  while (true)
  {
    if (rxFlag) // 若触发接收默认中断
    {
      for (tmrCount = 0; tmrCount <= UART_TIME_OUT_MS;) // 超时等待
      {
        if (UART0->USR & UART_USR_RFNE) // 若接收缓冲区非空
          tmrCount = 0;                 // 更新定时器计数值
      }

      if (rxBuff[HEADER] == 0xCC && rxBuff[TAIL] == 0xEE) // 若为上位机写指令
      {
        User_VOFA_RecvBoardData((uint16_t *)&boardDatas, rxBuff); // 保存指令数据
      }
      DMA_Init();      // 重置DMA目标地址
      rxFlag = false;  // 清除接收中断标志
      tmrFlag = false; // 清除定时器中断标志
      tmrCount = 0;    // 清除定时器中断计数值
    }
    else if (tmrCount) // 若触发定时器溢出中断
    {
     if (tmrCount >= DATA_TIME_DELAY) // 若达到数据更新周期
     {
       User_VOFA_SendBoardData(boardDatas);
       tmrCount = 0; // 清除定时器中断计数值
     }
      else if (tmrCount >= WAVE_TIME_DELAY) // 若达到波形更新周期
      {
        // srand(tmrCount); // 设置随机种子
        // float waveDatas[] =
        //     {
        //      rand(), // 通道0数据
        //      rand(), // 通道1数据
        //      rand(), // 通道2数据
        //      rand(), // 通道3数据
        //      };
        static float x = 0;
        float waveDatas[] = {sin(x), cos(x), -sin(x), -cos(x)}; // 波形数据
        x += 0.1;
        User_VOFA_SendWaveData(waveDatas); // 发送波形数据
      }
      tmrFlag = false; // 清除定时器中断标志
    }
  }
}

/**
 * @brief 发送4个通道的波形数据
 * @param datas 波形数据数组
 */
void User_VOFA_SendWaveData(float *datas)
{
  LOG_R("%c", 0xAA); // 发送报头
  for (uint32_t *byte = (uint32_t *)datas; byte < (uint32_t *)(datas + 4); byte++)
  {
    // 发送32位数据
    LOG_R("%c", (*byte) >> 24);
    LOG_R("%c", (*byte) >> 16);
    LOG_R("%c", (*byte) >> 8);
    LOG_R("%c", *byte);
  }
  LOG_R("%c", 0xEE); // 发送报尾
}

/**
 * @brief 发送开发板的运行参数
 * @param datas 开发板运行参数结构体
 */
void User_VOFA_SendBoardData(BoartDatas datas)
{
  LOG_R("%c", 0XBB); // 发送报头
  for (uint16_t *byte = (uint16_t *)&datas; byte < (uint16_t *)(&datas + 1); byte++)
  {
    LOG_R("%c", (*byte) >> 8); // 发送数据高8位
    LOG_R("%c", *byte);        // 发送数据低8位
  }
  LOG_R("%c", 0XEE); // 发送报尾
}

/**
 * @brief 接收并保存上位机下发的运行参数
 * @param datas 运行参数数组
 * @param rxBuff 接收缓冲区
 */
void User_VOFA_RecvBoardData(uint16_t *datas, uint8_t *rxBuff)
{
  if (rxBuff[HEADER] == 0xCC && rxBuff[TAIL] == 0xEE) // 若为上位机写指令
  {
    uint8_t id = rxBuff[DATA_ID];                             // 获取数据编号
    if (id >= 0 && id <= DATA_SUM)                            // 若编号合法
      *(datas + id) = (rxBuff[DATA_H] << 8) + rxBuff[DATA_L]; // 保存数据
  }
}

/**
 * @brief  DMA 初始化函数
 * @param  无
 * @return 无
 */
void DMA_Init()
{
  DMA->CR0 &= ~DMA_CR0_PEN;
  DMA->CH[0].CR0 = DMA_CH_CR0_CHIE | DMA_CH_CR0_TTC_P2M | DMA_CH_CR0_SINC_FIX;
  DMA->CH[0].CR1 = ARRAY_SIZE(rxBuff);
  DMA->CH[0].CR2 &= ~DMA_CH_CR2_SHSM;
  DMA->CH[0].CR3 = DMA_CH_CR3_SHSIF_UART0_RX;
  DMA->CH[0].SAR = (uint32_t)&UART0->RBR;
  DMA->CH[0].DAR = (uint32_t)rxBuff;
  DMA->CR0 = DMA_CR0_PEN;
  DMA->CR1 = DMA_CR1_CHWE_CH0 | DMA_CR1_CHEN_CH0;
}

/**
 * @brief  UART LL Rx默认中断回调
 * @param  Instance 指定UART外围设备
 * @return 无
 */
void LL_UART_RxDefaultCallback(UART_TypeDef *Instance)
{
  rxFlag = true; // 设置标志位
}

/**
 * @brief  TMR LL TB溢出中断回调
 * @param  Instance 指定TMR外围设备
 * @return 无
 */
void LL_TMR_TB_OverflowCallback(TMR_TypeDef *Instance)
{
  tmrFlag = true; // 设置标志位
  tmrCount++;     // 计数值自增
}
/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/
