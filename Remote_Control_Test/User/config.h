/**
 *******************************************************************************
 * @file      : config.h
 * @brief     : Board related config for devices & conditional compiling settings
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-16      Xue Donglai     1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H_
#define __CONFIG_H_
/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "usart.h"
#include <stdlib.h>
/* Exported types ------------------------------------------------------------*/
typedef uint8_t bool_t;
typedef enum _dvc_status_type_def
{
  DVC_OK,
  DVC_RX_ERROR,
  DVC_TX_ERROR,
  DVC_DATA_ERROR
} Dvc_StatusTypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Ctrl Define ------------------------------- */
#define CTRL_FREQ      1000.0f
#define HALF_CTRL_FREQ (CTRL_FREQ / 2)
/* Devices ------------------------------------*/
#define HTIM_CONTROL   htim6
#define HUART_DBUS_RC  huart3
/* Conditional Compiling ----------------------*/
/* Module Used Define */
#define USE_RC         1
/* Debug Settings -----------------------------*/
#define DEBUG_ON       0
#define DEBUG_OFF      (!DEBUG_ON)
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
#endif

/**
 * ------------------------------- Templates -----------------------------------
 */
/* .c template */
/**
 *******************************************************************************
 * @file      : xx.c/h
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-02-dd      Xue Donglai     1.
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* .h template */
/**
 *******************************************************************************
 * @file      : xx.c/h
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-02-dd      Xue Donglai     1.
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __XX_H_
#define __XX_H_
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
#endif

/* function header template */
/**
 *******************************************************************************
 * @brief     :
 * @param     :
 * @retval    :
 * @note      :
 *******************************************************************************
 */
