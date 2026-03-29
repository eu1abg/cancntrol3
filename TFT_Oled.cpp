#include <Arduino.h>
#include "TFT_Oled.h"
#include "can_mcp.h"

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;


void iniTFT_Oled(){ oled.init(); oled.clear();}
//===================================================================
void priv(){
    oled.setScale(1);  oled.setCursor(5, 0); oled.print("Портал CFG запущен!");
    oled.setCursor(5, 1); oled.print("WI-FI ESPConfig.");
    oled.setCursor(0, 3); oled.print("SSID = ");
    oled.setCursor(0, 5); oled.print("PASS = ");
}
//==================================================================
void ekr(){

oled.setCursor(0, 0);oled.print("------"); oled.invertText(1); oled.print("CAN Read");oled.invertText(0);oled.print("------ ");
  oled.setCursor(0, 1);oled.print("ID DLC         DATA ");
  oled.setCursor(0, 5); oled.print("------"); oled.invertText(1);oled.print("CAN Write");oled.invertText(0);oled.print("-----   ");
  oled.setCursor(0, 6);oled.print("ID DLC         DATA   "); 
  //=======================  Прием из CAN на экран  =====================================================================================================================  
   for (int s = 2; s<4; s++) 
 {  
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) 
   { oled.setCursor(0, s);oled.print(canMsg.can_id, HEX); oled.setCursor(20, s); oled.print(canMsg.can_dlc, HEX);
     oled.setCursor(33, s);
     oled.print(canMsg.data[0],HEX);oled.print(canMsg.data[1],HEX);oled.print(canMsg.data[2],HEX);oled.print(canMsg.data[3],HEX);oled.print(canMsg.data[4],HEX);
     oled.print(canMsg.data[5],HEX);oled.print(canMsg.data[6],HEX);oled.print(canMsg.data[7],HEX);oled.print("     "); 
    }
 } 



}






