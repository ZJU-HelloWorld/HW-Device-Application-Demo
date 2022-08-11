/**
 *******************************************************************************
 * @file      : fml_servo.c/h
 * @brief     : Servo Driver
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-10      xdl             1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_servo.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
static const uint8_t kChannelNum    = 7U;
static const float   kServoMinPulse = 500.0f;
static const float   kServoMaxPulse = 2500.0f;
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
#ifndef _CODE_INIT_ALL_PWM_CH
#define _CODE_INIT_ALL_PWM_CH
void FML_Pwm_InitAllCh(void)
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
#endif

/**
 *******************************************************************************
 * @brief     Initialize one pwm channels
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Servo_InitSingleCh(const uint8_t index)
{
  switch (index)
  {
    case 1U:
      HAL_TIM_Base_Start_IT(&HTIM_PWM1);
      HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH1);
      break;
    case 2U:
      HAL_TIM_Base_Start_IT(&HTIM_PWM1);
      HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH2);
      break;
    case 3U:
      HAL_TIM_Base_Start_IT(&HTIM_PWM1);
      HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH3);
      break;
    case 4U:
      HAL_TIM_Base_Start_IT(&HTIM_PWM1);
      HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH4);
      break;
    case 5U:
      HAL_TIM_Base_Start_IT(&HTIM_PWM2);
      HAL_TIM_PWM_Start(&HTIM_PWM2, HTIM_PWM_CH1);
      break;
    case 6U:
      HAL_TIM_Base_Start_IT(&HTIM_PWM2);
      HAL_TIM_PWM_Start(&HTIM_PWM2, HTIM_PWM_CH2);
      break;
    case 7U:
      HAL_TIM_Base_Start_IT(&HTIM_PWM2);
      HAL_TIM_PWM_Start(&HTIM_PWM2, HTIM_PWM_CH3);
      break;
    default:
      HAL_TIM_Base_Start_IT(&HTIM_PWM1);
      HAL_TIM_PWM_Start(&HTIM_PWM1, HTIM_PWM_CH1);
      break;
  }
}

/**
 *******************************************************************************
 * @brief     Set single servo chnnel with max pulse width
 * @param     const uint8_t index: from 'PWM' mark, one of 1 to 7 channel as output
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Servo_SetSingleChMax(const uint8_t index)
{
  switch (index)
  {
    case 1U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH1, kServoMaxPulse);
      break;
    case 2U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH2, kServoMaxPulse);
      break;
    case 3U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH3, kServoMaxPulse);
      break;
    case 4U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH4, kServoMaxPulse);
      break;
    case 5U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH1, kServoMaxPulse);
      break;
    case 6U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH2, kServoMaxPulse);
      break;
    case 7U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH3, kServoMaxPulse);
      break;
    default:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH1, kServoMaxPulse);
      break;
  }
}

/**
 *******************************************************************************
 * @brief     Set all servo chnnel with max pulse width
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Servo_SetAllChMax(void)
{
  for (uint8_t i = 1; i <= kChannelNum; i++)
  {
    FML_Servo_SetSingleChMax(i);
  }
}

/**
 *******************************************************************************
 * @brief     Set single servo chnnel with min pulse width
 * @param     const uint8_t index: from 'PWM' mark, one of 1 to 7 channel as output
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Servo_SetSingleChMin(const uint8_t index)
{
  switch (index)
  {
    case 1U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH1, kServoMinPulse);
      break;
    case 2U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH2, kServoMinPulse);
      break;
    case 3U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH3, kServoMinPulse);
      break;
    case 4U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH4, kServoMinPulse);
      break;
    case 5U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH1, kServoMinPulse);
      break;
    case 6U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH2, kServoMinPulse);
      break;
    case 7U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH3, kServoMinPulse);
      break;
    default:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH1, kServoMinPulse);
      break;
  }
}

/**
 *******************************************************************************
 * @brief     Set all servo chnnel with min pulse width
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Servo_SetAllChMin(void)
{
  for (uint8_t i = 1; i <= kChannelNum; i++)
  {
    FML_Servo_SetSingleChMin(i);
  }
}

/**
 *******************************************************************************
 * @brief     Set single servo to a special angle
 * @param     const uint8_t index: channel index to set
 * @param     const float target: angle target (degree)
 * @param     const float range: angle range of the servo (degree)
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Servo_SetSingleAngle(const uint8_t index, const float target, const float range)
{
  if (target > range)
    return;

  int cmd = target / range * (kServoMaxPulse - kServoMinPulse) + kServoMinPulse;

  switch (index)
  {
    case 1U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH1, cmd);
      break;
    case 2U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH2, cmd);
      break;
    case 3U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH3, cmd);
      break;
    case 4U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH4, cmd);
      break;
    case 5U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH1, cmd);
      break;
    case 6U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH2, cmd);
      break;
    case 7U:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM2, HTIM_PWM_CH3, cmd);
      break;
    default:
      __HAL_TIM_SET_COMPARE(&HTIM_PWM1, HTIM_PWM_CH1, cmd);
      break;
  }
}
