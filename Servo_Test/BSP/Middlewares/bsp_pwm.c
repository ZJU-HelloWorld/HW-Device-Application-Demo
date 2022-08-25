/**
 *******************************************************************************
 * @file      : bsp_pwm.c/h
 * @brief     : PWM device Driver
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-10      Xue Donglai     1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "bsp_pwm.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Initialize all 7 pwm channels (DJI Board Type C)
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void BSP_Pwm_InitAllCh(void)
{
  HAL_TIM_Base_Start_IT(&HTIM_PWM1);
  HAL_TIM_Base_Start_IT(&HTIM_PWM2);

  HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH1);
  HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH2);
  HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH3);
  HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH4);

  HAL_TIM_PWM_Start(&HTIM_PWM2, HTIM_PWM_CH1);
  HAL_TIM_PWM_Start(&HTIM_PWM2, HTIM_PWM_CH2);
  HAL_TIM_PWM_Start(&HTIM_PWM2, HTIM_PWM_CH3);
}
