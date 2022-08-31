/**
 *******************************************************************************
 * @file      : system.c/h
 * @brief     : task manager & user callback serving functions realization
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-02-17      wwy             1. Done
 *  V2.0        Null            Senior          1. Revised
 *  V3.0        2022-03-15      Xue Donglai     1. Refactored
 *                                              2. Decoupled, object-oriented
 *  V3.1        2022-08-01      Xue Donglai     1. Modified for test
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "system.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define IS_HTIM_CONTROL(htim)   ((htim) == &HTIM_CONTROL)
#define IS_HTIM_USB_RX_IT(htim) ((htim) == &HTIM_USB_RX_IT)
#define IS_HUART_MINIPC(huart)  ((huart) == &HUART_MINIPC)
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t     system_tick;
static AppInfoMsg_t msg;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void _Sys_Msg_Init(AppInfoMsg_t* msg);
static void _Sys_Task_Manager(void);

/**
 *******************************************************************************
 * @brief       Init devices, tasks et al and start IT
 * @param       None
 * @retval      None
 * @note        plz call me before while(1) segment in main.c
 *******************************************************************************
 */
void Sys_Init(void)
{
  /* ------------------- Device Init ----------------- */
#if USE_MINIPC_UART
  FML_Minipc_Init();
#endif
  /* -------------------- Task Init ------------------ */
  _Sys_Msg_Init(&msg);

  TLL_Perception_Init(&msg);
  TLL_Action_Init(&msg);

  /* Main IT init to start managing tasks */
  HAL_TIM_Base_Start_IT(&HTIM_CONTROL);
}

/**
 *******************************************************************************
 * @brief       Init msg between tasks
 * @param       AppInfoMsg_t* msg: msg struct containing task msgs
 * @arg         None
 * @retval      None
 *******************************************************************************
 */
static void _Sys_Msg_Init(AppInfoMsg_t* msg)
{
  for (uint8_t i = 0; i < APP_INFO_NUM; i++)
  {
    msg->app_info[i]   = NULL;
    msg->permission[i] = ASSIGN;
  }
}

/**
 *******************************************************************************
 * @brief     task manager
 * @param     None
 * @retval    None
 * @note      Called by TIM6 interrupt
 *******************************************************************************
 */
static void _Sys_Task_Manager(void)
{
  system_tick = HAL_GetTick();

  /* Perception --------------------------------------------------------------*/
  TLL_Perception_Task(system_tick, &msg);
  /* Action ------------------------------------------------------------------*/
  TLL_Action_Task(system_tick, &msg);

  /* Debug -------------------------------------------------------------------*/
#if DEBUG_ON
  Debug_Watcher();
#endif
}

/* Callbacks -----------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief     Timer callbacks in non blocking modes user realization
 * @param     TIM_HandleTypeDef *htim
 * @arg       HTIM_CONTROL - main task manager，1kHz，lowest priority
 * @arg       HTIM_USB_RX_IT - usb rx notificating，2kHz
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
  if (IS_HTIM_CONTROL(htim))
  {
    _Sys_Task_Manager();
  }

#if USE_MINIPC_USB
  if (IS_HTIM_USB_RX_IT(htim))
  {
    CommInfo_t* info = (CommInfo_t*)TLL_Get_CommInfoPtr();
    if (!info->mutex)
    {
      if (DVC_OK != FML_Minipc_RxDataHandler(&info->minipc_comm_info.minipc_data))
      {
      }
      HAL_TIM_Base_Stop_IT(&HTIM_USB_RX_IT);
    }
  }
#endif
}

#if USE_MINIPC_UART
/**
 *******************************************************************************
 * @brief     UART Rx complete callbacks in non blocking modes user realization
 * @param     UART_HandleTypeDef* huart
 * @arg       HUART_MINIPC
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
  if (IS_HUART_MINIPC(huart))
  {
    CommInfo_t* info = (CommInfo_t*)TLL_Get_CommInfoPtr();
    if (!info->mutex)
    {
      if (DVC_OK != FML_Minipc_RxDataHandler(&info->minipc_comm_info.minipc_data))
      {
      }
#if USE_MINIPC_UART_RX_IT
      FML_Minipc_Init();
#endif
    }
  }
}
#endif