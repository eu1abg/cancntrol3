#ifndef PORTAL_H
#define PORTAL_H

#include <Arduino.h>
#include <GyverPortal.h>
#include <LittleFS.h>
#include <TimerMs.h>
#include <TFT7735.h>
extern GyverPortal ui; 

///==========================================================
extern TimerMs tmr2;
// ====================== Переменные UI ======================
extern float vbat, tok,vmin;
extern String sel1,sel2,sel3 ,proshivka ,stroka; 
extern int valSelect1,btn1,sw; // выбор агрегата
extern int valSelect2; // выбор производителя
extern int valSelect3; // выбор авто
extern int valSlider;  // бар загрузки
extern int valSpin;    // время задержки передачи КАН в мс
extern int valSpin1;   // частота генератора
extern int valSpin2;   // заполнение генератора
extern bool valSwitch30;  // КЛ30
extern bool valSwitch15;  // КЛ15
extern bool valSwitch2;   // старт на зажигании
extern bool valSwitch3;   // старт
extern bool valSwitchG;   // генератор

// ====================== Строки для селекторов ======================
extern String nasos;
extern String vehle;
extern String column;
extern String blok;

extern String Alfa;
extern String Audi;
extern String BMW;
extern String Cadillac;
extern String Cevrolet;
extern String Citroen;
extern String Dodge;
extern String Renault;
extern String Fiat;
extern String Ford;
extern String Honda;
extern String Hyndai;
extern String Infiniti;
extern String JEEP;
extern String LandRover;
extern String Mazda;
extern String Mercedes;
extern String Mini;
extern String Mitsubishi;
extern String Opel;
extern String Subaru;
extern String Toyota;
extern String Volvo;
extern String VW;

extern String Nvolvo;
extern String Nscoda;
extern String Nreno;
extern String Npego;
extern String Nopel;
extern String Nmers;
extern String Nmazda;
extern String Njp;
extern String Nford;
extern String Nfiat;
extern String Ndaca;
extern String Nsitr;
extern String lada;
extern String bcitr;

// Функции UI
void build();
void action();

//void beforeRestart();

#endif
