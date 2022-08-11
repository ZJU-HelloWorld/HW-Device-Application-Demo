/**
 *******************************************************************************
 * @file      : fml_laser.c/h
 * @brief     : laser Driver
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        Null            Senior          1. Done
 *  V2.0        2022-03-16      xdl             1. Refactored
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_laser.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Initialize the laser
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Laser_Init(void)
{
  HAL_TIM_PWM_Start(&HTIM_PWM_LASER, HTIM_CH_LASER);
}

/**
 *******************************************************************************
 * @brief     Turn on the Laser
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Laser_TurnOn(void)
{
  __HAL_TIM_SetCompare(&HTIM_PWM_LASER, HTIM_CH_LASER, LASER_PWM_MAX);
}

/**
 *******************************************************************************
 * @brief     Turn on the laser and set to Max lumin
 * @param     LaserLumin_e lumin
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Laser_SetLumin(LaserLumin_e lumin)
{
  __HAL_TIM_SetCompare(&HTIM_PWM_LASER, HTIM_CH_LASER, lumin);
}

/**
 *******************************************************************************
 * @brief     Turn off the Laser
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Laser_TurnOff(void)
{
  __HAL_TIM_SetCompare(&HTIM_PWM_LASER, HTIM_CH_LASER, 0);
}