/**
 *******************************************************************************
 * @file      : api_notification.c/h
 * @brief     : Message notificating interface
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-03-04      xdl             1. Done
 *  V1.1        2022-07-17      xdl             1. Refactored
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
#include "fml_buzzer.h"
/* Exported types ------------------------------------------------------------*/
typedef enum _error_to_note_e
{
  NO_ERROR_TO_NOTE = 0,
  IS_GIMBAL_BOOSTER_ERROR,
  IS_CHASSIS_ERROR,
  IS_REFEREE_ERROR,
  IS_MINIPC_ERROR,
} ErrorToNote_e;
typedef struct _buzzer_note_info_t
{
  bool_t        is_playing_startup_music;
  ErrorToNote_e error_type_to_note;

  uint32_t music_cnt;         /* num of tones played */
  uint32_t error_warning_cnt; /* cnt for error duration */
} BuzzerNoteInfo_t;
/* Exported macro ------------------------------------------------------------*/
#ifndef CTRL_FREQ
#define CTRL_FREQ 1000.0f
#endif
#ifndef HALF_CTRL_FREQ
#define HALF_CTRL_FREQ (CTRL_FREQ / 2)
#endif
#ifndef MUSIC_FREQ
#define MUSIC_FREQ 10.0f
#endif
#define IS_TO_PLAY_STARTUP_MUSIC(tick) ((tick) % (int)(CTRL_FREQ / MUSIC_FREQ) == 0)
#define IS_PLAYING_STARTUP_MUSIC(info) ((info)->is_playing_startup_music)
#define IS_ERROR_TO_BUZZER_NOTE(info)  (NO_ERROR_TO_NOTE != (info)->error_type_to_note)
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void API_Note_Buzzer_Init(BuzzerNoteInfo_t* info);
void API_Note_Buzzer_PlayStartupMusic(const uint8_t* music, const uint32_t len,
                                      BuzzerNoteInfo_t* info);
void API_Note_Buzzer_Warn(BuzzerNoteInfo_t* info);
void API_Note_Buzzer_SetErrorType(const ErrorToNote_e type,
                                  BuzzerNoteInfo_t*   info);

#endif /* __API_NOTIFICATION_H_ */
