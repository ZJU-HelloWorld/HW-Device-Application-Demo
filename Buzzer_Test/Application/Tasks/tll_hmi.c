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
/* Includes ------------------------------------------------------------------*/
#include "tll_hmi.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define STARTUP_MUSIC_LEN 144U
/* Private constants ---------------------------------------------------------*/
static const Tone_e music_buf[STARTUP_MUSIC_LEN] = {
    RST, RST, RST, RST, RST, RST, RST, RST,
    G5b, G5b, G5b, G5b, G5b, G5b, G5b, G5b,

    G5b, G5b, G5b, RST, D6b, D6b, RST, RST,
    B5_, B5_, B5_, B5_, B5_, B5_, B5_, B5_,

    B5_, B5_, B5_, RST, A5_, RST, A5b, RST,
    G5b, G5b, RST, RST, E5_, RST, D5_, RST,

    RST, RST, D5b, RST, D5_, RST, E5_, RST,
    G5b, G5b, RST, RST, A5_, A5_, RST, RST,

    A5b, A5b, A5b, A5b, A5b, A5b, A5b, A5b,
    A5b, A5b, A5b, A5b, A5b, A5b, A5b, A5b,

    A5b, A5b, A5b, A5b, A5b, A5b, A5b, RST,
    A5_, A5_, A5_, RST, A6b, A6b, RST, RST,

    A5b, A5b, A5b, A5b, A5b, A5b, A5b, A5b,
    G5b, G5b, G5b, RST, E6_, E6_, RST, RST,

    E5_, E5_, E5_, E5_, RST, RST, RST, RST,
    E5b, E5b, E5b, RST, D6b, D6b, RST, RST,

    D5b, D5b, D5b, D5b, D5b, D5b, D5b, D5b,
    D5b, D5b, D5b, D5b, D5b, D5b, D5b, D5b // Debussy Suite bergamasque IV.Passepied
};
/* Private variables ---------------------------------------------------------*/
volatile NoteInfo_t note_info;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void _TLL_Hmi_NoteTask(NoteInfo_t* info, uint32_t system_tick);

/**
 *******************************************************************************
 * @brief     Human-Machine Interacting init
 * @param     None
 * @retval    None
 * @note      called by `Sys_Init`
 *******************************************************************************
 */
void TLL_Hmi_Init(void)
{
  note_info.mutex = 0u;
#if USE_BUZZER
  API_Note_Buzzer_Init((BuzzerNoteInfo_t*)&note_info.buzzer);
#endif
}

/**
 *******************************************************************************
 * @brief     Human-Machine Interacting task, including remote controlling,
 *            ctrl mode settings, UI drawing, music playing and error warning
 * @param     uint32_t system_tick
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void TLL_Hmi_Task(uint32_t system_tick)
{
  /* play startup music 8Hz，and warn if error occurs */
  _TLL_Hmi_NoteTask((NoteInfo_t*)&note_info, system_tick);
}

/**
 *******************************************************************************
 * @brief     Get pointer of the local volatile note_info
 * @param     None
 * @retval    volatile NoteInfo_t* &note_info
 * @note      None
 *******************************************************************************
 */
volatile NoteInfo_t* TLL_Get_NoteInfoPtr(void)
{
  return &note_info;
}

/**
 *******************************************************************************
 * @brief     HMI - note task
 * @param     NoteInfo_t* info
 * @param     uint32_t system_tick
 * @retval    None
 * @note      None
 *******************************************************************************
 */
static void _TLL_Hmi_NoteTask(NoteInfo_t* info, uint32_t system_tick)
{
  /* Enter Critical Section */
  info->mutex = 1u;

  if (IS_ERROR_TO_BUZZER_NOTE(&info->buzzer))
  {
    API_Note_Buzzer_Warn(&info->buzzer);
  }
  else if (IS_PLAYING_STARTUP_MUSIC(&info->buzzer) && // during playing
           IS_TO_PLAY_STARTUP_MUSIC(system_tick))     // interval between two tones
  {
    API_Note_Buzzer_PlayStartupMusic(music_buf, STARTUP_MUSIC_LEN, &info->buzzer);
  }

  /* Exit Critical Section */
  info->mutex = 0u;
}
