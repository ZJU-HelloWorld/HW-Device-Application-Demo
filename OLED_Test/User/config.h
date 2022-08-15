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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include <arm_math.h>
#include <math.h>
/* Exported types ------------------------------------------------------------*/
typedef uint8_t bool_t;
typedef enum _device_list_e
{
  DEVICE_RC = 0,
  DEVICE_BOARD_COMM,
  DEVICE_REFEREE,
  DEVICE_MINIPC,

  DEVICE_FRIC_MOTOR,
  DEVICE_FEED_MOTOR,
  DEVICE_GIMBAL_YAW_MOTOR,
  DEVICE_GIMBAL_PITCH_MOTOR,

  DEVICE_WHEEL_MOTOR_F,
  DEVICE_WHEEL_MOTOR_B,
  DEVICE_STEER_MOTOR_F,
  DEVICE_STEER_MOTOR_B,
  // DEVICE_...
  DEVICE_LIST_LEN
} DeviceList_e;

typedef enum _device_state_e
{
  DEVICE_OK = 0U,
  DEVICE_ERROR,
} DeviceState_e;

typedef enum _data_src_e
{
  USER_SET = 0,
  AUTO_GET
} DataSrc_e;
/* Exported macro ------------------------------------------------------------*/
#define IS_STEERABLE_STANDARD 1

/* Ctrl Define ------------------------------- */
#define CTRL_FREQ             1000.0f
#define HALF_CTRL_FREQ        (CTRL_FREQ / 2)
#define OLED_CMD_FREQ         5.0f
/* Devices ------------------------------------*/
#define HTIM_CONTROL          htim6
#define HI2C_OLED             hi2c2
#define VOTAGE_DROP           0.0f
#define HADC_INT              hadc1
#define HADC_EXT              hadc3

#if IS_STEERABLE_STANDARD
#define SUPERCAP_FULL_VOTAGE       24.8f
#define SUPERCAP_MIN_USABLE_VOTAGE 16.0f
#endif

/* Conditional Compiling ----------------------*/
/* Module Used Define */
#define USE_OLED  1
/* Debug Settings -----------------------------*/
#define DEBUG_ON  0
#define DEBUG_OFF (!DEBUG_ON)
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
#endif /* __CONFIG_H_ */

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
