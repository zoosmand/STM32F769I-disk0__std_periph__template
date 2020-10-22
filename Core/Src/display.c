/* Includes ------------------------------------------------------------------*/
#include "display.h"


/* Private variables ---------------------------------------------------------*/
const Font_TypeDef font_dot15x21 = {
  .width    = 18,
  .height   = 24,
  .color    = ARGB8888_White,
  .bgcolor  = ARGB8888_Darkgreen,
  .use_bg   = 1,
  .font     = (uint8_t*)font_15x21
};

const Font_TypeDef font_dot20x28 = {
  .width    = 24,
  .height   = 32,
  .color    = ARGB8888_White,
  .bgcolor  = ARGB8888_Darkgreen,
  .use_bg   = 1,
  .font =   (uint8_t*)font_20x28
};

const Font_TypeDef font_dot10x14 = {
  .width = 12,
  .height = 16,
  .color = _YELLOW,
  .bgcolor = _RED_0,
  .use_bg = 1,
  .font = (uint8_t*)font_10x14
};

const Font_TypeDef dateTimeFont = {
  .width = 12,
  .height = 16,
  .color = _RED_128,
  .bgcolor = _RED_0,
  .use_bg = 1,
  .font = (uint8_t*)font_10x14
};

static uint16_t xStart = 0;
static uint16_t yStart = 0;










////////////////////////////////////////////////////////////////////////////////


void Display_Init(void) {
  /* DMA2D */ 
  DMA2D_Init();
  Delay(1);

  /* FMC */
  FMC_Init(_SDRAM);
  Delay(1);

  /* DSI */
  DSI_Init();
  Delay(1);

  /* LTDC */
  LTDC_Init();
  Delay(1);

  /* Display OTM8009A */
  OTM8009A_Init(OTM8009A_FORMAT_RGB888);
  Delay(1);
}




/**
  * @brief  Fills a layer of display with color
  * @param  layer: number of layer
  * @param  color: color
  * @retval None
  */
void FillLayer(uint8_t layer, uint32_t color) {
  __IO uint32_t layerAddr = 0;
  __IO uint32_t layerBytes = 0;

  switch (layer) {
    case L1:
      layerAddr = L1_ADDR;
      layerBytes = L1_BYTES;
      break;
    
    case L2:
      layerAddr = L2_ADDR;
      layerBytes = L2_BYTES;
      break;
    
    default:
      return;
      break;
  }

  for (uint32_t i = 0; i < layerBytes; i += 4) {
    *(__O uint32_t*)(layerAddr + i) = color;
  }
}




/**
  * @brief  Draws a pixel on a layer of display with color
  * @param  layer: number of layer
  * @param  x: x coordinate
  * @param  y: y coordinate 
  * @param  color: color
  * @retval None
  */
void DrawPixel(uint8_t layer, uint16_t x, uint16_t y, uint32_t color) {
  switch (layer) {
    case L1:
      *(__O uint32_t*)(L1_ADDRESS(x, y)) = color;
      break;
    
    case L2:
      *(__O uint32_t*)(L2_ADDRESS(x, y)) = color;
      break;
    
    default:
      return;
      break;
  }
}




/**
  * @brief  Draws a vertical line on a layer of display with color
  * @param  layer: number of layer
  * @param  x: x coordinate
  * @param  y: y coordinate 
  * @param  h: height of a line
  * @param  color: color
  * @retval None
  */
void DrawVLine(uint8_t layer, uint16_t x, uint16_t y, uint16_t h, uint32_t color) {
  uint32_t layerAddr = 0;
  uint32_t height = 0;
  uint32_t width = 0;

  switch (layer) {
    case L1:
      layerAddr = L1_ADDRESS(x, y);
      height = L1_HEIGHT;
      width = L1_WIDTH;
      break;
    
    case L2:
      layerAddr = L2_ADDRESS(x, y);
      height = L2_HEIGHT;
      width = L2_WIDTH;
      break;
    
    default:
      return;
      break;
  }

  if ((x >= height) || (y >= width)) return;
  if ((y + h - 1) >= height)  h = height - y;

  while (h--) {
    *(__O uint32_t*)(layerAddr) = color;
    layerAddr += 4;
  }
}





/**
  * @brief  Draws a horizontal line on a layer of display with color
  * @param  layer: number of layer
  * @param  x: x coordinate
  * @param  y: y coordinate 
  * @param  w: weight of a line
  * @param  color: color
  * @retval None
  */
void DrawHLine(uint8_t layer, uint16_t x, uint16_t y, uint16_t w, uint32_t color) {
  uint32_t layerAddr = 0;
  uint32_t height = 0;
  uint32_t width = 0;
  uint32_t hh = 0;

  switch (layer) {
    case L1:
      layerAddr = L1_ADDRESS(x, y);
      height = L1_HEIGHT;
      width = L1_WIDTH;
      hh = (uint32_t)(L1_HEIGHT << 2);
      break;
    
    case L2:
      layerAddr = L2_ADDRESS(x, y);
      height = L2_HEIGHT;
      width = L2_WIDTH;
      hh = (uint32_t)(L2_HEIGHT << 2);
      break;
    
    default:
      return;
      break;
  }

  if ((x >= height) || (y >= width)) return;
  if ((x + w - 1) >= width)  w = width - x;

  while (w--) {
    *(__O uint32_t*)(layerAddr) = color;
    layerAddr += hh;
  }
}



/**
  * @brief  Fills rectangle on a layer of display with color
  * @param  layer: number of layer
  * @param  x: x coordinate
  * @param  y: y coordinate 
  * @param  h: height of a rectangle
  * @param  w: weight of a rectangle
  * @param  color: color
  * @retval None
  */
void FillRectangle(uint8_t layer, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color) {
  uint32_t layerAddr = 0;
  uint32_t height = 0;
  uint32_t width = 0;
  uint32_t ww = 0;

  switch (layer) {
    case L1:
      layerAddr = L1_ADDRESS(x, y);
      height = L1_HEIGHT;
      width = L1_WIDTH;
      ww = (uint32_t)((L1_HEIGHT << 2) - (h << 2));
      break;
    
    case L2:
      layerAddr = L2_ADDRESS(x, y);
      height = L2_HEIGHT;
      width = L2_WIDTH;
      ww = (uint32_t)((L2_HEIGHT << 2) - (h << 2));
      break;
    
    default:
      return;
      break;
  }

  if ((x >= width) || (y >= height) || (w == 0) || (h == 0)) return;
  if ((x + w - 1) >= width)  w = width  - x;
  if ((y + h - 1) >= height) h = height - y;

  uint16_t hh = 0;

  while (w--) {
    hh = h;
    while (hh--) {
      *(__O uint32_t*)(layerAddr) = color;
      layerAddr += 4;
    }
    layerAddr += ww;
  }
}




/**
  * @brief  Draws symbol on a layer of display
  * @param  layer: number of layer
  * @param  x: pointer to x coordinate
  * @param  y: pointer to y coordinate 
  * @param  font: pointer to font structure containes font paramenters:
  *               - width of a symbol
  *               - height of a symbol
  *               - color of a symbol
  *               - background color behind a symbol
  *               - flag - use or don't use background color
  *               - array of symbols
  * @param  pos: position in the sysmbol's array
  * @retval None
  */
void DrawSymbol(uint8_t layer, uint16_t *x, uint16_t *y, const Font_TypeDef *font, uint8_t pos) {
  if ((pos > 126) || (pos < 32)) {
    if (pos == 176) pos = 95;
    else return;
  } else {
    pos -= 32;
  }
  int16_t w = font->width;
  int16_t h = font->height;
  uint32_t layerAddr = 0;
  uint32_t height = 0;
  uint32_t width = 0;
  uint32_t ww = 0;
  
  switch (layer) {
    case L1:
      layerAddr = L1_ADDRESS(*x, *y);
      height = L1_HEIGHT;
      width = L1_WIDTH;
      ww = (uint32_t)((L1_HEIGHT << 2) - (h << 2));
      break;
    
    case L2:
      layerAddr = L2_ADDRESS(*x, *y);
      height = L2_HEIGHT;
      width = L2_WIDTH;
      ww = (uint32_t)((L2_HEIGHT << 2) - (h << 2));
      break;
    
    default:
      return;
      break;
  }

  if ((*x >= width) || (*y >= height) || (w == 0) || (h == 0)) return;
  if ((*x + w - 1) >= width)  w = width  - *x;
  if ((*y + h - 1) >= height) h = height - *y;

  uint8_t smb = 0;
  uint8_t z = 0;
  uint8_t *fontAddr = font->font;
  
  uint16_t hh = 0;
  *x += w;

  while (w--) {
    z = font->height / 8;
    while (z--) {
      smb = fontAddr[(pos * font->width * (font->height / 8))];
      fontAddr++;

      hh = 8;
      while (hh--) {
        if (smb & 0x01) {
          *(__IO uint32_t*)layerAddr = font->color;
        } else {
          if (font->use_bg) {
            *(__O uint32_t*)layerAddr = font->bgcolor;
          }
        }
        layerAddr +=4;
        smb >>= 1;
      }
    }
    layerAddr += ww;
  }
}




/**
  * @brief  Prints a string on a layer of display
  * @param  layer: number of layer
  * @param  x: pointer to x coordinate
  * @param  y: pointer to y coordinate 
  * @param  font: pointer to font structure containes font paramenters:
  *               - width of a symbol
  *               - height of a symbol
  *               - color of a symbol
  *               - background color behind a symbol
  *               - flag - use or not use background color
  *               - array of symbols
  * @param  buf: pointer to buffer with a string
  * @param  wrap: wrap or not wrap to the next line 
  * @retval None
  */
void PrintString(uint8_t layer, uint16_t *x, uint16_t *y, const Font_TypeDef *font, const char *buf, uint8_t wrap) {
  uint32_t width = 0;

  switch (layer) {
    case L1:
      width = L1_WIDTH;
      break;
    
    case L2:
      width = L2_WIDTH;
      break;
    
    default:
      return;
      break;
  }

  while (*buf) {
    if (*x > width - 10) {
      if (wrap) {
        *x = 0;
        *y -= (font->height + 4);
      } else {
        return;
      }
    }
    DrawSymbol(layer, x, y, font, *buf);
    buf++;
  }
}





/**
  * @brief  Reads date and time from the RTC and displays them
  * @param  None
  * @retval None
  */
void DisplayDateAndTime_Handler(void) {
    static char dateStr[12];
    static char timeStr[12];
    
    sprintf(timeStr, "%2x:%02x:%02x ", RTC_GetHour, RTC_GetMinute, RTC_GetSecond);
    sprintf(dateStr, "%2x/%x/%4x ", RTC_GetDay, RTC_GetMonth, RTC_GetYear);
    // printf("date: %s\n\r", dateStr);
    // printf("time: %s\n\r", timeStr);

    DisplayDate(dateStr);
    DisplayTime(timeStr);
}



/**
  * @brief  Displays date on a layer 1 of display to certain coordinates
  * @param  buf: pointer to buffer with date digits
  * @retval None
  */
void DisplayDate(const char* buf) {
  xStart = 30;
  yStart = 20;

  PrintString(L2, &xStart, &yStart, &dateTimeFont, buf, 0);
}




/**
  * @brief  Displays time on a layer 1 of display to certain coordinates
  * @param  buf: pointer to buffer with time digits
  * @retval None
  */
void DisplayTime(const char* buf) {
  xStart = 170;
  yStart = 20;

  PrintString(L1, &xStart, &yStart, &dateTimeFont, buf, 0);
}





