#ifndef __DISPLAY_H
#define __DISPLAY_H

#ifdef __cplusplus
  extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
typedef struct {
  uint8_t     width;
  uint8_t     height;
  uint32_t    color;
  uint32_t    bgcolor;
  uint8_t     use_bg;
  uint8_t     *font;
} Font_TypeDef;


/* Display defines -----------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////
// #define _PORTRAIT_

#ifndef _PORTRAIT_
  #define _LANDSCAPE_
#endif

// -------- Portrait ---------
#ifdef _PORTRAIT_
  #define DISPLAY_HEIGHT              (uint16_t)(800)
  #define DISPLAY_WIDTH               (uint16_t)(480)
#endif

// -------- Landscape --------
#ifdef _LANDSCAPE_
  #define DISPLAY_HEIGHT             (uint16_t)(480)
  #define DISPLAY_WIDTH              (uint16_t)(800)
#endif


/* All padding in portrait mode should be zero */
#ifdef _PORTRAIT_ 
  #define L1_PADDING_LEFT             (uint8_t)0
  #define L1_PADDING_RIGHT            (uint8_t)0
  #define L1_PADDING_TOP              (uint8_t)0
  #define L1_PADDING_BOTTOM           (uint8_t)0
  #define L2_PADDING_LEFT             (uint8_t)0
  #define L2_PADDING_RIGHT            (uint8_t)0
  #define L2_PADDING_TOP              (uint8_t)0
  #define L2_PADDING_BOTTOM           (uint8_t)0
#endif

#ifdef _LANDSCAPE_
  #define L1_PADDING_LEFT             (uint8_t)10
  #define L1_PADDING_RIGHT            (uint8_t)10
  #define L1_PADDING_TOP              (uint8_t)10
  #define L1_PADDING_BOTTOM           (uint8_t)10
  #define L2_PADDING_LEFT             (uint8_t)20
  #define L2_PADDING_RIGHT            (uint8_t)20
  #define L2_PADDING_TOP              (uint8_t)20
  #define L2_PADDING_BOTTOM           (uint8_t)20
#endif

#define L1_HEIGHT                   (uint16_t)(DISPLAY_HEIGHT - L1_PADDING_BOTTOM - L1_PADDING_TOP)
#define L1_WIDTH                    (uint16_t)(DISPLAY_WIDTH - L1_PADDING_LEFT - L1_PADDING_RIGHT)
#define L2_HEIGHT                   (uint16_t)(DISPLAY_HEIGHT - L2_PADDING_BOTTOM - L2_PADDING_TOP)
#define L2_WIDTH                    (uint16_t)(DISPLAY_WIDTH - L2_PADDING_LEFT - L2_PADDING_RIGHT)

#define L1_BYTES                    (uint32_t)(L1_HEIGHT * L1_WIDTH * 4)
#define L2_BYTES                    (uint32_t)(L2_HEIGHT * L2_WIDTH * 4)
#define L1_ADDR                     SDRAM_START_ADDR
#define L2_ADDR                     (uint32_t)(L1_ADDR + L1_BYTES)

//////////////////////////////////////////////////////////////////////////
/* Colors with the Alpha layer */
#define _WHITE      (ARGB8888_White | (255 << ALPHA_Pos))
#define _WHITE_0    ARGB8888_White
#define _ORANGE     (ARGB8888_Orange | (255 << ALPHA_Pos))
#define _YELLOW     (ARGB8888_Yellow | (255 << ALPHA_Pos))
#define _GREEN      (ARGB8888_Green | (255 << ALPHA_Pos))
#define _RED_128    (ARGB8888_Red | (128 << ALPHA_Pos))
#define _RED_0      ARGB8888_Red
#define _DGREEN_64  (ARGB8888_Darkgreen | (64 << ALPHA_Pos))



/* Private defines -----------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/
#define L1_ADDRESS(x, y)  (L1_ADDR + (x * L1_HEIGHT * 4) + (y * 4))
#define L2_ADDRESS(x, y)  (L2_ADDR + (x * L2_HEIGHT * 4) + (y * 4))


/* Exported functions prototypes ---------------------------------------------*/
void Display_Init(void);

void FillLayer(uint8_t layer, uint32_t color);
void FillRectangle(uint8_t layer, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color);
void DrawPixel(uint8_t layer, uint16_t x, uint16_t y, uint32_t color);
void DrawVLine(uint8_t layer, uint16_t x, uint16_t y, uint16_t h, uint32_t color);
void DrawHLine(uint8_t layer, uint16_t x, uint16_t y, uint16_t w, uint32_t color);
void DrawSymbol(uint8_t layer, uint16_t *x, uint16_t *y, const Font_TypeDef *font, uint8_t pos);
void PrintString(uint8_t layer, uint16_t *x, uint16_t *y, const Font_TypeDef *font, const char *buf, uint8_t wrap);

void DisplayDateAndTime_Handler(void);
void DisplayDate(const char* buf);
void DisplayTime(const char* buf);







#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */
