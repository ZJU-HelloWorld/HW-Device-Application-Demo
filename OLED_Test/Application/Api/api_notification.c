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
/* Includes ------------------------------------------------------------------*/
#include "api_notification.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define USER_STRING1 "Aim R"
#define USER_STRING2 "Aim B"
#define USER_STRING3 "UNSET"
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Initialize the oled notification interface
 * @param     OledNoteInfo_t* info: oled notificating info struct
 * @retval    OledNoteInfo_t* info: modified within the function
 * @note      Set the member 'device_name_string' of OledNoteInfo_t for displaying
 *******************************************************************************
 */
void API_Note_Oled_Init(const unsigned char (*string_list)[DEVICE_NAME_STRING_LEN],
                        const uint8_t   len,
                        OledNoteInfo_t* info)
{
  if (NULL == info)
    return;

  info->pwr_data.battery_perc            = 0;
  info->pwr_data.supercap_perc           = 0;
  info->pwr_data.volt_vrefint_proportion = FML_Pwrsrc_GetVrefintProportion();
  info->enemy_color                      = UNSET;

  if (NULL != string_list)
  {
    memcpy(info->device_string_list, string_list,
           len * DEVICE_NAME_STRING_LEN * sizeof(unsigned char));
  }

  FML_Oled_OperateGram(PEN_CLEAR, &info->gram);
  FML_Oled_RefreshGram(&info->gram);
}

/**
 *******************************************************************************
 * @brief     Modify icon box data to generate dynamic oled box to display
 * @param     const uint8_t col: column in the icon data array, from 0
 * @param     const uint8_t row: row in the icon data array, from 0
 * @param     const uint16_t max_col: max column of the icon data array
 * @param     const uint16_t max_row: max row of the icon data array
 * @param     const uint8_t data: the new data for replacing
 * @param     uint8_t* box: icon data array
 * @retval    uint8_t* box
 * @note      None
 *******************************************************************************
 */
void API_Note_Oled_ModifyIconBox(const uint8_t col, const uint8_t row,
                                 const uint16_t max_col, const uint16_t max_row,
                                 const uint8_t data,
                                 uint8_t*      box)
{
  if (col >= max_col || row >= max_row)
    return;
  if (NULL == box)
    return;

  box[col * max_row + row] = data;
}

/**
 *******************************************************************************
 * @brief     Set battery percentage in power data struct
 * @param     const DataSrc_e src: data source, USER_SET or AUTO_GET
 * @param     const float votage: if USER_SET will be used, else ignored, plz set to NULL
 * @param     OledNoteInfo_t* info: oled notificating info struct
 * @retval    OledNoteInfo_t* info: modified within the function
 * @note      None
 *******************************************************************************
 */
void API_Note_Oled_SetBatteryPerc(const DataSrc_e src, const float votage,
                                  OledNoteInfo_t* info)
{
  if (NULL == info)
    return;

  float battery_votage =
      USER_SET == src ? votage
                      : FML_Pwrsrc_GetBatteryVotage(info->pwr_data.volt_vrefint_proportion);

  static float last_volt = 22.4f, volt = 22.4f;
  volt = 0.6f * battery_votage + 0.4 * last_volt;

  float volt_2 = volt * volt;
  float volt_3 = volt_2 * volt;
  float perc;

  perc = volt < 19.5f   ? 0.0f
         : volt < 21.9f ? (0.005664f * volt_3 - 0.3386f * volt_2 + 6.765f * volt - 45.17f)
         : volt < 25.5f ? (0.02269f * volt_3 - 1.654f * volt_2 + 40.34f * volt - 328.4f)
                        : 1.0f;

  info->pwr_data.battery_perc = (uint16_t)(perc * 100);

  last_volt = volt;
}

/**
 *******************************************************************************
 * @brief     Set supercap percentage in power data struct
 * @param     const DataSrc_e src: data source, USER_SET or AUTO_GET
 * @param     const float votage: if USER_SET will be used, else ignored, plz set to NULL
 * @param     OledNoteInfo_t* info: oled notificating info struct
 * @retval    OledNoteInfo_t* info: modified within the function
 * @note      None
 *******************************************************************************
 */
void API_Note_Oled_SetSupercapPerc(const DataSrc_e src, const float votage,
                                   OledNoteInfo_t* info)
{
  if (NULL == info)
    return;

  float supercap_votage =
      USER_SET == src ? votage
                      : 0; // TODO

  static float last_volt = 22.4f, volt = 22.4f;
  volt = 0.6f * supercap_votage + 0.4f * last_volt;

  float volt_2    = volt * volt;
  float cap_max_2 = SUPERCAP_FULL_VOTAGE * SUPERCAP_FULL_VOTAGE;
  float cap_min_2 = SUPERCAP_MIN_USABLE_VOTAGE * SUPERCAP_MIN_USABLE_VOTAGE;

  float perc;
  perc                         = (volt_2 - cap_min_2) / (cap_max_2 - cap_min_2);
  info->pwr_data.supercap_perc = (uint16_t)(perc * 100);

  last_volt = volt;
}

/**
 *******************************************************************************
 * @brief     Set enemy color in oled info struct
 * @param     const EnemyColor_e color: UNSET, RED or BLUE
 * @param     OledNoteInfo_t* info: oled notificating info struct
 * @retval    OledNoteInfo_t* info: modified within the function
 * @note      None
 *******************************************************************************
 */
void API_Note_Oled_SetEnemyColor(const EnemyColor_e color, OledNoteInfo_t* info)
{
  if (NULL == info)
    return;

  info->enemy_color = color;
}

/**
 *******************************************************************************
 * @brief     Set device state in oled info struct
 * @param     const DeviceList_e index
 * @param     const DeviceState_e state: OK or ERROR
 * @param     DeviceState_e* list: device info list
 * @retval    DeviceState_e* list: Modified
 * @note      None
 *******************************************************************************
 */
void API_Note_Oled_SetDeviceState(const DeviceList_e index, const DeviceState_e state,
                                  DeviceState_e* list)
{
  if (NULL == list)
    return;

  list[index] = state;
}

/**
 *******************************************************************************
 * @brief     Transmit data to OLED gram
 * @param     const OledIcon_t* dynamic_box: dymanic box
 * @param     const DeviceState_e* error_list: device error list for notification
 * @arg       1 - Error, 0 - OK
 * @param     const uint8_t device_len: device list length
 * @param     OledNoteInfo_t* info: oled notificating info struct
 * @retval    OledNoteInfo_t* info: modified within the function
 * @note      `Standard` specific
 *******************************************************************************
 */
void API_Note_Oled_Refresh(const OledIcon_t*    dynamic_box,
                           const DeviceState_e* error_list, const uint8_t device_len,
                           OledNoteInfo_t* info)
{
  if (NULL == info)
    return;

  FML_Oled_OperateGram(PEN_CLEAR, &info->gram);
  FML_Oled_DisplayIcon(1, 1,
                       &battery_box, &info->gram);

  /* Display battery percentage */
  if (info->pwr_data.battery_perc < 10)
  {
    FML_Oled_Printf(info->pwr_data.battery_perc < 10    ? 1 + CHAR_WIDTH * 1.5
                    : info->pwr_data.battery_perc < 100 ? 1 + CHAR_WIDTH * 1.0
                                                        : 1 + CHAR_WIDTH * 0.5,
                    1 + 1,
                    &info->gram, "%d", info->pwr_data.battery_perc);
  }
  FML_Pwrsrc_Init(); /* Reinit Battery Votage ADC Transmit */

  /* Display Dynamic Icon */
  uint8_t kIconBeginPixelCol = BATTERY_BOX_MAX_PIXEL_A_ROW + 5;
  FML_Oled_DisplayIcon(kIconBeginPixelCol, 1, dynamic_box, &info->gram);

  /* Display Enemy Color */
  uint8_t kTxtBeginPixelCol = BATTERY_BOX_MAX_PIXEL_A_ROW + 5 + dynamic_box->length + 5;
  FML_Oled_Printf(kTxtBeginPixelCol, 1 + 1,
                  &info->gram,
                  RED == info->enemy_color    ? USER_STRING1
                  : BLUE == info->enemy_color ? USER_STRING2
                                              : USER_STRING3);

  /* Display Device Info */
  uint8_t show_col, show_row;
  for (uint8_t i = 0; i < device_len; i++)
  {
    /* 3 devices a row */
    show_col = i % 3 * (MAX_COLUMN / 3);
    show_row = BATTERY_BOX_MAX_PIXEL_A_COL + 1 + i / 3 * CHAR_HEIGHT;
    FML_Oled_DisplayIcon(show_col, show_row,
                         &check_box[error_list[i]], &info->gram);
    FML_Oled_DisplayString(show_col + CHECK_BOX_MAX_PIXEL_A_ROW + 1, show_row,
                           info->device_string_list[i], &info->gram);
  }

  FML_Oled_RefreshGram(&info->gram);
}