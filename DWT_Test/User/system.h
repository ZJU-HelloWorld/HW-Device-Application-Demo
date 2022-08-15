/**
 *******************************************************************************
 * @file      : system.c/h
 * @brief     : task manager & user callback serving functions realization
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-02-17      wwy             1. Done
 *  V2.0        Null            Senior          1. Revised
 *  V3.0        2022-03-15      xdl             1. Refactored
 *                                              2. Decoupled, object-oriented
 *  V3.1        2022-08-01      xdl             1. Modified for test
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_H_
#define __SYSTEM_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "debug.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void Sys_Init(void);

#endif /* __SYSTEM_H_ */
