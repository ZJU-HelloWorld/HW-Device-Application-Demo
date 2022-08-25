/**
 *******************************************************************************
 * @file      : fml_pwrsrc.c/h
 * @brief     : Battery remaning power & supercap remaining power detect
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-19      Xue Donglai     1. Done
 *******************************************************************************
 * @attention : Using DMA, please realize `HAL_ADC_ConvCpltCallback` in system.c
 *              to call data processing functions after conversion finish
 *              Modified from bsp_adc.c/h (C) COPYRIGHT 2019 DJI
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_pwrsrc.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
static const float kVRefInternal = 1.2f;
/* Private variables ---------------------------------------------------------*/
volatile static uint16_t int_data_buf;
volatile static uint16_t ext_data_buf[2];
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Init power source sampling
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Pwrsrc_Init(void)
{
  HAL_ADC_Start_DMA(&HADC_EXT, (uint32_t*)&ext_data_buf, 2);
}

/**
 *******************************************************************************
 * @brief     Get internal voltage reference proportion by checking the 1.2V ref source
 * @param     None
 * @retval    float
 * @note      None
 *******************************************************************************
 */
float FML_Pwrsrc_GetVrefintProportion(void)
{
  uint32_t total_int_data = 0;

  for (uint8_t i = 0; i < 50; i++)
  {
    HAL_ADC_Start(&HADC_INT);
    HAL_ADC_PollForConversion(&HADC_INT, 10);
    int_data_buf = HAL_ADC_GetValue(&HADC_INT);
    HAL_ADC_Stop(&HADC_INT);

    total_int_data += int_data_buf;
  }

  return (50.0f * kVRefInternal / total_int_data);
}

/**
 *******************************************************************************
 * @brief     Get battery voltage according to ADC sample and proportion
 * @param     const float proportion
 * @retval    float
 * @note      None
 *******************************************************************************
 */
float FML_Pwrsrc_GetBatteryVotage(const float proportion)
{
  float votage;
  float ratio = (22.0f + 200.0f) / 22.0f; // kOhm
  votage      = (float)ext_data_buf[0] * proportion * ratio + VOTAGE_DROP;

  return votage;
}
