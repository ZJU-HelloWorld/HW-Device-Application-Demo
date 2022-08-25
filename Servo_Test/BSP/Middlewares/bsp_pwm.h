/**
 *******************************************************************************
 * @file      : bsp_pwm.c/h
 * @brief     : PWM device Driver
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-10      Xue Donglai     1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "tim.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void BSP_Pwm_InitAllCh(void);

#endif /* __BSP_PWM_H__ */
