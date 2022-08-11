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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FML_LIMIT_H_
#define __FML_LIMIT_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LIMIT_VAL(data, lmt1, lmt2) \
  {                                 \
    if ((lmt1) <= (lmt2))           \
    {                               \
      if ((data) < (lmt1))          \
      {                             \
        (data) = (lmt1);            \
      }                             \
      else if ((data) > (lmt2))     \
      {                             \
        (data) = (lmt2);            \
      }                             \
    }                               \
    else if ((lmt2) < (lmt1))       \
    {                               \
      if ((data) < (lmt2))          \
      {                             \
        (data) = (lmt2);            \
      }                             \
      else if ((data) > (lmt1))     \
      {                             \
        (data) = (lmt1);            \
      }                             \
    }                               \
  }
#define ACROSS_ZERO_HANDLER(ref, fdb) \
  {                                   \
    if ((ref) - (fdb) >= 180)         \
    {                                 \
      (ref) -= 360;                   \
    }                                 \
    else if ((ref) - (fdb) < -180)    \
    {                                 \
      (ref) += 360;                   \
    }                                 \
  }                                   \
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
bool_t FML_InRange(float val, float bound1, float bound2);

#endif