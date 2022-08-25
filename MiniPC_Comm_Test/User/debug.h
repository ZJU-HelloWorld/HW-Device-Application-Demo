/**
 *******************************************************************************
 * @file      : debug.c/h
 * @brief     : watch variables
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        Null            Senior          1. Done
 *  V2.0        2022-08-01      Xue Donglai     1. Refactored
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H_
#define __DEBUG_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void     Debug_Watcher(void);
void     Debug_Dwt_Init(void);
uint32_t Debug_Dwt_GetTickUS(void);

#endif /* __DEBUG_H_ */