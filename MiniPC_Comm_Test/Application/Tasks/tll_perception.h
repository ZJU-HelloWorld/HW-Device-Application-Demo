/**
 *******************************************************************************
 * @file      : tll_perception.c/h
 * @brief     : Perception task, including handling referee info, attitude data,
 *              minipc and supercap control board data et al.
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-08-15      xdl             1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TLL_PERCEPTION_H_
#define __TLL_PERCEPTION_H_
/* Includes ------------------------------------------------------------------*/
#include "api_comm.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void                 TLL_Perception_Init(void);
void                 TLL_Perception_Task(uint32_t system_tick);
volatile CommInfo_t* TLL_Get_CommInfoPtr(void);

#endif /* __TLL_PERCEPTION_H_ */