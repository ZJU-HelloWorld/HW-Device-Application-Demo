/**
 *******************************************************************************
 * @file      : fml_laser.c/h
 * @brief     : laser Driver
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        Null            Senior          1. Done
 *  V2.0        2022-03-16      Xue Donglai     1. Refactored
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FML_LASER_H__
#define __FML_LASER_H__
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "tim.h"
/* Exported types ------------------------------------------------------------*/
typedef enum _laser_lumin_e
{
  LASER_PWM_MAX = 8399,
  LASER_PWM_MED = 4199,
  LASER_PWM_MIN = 2099
} LaserLumin_e;
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void FML_Laser_Init(void);
void FML_Laser_TurnOn(void);
void FML_Laser_SetLumin(LaserLumin_e lumin);
void FML_Laser_TurnOff(void);

#endif /* __FML_LASER_H__ */
