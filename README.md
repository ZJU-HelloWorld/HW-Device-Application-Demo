**HWModuleTestProjects**

# Hello World 电控模块测试例程

## A 目录结构

```
.\
├── Buzzer_Test   			# 板载PWM
├── DWT_Test						# 内核DWT计时器
├── IMU_Test	  				# SPI C板内部, PWM C板内部
├── Laser_Test					# 5V接口外接
├── MiniPC_Comm_Test		# (板上印字)UART2外接 或 USB接口外接
├── Motor_Test					# CAN外接 - 2006 / 3508 / 6020
├── OLED_Test						# I2C 4-pin GPIO外接（牛角座）
├── Referee_Test				# (板上印字)UART1外接
├──	Remote_Control_Test # DBUS外接
├── Servo_Test					# PWM(共7路)外接
├── Snail_Test					# PWM(共7路)外接
├── SuperCap_Comm_Test	# CAN外接
```

## B 提示

* 荧光充能模块需经降压模组（官方）供电（5V）
* MiniPC供电须经降压模组（自研）供电（19V）

