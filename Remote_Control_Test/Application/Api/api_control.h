/**
 *******************************************************************************
 * @file      : api_control.c/h
 * @brief     : User Control interface (User Command Only)
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-04-17      wwy             1. Done
 *  V1.1        Null            Senior          1. Revised
 *  V2.0        2022-03-11      Xue Donglai     1. Refactored
 *  V2.1        2022-08-01      Xue Donglai     1. Revised
 *******************************************************************************
 * @attention : api_control.c/h are not general application interfaces, but
 *              can be specially modified by users for various services and arms.
 *              This file is for Standard specially.
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_CONTROL_H_
#define __API_CONTROL_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "fml_rc.h"
/* Exported types ------------------------------------------------------------*/
typedef enum _ctrl_source_e
{
  REMOTE_CTRL,
  KEYBOARD_MOUSE_CTRL
} CtrlSource_e;

typedef struct _ctrl_info_t
{
  /* mutex */
  bool_t mutex;
  
  CtrlSource_e   ctrl_src;
  MouseKbEvent_t event;

  /* raw data */
  RcData_t data;
  RcData_t last_data;
} CtrlInfo_t;
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void API_Ctrl_Init(CtrlInfo_t* info);
void API_Ctrl_UpdateCtrlSrc(const RcData_t* last_data, const RcData_t* data,
                            CtrlSource_e* src);
void API_Ctrl_UpdateCtrlInfo(CtrlInfo_t* info);
#endif /* __API_CONTROL_H_ */
