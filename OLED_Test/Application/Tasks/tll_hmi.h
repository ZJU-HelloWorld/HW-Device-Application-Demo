/**
 *******************************************************************************
 * @file      : tll_hmi.c/h
 * @brief     : human-machine interaction
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-03-17      Xue Donglai     1. Done
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
#include "api_notification.h"
#include "config.h"
/* Exported types ------------------------------------------------------------*/
typedef struct _note_info_t
{
  OledNoteInfo_t oled;
  DeviceState_e  error_list[DEVICE_LIST_LEN];
} NoteInfo_t;
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void                 TLL_Hmi_Init(void);
void                 TLL_Hmi_Task(uint32_t system_tick);
volatile NoteInfo_t* TLL_Get_NoteInfoPtr(void);

#endif /* __TLL_HMI_H_ */