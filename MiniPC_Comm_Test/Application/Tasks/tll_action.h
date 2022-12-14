/**
 *******************************************************************************
 * @file      : tll_action.c/h
 * @brief     : Action task, including transmitting data to referee and other
                tx tasks, cmd acting components et al.
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-08-15      Xue Donglai     1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TLL_ACTION_H_
#define __TLL_ACTION_H_
/* Includes ------------------------------------------------------------------*/
#include "api_comm.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void TLL_Action_Init(AppInfoMsg_t* msg);
void TLL_Action_Task(uint32_t system_tick, AppInfoMsg_t* msg);

#endif /* __TLL_ACTION_H_ */
