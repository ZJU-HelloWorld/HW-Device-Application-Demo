**HWModuleTestDemo**

# Hello World 电控模块测试例程

Copyright (c) 2022 Hello World Team of Zhejiang University.

All Rights Reserved.

## A 简介

* 该仓库包含基于大疆RoboMaster开发板C型的多种板载设备和外设测试例程，方便学习和测试.
* 该仓库遵循GPLv3.0开源协议.

## B 目录结构

```
.\
├── Buzzer_Test         # 板载PWM
├── DWT_Test            # 内核DWT计时器
├── IMU_Test            # 板载SPI, 板载PWM
├── Laser_Test          # 5V接口外接
├── MiniPC_Comm_Test    # (C板上印字)UART2外接 或 USB接口外接
├── Motor_Test          # CAN外接 - 2006 / 3508 / 6020
├── OLED_Test           # I2C 4-pin GPIO外接（牛角座）
├── Referee_Test        # (C板上印字)UART1外接
├── Remote_Control_Test # DBUS外接
├── Servo_Test          # PWM(共7路)外接
├── Snail_Test          # PWM(共7路)外接
└── SuperCap_Comm_Test  # CAN外接
```
## C 模块功能说明
### Buzzer 蜂鸣器
* 在 `./User/main.c` `main`函数主循环中设置设备错误状态以实现告警.
* 可于 `./Application/Tasks/tll_hmi.c` 中修改播放开机音乐的长度和内容.
* 只有当无设备错误时，开机音乐能正常完整播放.

### DWT(datawatchpoint and trace) DWT计时器
* 在 `system.c` 中的 `Sys_Task_Manager` 函数测量程序运行用时.
* 使用DWT计时器可以获得us级别的系统时钟数据.

### IMU 惯性测量单元
TODO

### Laser 红点激光器
* 请将红点激光器连接至C板上'5V'接口.
* 在`./User/main.c` `main`函数主循环中调节亮度.

### STM32-MiniPC Communication 上下位机通信测试
TODO

### Motor 电机
TODO

### OLED OLED显示
* 请使用8pin牛角接插件将OLED连接至C板上I2C接口.
* 在`./User/main.c` `main`函数主循环中简单手动设置要在OLED上展示的设备在线情况等.
* 在`./User/config.h` 中修改 `IS_STEERABLE_STANDARD` 编译开关来选择是否显示以舵轮步兵为例的额外动态图标和文字.
* 用户可于`./Application/Tasks/tll_hmi.c` 中设置自定义显示内容. 若不按照现有格式显示，可能需要修改 `API` 层函数.

### Referee 裁判系统串口通信
TODO

### Remote Control 遥控系统
* 请将DR16接收机连接至C板上DBUS接口，并与DT7遥控器正确对频.
* 没有设置用户接口，请Debug或使用J-Scope等软件浏览数据.

### Servo 舵机
* 请将舵机连接至C板上PWM接口.
* 在`./User/main.c` `main`函数中初始化使用的输出通道.
* 在`./User/main.c` `main`函数主循环中设置舵机角度. 若要精确设置角度，请同时输入舵机的转动范围，如180°舵机对应180.

### Snail Snail电机
TODO

### SuperCap Control Communication 超级电容主控通信测试
TODO

## D 模块文件组织
* 完整目录
```
.\
├───Application
│   ├───Api
│   └───Tasks
├───Bsp
│   ├───Inc
│   └───Src
├───Components
│   ├───Algorithms
│   ├───Devices
│   ├───Middlewares
│   └───USB_DEVICE
├───Docs
├───Drivers
├───MDK-ARM
└───User
    ├───config.h
    ├───debug.c/h
    ├───main.c
    └───system.c/h
```
* 完整例程结构
```
Xx_Test
  ├───Drivers/Startup
  ├───Drivers/STM32F4XX_HAL_Driver
  ├───Drivers/CMSIS
  ├───Drivers/USB_Device_Library
  ├───BSP/Core
  ├───Components/Algorithm
  ├───Components/Device
  ├───Components/Middleware
  ├───Components/USB_DEVICE
  ├───Application/Interface
  ├───Application/Task
  └───Application/User
```
* 部分例程结构并不完整，仅供参考和测试.

## E 其他提示
### 学习、验证和测试
* 请仔细阅读 `C 模块功能说明` 中对应的说明，并浏览各模块目录下 `./Docs` 文件夹（如有）.
* 便于调整设置的用户接口主要包括 `./User/main.c`, `./User/system.c`, `./User/config.h` 等. 
* 可供修改测试的部分除用户接口外，还包括 `./Application/Tasks` 内的相关文件，可供自定义修改.
* `API` 层和 `FML` 层文件不建议修改.

### 应用于项目
* 将例程应用于项目时，请尽量遵循以下设计原则和规范: 
  * 例程中有部分在 `main.c` `main`函数 while 循环中实现的功能，应封装至 `TLL` 层；在while中实现是由于无法获取实际工程的数据流或测试例程相对于完整项目实现结构并不完整.
  * `FML` 功能模块层对应底层组件，包括设备驱动、算法模块实现等，请不要随意修改；
  * `API` 应用接口层对应应用接口，是一类功能的抽象，请不要在该层相关文件中定义实体变量；该层调用各底层组件以实现功能；
  * `TLL` 任务逻辑层对用任务逻辑，在该层实现实体，进行数据初始化，向相关应用接口传入数据参数，并留出数据指针接口供任务间数据传递和调试使用；该层调用应用接口，按照设计的逻辑实现相关功能；
  * `./User` 目录包含：
    * `config.h`: 硬件接口定义、类型定义、模块条件编译指令及其他全局通用定义；
    * `system.c/h`: 可调用各层函数，以简洁地实现设备初始化、数据初始化；对由裸机开发、中断嵌套的工程，实现主定时器中断对各任务的调用，实现任务间的数据传递；实现各类中断服务函数；对于机器人，按照`用户接口-感知-决策-控制执行`顺序调用任务；
    * `debug.c/h`: 提供调试接口函数，读入任务数据供调试使用.
    * `main.c`: 调用全局初始化函数.
  * 请不要跨层调用；
  * 请注意代码规范，可参考Google C++风格指南.
  
* 更详细的规范请参考组内资料.

## F 贡献
* 欢迎提出ISSUE和提交PR来帮助我们改进.

