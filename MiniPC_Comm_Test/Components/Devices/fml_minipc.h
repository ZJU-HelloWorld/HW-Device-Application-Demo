/**
 *******************************************************************************
 * @file      : fml_minipc.c/h
 * @brief     : Communicate with MiniPC through UART
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        Null            Senior          1. Done
 *  V2.0        2022-08-10      Xue Donglai     1. Refactored
 *******************************************************************************
 * @attention : User can modify tx/rx data length in fml_minipc.h
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FML_MINIPC_H_
#define __FML_MINIPC_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "usart.h"
#include "usbd_cdc_if.h"
/* Exported types ------------------------------------------------------------*/
/* User Modification Begin --------------------------- */
typedef enum _minipc_data_len_e
{
  MINIPC_TX_BUF_LEN      = 13U,
  MINIPC_TX_DATA_BUF_LEN = 11U,
  MINIPC_RX_BUF_LEN      = 9U,
  MINIPC_RX_DATA_BUF_LEN = 5U,
} MinipcDataLen_e;
/* User Modification End ----------------------------- */
typedef enum _minipc_head_id_e
{
  MINIPC_RxHEAD1 = 0xAA,
  MINIPC_RxHEAD2 = 0xBB,
  MINIPC_RxHEAD3 = 0xCC,
  MINIPC_RxSTOP  = 0xFF,
  MINIPC_TxHEAD1 = 0x3F,
  MINIPC_TxHEAD2 = 0x4F,
  MINIPC_TxCHECK = 0x9F,
} MinipcHeadID_e;

typedef enum _minipc_rx_state_e
{
  HEAD_RCVING,
  DATA_RCVING,
  DATA_STOP,
  RCV_STOP,
} MinipcRxState_e;

typedef struct _minipc_rx_fsm_t
{
  MinipcRxState_e state;
  uint8_t         head_cnt;
  uint8_t         data_cnt;
} MinipcRxFsm_t;

typedef struct _minipc_data_t
{
  /* Rx Related */
  uint8_t rx_data_buf[MINIPC_RX_DATA_BUF_LEN];
  bool_t  rx_update_flag;

  uint32_t rx_frame_tick;
  uint32_t last_rx_frame_tick;
  uint32_t frame_interval;
#if (USE_MINIPC_UART && USE_MINIPC_UART_RX_IT)
  MinipcRxFsm_t rx_fsm;
#endif
  /* Tx Data */
  uint8_t tx_data_buf[MINIPC_TX_DATA_BUF_LEN];
} MinipcData_t;

typedef enum _enemy_color_e
{
  UNSET = 0U,
  RED   = 1U,
  BLUE  = 2U,
} EnemyColor_e;
/* Exported macro ------------------------------------------------------------*/
#define RESET_RX_IT_FSM(fsm)   \
  {                            \
    (fsm).state    = RCV_STOP; \
    (fsm).head_cnt = 0U;       \
    (fsm).data_cnt = 0U;       \
  }
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
#if USE_MINIPC_UART
void FML_Minipc_Init(void);
void FML_Minipc_RxReset(void);
#elif USE_MINIPC_USB

#endif
Dvc_StatusTypeDef FML_Minipc_RxDataHandler(MinipcData_t* data);
Dvc_StatusTypeDef FML_Minipc_TxData(const uint8_t* data, const uint16_t len);

#endif /* __FML_MINIPC_H_ */