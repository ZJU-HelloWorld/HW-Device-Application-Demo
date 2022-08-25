/**
 *******************************************************************************
 * @file      : fml_rc.c/h
 * @brief     : Remote Control functional module
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-01-29      not wwy         1. DMA rcv
 *  V2.0        2022-02-11      Xue Donglai     1. Refactored
 *                                              2. Using HAL
 *  V2.1        2022-08-02      Xue Donglai     1. Revised
 *******************************************************************************
 * @attention : if we have a pointer MouseKbEvent_t* ptr,
 *  use `ptr->duration_u.duration_single.A` to get pressed duration of key `A`;
 *  use `ptr->duration_u.duration_single.ms_l` to get pressed duration of left button;
 *    p.s. duration is in ms (ticks);
 *  use `ptr->event_u.event_single.A` to get event of key `A`.
 *  use `ptr->event_u.event_single.ms_l` to get event of left button;
 *    arg: IDLE(0x00), PRESSED(0x01), HOLD(0x02), RELEASED(0x03)
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_rc.h"
/* Private types -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define DBUS_RX_BUF_LEN 18U
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile uint8_t dbus_rx_buf[DBUS_RX_BUF_LEN];
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *******************************************************************************
 * @brief     Init RC module based on DBUS protocal, uart DMA rcving
 * @param     None
 * @retval    None
 * @note      Remote Controller or Mouse & Keyboard
 *******************************************************************************
 */
void FML_Rc_Init(void)
{
  memset((uint8_t*)dbus_rx_buf, 0, DBUS_RX_BUF_LEN);
  HAL_UART_Receive_DMA(&HUART_DBUS_RC, (uint8_t*)dbus_rx_buf, DBUS_RX_BUF_LEN);
}

/**
 *******************************************************************************
 * @brief     if error occurs reset data buf and transmit
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Rc_DbusReset(void)
{
  HAL_UART_Abort(&HUART_DBUS_RC);
  memset((uint8_t*)dbus_rx_buf, 0, DBUS_RX_BUF_LEN);
  HAL_UART_Receive_DMA(&HUART_DBUS_RC, (uint8_t*)dbus_rx_buf, DBUS_RX_BUF_LEN);
}

/**
 *******************************************************************************
 * @brief     process the raw rx data to get useful data
 * @param     RcData_t *rc_data: rc data struct to be modified
 * @retval    Dvc_StatusTypeDef: status
 * @retval    RcData_t *rc_data
 * @note      plz call this func in HAL_UART_RxCpltCallback
 *******************************************************************************
 */
Dvc_StatusTypeDef FML_Rc_RxDataHandler(RcData_t* rc_data)
{
  if (NULL == rc_data)
    return DVC_DATA_ERROR;

  Dvc_StatusTypeDef status = DVC_OK;
  /* prevent being modified unexpectedly */
  uint8_t local_dbus_buf[DBUS_RX_BUF_LEN] = {0};
  memcpy(local_dbus_buf, (uint8_t*)dbus_rx_buf, sizeof(dbus_rx_buf));

  rc_data->ch1 = (local_dbus_buf[0] | local_dbus_buf[1] << 8) & 0x07FF;
  rc_data->ch1 -= RC_CH_OFFSET;
  rc_data->ch2 = (local_dbus_buf[1] >> 3 | local_dbus_buf[2] << 5) & 0x07FF;
  rc_data->ch2 -= RC_CH_OFFSET;
  rc_data->ch3 = (local_dbus_buf[2] >> 6 | local_dbus_buf[3] << 2 | local_dbus_buf[4] << 10) & 0x07FF;
  rc_data->ch3 -= RC_CH_OFFSET;
  rc_data->ch4 = (local_dbus_buf[4] >> 1 | local_dbus_buf[5] << 7) & 0x07FF;
  rc_data->ch4 -= RC_CH_OFFSET;

  rc_data->sw1 = ((local_dbus_buf[5] >> 4) & 0x000C) >> 2;
  rc_data->sw2 = (local_dbus_buf[5] >> 4) & 0x0003;

  rc_data->mouse.x = local_dbus_buf[6] | (local_dbus_buf[7] << 8);
  rc_data->mouse.y = local_dbus_buf[8] | (local_dbus_buf[9] << 8);
  rc_data->mouse.z = local_dbus_buf[10] | (local_dbus_buf[11] << 8);

  rc_data->mouse.l = local_dbus_buf[12];
  rc_data->mouse.r = local_dbus_buf[13];

  rc_data->kb.key_code = local_dbus_buf[14] | local_dbus_buf[15] << 8;

  /* Wheel at the top left of DT7 */
  rc_data->ch5 = local_dbus_buf[16] | local_dbus_buf[17] << 8;
  rc_data->ch5 -= RC_CH_OFFSET;

  if (abs(rc_data->ch1) > RC_CH_RANGE ||
      abs(rc_data->ch2) > RC_CH_RANGE ||
      abs(rc_data->ch3) > RC_CH_RANGE ||
      abs(rc_data->ch4) > RC_CH_RANGE ||
      rc_data->sw1 == 0 ||
      rc_data->sw2 == 0 ||
      abs(rc_data->ch5) > RC_CH_RANGE)
  {
    status = DVC_DATA_ERROR;
  }
  else
  {
    rc_data->RH    = (float)rc_data->ch1 / RC_CH_RANGE;
    rc_data->RV    = (float)rc_data->ch2 / RC_CH_RANGE;
    rc_data->LH    = (float)rc_data->ch3 / RC_CH_RANGE;
    rc_data->LV    = (float)rc_data->ch4 / RC_CH_RANGE;
    rc_data->WHEEL = (float)rc_data->ch5 / RC_CH_RANGE;
  }

  return status;
}

/**
 *******************************************************************************
 * @brief     update mouse and keyboard event through updated data and HAL_GetTick
 * @param     const RcData_t* last_rc_data
 * @param     const RcData_t* rc_data
 * @param     MouseKbEvent_t* event
 * @retval    MouseKbEvent_t* event
 * @note      None
 *******************************************************************************
 */
void FML_Rc_GetMouseKbEvent(const RcData_t* last_rc_data, const RcData_t* rc_data,
                            MouseKbEvent_t* event)
{
  uint64_t msk;

  /* mouse l */
  msk = !last_rc_data->mouse.l && rc_data->mouse.l   ? PRESSED
        : last_rc_data->mouse.l && rc_data->mouse.l  ? HOLD
        : last_rc_data->mouse.l && !rc_data->mouse.l ? RELEASED
                                                     : IDLE;
  event->event_u.event &= ~0x03;
  event->event_u.event |= msk;

  /* mouse r */
  msk = !last_rc_data->mouse.r && rc_data->mouse.r   ? PRESSED
        : last_rc_data->mouse.r && rc_data->mouse.r  ? HOLD
        : last_rc_data->mouse.r && !rc_data->mouse.r ? RELEASED
                                                     : IDLE;
  event->event_u.event &= ~(0x03 << 2);
  event->event_u.event |= msk << 2;

  /* key code */
  for (uint8_t i = 0; i < 18; i++)
  {
    /* for keys */
    if (i > 1)
    {
      uint16_t last_key = last_rc_data->kb.key_code & (0x01 << (i - 2));
      uint16_t key      = rc_data->kb.key_code & (0x01 << (i - 2));
      msk               = !last_key && key   ? PRESSED
                          : last_key && key  ? HOLD
                          : last_key && !key ? RELEASED
                                             : IDLE;
      event->event_u.event &= ~(0x03 << (i * 2));
      event->event_u.event |= msk << (i * 2);
    }

    /* for mouse and keys, update hold duration */
    switch ((event->event_u.event & ((uint64_t)0x03 << (i * 2))) >> (i * 2))
    {
      case PRESSED:
        event->pressed_tick[i] = HAL_GetTick();
        break;
      case HOLD:
        event->duration_u.duration[i] = HAL_GetTick() - event->pressed_tick[i];
        break;
      default:
        event->pressed_tick[i] = event->duration_u.duration[i] = 0;
        break;
    }
  }
}