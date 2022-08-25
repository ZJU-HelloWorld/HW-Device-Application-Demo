/**
 *******************************************************************************
 * @file      : fml_buzzer.c/h
 * @brief     : Buzzer driver
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        Null            Senior          1. Firstly Done
 *  V2.0        2022-03-16      Xue Donglai     1. Refactored
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_buzzer.h"
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define GET_DURATION_US(tone) \
  (int)(1000000 / (440 * pow(1.05946f, (tone)-69))) // 440 * 2^((n-69)/12) Hz
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Initialize the buzzer
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Buzzer_Init(void)
{
  HAL_TIM_PWM_Start(&HTIM_PWM_BUZZER, HTIM_PWM_CH_BUZZER);
}

/**
 *******************************************************************************
 * @brief     Set to a specific tone
 * @param     Tone_e tone
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Buzzer_SetTone(Tone_e tone)
{
  if (RST == tone)
  {
    __HAL_TIM_SET_AUTORELOAD(&HTIM_PWM_BUZZER, 0);
    __HAL_TIM_SET_COMPARE(&HTIM_PWM_BUZZER, HTIM_PWM_CH_BUZZER, 0);
  }
  else
  {
    /* Reload the counter, that is, modify ARR to modify the tone */
    __HAL_TIM_SET_AUTORELOAD(&HTIM_PWM_BUZZER, GET_DURATION_US(tone));
    /* Set the duty ratio, that is, modify CCR */
    __HAL_TIM_SET_COMPARE(&HTIM_PWM_BUZZER, HTIM_PWM_CH_BUZZER, GET_DURATION_US(tone) / 2U);
  }
}
