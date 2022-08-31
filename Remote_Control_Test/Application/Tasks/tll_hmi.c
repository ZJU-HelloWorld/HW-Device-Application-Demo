/**
 *******************************************************************************
 * @file      : tll_hmi.c/h
 * @brief     : human-machine interaction, including remote ctrl, mode update,
                UI drawing, music playing and notification et al.
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-03-17      Xue Donglai     1. Done
 *  V1.1        2022-07-23      Xue Donglai     1. Revised
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
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile CtrlInfo_t ctrl_info;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void _TLL_Hmi_UpdateCtrlData(CtrlInfo_t* info);

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
  ctrl_info.mutex = 0u;
#if USE_RC
  API_Ctrl_Init((CtrlInfo_t*)&ctrl_info);
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
  /* rc update data, incluing ctrl src, mode and detailed info */
  _TLL_Hmi_UpdateCtrlData((CtrlInfo_t*)&ctrl_info);
}

/**
 *******************************************************************************
 * @brief     Get pointer of the local volatile ctrl_info
 * @param     None
 * @retval    volatile CtrlInfo_t* &ctrl_info
 * @note      None
 *******************************************************************************
 */
volatile CtrlInfo_t* TLL_Get_CtrlInfoPtr(void)
{
  return &ctrl_info;
}

/**
 *******************************************************************************
 * @brief     HMI - update control data
 * @param     CtrlInfo_t* info
 * @retval    None
 * @note      update data, incluing ctrl src, mode and detailed info
 *******************************************************************************
 */
static void _TLL_Hmi_UpdateCtrlData(CtrlInfo_t* info)
{
  /* Enter Critical Section */
  info->mutex = 1u;

  /* Update Ctrl Source */
  API_Ctrl_UpdateCtrlSrc(&info->last_data, &info->data, &info->ctrl_src);
  /* According to src and data, set mode and update action cmd */
  API_Ctrl_UpdateCtrlInfo(info);
  info->last_data = info->data;

  /* Exit Critical Section */
  info->mutex = 0u;
}
