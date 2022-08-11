/**
 *******************************************************************************
 * @file      : system.c/h
 * @brief     : task manager & user callback serving funtions realization
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-02-17      wwy             1. Done
 *  V2.0        Null            Senior          1. Revised
 *  V3.0        2022-03-15      xdl             1. Refactored
 *                                              2. Decoupled, object-oriented
 *  V3.1        2022-07-18      xdl             1. Modified for test
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
#define IS_HTIM_CONTROL(htim) ((htim) == &HTIM_CONTROL)
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t system_tick;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void _Sys_Task_Manager(void);

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
#if USE_BUZZER
  FML_Buzzer_Init();
#endif
  /* ------------------- Device Init ----------------- */

  /* ------ Communication Init & Algorithms Init ----- */

  /* -------------------- Task Init ------------------ */
  TLL_Hmi_Init();

  /* Main IT init to start managing tasks */
  HAL_TIM_Base_Start_IT(&HTIM_CONTROL);
}

/**
 *******************************************************************************
 * @brief     task manager
 * @param     None
 * @retval    None
 * @note      Called by TIM6 interrupt，1KHz run tasks by order
 *******************************************************************************
 */
static void _Sys_Task_Manager(void)
{
  system_tick = HAL_GetTick();

  /* Human-machine Interaction -----------------------------------------------*/
  TLL_Hmi_Task(system_tick);

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
 * @arg       htim6 main task manager，1kHz，lowest priority
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
}
