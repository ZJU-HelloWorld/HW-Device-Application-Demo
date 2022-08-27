/**
 *******************************************************************************
 * @file      : tll_action.c/h
 * @brief     : Action task, including transmitting data to referee and other
                tx tasks, cmd acting components et al.
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-08-15      Xue Donglai     1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "tll_action.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void _TLL_Action_SendMinipcData(CommInfo_t* info);

/**
 *******************************************************************************
 * @brief       Action task init
 * @param       AppInfoMsg_t* msg:
 * @retval      None
 * @note        called by `Sys_Init`
 *******************************************************************************
 */
void TLL_Action_Init(AppInfoMsg_t* msg)
{
  UNUSED(msg);
}

/**
 *******************************************************************************
 * @brief       Acion task, including transmitting data to referee and other
                tx tasks, cmd acting components et al.
 * @param       uint32_t system_tick:
 * @param       AppInfoMsg_t* msg:
 * @arg         None
 * @retval      None
 *******************************************************************************
 */
void TLL_Action_Task(uint32_t system_tick, AppInfoMsg_t* msg)
{
  /* minipc send tx data */
  if (IS_TO_SEND_MINIPC(system_tick))
  {
    _TLL_Action_SendMinipcData((CommInfo_t*)msg->app_info[COMM_INFO]);
  }
}

/**
 *******************************************************************************
 * @brief     ACTION - send minipc data
 * @param     CommInfo_t* info
 * @retval    None
 * @note      None
 *******************************************************************************
 */
static void _TLL_Action_SendMinipcData(CommInfo_t* info)
{
  if (API_OK != API_Comm_SendMinipcFrameInfo(info))
  {
  }
}
