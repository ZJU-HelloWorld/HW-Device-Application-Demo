/**
 *******************************************************************************
 * @file      : config.h
 * @brief     : Board related config for devices & conditional compiling settings
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-07-16      xdl             1. Done
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
/* Exported types ------------------------------------------------------------*/
typedef uint8_t bool_t;
/* Component Mode Enum ------------------------*/
typedef enum _dvc_status_type_def
{
  DVC_OK,
  DVC_RX_ERROR,
  DVC_TX_ERROR,
  DVC_DATA_ERROR
} Dvc_StatusTypeDef;

typedef enum _api_status_type_def
{
  API_OK,
  API_CONNECT_ERROR,
  API_DATA_ERROR
} Api_StatusTypeDef;

typedef enum _ctrl_state_e
{
  FIRE      = 1U,
  STOP_FIRE = 0U,
} CtrlState_e;

/* Priority: lowest 0 */
typedef enum _auto_aim_mode_e
{
  AUTO_AIM_CLOSE = 0U,
  LOCK_PITCH,
  ANTI_BALLANCED_STANDARD_PREDICT,
  ANTI_BALLANCED_STANDARD_TWIST,
  BIG_BUFF,
  SMALL_BUFF,
  ANTI_TWIST,
  PREDICT,

  AUTO_AIM_MODE_NUM
} AutoAimMode_e;

typedef enum _minipc_mode_e
{
  MINIPC_OFF = 0U,
  MINIPC_ON,
} MinipcMode_e;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define IS_STEERABLE_STANDARD  1
/* Ctrl Define ------------------------------- */
#define CTRL_FREQ              1000.0f
#define HALF_CTRL_FREQ         (CTRL_FREQ / 2)
#define MINIPC_SEND_FREQ       500.0f
/* Devices ------------------------------------*/
#define HTIM_CONTROL           htim6
#define HTIM_USB_RX_IT         htim3
#define HUART_MINIPC           huart1
/* Conditional Compiling ----------------------*/
/* Module Used Define */
#define USE_MINIPC_UART        0
#define USE_MINIPC_UART_RX_IT  0
#define USE_MINIPC_UART_RX_DMA (!USE_MINIPC_UART_RX_IT)
#define USE_MINIPC_UART_TX_IT  0
#define USE_MINIPC_UART_TX_DMA (!USE_MINIPC_UART_TX_IT)
#define USE_MINIPC_USB         (!USE_MINIPC_UART)
/* Debug Settings -----------------------------*/
#define DEBUG_ON               0
#define DEBUG_OFF              (!DEBUG_ON)
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
 *  V1.0        2022-02-dd      xdl             1.
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
 *  V1.0        2022-02-dd      xdl             1.
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
