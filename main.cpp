#include <Arduino.h>

//#include <LittleFS.h>
//#include <GyverPortal.h>
//GyverPortal ui(&LittleFS);  // передать ссылку на fs (SPIFFS/LittleFS)

#include <config.h>
#include <SPI.h>
#include "portal.h"
#include "sdcard.h"
#include "can_mcp.h"
//------------------------------------

//-----------------------------------------
 #include "TFT7735.h"
// #endif

#include <SimplePortal.h>
#include <WiFi.h>

//========================================================================================================
// имя точки в режиме AP
const char *ssid = "CANkontroller";
const char *password = "";

//============================================================================================================================================

#include <stdlib.h>
#include <SPI.h>
//#include <SD.h>

//============================================================================================================================================


#include <TimerMs.h>
TimerMs tmr1(50, 1, 0); // таймер на слайдер
//TimerMs tmr2(1,1,0); // таймер на передачу кан сигналов
TimerMs tmr3(3000, 1, 0); // таймер считывания напряжения tok;
TimerMs tmr4(5000, 1, 0); // таймер считывания напряжения Vbat

//============================================================================================================================================
#include <driver/ledc.h>
//#define GEN_PIN 4   
//GyverPortal ui(&LittleFS);
//============================================================================================================================================
uint32_t Freq;
int d = 0; // поправка для форм месаги
int i = 0; // счетчик для месаг
int n = 0; // счетчик массива для считывания
//int sw = 0; // временна переменная
int r = 0;
//============================================================================================================================================
unsigned long timing;
String test="";
//===========================================================================================
int valNum;
uint32_t t =0;
int portall = 0;  bool stop=0; bool GEN=0;   
// ==================== Задача для Core 0 ====================
//========================= ОСНОВНОЙ ЛУУП ===========================================================================
void TaskHardware(void *pvParameters) {for (;;) {
//==========================================================================================

    if (tmr4.tick())  { vbat = (analogRead(39) * 3.3 / 4096)*4.4; } // измеряем напряжениеSerial.print(vbat);
    if (vbat < vmin) { tft.setTextSize(2);tft.setCursor(0, 0); tft.print(" bat= "); tft.print(vbat);tft.setCursor(0, 5);tft.print(" BatLow!!! ");
     ui.log.println("ТРЕБУЕТСЯ ЗАРЯДКА АКБ.");tft.setTextSize(1); valSwitch30 = 0;valSwitch3 = 0; valSwitch15 =0; valSwitchG=0; }




//==========================================================================================                
    if (tmr3.tick()) {tok= (1.6 - (analogRead(36) * 3.3 / 4096))*5.34; } // ПОДОБРАТЬ КООФ ТОКА
      if (tok > 10 )  { valSwitch30 = 0; } // защита по току
//==========================================================================================        
    if (valSwitch30 == 1) { digitalWrite(k61,HIGH);}  //  включаем питание рейки реле k61
       else {digitalWrite(k61,LOW);}
    if  (valSwitch15 == 1) {digitalWrite(k15,HIGH);}  //  включаем зажигание реле к15
       else {digitalWrite(k15,LOW);}
       
  //  if  ((stroka == "/колонка/LADA/Granda/k61_MOD_.trc") && (valSwitch3==1)) {GEN= 0;ledcDetachPin(GEN_PIN); ledcAttachPin(GEN_PIN, 0); ledcSetup(0, 20, 8); ledcWrite(0, 127); }   //  включаем шим на выход оборотыk61_MOD_NO_Str.trc
  //     else {GEN=1;}  //ledcWriteTone(0, 0);ledcWrite(0, 0); https://docs-espressif-com.translate.goog/projects/arduino-esp32/en/latest/api/ledc.html?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru

      //analogWriteFrequency(GEN_PIN,20);analogWrite(GEN_PIN, 50);
   
   //if (( btn1 == 1 ) && (valSwitch3 == 0)) { r = 0;  valSlider = 0;  SDFunction();   }  //  включаем чтение карточки tone(tonePin, 659, 165.441);
  
   //if ((valSwitch3 == 1) && ( btn1 != 1)) {  stop=0; TXFunction(); }   else {  stop=1;} // включаем передачу в кан
   
  //  if (valSwitchG == 1) {ledcWrite(0, (2.55*valSpin2));}  //  вкл генератор //analogWriteFrequency(GEN_PIN,valSpin1);analogWrite(GEN_PIN, (2.55*valSpin2));
  //    else {if( GEN==1) {ledcWrite(0, 0);}}  
  //============================================================================================================================================

 // ekr();  



 
        delay(1);
    }
}

// ==================== Задача для Core 1 ====================
void TaskWeb(void *pvParameters) { for (;;) { build();ui.tick();action();//beforeRestart();
   delay(1);}}
//===========================================================================================

void setup() {
  
  pinMode(k61, OUTPUT); // реле К61 
  pinMode(k15, OUTPUT);  // реле К15
 // ledcAttachPin(GEN_PIN, 0); ledcSetup(0, 400, 8); // выход обороты   ledcAttach(19, 500, 8); ledcWrite(19,regulator.getResultTimer()); 
  pinMode(39, INPUT);   // вход контроля 12вольт
  pinMode(36, INPUT);   // вход контроля ток
  pinMode(kn1, INPUT_PULLUP);   // кнопка 1
  pinMode(kn2, INPUT_PULLUP);   // кнопка 2
  SPI.begin(18, 19, 23); // SCK, MISO, MOSI 
  spiSD.begin(14, 12, 13); // SCK, MISO, MOSI


 
//===========================================================================================
  Serial.begin(115200);


iniTFT7735(); initSD(); delay(3000); tft.fillScreen(TFT_BLACK);
if(digitalRead(kn1)==0 && digitalRead(kn2)==0) { tft.setCursor(0, 30); tft.setTextColor(TFT_YELLOW, TFT_BLACK); tft.print("Запущен ESP Config 2min !!");  portalRun(1000);} // переделать на 2 минуты
  
  if (portalStatus() == SP_SUBMIT) { 
     portall = 1;
  tft.setCursor(0,0); tft.print(portalCfg.SSID); 
  tft.setCursor(0, 10);tft.print(portalCfg.pass); portalStop(); delayFunction(5000);
     WiFi.softAPdisconnect(); WiFi.disconnect(); WiFi.mode(WIFI_STA); WiFi.begin(portalCfg.SSID, portalCfg.pass); tft.setCursor(0, 5);
     while (WiFi.status() != WL_CONNECTED) { delayFunction(300); tft.print(".");}
     tft.setCursor(60, 50);tft.fillScreen(TFT_BLACK);Serial.print(WiFi.localIP()); tft.println(WiFi.localIP()); delay(5000);
    } //===========================================================================================
      else { portalStop(); delayFunction(1000); portall = 1; WiFi.disconnect();WiFi.mode(WIFI_AP); tft.fillScreen(TFT_BLACK);
      while (!WiFi.softAP(ssid, password)) {delayFunction(300); tft.print(".");}
                           tft.setCursor(35, 20); tft.print("АР активирована !");
   tft.setTextColor(TFT_CYAN, TFT_BLACK); tft.setCursor(40, 40); tft.print("CANcontroller..");
   tft.setTextColor(TFT_BLUE, TFT_BLACK); tft.setTextSize(2);   tft.setCursor(5, 60);tft.print(WiFi.softAPIP()); }    
     
  delay(3000); tft.fillScreen(TFT_BLACK);tft.setTextSize(1); 

if (!LittleFS.begin()) Serial.println("FS Error"); 

  ui.attachBuild(build); ui.attach(action); ui.start(); ui.log.start(500);
   //===========================================================================================
//initFS();
 //CAN_init(); // initSD();
 //============================================================================================================================================   
  Serial.print("ZADAch");
 // В КОНЦЕ setup() СОЗДАЕМ ЗАДАЧИ
//xTaskCreatePinnedToCore( TaskHardware,"Hardware",8192, NULL,1,NULL, 0 );
 //xTaskCreatePinnedToCore(  TaskWeb,"Web",8192,NULL,1, NULL,1);
}

void loop() { 
// vTaskDelay(1000 / portTICK_PERIOD_MS);
build();ui.tick();action();

// if (tmr4.tick())  { vbat = (analogRead(39) * 3.3 / 4096)*4.4; } // измеряем напряжениеSerial.print(vbat);
//     if (vbat < vmin) { tft.setTextSize(2);tft.setCursor(0, 0); tft.print(" bat= "); tft.print(vbat);tft.setCursor(0, 5);tft.print(" BatLow!!! ");
//      ui.log.println("ТРЕБУЕТСЯ ЗАРЯДКА АКБ.");tft.setTextSize(1); valSwitch30 = 0;valSwitch3 = 0; valSwitch15 =0; valSwitchG=0; }




// //==========================================================================================                
//     if (tmr3.tick()) {tok= (1.6 - (analogRead(36) * 3.3 / 4096))*5.34; } // ПОДОБРАТЬ КООФ ТОКА
//       if (tok > 10 )  { valSwitch30 = 0; } // защита по току
// //==========================================================================================        
//     if (valSwitch30 == 1) { digitalWrite(k61,HIGH);}  //  включаем питание рейки реле k61
//        else {digitalWrite(k61,LOW);}
//     if  (valSwitch15 == 1) {digitalWrite(k15,HIGH);}  //  включаем зажигание реле к15
//        else {digitalWrite(k15,LOW);}
       
  //  if  ((stroka == "/колонка/LADA/Granda/k61_MOD_.trc") && (valSwitch3==1)) {GEN= 0;ledcDetachPin(GEN_PIN); ledcAttachPin(GEN_PIN, 0); ledcSetup(0, 20, 8); ledcWrite(0, 127); }   //  включаем шим на выход оборотыk61_MOD_NO_Str.trc
  //     else {GEN=1;}  //ledcWriteTone(0, 0);ledcWrite(0, 0); https://docs-espressif-com.translate.goog/projects/arduino-esp32/en/latest/api/ledc.html?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru

      //analogWriteFrequency(GEN_PIN,20);analogWrite(GEN_PIN, 50);
   
   //if (( btn1 == 1 ) && (valSwitch3 == 0)) { r = 0;  valSlider = 0;  SDFunction();   }  //  включаем чтение карточки tone(tonePin, 659, 165.441);
  
   //if ((valSwitch3 == 1) && ( btn1 != 1)) {  stop=0; TXFunction(); }   else {  stop=1;} // включаем передачу в кан
   
  //  if (valSwitchG == 1) {ledcWrite(0, (2.55*valSpin2));}  //  вкл генератор //analogWriteFrequency(GEN_PIN,valSpin1);analogWrite(GEN_PIN, (2.55*valSpin2));
  //    else {if( GEN==1) {ledcWrite(0, 0);}}  
  //============================================================================================================================================

 // ekr();  




 } 
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 void initFS(){
  if (!LittleFS.begin()) Serial.println("FS Error"); 
  
   Freq = getCpuFrequencyMhz();
   // SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SD_CS); 
     tft.setCursor(0, 15); tft.print("CPU="); tft.print(Freq); tft.print("MHz");
    delay(1000); tft.fillScreen(TFT_BLACK);  
 }