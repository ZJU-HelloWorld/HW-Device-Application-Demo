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
#if IS_STEERABLE_STANDARD
#define SUPERCAP_BOX_ARRAY_MAX_A_ROW 48 /* max colomn number, or max pixels each row */
#define SUPERCAP_BOX_ARRAY_MAX_A_COL 2  /* 14 pixels need 2 Bytes */

#define SUPERCAP_BOX_MAX_PIXEL_A_ROW 48 /* in pixel */
#define SUPERCAP_BOX_MAX_PIXEL_A_COL 14
#endif
/* Private constants ---------------------------------------------------------*/
const static unsigned char device_name_string[DEVICE_LIST_LEN][DEVICE_NAME_STRING_LEN] = {
    "RC  \0", "Comm\0", "Refr\0",
    "PC  \0", "Fric\0", "Feed\0",
    "Yaw \0", "Pth \0", "WhlF\0",
    "WhlB\0", "StrF\0", "StrB\0", // device order see `config.h`
};
/* Private variables ---------------------------------------------------------*/
volatile NoteInfo_t note_info;

#if IS_STEERABLE_STANDARD
static OledIcon_t dynamic_box;
static uint8_t    supercap_box_data[SUPERCAP_BOX_ARRAY_MAX_A_ROW * SUPERCAP_BOX_ARRAY_MAX_A_COL] = {
       0xFF, 0xFC, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04,
       0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04,
       0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04,
       0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04,
       0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04,
       0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0x80, 0x04, 0xFF, 0xFC, 0x07, 0x80,
       /* 48 x 14 */
};

static OledIcon_t supercap_box = {.length = SUPERCAP_BOX_MAX_PIXEL_A_ROW,
                                  .width  = SUPERCAP_BOX_MAX_PIXEL_A_COL,
                                  .data   = (uint8_t*)supercap_box_data};
#endif
/* External variables --------------------------------------------------------*/
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
  note_info.mutex = 0;
#if USE_OLED
  API_Note_Oled_Init(device_name_string, DEVICE_LIST_LEN, (OledNoteInfo_t*)&note_info.oled);
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
  /* oled display to warn if error occurs */
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

  if (IS_TO_CMD_OLED(system_tick))
  {
    API_Note_Oled_SetBatteryPerc(AUTO_GET, NULL, &info->oled);
#if IS_STEERABLE_STANDARD
    /* Generate dynamic supercap icon box */
    for (uint8_t i = 1; i < SUPERCAP_BOX_MAX_PIXEL_A_ROW - 2; i++)
    {
      if (i <= info->oled.supercap_perc * (SUPERCAP_BOX_MAX_PIXEL_A_ROW - 3) / 100)
      {
        /* fill one column */
        API_Note_Oled_ModifyIconBox(i, 0,
                                    SUPERCAP_BOX_ARRAY_MAX_A_ROW, SUPERCAP_BOX_ARRAY_MAX_A_COL,
                                    0xFF, supercap_box_data);
        API_Note_Oled_ModifyIconBox(i, 1,
                                    SUPERCAP_BOX_ARRAY_MAX_A_ROW, SUPERCAP_BOX_ARRAY_MAX_A_COL,
                                    0xFC, supercap_box_data);
      }
      else /* only box line */
      {
        API_Note_Oled_ModifyIconBox(i, 0,
                                    SUPERCAP_BOX_ARRAY_MAX_A_ROW, SUPERCAP_BOX_ARRAY_MAX_A_COL,
                                    0x80, supercap_box_data);
        API_Note_Oled_ModifyIconBox(i, 1,
                                    SUPERCAP_BOX_ARRAY_MAX_A_ROW, SUPERCAP_BOX_ARRAY_MAX_A_COL,
                                    0x04, supercap_box_data);
      }
    }
    dynamic_box = supercap_box;
    /* acion */
    if (API_OK != API_Note_Oled_Refresh(&dynamic_box, info->error_list, DEVICE_LIST_LEN, &info->oled))
    {
    }
#else
    if (API_OK != API_Note_Oled_Refresh(NULL, info->error_list, DEVICE_LIST_LEN, &info->oled))
    {
    }
#endif
  }

  /* Exit Critical Section */
  info->mutex = 0u;
}
