/**
 *******************************************************************************
 * @file      : fml_pwrsrc.c/h
 * @brief     : Battery remaning power & supercap remaining power detect
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-19      xdl             1. Done
 *******************************************************************************
 * @attention : Modified from bsp_adc.c/h (C) COPYRIGHT 2019 DJI
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FML_PWRSRC_H
#define __FML_PWRSRC_H
/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "config.h"
/* Exported types ------------------------------------------------------------*/
typedef enum _adc_src_e
{
  ADC_INTERNAL,
  ADC_EXTERNAL,
} AdcSrc_e;
typedef struct _pwrsrc_data_t
{
  float    volt_vrefint_proportion;
  uint16_t battery_perc;
} PwrsrcData_t;
/* Exported macro ------------------------------------------------------------*/
#ifndef VOTAGE_DROP
#define VOTAGE_DROP 0.0f
#endif
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void  FML_Pwrsrc_Init(void);
float FML_Pwrsrc_GetVrefintProportion(void);
float FML_Pwrsrc_GetBatteryVotage(const float proportion);

#endif /* __FML_PWRSRC_H */