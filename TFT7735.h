#ifndef TFT7735_H
#define TFT7735_H

#include <TFT_eSPI.h>
//#include <SPI.h>

#define TFT_WIDTH  128
#define TFT_HEIGHT 160

#define TFT_INVERSION_OFF
 //#define TFT_INVERSION_ON
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
#define TFT_MISO 19 
#define TFT_BL 17

extern TFT_eSPI tft;

void iniTFT7735() ;
void priv7735();
void ekr7735();














#endif