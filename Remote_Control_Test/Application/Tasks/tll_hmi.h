/**
 *******************************************************************************
 * @file      : tll_hmi.c/h
 * @brief     : human-machine interaction, including remote ctrl, mode update,
                UI drawing, music playing and notification et al.
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-03-17      xdl             1. Done
 *  V1.1        2022-07-23      xdl             1. Revised
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TLL_HMI_H_
#define __TLL_HMI_H_
/* Includes ------------------------------------------------------------------*/
#include "api_control.h"
#include "config.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void                 TLL_Hmi_Init(void);
void                 TLL_Hmi_Task(uint32_t system_tick);
volatile CtrlInfo_t* TLL_Get_CtrlInfoPtr(void);

#endif /* __TLL_HMI_H_ */
