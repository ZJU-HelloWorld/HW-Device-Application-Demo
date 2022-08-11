/**
 *******************************************************************************
 * @file      : fml_servo.c/h
 * @brief     : Servo Driver
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-10      xdl             1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FML_SERVO_H__
#define __FML_SERVO_H__
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "tim.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
#ifndef _HEADER_INIT_ALL_PWM_CH
#define _HEADER_INIT_ALL_PWM_CH
void FML_Pwm_InitAllCh(void);
#endif
void FML_Servo_InitSingleCh(const uint8_t index);
void FML_Servo_SetSingleChMax(const uint8_t index);
void FML_Servo_SetAllChMax(void);
void FML_Servo_SetSingleChMin(const uint8_t index);
void FML_Servo_SetAllChMin(void);
void FML_Servo_SetSingleAngle(const uint8_t index, const float target, const float range);

#endif /* __FML_SERVO_H_ */
