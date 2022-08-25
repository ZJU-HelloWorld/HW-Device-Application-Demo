/**
 *******************************************************************************
 * @file      : api_notification.c/h
 * @brief     : Message notificating interface
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-03-04      Xue Donglai     1. Done
 *  V1.1        2022-07-17      Xue Donglai     1. Refactored
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_NOTIFICATION_H_
#define __API_NOTIFICATION_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "fml_limit.h"
#include "fml_minipc.h"
#include "fml_oled.h"
#include "fml_pwrsrc.h"
/* Exported macro ------------------------------------------------------------*/
#ifndef CTRL_FREQ
#define CTRL_FREQ 1000.0f
#endif
#ifndef HALF_CTRL_FREQ
#define HALF_CTRL_FREQ (CTRL_FREQ / 2)
#endif
#ifndef OLED_CMD_FREQ
#define OLED_CMD_FREQ 5.0f
#endif
#define IS_TO_CMD_OLED(tick)   (0 == (tick) % (int)(CTRL_FREQ / OLED_CMD_FREQ))
#define DEVICE_NAME_STRING_LEN 5
/* Exported types ------------------------------------------------------------*/
typedef struct _oled_note_info_t
{
  PwrsrcData_t pwr_data;

#if IS_STEERABLE_STANDARD
  uint16_t     supercap_perc;
  EnemyColor_e enemy_color;
#endif

  unsigned char device_string_list[DEVICE_LIST_LEN][DEVICE_NAME_STRING_LEN];

  OledGram_t gram;
} OledNoteInfo_t;
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void API_Note_Oled_Init(const unsigned char (*string_list)[DEVICE_NAME_STRING_LEN],
                        const uint8_t   len,
                        OledNoteInfo_t* info);
void API_Note_Oled_ModifyIconBox(const uint8_t col, const uint8_t row,
                                 const uint16_t max_col, const uint16_t max_row,
                                 const uint8_t data,
                                 uint8_t*      box);
void API_Note_Oled_SetBatteryPerc(const DataSrc_e src, const float votage,
                                  OledNoteInfo_t* info);

#if IS_STEERABLE_STANDARD
void API_Note_Oled_SetSupercapPerc(const DataSrc_e src, const float votage,
                                   OledNoteInfo_t* info);
void API_Note_Oled_SetEnemyColor(const EnemyColor_e color, OledNoteInfo_t* info);
#endif

void API_Note_Oled_SetDeviceState(const DeviceList_e index, const DeviceState_e state,
                                  DeviceState_e* list);

Api_StatusTypeDef API_Note_Oled_Refresh(const OledIcon_t*    dynamic_box,
                                        const DeviceState_e* error_list, const uint8_t device_len,
                                        OledNoteInfo_t* info);

#endif /* __API_NOTIFICATION_H_ */
