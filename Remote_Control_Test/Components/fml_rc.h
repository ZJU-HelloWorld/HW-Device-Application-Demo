/**
 *******************************************************************************
 * @file      : fml_rc.c/h
 * @brief     : Remote Control functional module
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2019-01-29      not wwy         1. DMA rcv
 *  V2.0        2022-02-11      xdl             1. Refactored
 *                                              2. Using HAL
 *  V2.1        2022-08-02      xdl             1. Revised
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FML_RC_H_
#define __FML_RC_H_
/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "usart.h"
#include <string.h>
/* Exported types ------------------------------------------------------------*/
typedef enum _mouse_kb_event_type_e
{
  IDLE     = 0x00,
  PRESSED  = 0x01,
  HOLD     = 0x02,
  RELEASED = 0x03
} MouseKbEventType_e;

typedef __PACKED_STRUCT _rc_data_t
{
  /* -1 ~ 1 */
  float LV;
  float LH;
  float RV;
  float RH;
  float WHEEL;

  /* offset(init value) 1024, ch value: -660 ~ 660 */
  int16_t ch1;
  int16_t ch2;
  int16_t ch3;
  int16_t ch4;
  /* switch val: 1 3 2 */
  uint8_t sw1;
  uint8_t sw2;

  struct
  {
    int16_t x;
    int16_t y;
    int16_t z; // useless
    /* press:1 release:0 */
    uint8_t l;
    uint8_t r;
  } mouse;

  union
  {
    uint16_t key_code;
    /*************************************************************************
     * 15   14   13   12   11   10   9   8   7   6     5     4   3   2   1
     * V    C    X    Z    G    F    R   E   Q  CTRL SHIFT   D   A   S   W
     *************************************************************************/
    struct
    {
      uint16_t W     : 1;
      uint16_t S     : 1;
      uint16_t A     : 1;
      uint16_t D     : 1;
      uint16_t SHIFT : 1;
      uint16_t CTRL  : 1;
      uint16_t Q     : 1;
      uint16_t E     : 1;
      uint16_t R     : 1;
      uint16_t F     : 1;
      uint16_t G     : 1;
      uint16_t Z     : 1;
      uint16_t X     : 1;
      uint16_t C     : 1;
      uint16_t V     : 1;
      uint16_t B     : 1;
    } bit;
  } kb;

  /* offset(init val) 1024, down to 660, up to -660 */
  int16_t ch5;
}
RcData_t;

typedef __PACKED_STRUCT _mouse_kb_event_t
{
  union
  {
    uint64_t event;
    struct
    {
      uint8_t ms_l  : 2;
      uint8_t ms_r  : 2;
      uint8_t W     : 2;
      uint8_t S     : 2;
      uint8_t A     : 2;
      uint8_t D     : 2;
      uint8_t SHIFT : 2;
      uint8_t CTRL  : 2;
      uint8_t Q     : 2;
      uint8_t E     : 2;
      uint8_t R     : 2;
      uint8_t F     : 2;
      uint8_t G     : 2;
      uint8_t Z     : 2;
      uint8_t X     : 2;
      uint8_t C     : 2;
      uint8_t V     : 2;
      uint8_t B     : 2;
    } event_single;
  } event_u;

  uint32_t pressed_tick[18];
  union
  {
    uint32_t duration[18];
    struct
    {
      uint32_t ms_l  : 32;
      uint32_t ms_r  : 32;
      uint32_t W     : 32;
      uint32_t S     : 32;
      uint32_t A     : 32;
      uint32_t D     : 32;
      uint32_t SHIFT : 32;
      uint32_t CTRL  : 32;
      uint32_t Q     : 32;
      uint32_t E     : 32;
      uint32_t R     : 32;
      uint32_t F     : 32;
      uint32_t G     : 32;
      uint32_t Z     : 32;
      uint32_t X     : 32;
      uint32_t C     : 32;
      uint32_t V     : 32;
      uint32_t B     : 32;
    } duration_single;
  } duration_u;
}
MouseKbEvent_t;

/* Exported macro ------------------------------------------------------------*/
#define RC_SW_UP     1U
#define RC_SW_MI     3U
#define RC_SW_DN     2U
#define RC_CH_OFFSET 1024U
#define RC_CH_RANGE  660U
#define RC_WHEEL_DN  (RC_CH_OFFSET + RC_CH_RANGE)
#define RC_WHEEL_UP  (RC_CH_OFFSET - RC_CH_RANGE)
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void              FML_Rc_Init(void);
void              FML_Rc_DbusReset(void);
Dvc_StatusTypeDef FML_Rc_RxDataHandler(RcData_t* rc_data);
void              FML_Rc_GetMouseKbEvent(const RcData_t* last_rc_data, const RcData_t* rc_data,
                                         MouseKbEvent_t* event);

#endif /* __FML_RC_H_ */
