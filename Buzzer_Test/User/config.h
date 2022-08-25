/**
 *******************************************************************************
 * @file      : config.h
 * @brief     : Board related config for devices & conditional compiling settings
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-16      Xue Donglai     1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H_
#define __CONFIG_H_
/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include <arm_math.h>
#include <math.h>
/* Exported types ------------------------------------------------------------*/
typedef uint8_t bool_t;
/* Exported macro ------------------------------------------------------------*/
/* Ctrl Define ------------------------------- */
#define CTRL_FREQ          1000.0f
#define HALF_CTRL_FREQ     (CTRL_FREQ / 2)
#define MUSIC_FREQ         10.0f
/* Devices ------------------------------------*/
#define HTIM_CONTROL       htim6
#define HTIM_PWM_BUZZER    htim4
#define HTIM_PWM_CH_BUZZER TIM_CHANNEL_3
/* Conditional Compiling ----------------------*/
/* Module Used Define */
#define USE_BUZZER         1
/* Debug Settings -----------------------------*/
#define DEBUG_ON           0
#define DEBUG_OFF          (!DEBUG_ON)
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
#endif /* __CONFIG_H_ */
