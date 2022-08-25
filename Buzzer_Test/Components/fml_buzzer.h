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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FML_BUZZER_H_
#define __FML_BUZZER_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "tim.h"
/* Exported types ------------------------------------------------------------*/
typedef enum _tone_e
{
  C3_ = 48U,
  D3b,
  D3_,
  E3b,
  E3_,
  F3_,
  G3b,
  G3_,
  A3b,
  A3_,
  B3b,
  B3_,

  C4_,
  D4b,
  D4_,
  E4b,
  E4_,
  F4_,
  G4b,
  G4_,
  A4b,
  A4_ = 69U, // 440HZ
  B4b,
  B4_,

  C5_,
  D5b,
  D5_,
  E5b,
  E5_,
  F5_,
  G5b,
  G5_,
  A5b,
  A5_,
  B5b,
  B5_,

  C6_,
  D6b,
  D6_,
  E6b,
  E6_,
  F6_,
  G6b,
  G6_,
  A6b,
  A6_,
  B6b,
  B6_,

  RST
} Tone_e;
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void FML_Buzzer_Init(void);
void FML_Buzzer_SetTone(Tone_e tone);

#endif /* __FML_BUZZER_H_ */