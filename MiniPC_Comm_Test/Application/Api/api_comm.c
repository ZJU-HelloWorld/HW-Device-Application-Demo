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
/* Includes ------------------------------------------------------------------*/
#include "api_comm.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Init minipc communication data
 * @param     CommInfo_t* info
 * @retval    CommInfo_t* info
 * @note      None
 *******************************************************************************
 */
void API_Comm_Minipc_Init(CommInfo_t* info)
{
  if (NULL == info)
    return;

#if IS_STEERABLE_STANDARD
  info->minipc_vars.rx.auto_fire_cmd = STOP_FIRE;
  info->minipc_vars.rx.auto_pitch    = 0.0f;
  info->minipc_vars.rx.auto_yaw      = 0.0f;
  info->minipc_vars.rx.enemy_color   = UNSET;
  info->minipc_vars.rx.target        = NO_TAR;

  info->minipc_vars.tx.aim_mode    = AUTO_AIM_CLOSE;
  info->minipc_vars.tx.bullet_spd  = 15.0f;
  info->minipc_vars.tx.minipc_mode = MINIPC_ON;
  info->minipc_vars.tx.pitch       = 0.0f;
  info->minipc_vars.tx.yaw         = 0.0f;
  info->minipc_vars.tx.roll        = 0.0f;
  info->minipc_vars.tx.enemy_color = UNSET;

  info->minipc_data.frame_interval     = 0U;
  info->minipc_data.last_rx_frame_tick = 0U;
  info->minipc_data.rx_frame_tick      = 0U;
  info->minipc_data.rx_update_flag     = 0U;
#endif

  memset(info->minipc_data.rx_data_buf, 0, MINIPC_RX_DATA_BUF_LEN);
  memset(info->minipc_data.tx_data_buf, 0, MINIPC_TX_DATA_BUF_LEN);

#if (USE_MINIPC_UART && USE_MINIPC_UART_RX_IT)
  RESET_RX_IT_FSM(info->minipc_data.rx_fsm);
#endif
}

/**
 *******************************************************************************
 * @brief     handle data rx from minipc
 * @param     CommInfo_t* info
 * @retval    CommInfo_t* info
 * @note      None
 *******************************************************************************
 */
void API_Comm_UpdateMinipcFrameInfo(CommInfo_t* info)
{
  if (NULL == info)
    return;

  uint8_t* raw_data = &info->minipc_data.rx_data_buf[0];

#if IS_STEERABLE_STANDARD
  info->minipc_vars.rx.auto_pitch = (int16_t)((raw_data[0] << 8) | raw_data[1]);
  info->minipc_vars.rx.auto_pitch /= 100.0f;
  info->minipc_vars.rx.auto_yaw = (int16_t)((raw_data[2] << 8) | raw_data[3]);
  info->minipc_vars.rx.auto_yaw /= 100.0f;
  info->minipc_vars.rx.auto_fire_cmd = (uint8_t)(raw_data[4] & 0x01);
  info->minipc_vars.rx.enemy_color   = (uint8_t)((raw_data[4] & 0b00001100) >> 2);
  info->minipc_vars.rx.target        = (uint8_t)((raw_data[4] & 0xF0) >> 4);
#endif
}

/**
 *******************************************************************************
 * @brief     Generate frame sent to MiniPC and cmd tx
 * @param     CommInfo_t* info
 * @retval    Api_StatusTypeDef status
 * @retval    CommInfo_t* info
 * @note      None
 *******************************************************************************
 */
Api_StatusTypeDef API_Comm_SendMinipcFrameInfo(CommInfo_t* info)
{
  if (NULL == info)
    return API_DATA_ERROR;

  Api_StatusTypeDef status = API_OK;
#if IS_STEERABLE_STANDARD
  uint8_t      tmp_mode_code;
  int16_t      tmp_spd   = info->minipc_vars.tx.bullet_spd * 100;
  int16_t      tmp_roll  = info->minipc_vars.tx.roll * 100;
  int16_t      tmp_pitch = info->minipc_vars.tx.pitch * 100;
  int16_t      tmp_yaw   = info->minipc_vars.tx.yaw * 100;
  EnemyColor_e tmp_color = info->minipc_vars.tx.enemy_color;

  switch (info->minipc_vars.tx.aim_mode)
  {
    case AUTO_AIM_CLOSE:
      tmp_mode_code = 0x00;
      break;
    case PREDICT:
    case LOCK_PITCH:
      tmp_mode_code = 0x01;
      break;
    case ANTI_TWIST:
      tmp_mode_code = 0x02;
      break;
    case SMALL_BUFF:
      tmp_mode_code = 0x03;
      break;
    case BIG_BUFF:
      tmp_mode_code = 0x04;
      break;
    case ANTI_BALLANCED_STANDARD_PREDICT:
      tmp_mode_code = 0x05;
      break;
    case ANTI_BALLANCED_STANDARD_TWIST:
      tmp_mode_code = 0x06;
      break;
    default:
      tmp_mode_code = 0x00;
  }
  /* close MiniPC */
  if (MINIPC_OFF == info->minipc_vars.tx.minipc_mode)
  {
    tmp_mode_code = 0x7f;
  }
  /* Generate tx frame */
  info->minipc_data.tx_data_buf[0]  = (uint8_t)tmp_mode_code;
  info->minipc_data.tx_data_buf[1]  = (uint8_t)(tmp_spd >> 8);
  info->minipc_data.tx_data_buf[2]  = (uint8_t)tmp_spd;
  info->minipc_data.tx_data_buf[3]  = 0x9f;
  info->minipc_data.tx_data_buf[4]  = (uint8_t)(tmp_roll >> 8);
  info->minipc_data.tx_data_buf[5]  = (uint8_t)tmp_roll;
  info->minipc_data.tx_data_buf[6]  = (uint8_t)(tmp_pitch >> 8);
  info->minipc_data.tx_data_buf[7]  = (uint8_t)tmp_pitch;
  info->minipc_data.tx_data_buf[8]  = (uint8_t)(tmp_yaw >> 8);
  info->minipc_data.tx_data_buf[9]  = (uint8_t)tmp_yaw;
  info->minipc_data.tx_data_buf[10] = (uint8_t)tmp_color;
#endif

  if (DVC_OK != FML_Minipc_TxData((uint8_t*)info->minipc_data.tx_data_buf, MINIPC_TX_DATA_BUF_LEN))
  {
    status = API_DATA_ERROR;
  }

  return status;
}
