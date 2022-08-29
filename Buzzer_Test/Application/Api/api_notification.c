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
/* Includes ------------------------------------------------------------------*/
#include "api_notification.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define TONE_WARNING A4_
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t tick;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Initialize the buzzer notification interface
 * @param     BuzzerNoteInfo_t* info: buzzer notificating info struct
 * @retval    BuzzerNoteInfo_t* info: modified within the function
 * @note      None
 *******************************************************************************
 */
void API_Note_Buzzer_Init(BuzzerNoteInfo_t* info)
{
  if (NULL == info)
    return;

  info->is_playing_startup_music = 1U;
  info->music_cnt                = 0U;
  info->error_type_to_note       = NO_ERROR_TO_NOTE;
}

/**
 *******************************************************************************
 * @brief     Play startup music
 * @param     const uint8_t* music: music array addr
 * @param     const uint32_t len: length of startup music
 * @param     BuzzerNoteInfo_t* info
 * @retval    BuzzerNoteInfo_t* info: set the playing mark and counter
 * @note      None
 *******************************************************************************
 */
void API_Note_Buzzer_PlayStartupMusic(const Tone_e* music, const uint32_t len,
                                      BuzzerNoteInfo_t* info)
{
  if (NULL == info)
    return;

  if (len == info->music_cnt)
  {
    info->is_playing_startup_music = 0U;
    /* the counter will remain the value */
    FML_Buzzer_SetTone(RST);
    return;
  }

  info->music_cnt++;
  if (info->music_cnt >= len) // protect memory
    return;

  FML_Buzzer_SetTone(music[info->music_cnt]);
}

/**
 *******************************************************************************
 * @brief     Buzzer warns when an error occurs
 * @param     BuzzerNoteInfo_t* info
 * @retval    BuzzerNoteInfo_t* info: set the counter for warning
 * @note      plz call this function in CTRL_FREQ (default 1kHz)
 *******************************************************************************
 */
void API_Note_Buzzer_Warn(BuzzerNoteInfo_t* info)
{
  if (NULL == info)
    return;

  if (NO_ERROR_TO_NOTE == info->error_type_to_note)
  {
    info->error_warning_cnt = 0U;
    FML_Buzzer_SetTone(RST);
    return;
  }

  /* warn 0.5Hz with 440Hz tone.s
     if gimbal or ammo-booster error, B-B-B...,
     if chassis error, BB-BB-BB...,
     if referee communicating error, BBB-BBB-BBB...,
     if minipc communicating error, BBBB-BBBB-BBBB... */
  tick = HAL_GetTick();
  if (0 == tick % (int)(HALF_CTRL_FREQ / info->error_type_to_note))
  {
    if (info->error_type_to_note * 4 == ++info->error_warning_cnt)
      info->error_warning_cnt = 0U;

    /* B for error_type_to_note times within 1 sec, and rest for another 1 sec */
    if (info->error_warning_cnt % 2 &&
        info->error_warning_cnt < info->error_type_to_note * 2)
      FML_Buzzer_SetTone(TONE_WARNING);
    else
      FML_Buzzer_SetTone(RST);
  }
}

/**
 *******************************************************************************
 * @brief     Set the error type to warn
 * @param     const ErrorToNote_e type: error type
 * @arg       IS_GIMBAL_BOOSTER_ERROR, IS_CHASSIS_ERROR, IS_REFEREE_ERROR, IS_MINIPC_ERROR
 * @param     BuzzerNoteInfo_t* info
 * @retval    BuzzerNoteInfo_t* info: modefied within the function
 * @note      None
 *******************************************************************************
 */
void API_Note_Buzzer_SetErrorType(const ErrorToNote_e type,
                                  BuzzerNoteInfo_t*   info)
{
  if (NULL == info)
    return;

  info->error_type_to_note = type;
}
