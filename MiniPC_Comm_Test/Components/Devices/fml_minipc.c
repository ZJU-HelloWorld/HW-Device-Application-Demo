/**
 *******************************************************************************
 * @file      : fml_minipc.c/h
 * @brief     : Communicate with MiniPC through UART
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        Null            Senior          1. Done
 *  V2.0        2022-08-10      xdl             1. Refactored
 *******************************************************************************
 * @attention : User can modify tx/rx data length in fml_minipc.h
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_minipc.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if USE_MINIPC_UART
#if USE_MINIPC_UART_RX_DMA
static volatile uint8_t uart_rx_buf[MINIPC_RX_BUF_LEN];
static volatile uint8_t uart_tx_buf[MINIPC_TX_BUF_LEN];
#elif USE_MINIPC_UART_RX_IT
static volatile uint8_t uart_rx_buf = 0;
static volatile uint8_t uart_tx_buf[MINIPC_TX_BUF_LEN];
#endif
#elif USE_MINIPC_USB
static volatile uint8_t usb_tx_buf[MINIPC_TX_BUF_LEN];
/* External variables --------------------------------------------------------*/
extern volatile uint8_t  usb_rx_buf[APP_RX_DATA_SIZE];
extern volatile uint32_t usb_rx_len;
#endif
/* Private function prototypes -----------------------------------------------*/

#if USE_MINIPC_UART
/**
 *******************************************************************************
 * @brief     Init MiniPC communication based on UART, DMA or IT
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Minipc_Init(void)
{
#if USE_MINIPC_UART_RX_DMA
  memset((uint8_t*)uart_rx_buf, 0, MINIPC_RX_BUF_LEN);
  HAL_UART_Receive_DMA(&HUART_MINIPC, (uint8_t*)uart_rx_buf, MINIPC_RX_BUF_LEN);
#elif USE_MINIPC_UART_RX_IT
  uart_rx_buf = 0;
  HAL_UART_Receive_IT(&HUART_MINIPC, (uint8_t*)&uart_rx_buf, 1);
#endif
}

/**
 *******************************************************************************
 * @brief     if error occurs reset data buf and transmit
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Minipc_RxReset(void)
{
#if USE_MINIPC_UART_RX_DMA
  HAL_UART_DMAStop(&HUART_MINIPC);
  memset((uint8_t*)uart_rx_buf, 0, MINIPC_RX_BUF_LEN);
  HAL_UART_Receive_DMA(&HUART_MINIPC, (uint8_t*)uart_rx_buf, MINIPC_RX_BUF_LEN);
#elif USE_MINIPC_UART_RX_IT

#endif
}
#endif

/**
 *******************************************************************************
 * @brief     MiniPC data receiving handler
 * @param     MinipcData_t* data
 * @retval    Dvc_StatusTypeDef status
 * @retval    MinipcData_t* data
 * @note      if finish receiving a frame, set data->rx_update_flag to 1.
 *******************************************************************************
 */
Dvc_StatusTypeDef FML_Minipc_RxDataHandler(MinipcData_t* data)
{
  if (NULL == data)
    return DVC_DATA_ERROR;

  Dvc_StatusTypeDef status = DVC_OK;
#if USE_MINIPC_UART
#if USE_MINIPC_UART_RX_DMA
  if (MINIPC_RxHEAD1 == uart_rx_buf[0] &&
      MINIPC_RxHEAD2 == uart_rx_buf[1] &&
      MINIPC_RxHEAD3 == uart_rx_buf[2] &&
      MINIPC_RxSTOP == uart_rx_buf[MINIPC_RX_BUF_LEN - 1])
  {
    memcpy(data->rx_data_buf, (uint8_t*)&uart_rx_buf[3], MINIPC_RX_DATA_BUF_LEN);

    data->rx_frame_tick      = HAL_GetTick();
    data->frame_interval     = data->rx_frame_tick - data->last_rx_frame_tick;
    data->last_rx_frame_tick = data->rx_frame_tick;

    data->rx_update_flag = 1U;
  }
  else
  {
    status = DVC_DATA_ERROR;
  }
#elif USE_MINIPC_UART_RX_IT
  uint8_t minipc_rcv_data = uart_rx_buf;

  switch (data->rx_fsm.state)
  {
    case RCV_STOP:
    {
      if (MINIPC_RxHEAD1 == minipc_rcv_data)
      {
        data->rx_fsm.head_cnt++;
        data->rx_fsm.state = HEAD_RCVING;
      }
      else
      {
        RESET_RX_IT_FSM(data->rx_fsm);
      }
      break;
    }
    case HEAD_RCVING:
    {
      if (1U == data->rx_fsm.head_cnt &&
          MINIPC_RxHEAD2 == minipc_rcv_data)
      {
        data->rx_fsm.head_cnt++;
        data->rx_fsm.state = HEAD_RCVING;
      }
      else if (2U == data->rx_fsm.head_cnt &&
               MINIPC_RxHEAD3 == minipc_rcv_data)
      {
        data->rx_fsm.head_cnt++;
        data->rx_fsm.state = DATA_RCVING;
      }
      else
      {
        RESET_RX_IT_FSM(data->rx_fsm);
        status = DVC_DATA_ERROR;
      }
      break;
    }
    case DATA_RCVING:
    {
      if (data->rx_fsm.data_cnt < MINIPC_RX_DATA_BUF_LEN - 1)
      {
        data->rx_data_buf[data->rx_fsm.data_cnt++] = minipc_rcv_data;
        data->rx_fsm.state                         = DATA_RCVING;
      }
      else if (data->rx_fsm.data_cnt == MINIPC_RX_DATA_BUF_LEN - 1)
      {
        data->rx_data_buf[data->rx_fsm.data_cnt++] = minipc_rcv_data;
        data->rx_fsm.state                         = DATA_STOP;
      }
      else
      {
        RESET_RX_IT_FSM(data->rx_fsm);
      }
      break;
    }
    case DATA_STOP:
    {
      if (MINIPC_RxSTOP == minipc_rcv_data)
      {
        data->rx_frame_tick      = HAL_GetTick();
        data->frame_interval     = data->rx_frame_tick - data->last_rx_frame_tick;
        data->last_rx_frame_tick = data->rx_frame_tick;

        data->rx_update_flag = 1U;
      }
      else
      {
        RESET_RX_IT_FSM(data->rx_fsm);
        status = DVC_DATA_ERROR;
      }
      break;
    }
    default:
    {
      RESET_RX_IT_FSM(data->rx_fsm);
    }
  }
#endif
#elif USE_MINIPC_USB
  if (MINIPC_RX_BUF_LEN == usb_rx_len &&
      MINIPC_RxHEAD1 == usb_rx_buf[0] &&
      MINIPC_RxHEAD2 == usb_rx_buf[1] &&
      MINIPC_RxHEAD3 == usb_rx_buf[2] &&
      MINIPC_RxSTOP == usb_rx_buf[MINIPC_RX_BUF_LEN - 1])
  {
    memcpy(data->rx_data_buf, (uint8_t*)&usb_rx_buf[3], MINIPC_RX_DATA_BUF_LEN);

    data->rx_frame_tick      = HAL_GetTick();
    data->frame_interval     = data->rx_frame_tick - data->last_rx_frame_tick;
    data->last_rx_frame_tick = data->rx_frame_tick;

    data->rx_update_flag = 1U;
  }
  else
  {
    status = DVC_DATA_ERROR;
  }
#endif
  return status;
}

/**
 *******************************************************************************
 * @brief     transmit data to minipc, UART or USB
 * @param     const uint8_t* data
 * @param     const uint16_t len
 * @retval    Dvc_StatusTypeDef: status
 * @note      None
 *******************************************************************************
 */
Dvc_StatusTypeDef FML_Minipc_TxData(const uint8_t* data, const uint16_t len)
{
  if (NULL == data)
    return DVC_TX_ERROR;

  Dvc_StatusTypeDef status = DVC_OK;
#if USE_MINIPC_UART
  uint16_t tx_len = len + 2;
  uart_tx_buf[0]  = MINIPC_TxHEAD1;
  uart_tx_buf[1]  = MINIPC_TxHEAD2;
  memcpy((uint8_t*)&uart_tx_buf[2], data, len);
#if USE_MINIPC_UART_TX_DMA
  if (HAL_UART_Transmit_DMA(&HUART_MINIPC, (uint8_t*)uart_tx_buf, tx_len) != HAL_OK)
  {
    status = DVC_TX_ERROR;
  }
#elif USE_MINIPC_UART_TX_IT
  if (HAL_UART_Transmit_IT(&HUART_MINIPC, (uint8_t*)uart_tx_buf, tx_len) != HAL_OK)
  {
    status = DVC_TX_ERROR;
  }
#endif
#elif USE_MINIPC_USB
  uint16_t tx_len = len + 2;
  usb_tx_buf[0]   = MINIPC_TxHEAD1;
  usb_tx_buf[1]   = MINIPC_TxHEAD2;
  memcpy((uint8_t*)&usb_tx_buf[2], data, len);
  if (CDC_Transmit_FS((uint8_t*)usb_tx_buf, tx_len) != USBD_OK)
  {
    status = DVC_TX_ERROR;
  }
#endif
  return status;
}
