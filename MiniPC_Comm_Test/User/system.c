/**
 *******************************************************************************
 * @file      : system.c/h
 * @brief     : task manager & user callback serving functions realization
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-02-17      wwy             1. Done
 *  V2.0        Null            Senior          1. Revised
 *  V3.0        2022-03-15      xdl             1. Refactored
 *                                              2. Decoupled, object-oriented
 *  V3.1        2022-08-01      xdl             1. Modified for test
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
static uint32_t system_tick;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Sys_Task_Manager(void);

/**
 *******************************************************************************
 * @brief     Init devices, tasks et al and start IT
 * @param     None
 * @retval    None
 * @note      plz call me before while(1) segment in main.c
 *******************************************************************************
 */
void Sys_Init(void)
{
  /* ----------------------BSP Init ------------------ */
  /* ------------------- Device Init ----------------- */
#if USE_MINIPC_UART
  FML_Minipc_Init();
#endif
  /* ------ Communication Init & Algorithms Init ----- */
  /* -------------------- Task Init ------------------ */
  TLL_Perception_Init();
  TLL_Action_Init();

  /* Main IT init to start managing tasks */
  HAL_TIM_Base_Start_IT(&HTIM_CONTROL);
#if USE_MINIPC_USB
  HAL_TIM_Base_Start_IT(&HTIM_USB_RX_IT);
#endif
}

/**
 *******************************************************************************
 * @brief     task manager
 * @param     None
 * @retval    None
 * @note      Called by TIM6 interrupt，1KHz run tasks by order
 *******************************************************************************
 */
static void Sys_Task_Manager(void)
{
  system_tick = HAL_GetTick();

  CommInfo_t* tmp_comm_info = (CommInfo_t*)TLL_Get_CommInfoPtr();
  /* Perception --------------------------------------------------------------*/
  TLL_Perception_Task(system_tick);
  /* Action ------------------------------------------------------------------*/
  TLL_Action_Task(system_tick, tmp_comm_info);
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
    Sys_Task_Manager();
  }

#if USE_MINIPC_USB
  if (IS_HTIM_USB_RX_IT(htim))
  {
    CommInfo_t* tmp_info = (CommInfo_t*)TLL_Get_CommInfoPtr();
    if (DVC_DATA_ERROR == FML_Minipc_RxDataHandler(&tmp_info->minipc_data))
    {
    }

    HAL_TIM_Base_Stop_IT(&HTIM_USB_RX_IT);
  }
#endif
}

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
#if USE_MINIPC_UART
  if (IS_HUART_MINIPC(huart))
  {
    CommInfo_t* tmp_info = (CommInfo_t*)TLL_Get_CommInfoPtr();
    if (DVC_OK != FML_Minipc_RxDataHandler(&tmp_info->minipc_data))
    {
    }
#if USE_MINIPC_UART_RX_IT
    FML_Minipc_Init();
#endif
  }
#endif
}