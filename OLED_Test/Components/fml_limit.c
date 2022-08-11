/**
 *******************************************************************************
 * @file      : fml_limit.c/h
 * @brief     : limitation macro and functions
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-17      xdl             1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_limit.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     judge if given value is in the given range
 * @param     float val
 * @param     float bound1
 * @param     float bound2
 * @retval    bool_t 1 - in range, 0 - not in range
 * @note      None
 *******************************************************************************
 */
bool_t FML_InRange(float val, float bound1, float bound2)
{
  if (bound1 <= bound2)
    return (val >= bound1 && val <= bound2);
  else
    return (val <= bound1 && val >= bound2);
}
