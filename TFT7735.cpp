#include <Arduino.h>
#include "TFT7735.h"

TFT_eSPI tft = TFT_eSPI();

void iniTFT7735(){ 


  delay(50);
tft.init();tft.setRotation(3);tft.fillScreen(TFT_BLACK);tft.setTextSize(1);
tft.setCursor(0, 0);tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("TFT OK"); delay(1000);}
//==============================================================
void priv7735(){

}
//===============================================================
void ekr7735(){

}
//=================================================================
