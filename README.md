# PyQt Power Tool

PyQt电源调试工具，用于电源模块的实时监控和参数配置。

## 项目概述

- **上位机**: PyQt5开发的桌面应用
- **下位机**: TAE32F53xx MCU
- **通信**: 串口/UART
- **协议**: 自定义VOFA+协议

## 功能特性

### 上位机功能 (wave_py)
- 实时波形显示
- 多通道数据监控
- 参数配置界面
- 数据记录与导出
- 串口通信管理

### 下位机功能 (ProjectVOFA)
- ADC数据采集
- PWM波形生成
- 串口数据传输
- 实时参数调节

## 技术栈

### 上位机
- **语言**: Python 3.8+
- **框架**: PyQt5
- **工具**: VOFA+协议
- **打包**: PyInstaller

### 下位机
- **MCU**: TAE32F53xx
- **IDE**: Keil MDK / Eclipse
- **库**: LL库 (Low Layer)

## 项目结构

```
PyQt电源调试工具/
├── wave_py/              # PyQt上位机
│   ├── main.py          # 主程序
│   ├── ui_MainWindow.py # 主界面
│   ├── ui_ChannelDialog.py
│   ├── ui_ParamDialog.py
│   └── old/             # 旧版本
└── ProjectVOFA/         # MCU下位机
    ├── User/            # 用户代码
    ├── Project/         # 工程文件
    └── main.spec        # 打包配置
```

## 快速开始

### 上位机运行
```bash
cd wave_py
pip install pyqt5 pyserial
python main.py
```

### 下位机编译
1. 使用Keil打开Project/MDK/Project.uvprojx
2. 编译并下载到TAE32F53xx

## 通信协议

- 帧头: 0xAA 0x55
- 数据长度: 可变
- 校验: CRC8
- 波特率: 115200

## 学习收获

- PyQt5界面开发
- 串口通信编程
- MCU数据采集
- 上下位机联调

## 相关项目

- [STM32-Projects](https://github.com/1184197761/STM32-Projects) - 嵌入式项目

---
*电源调试工具开发实践*
