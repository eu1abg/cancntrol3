#include <Arduino.h>
#include "config.h"
#include "TFT7735.h"
#include "sdcard.h"
#include "portal.h"
#include "can_mcp.h"
#include "TFT_Oled.h"

//===================================================================

SPIClass spiSD(HSPI);

File myFile; File root;
int intData[500];


String str=""; 
char s;uint32_t now;
uint8_t *fileBuffer = NULL;
size_t fileSize = 0;


//===========================================================================================
void SDFunction(){  
 myFile = SD.open(stroka);
  oled.clear(); memset(intData, 0, sizeof(500)); n = 0; i = 0; //oled.print(" Ok!");

  if (myFile) { oled.setCursor(0, 0);oled.print("File-");oled.print(stroka); oled.setCursor(10, 2);oled.print("File size = ");oled.print(myFile.size());}
          oled.setCursor(35, 5);  oled.println("LOADING");
          for(int i=0;i<2000;i++) { oled.dot((i/15), 60);valSlider = i;  delayFunction(1); }
    oled.clear();  btn1 = 0;
   ui.log.println("++++++++++++++++++++++++");
   ui.log.println("  Загрузка завершена!!  ");
   ui.log.println("++++++++++++++++++++++++");
   myFile.close();
//----------------------------------------------------------------------------------------


// bool loadFileToRAM(const char* path) {
//     File file = SD.open(path);
//     if (!file) {
//         Serial.println("Ошибка открытия файла");
//         return false;
//     }

//     fileSize = file.size();
//     Serial.print("Размер файла: ");
//     Serial.println(fileSize);

//     fileBuffer = (uint8_t*)malloc(fileSize);
//     if (!fileBuffer) {
//         Serial.println("Не хватает RAM!");
//         file.close();
//         return false;
//     }

//     file.read(fileBuffer, fileSize);
//     file.close();

//     Serial.println("Файл загружен в RAM");
//     return true;
// }


//------------------------------------------------------------------------------------


   }
   //===========================================================================================
void TXFunction(){  
  myFile = SD.open(stroka); n = 0; i = 0;      //"/насос/SKODA/sk302/k61_MOD_.trc"
    if (myFile) {Serial.print("File size = ");Serial.println(myFile.size());}
      while (myFile.available()) {  
           s = (char)myFile.read(); 
            if ((s!=',') && (s!= '\n')) { str += s;  } 
                 else { intData[n] = strtoul(str.c_str(), NULL, 16); str = ""; n = n +1; }
     if(n==10) {
    canMsg2.can_id =  intData[0]; 
    canMsg2.can_dlc = intData[1];
    canMsg2.data[0] = intData[2];
    canMsg2.data[1] = intData[3];
    canMsg2.data[2] = intData[4];
    canMsg2.data[3] = intData[5]; 
    canMsg2.data[4] = intData[6];
    canMsg2.data[5] = intData[7];
    canMsg2.data[6] = intData[8];
    canMsg2.data[7] = intData[9];
 
label1:         if(valSwitch3==0 ) {   myFile.close();return; }// выход из цикла чтения файла
     if (tmr2.tick()) { 
      mcp2515.sendMessage(&canMsg2);
    oled.clear(0, 59, 128, 64);
    oled.setCursor(0, 7); oled.print(canMsg2.can_id, HEX); oled.setCursor(20, 7); oled.print(canMsg2.can_dlc, HEX); 
    oled.setCursor(33, 7); oled.print(canMsg2.data[0],HEX), oled.print(canMsg2.data[1],HEX);oled.print(canMsg2.data[2],HEX);
    oled.print(canMsg2.data[3],HEX);oled.print(canMsg2.data[4],HEX);oled.print(canMsg2.data[5],HEX);oled.print(canMsg2.data[6],HEX);
    oled.print(canMsg2.data[7],HEX);

    ui.log.print(canMsg2.can_id,HEX);ui.log.print(" "); ui.log.print(canMsg2.can_dlc); ui.log.print(" ");
    ui.log.print(canMsg2.data[0],HEX); ui.log.print(canMsg2.data[1],HEX);ui.log.print(canMsg2.data[2],HEX);ui.log.print(canMsg2.data[3],HEX);
    ui.log.print(canMsg2.data[4],HEX);ui.log.print(canMsg2.data[5],HEX);ui.log.print(canMsg2.data[6],HEX);ui.log.println(canMsg2.data[7],HEX);  
    //============================================================================================================================================  
       n = 0; 
      } else goto label1;
     
      
 
    // //============================================================================================================================================  
   } 
      
      }
  myFile.close();
    }
//===========================================================================================
// void parseAndSend() {
//     String str = "";
//     int intData[10];
//     int n = 0;

//     for (size_t i = 0; i < fileSize; i++) {
//         char s = fileBuffer[i];

//         if (s != ',' && s != '\n') {
//             str += s;
//         } else {
//             intData[n++] = strtoul(str.c_str(), NULL, 16);
//             str = "";
//         }

//         if (n == 10) {

//             canMsg2.can_id  = intData[0];
//             canMsg2.can_dlc = intData[1];

//             for (int j = 0; j < 8; j++) {
//                 canMsg2.data[j] = intData[j + 2];
//             }

//             // стоп по кнопке
//             if (valSwitch3 == 0) return;

//             while (!tmr2.tick()) {
//                 if (valSwitch3 == 0) return;
//             }

//             mcp2515.sendMessage(&canMsg2);

//             // лог
//             Serial.println(canMsg2.can_id, HEX);

//             n = 0;
//         }
//     }
// }
//===========================================================================================
 void delayFunction(int t) {  now = millis(); while ((millis() - now) < (t+1)) { yield(); }  } // функция delay yield();ui.updateInt("sw2", valSwitch2); ui.update(); 
 
 //=======================================================================
 void initSD(){ 
 
  tft.setCursor(5, 5); tft.print("Initializing SD card...");
   if (!SD.begin(SD_CS, spiSD)) { tft.setCursor(5, 10); tft.println("initialization failed!");delayFunction(5000); return; }

   for (int i = 0; i< 160; i++) {tft.drawPixel(i, 20, TFT_GREEN); delay(5);} 
   delay(1000);tft.fillScreen(TFT_BLACK); tft.setTextColor(TFT_BLACK, TFT_GREEN);
   tft.setCursor(5,0); tft.println("SD card... OK"); 
   // --- Читаем корень ---
   tft.setTextColor(TFT_CYAN, TFT_BLACK);
  File root = SD.open("/"); 
  if (!root) {tft.println("Open root FAIL"); return;}
tft.println(" ");
 tft.println("Folders:");root.rewindDirectory();
int y=30;
  while (true) {
    File entry = root.openNextFile();if (!entry) { break;}

    if (entry.isDirectory()) {
      tft.setCursor(0, y);
      tft.print("[DIR] ");
      tft.println(entry.name());
      y += 12;
// чтобы не вылезти за экран
      if (y > 150) break;}
entry.close();
  }
}
//==================================================================================

