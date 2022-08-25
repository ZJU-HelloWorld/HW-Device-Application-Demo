/**
 *******************************************************************************
 * @file      : debug.c/h
 * @brief     : watch variables
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        Null            Senior          1. Done
 *  V2.0        2022-08-01      Xue Donglai     1. Refactored
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "debug.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Register Base Address */
#define DWT_CR           *(uint32_t*)0xE0001000
#define DWT_CYCCNT       *(uint32_t*)0xE0001004
#define DEM_CR           *(uint32_t*)0xE000EDFC
/* bit to Enable */
#define DEM_CR_TRCENA    (0x01 << 24)
#define DWT_CR_CYCCNTENA (0x01 << 0)
/* Private constants ---------------------------------------------------------*/
const uint32_t kSysClockFreqMHz = 168U; // 168MHz
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     get variables from tasks to watch
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void Debug_Watcher(void)
{
}

/**
 *******************************************************************************
 * @brief     init DWT
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void Debug_Dwt_Init(void)
{
  /* Enable DWT */
  DEM_CR |= (uint32_t)DEM_CR_TRCENA;

  /* DWT CYCCNT Register set to 0 */
  DWT_CYCCNT = (uint32_t)0U;

  /* Enable Cortex-M DWT CYCCNT Reg */
  DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
}

/**
 *******************************************************************************
 * @brief     Get DWT Tick
 * @param     None
 * @retval    uint32_t
 * @note      in uSecond
 *******************************************************************************
 */
uint32_t Debug_Dwt_GetTickUS(void)
{
  return ((uint32_t)DWT_CYCCNT / kSysClockFreqMHz);
}