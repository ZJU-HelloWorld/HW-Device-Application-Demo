/**
 *******************************************************************************
 * @file      : fml_oled.c/h
 * @brief     : 0.96 inch oled use SSD1306 driver. Init oled and command setting.
 *              Operate GRAM to show icon, num, char and string.
 * @history   :
 *  Version     Date            Author          Note
 *  V1.0        2018-12-26      RM              1. Done
 *  V2.0        2022-07-18      xdl             1. Modified
 *******************************************************************************
 * @attention : Modified from oled.c/h, oledfont.h, bsp_i2c.c/h
 *              (C) COPYRIGHT 2019 DJI
 *******************************************************************************
 *  Copyright (c) 2022 HelloWorld, Zhejiang University.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "fml_oled.h"
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define OLED_I2C_ADDRESS 0x78
#define OLED_CMD         0x00
#define OLED_DATA        0x01
#define X_WIDTH          MAX_COLUMN
#define Y_WIDTH          MAX_ROW
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void _FML_Oled_WriteByte(uint8_t data, uint8_t cmd);
static void _FML_Oled_SetPoint(uint8_t x, uint8_t y);
static void _FML_Oled_DisplayPoint(const uint8_t x, const uint8_t y, const OledPen_e pen,
                                   OledGram_t* gram);

/**
 *******************************************************************************
 * @brief     Initialize OLED
 * @param     None
 * @retval    None
 * @note      Call HAL_Delay(30) in this func
 *******************************************************************************
 */
void FML_Oled_Init(void)
{
  HAL_Delay(30);                       /* waiting for OLED hardware reset */
  _FML_Oled_WriteByte(0xAE, OLED_CMD); // display off
  _FML_Oled_WriteByte(0x40, OLED_CMD); //--set start line address
  _FML_Oled_WriteByte(0x81, OLED_CMD); //--set contrast control register
  _FML_Oled_WriteByte(0xFF, OLED_CMD); // brightness 0x00~0xff
  _FML_Oled_WriteByte(0xa4, OLED_CMD); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  _FML_Oled_WriteByte(0xa6, OLED_CMD); //--set normal display
  _FML_Oled_WriteByte(0x20, OLED_CMD); // Set Memory Addressing Mode
  _FML_Oled_WriteByte(0x00, OLED_CMD); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
  _FML_Oled_WriteByte(0x21, OLED_CMD);
  _FML_Oled_WriteByte(0x00, OLED_CMD);
  _FML_Oled_WriteByte(0x7F, OLED_CMD);
  _FML_Oled_WriteByte(0x22, OLED_CMD);
  _FML_Oled_WriteByte(0x00, OLED_CMD);
  _FML_Oled_WriteByte(0x07, OLED_CMD);
  _FML_Oled_WriteByte(0x3F, OLED_CMD); //
  _FML_Oled_WriteByte(0xc8, OLED_CMD); // Set COM Output Scan Direction
  _FML_Oled_WriteByte(0xa1, OLED_CMD); //--set segment re-map 0 to 127
  _FML_Oled_WriteByte(0xa8, OLED_CMD); //--set multiplex ratio(1 to 64)
  _FML_Oled_WriteByte(0x00, OLED_CMD); //
  _FML_Oled_WriteByte(0xd3, OLED_CMD); //-set display offset
  _FML_Oled_WriteByte(0x00, OLED_CMD); //-not offset
  _FML_Oled_WriteByte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
  _FML_Oled_WriteByte(0xF0, OLED_CMD); //--set divide ratio
  _FML_Oled_WriteByte(0xd9, OLED_CMD); //--set pre-charge period
  _FML_Oled_WriteByte(0x22, OLED_CMD); //
  _FML_Oled_WriteByte(0xda, OLED_CMD); //--set com pins hardware configuration
  _FML_Oled_WriteByte(0x12, OLED_CMD);
  _FML_Oled_WriteByte(0xdb, OLED_CMD); //--set vcomh
  _FML_Oled_WriteByte(0x20, OLED_CMD); // 0x20,0.77xVcc
  _FML_Oled_WriteByte(0x8d, OLED_CMD); //--set DC-DC enable
  _FML_Oled_WriteByte(0x14, OLED_CMD); //
  _FML_Oled_WriteByte(0xaf, OLED_CMD); //--turn on oled panel
}

/**
 *******************************************************************************
 * @brief     turn on OLED display
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Oled_DisplayOn(void)
{
  _FML_Oled_WriteByte(0x8d, OLED_CMD);
  _FML_Oled_WriteByte(0x14, OLED_CMD);
  _FML_Oled_WriteByte(0xaf, OLED_CMD);
}

/**
 *******************************************************************************
 * @brief     turn off OLED display
 * @param     None
 * @retval    None
 * @note      None
 *******************************************************************************
 */
void FML_Oled_DisplayOff(void)
{
  _FML_Oled_WriteByte(0x8d, OLED_CMD);
  _FML_Oled_WriteByte(0x10, OLED_CMD);
  _FML_Oled_WriteByte(0xae, OLED_CMD);
}

/**
 *******************************************************************************
 * @brief     operate the graphic ram (size: 128*8 char)
 * @param     const OledPen_e pen: the type of operate.
 * @arg       PEN_CLEAR: set ram to 0x00
 * @arg       PEN_WRITE: set ram to 0xff
 * @arg       PEN_INVERSION: bit inversion
 * @param     OledGram_t* gram: graphic ram to operate
 * @retval    OledGram_t* gram
 * @note      None
 *******************************************************************************
 */
void FML_Oled_OperateGram(const OledPen_e pen, OledGram_t* gram)
{
  if (NULL == gram)
    return;

  for (uint8_t i = 0; i < 8; i++)
  {
    for (uint8_t n = 0; n < 128; n++)
    {
      gram->gram_data[i][n] = (PEN_WRITE == pen)   ? 0xff
                              : (PEN_CLEAR == pen) ? 0x00
                                                   : 0xff - gram->gram_data[i][n];
    }
  }
}

/**
 *******************************************************************************
 * @brief     send the data of gram to oled sreen
 * @param     OledGram_t* gram: graphic ram to operate
 * @retval    OledGram_t* gram
 * @note      None
 *******************************************************************************
 */
void FML_Oled_RefreshGram(OledGram_t* gram)
{
  if (NULL == gram)
    return;

  _FML_Oled_SetPoint(0, 0);
  gram->cmd = 0x40;
  HAL_I2C_Master_Transmit_DMA(&HI2C_OLED, OLED_I2C_ADDRESS, (uint8_t*)gram, 1025);
}

/**
 *******************************************************************************
 * @brief     draw a line from (x1, y1) to (x2, y2)
 * @param     const uint8_t x1, y1: the start point of line
 * @param     const uint8_t x2, y2: the end of line
 * @param     const OledPen_e pen: the type of operate.
 * @arg       PEN_CLEAR: set ram to 0x00
 * @arg       PEN_WRITE: set ram to 0xff
 * @arg       PEN_INVERSION: bit inversion
 * @param     OledGram_t* gram: graphic ram to operate
 * @retval    OledGram_t* gram
 * @note      None
 *******************************************************************************
 */
void FML_Oled_DisplayLine(const uint8_t x1, const uint8_t y1,
                          const uint8_t x2, const uint8_t y2,
                          const OledPen_e pen,
                          OledGram_t*     gram)
{
  if (NULL == gram)
    return;

  uint8_t col = 0, row = 0;
  uint8_t x_st = 0, x_ed = 0, y_st = 0, y_ed = 0;
  float   k = 0.0f, b = 0.0f;

  if (y1 == y2)
  {
    (x1 <= x2) ? (x_st = x1) : (x_st = x2);
    (x1 <= x2) ? (x_ed = x2) : (x_ed = x1);

    for (col = x_st; col <= x_ed; col++)
    {
      _FML_Oled_DisplayPoint(col, y1, pen, gram);
    }
  }
  else if (x1 == x2)
  {
    (y1 <= y2) ? (y_st = y1) : (y_st = y2);
    (y1 <= y2) ? (y_ed = y2) : (y_ed = y1);

    for (row = y_st; row <= y_ed; row++)
    {
      _FML_Oled_DisplayPoint(x1, row, pen, gram);
    }
  }
  else
  {
    k = ((float)(y2 - y1)) / (x2 - x1);
    b = (float)y1 - k * x1;

    (x1 <= x2) ? (x_st = x1) : (x_st = x2);
    (x1 <= x2) ? (x_ed = x2) : (x_ed = x2);

    for (col = x_st; col <= x_ed; col++)
    {
      _FML_Oled_DisplayPoint(col, (uint8_t)(col * k + b), pen, gram);
    }
  }
}

/**
 *******************************************************************************
 * @brief     show a character
 * @param     const uint8_t col: column of character
 * @param     const uint8_t row: row of character
 * @param     const uint8_t chr: the character ready to show
 * @param     OledGram_t* gram: graphic ram to operate
 * @retval    OledGram_t* gram
 * @note      None
 *******************************************************************************
 */
void FML_Oled_DisplayChar(const uint8_t col, const uint8_t row, const uint8_t ch,
                          OledGram_t* gram)
{
  if (NULL == gram)
    return;

  uint8_t x      = col;
  uint8_t y      = row;
  uint8_t y0     = y;
  uint8_t tmp_ch = ch - ' ';
  uint8_t tmp_ascii;

  for (uint8_t i = 0; i < 12; i++)
  {
    tmp_ascii = asc2_1206[tmp_ch][i];

    for (uint8_t j = 0; j < 8; j++)
    {
      if (tmp_ascii & 0x80)
        _FML_Oled_DisplayPoint(x, y, PEN_WRITE, gram);
      else
        _FML_Oled_DisplayPoint(x, y, PEN_CLEAR, gram);

      tmp_ascii <<= 1;
      y++;
      if ((y - y0) == 12)
      {
        y = y0;
        x++;
        break;
      }
    }
  }
}

/**
 *******************************************************************************
 * @brief     show a character string
 * @param     const uint8_t col: column of character string begin
 * @param     const uint8_t row: row of character string begin
 * @param     const uint8_t chr: the pointer to character string
 * @param     OledGram_t* gram: graphic ram to operate
 * @retval    OledGram_t* gram
 * @note      None
 *******************************************************************************
 */
void FML_Oled_DisplayString(const uint8_t col, const uint8_t row, const uint8_t* ch,
                            OledGram_t* gram)
{
  if (NULL == gram)
    return;

  uint8_t n       = 0;
  uint8_t tmp_col = col, tmp_row = row;

  while (ch[n] != '\0')
  {
    FML_Oled_DisplayChar(tmp_col, tmp_row, ch[n], gram);
    tmp_col += CHAR_WIDTH;

    if (tmp_col > X_WIDTH - CHAR_WIDTH)
    {
      tmp_col = 0;
      tmp_row += CHAR_HEIGHT;
    }
    n++;
  }
}

/**
 *******************************************************************************
 * @brief     formatted output in oled 128*64
 * @param     const uint8_t col: column of character string begin, 0 <= col <= 20;
 * @param     const uint8_t row: row of character string begin, 0 <= row <= 4;
 * @param     OledGram_t* gram: graphic ram to operate
 * @param     *fmt: the pointer to format character string
 * @retval    OledGram_t* gram
 * @note      if the character length is more than one row at a time,
 *            the extra characters will be truncated
 *******************************************************************************
 */
void FML_Oled_Printf(const uint8_t col, const uint8_t row, OledGram_t* gram,
                     const char* fmt, ...)
{
  if (NULL == gram || NULL == fmt)
    return;

  static uint8_t LCD_BUF[22] = {0};
  static va_list ap;
  uint16_t       remain_size = 0;

  va_start(ap, fmt);
  remain_size = vsprintf((char*)LCD_BUF, fmt, ap);
  va_end(ap);

  LCD_BUF[remain_size] = '\0';

  FML_Oled_DisplayString(col, row, LCD_BUF, gram);
}

/**
 *******************************************************************************
 * @brief     show a graph
 * @param     const uint8_t x: the start pont of the icon
 * @param     const uint8_t y: the start pont of the icon
 * @param     const OledIcon_t* icon
 * @param     OledGram_t* gram: graphic ram to operate
 * @retval    OledGram_t* gram
 * @note      None
 *******************************************************************************
 */
void FML_Oled_DisplayIcon(const uint8_t x, const uint8_t y, const OledIcon_t* icon,
                          OledGram_t* gram)
{
  if (NULL == gram || NULL == icon)
    return;

  uint8_t  temp_char;
  uint16_t i = 0;

  for (uint8_t col = 0; col < icon->length; col++)
  {
    for (uint8_t row = 0; row < icon->width;)
    {
      temp_char = icon->data[i];
      i++;
      for (uint8_t j = 0; j < 8; j++)
      {
        if (temp_char & 0x80)
        {
          _FML_Oled_DisplayPoint(x + col, y + row, PEN_WRITE, gram);
        }
        else
        {
          _FML_Oled_DisplayPoint(x + col, y + row, PEN_CLEAR, gram);
        }
        temp_char <<= 1;
        row++;
        if (row == icon->width)
        {
          break;
        }
      }
    }
  }
}

/**
 *******************************************************************************
 * @brief     Write data/command to OLED
 * @param     uint8_t data: the data ready to write
 * @param     uint8_t cmd: OLED_CMD means command; OLED_DATA means data
 * @retval    None
 * @note      DMA Trans
 *******************************************************************************
 */
static void _FML_Oled_WriteByte(uint8_t data, uint8_t cmd)
{
  static uint8_t cmd_data[2];
  cmd_data[0] = (cmd == OLED_CMD) ? 0x00 : 0x40;
  cmd_data[1] = data;
  HAL_I2C_Master_Transmit(&HI2C_OLED, OLED_I2C_ADDRESS, cmd_data, 2, 10);
}

/**
 *******************************************************************************
 * @brief     cursor set to (x,y) point
 * @param     uint8_t x: X-axis, from 0 to 127
 * @param     uint8_t y: Y-axis, from 0 to 7
 * @retval    None
 * @note      None
 *******************************************************************************
 */
static void _FML_Oled_SetPoint(uint8_t x, uint8_t y)
{
  x &= 0x7F;
  y &= 0x07;
  _FML_Oled_WriteByte(0x21, OLED_CMD);
  _FML_Oled_WriteByte(0x00 + x, OLED_CMD);
  _FML_Oled_WriteByte(0x7F, OLED_CMD);
  _FML_Oled_WriteByte(0x22, OLED_CMD);
  _FML_Oled_WriteByte(0x00 + y, OLED_CMD);
  _FML_Oled_WriteByte(0x07, OLED_CMD);
}

/**
 *******************************************************************************
 * @brief     draw one bit of graphic raw, operate one point of screan(128*64)
 * @param     const uint8_t x: x-axis, [0, X_WIDTH-1]
 * @param     const uint8_t y: y-axis, [0, Y_WIDTH-1]
 * @param     const OledPen_e pen: the type of operate.
 * @arg       PEN_CLEAR: set (x,y) to 0
 * @arg       PEN_WRITE: set (x,y) to 1
 * @arg       PEN_INVERSION: (x,y) value inversion
 * @param     OledGram_t* gram: graphic ram to operate
 * @retval    OledGram_t* gram
 * @retval    None
 * @note      None
 *******************************************************************************
 */
static void _FML_Oled_DisplayPoint(const uint8_t x, const uint8_t y, const OledPen_e pen,
                                   OledGram_t* gram)
{
  if (NULL == gram)
    return;

  /* check the corrdinate */
  if ((x > (X_WIDTH - 1)) || (y > (Y_WIDTH - 1)))
  {
    return;
  }
  uint8_t page = y / 8;
  uint8_t row  = y % 8;

  switch (pen)
  {
    case PEN_WRITE:
      gram->gram_data[page][x] |= 1 << row;
      break;
    case PEN_INVERSION:
      gram->gram_data[page][x] ^= 1 << row;
      break;
    default:
      gram->gram_data[page][x] &= ~(1 << row);
      break;
  }
}
