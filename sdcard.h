#ifndef SDCARD_H
#define SDCARD_H


#define SD_MOSI 13
#define SD_MISO 12
#define SD_SCLK 14
#define SD_CS   15

extern SPIClass spiSD;

#include <SD.h>
//#include <LittleFS.h>


// глобальные
extern File myFile;
extern File root;
extern String str;
extern char s;
extern uint32_t now;

extern uint8_t *fileBuffer;
extern size_t fileSize;

extern int intData[500];
extern int n;
extern int i;

// функции
void SDFunction();
void TXFunction();
void delayFunction(int t);

void initSD();
//void listDirectories(File dir, int y);

#endif