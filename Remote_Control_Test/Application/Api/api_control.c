/**
 *******************************************************************************
 * @file      : api_control.c/h
 * @brief     : User Control interface (User Command Only)
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-04-17      wwy             1. Done
 *  V1.1        Null            Senior          1. Revised
 *  V2.0        2022-03-11      xdl             1. Refactored
 *  V2.1        2022-08-01      xdl             1. Revised
 *******************************************************************************
 * @attention : api_control.c/h are not general application interfaces, but
 *              can be specially modified by users for various services and arms.
 *              This file is for Standard specially.
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "api_control.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Init ctrl data
 * @param     CtrlInfo_t* info
 * @retval    CtrlInfo_t* info
 * @note      None
 *******************************************************************************
 */
void API_Ctrl_Init(CtrlInfo_t* info)
{
  if (NULL == info)
    return;

  info->ctrl_src = REMOTE_CTRL;

  memset(&info->event, 0, sizeof(MouseKbEvent_t));
  memset(&info->last_data, 0, sizeof(RcData_t));
  memset(&info->data, 0, sizeof(RcData_t));
}

/**
 *******************************************************************************
 * @brief     Update ctrl source
 * @param     const RcData_t* last_data
 * @param     const RcData_t* data
 * @param     CtrlSource_e* src
 * @retval    CtrlSource_e* src
 * @note      key pressed or mouse clicked or moved, update crl source to KEYBOARD_MOUSE_CTRL
 *            else if switch switched or lever levered update to REMOTE_CTRL
 *            else remain the latest source
 *******************************************************************************
 */
void API_Ctrl_UpdateCtrlSrc(const RcData_t* last_data, const RcData_t* data,
                            CtrlSource_e* src)
{
  if (NULL == last_data || NULL == data || NULL == src)
    return;

  if (data->kb.key_code || data->mouse.l || data->mouse.r ||
      data->mouse.x != last_data->mouse.x ||
      data->mouse.y != last_data->mouse.y)
  {
    *src = KEYBOARD_MOUSE_CTRL;
  }
  else if (data->LH || data->LV || data->RH || data->RV ||
           data->sw1 != last_data->sw1 ||
           data->sw2 != last_data->sw2 ||
           data->WHEEL != last_data->WHEEL)
  {
    *src = REMOTE_CTRL;
  }
  /* else remain unchanged */
}

/**
 *******************************************************************************
 * @brief     Set modes and Update action commands for standard
 * @param     CtrlInfo_t* info
 * @param     CtrlInfo_t* info
 * @note      None
 *******************************************************************************
 */
void API_Ctrl_UpdateCtrlInfo(CtrlInfo_t* info)
{
  if (KEYBOARD_MOUSE_CTRL == info->ctrl_src)
  {
    FML_Rc_GetMouseKbEvent(&info->last_data, &info->data, &info->event);
  }
  else if (REMOTE_CTRL == info->ctrl_src)
  {
  }
}
