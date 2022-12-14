/**
 *******************************************************************************
 * @file      : tll_perception.c/h
 * @brief     : Perception task, including handling referee info, attitude data,
 *              minipc and supercap control board data et al.
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
#include "tll_perception.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile static CommInfo_t comm_info;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void _TLL_Perception_UpdateMinipcData(CommInfo_t* info);

/**
 *******************************************************************************
 * @brief     Perception task init
 * @param     None
 * @retval    None
 * @note      called by `Sys_Init`
 *******************************************************************************
 */
void TLL_Perception_Init(AppInfoMsg_t* msg)
{
  comm_info.mutex = 0u;
#if (USE_MINIPC_UART || USE_MINIPC_USB)
  API_Comm_Minipc_Init((MinipcCommInfo_t*)&comm_info.minipc_comm_info);
  if (ASSIGN == msg->permission[COMM_INFO])
  {
    msg->app_info[COMM_INFO]   = (void*)TLL_Get_CommInfoPtr();
    msg->permission[COMM_INFO] = WRITE;
  }
#endif
}

/**
 *******************************************************************************
 * @brief       Perception task, including handling referee info, attitude data,
 *              minipc and supercap control board data et al.
 * @param       uint32_t system_tick:
 * @param       AppInfoMsg_t* msg:
 * @arg         None
 * @retval      None
 *******************************************************************************
 */
void TLL_Perception_Task(uint32_t system_tick, AppInfoMsg_t* msg)
{
  CommInfo_t* info = (CommInfo_t*)msg->app_info[COMM_INFO];

  /* minipc update rx data and handle */
  _TLL_Perception_UpdateMinipcData(info);
}

/**
 *******************************************************************************
 * @brief     Get pointer of the local volatile comm_info
 * @param     None
 * @retval    volatile CommInfo_t* &comm_info
 * @note      None
 *******************************************************************************
 */
volatile CommInfo_t* TLL_Get_CommInfoPtr(void)
{
  return &comm_info;
}

/**
 *******************************************************************************
 * @brief     PERCEPTION - update minipc data and handle
 * @param     CommInfo_t* info
 * @retval    None
 * @note      None
 *******************************************************************************
 */
static void _TLL_Perception_UpdateMinipcData(CommInfo_t* info)
{
  /* Enter Critical Section */
  info->mutex = 1u;

  if (info->minipc_comm_info.minipc_data.rx_update_flag)
  {
    info->minipc_comm_info.minipc_data.rx_update_flag = 0;
    API_Comm_UpdateMinipcFrameInfo(&info->minipc_comm_info);
  }
  /* Exit Critical Section */
  info->mutex = 0u;
}
