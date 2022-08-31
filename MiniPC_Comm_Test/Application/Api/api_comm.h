/**
 *******************************************************************************
 * @file      : api_comm.c/h
 * @brief     : Communicate with MiniPC, Super Cap Ctrl, et al.
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2022-08-17      Xue Donglai     1. Done
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_COMM_H_
#define __API_COMM_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "fml_minipc.h"
/* Exported macro ------------------------------------------------------------*/
#ifndef CTRL_FREQ
#define CTRL_FREQ 1000.0f
#endif
#ifndef MINIPC_SEND_FREQ
#define MINIPC_SEND_FREQ 500.0f
#endif
#define IS_TO_SEND_MINIPC(tick) \
  ((tick) % (uint16_t)(CTRL_FREQ / MINIPC_SEND_FREQ) == 0)
/* Exported types ------------------------------------------------------------*/
typedef enum _aim_type
{
  SENTRY     = 0x00,
  HERO       = 0x01,
  ENGINEER   = 0x02,
  STANDARD3  = 0x03,
  STANDARD4  = 0x04,
  STANDARD5  = 0x05,
  OUTPOST    = 0x06,
  BASE_SMALL = 0x07,
  BASE_BIG   = 0x07,
  NO_TAR     = 0x08,
} AimType_e;

typedef struct _minipc_comm_info_t
{
#if IS_STEERABLE_STANDARD
  struct
  {
    struct
    {
      float        auto_yaw;
      float        auto_pitch;
      CtrlState_e  auto_fire_cmd;
      EnemyColor_e enemy_color;
      AimType_e    target;
    } rx;
    struct
    {
      AutoAimMode_e aim_mode;
      MinipcMode_e  minipc_mode;
      float         bullet_spd;
      float         roll;
      float         pitch;
      float         yaw;
      EnemyColor_e  enemy_color;
    } tx;
  } minipc_vars;
#endif
  /* raw data */
  MinipcData_t minipc_data;
} MinipcCommInfo_t;

typedef struct _comm_info_t
{
  /* mutex */
  bool_t           mutex;
  MinipcCommInfo_t minipc_comm_info;
} CommInfo_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void              API_Comm_Minipc_Init(MinipcCommInfo_t* info);
void              API_Comm_UpdateMinipcFrameInfo(MinipcCommInfo_t* info);
Api_StatusTypeDef API_Comm_SendMinipcFrameInfo(MinipcCommInfo_t* info);

#endif /* __API_COMM_H_ */
