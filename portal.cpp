#include "portal.h"

GyverPortal ui(&LittleFS);
//GyverPortal ui;   // 👈 БЕЗ LittleFS здесь
//===============================================================
TimerMs tmr2(1,1,0); // таймер на передачу кан сигналов
// ====================== Переменные UI ======================
float vbat, tok,vmin = 9.5;
String sel1 = "",sel2 = "",sel3 = "",proshivka = "Прошивка",stroka= " ";
int valSelect1 = 0,btn1,sw=0;
int valSelect2 = 0;
int valSelect3 = 0;
int valSlider = 0;
int valSpin = 0;
int valSpin1 = 400;
int valSpin2 = 50;
bool valSwitch30 = false;
bool valSwitch15 = false;
bool valSwitch2 = false;
bool valSwitch3 = false;
bool valSwitchG = false;

// ====================== Строки для селекторов ======================
String nasos = "VOLVO,SKODA,RENAULT,PEUGEOT,OPEL,MERCEDES,MAZDA,JEEP,FORD,FIAT,DACIA,CITROEN";
String vehle = "Audi,BMW,Alfa,Cadillac,Cevrolet,Citroen,Dodge,Renault,Fiat,Ford,Honda,Hyndai,Infiniti,JEEP,LandRover,Mazda,Mercedes,Mini,Mitsubishi,Opel,Subaru,Toyota,Volvo,VW";
String column = "LADA, ";
String blok = "CITROEN, ";

String Alfa = "Alfa_Giulia952(2017-), Alfa_Giulietta940(2011-17),Alfa_Mito955(2008-2013)";
String Audi ="A4(2011-2016), ";
String BMW = "3-E81(2006-2011),Z4-E85(2005-2009)";
String Cadillac = "ATS(2013-), ";
String Cevrolet = "Terrain(2009),Colorado(2015),Malibu(2015)";
String Citroen = "C3-III(2016-),C4(2014-),DS3(2012-2015)";
String Dodge = "Charger(2017-),Grand-CherokeeIV-WK-WD-WK2(2017),RAM1500-DS-DJ(2008)";
String Renault = "";
String Fiat = "500(2007-),Bravo198(2007-),Idea(2004-),Panda169(2004-),Panda312(2012-),Punto188(2007-),Punto199(2005-),Stilo192(2005-),Tipo356(2015-)";
String Ford = "Fusion(2013-),Escort(2016-),Explorer(2011-),F150(2010-),Fiesta(2008-),FocusIII(2011-),KA(2008-),Taurus(2012-),Escape (2008-)";
String Honda = "Accord-IX(2012-),AccordVIII(2008-),Civic-IX(2012-),Civic-X(2015-),CivicVIII(2006-),CRV-III(2008-2012),CRV-IV(2012-),CRV-V(2015-),HRV(2015-),JazzIII-GE(2008-)";
String Hyndai = "30-FD(2011-),i30-FD(2012-),i40-VF(2011-),Santafe(2012-),Sonata-YF(2014-),Tycson-TLE(2015-),Genesis-DH(2014-)";
String Infiniti = "Q50(2015-), ";
String JEEP = "Cheroocke KL, ";
String LandRover = "DiscoverySport-L550(2014-),DiscoveryV-L462(2016),RangeRoverEvoque-LV(2011-),RangeRoverSport-LW(2013-)";
String Mazda = "6-GH(2008-), ";
String Mercedes = "A-w169(2004-2012),C-w204(2007-),CLS-C218(2011-),M-w166(2011-)";
String Mini = "R56(2006-2013), ";
String Mitsubishi = "Colt(2004-),LancerX";
String Opel = "InsigniaB(2017-), ";
String Subaru = "Forester(2012-),Outback(2009-)";
String Toyota = "Corolla(2012-2018), ";
String Volvo = "v40, ";
String VW = "Golf5(2004-),Golf7(2015-),PassatB6,PassatB8(2014-),Tiguan";

String Nvolvo = "vo303,vo302,vo301";
String Nscoda = "sk302,sk301";
String Nreno = "re308,re307,re306,re305,re303";
String Npego = "pe316,pe313,pe309,pe305,pe304,pe303,pe302,pe301";
String Nopel = "op309,op308,op307,op305,op304";
String Nmers = "me303,me302";
String Nmazda = "ma303,ma302,ma301";
String Njp = "jp302,jp301";
String Nford = "fo308,fo306,fo305,fo304,fo302,fo301";
String Nfiat = "fi301, ";
String Ndaca = "dc301, ";
String Nsitr = "ci308,ci307,ci306,ci305,ci303,ci301";
String lada = "Granda, ";
String bcitr = "C5(2004-2008), ";
//===========================================================================================

//============================================================================================================================================
 void action() 
{ 
  //======================= Отправка данных ====================================================================
 if (ui.update()) { 
     //ui.updateInt("sw2", valSwitch2);
     //ui.updateInt("sld", valSlider);
     //ui.updateInt("sw3", valSwitch3);     
     //ui.updateInt("spn", valSpin); 
     ui.updateFloat("num", vbat); 
     ui.updateFloat("num1", tok);      
     }
  //============================= Прием данных ============================================================== 
   if (ui.click("sld")) { valSlider = ui.getInt("sld");} 
   if (ui.click("sw30")) { valSwitch30 = ui.getBool("sw30");} 
   if (ui.click("sw15")) { valSwitch15 = ui.getBool("sw15");}   
   if (ui.click("sw2")) { valSwitch2 = ui.getBool("sw2");} 
   if (ui.click("sw3")) { valSwitch3 = ui.getBool("sw3");}
   if (ui.click("swG")) { valSwitchG = ui.getBool("swG");}
   if (ui.click("spn")) { valSpin = ui.getInt("spn"); tmr2.setTime(valSpin);} 
   if (ui.click("spn1")) { valSpin1 = ui.getInt("spn1"); ledcSetup(0, valSpin1, 8); } 
   if (ui.click("spn2")) { valSpin2 = ui.getInt("spn2");}    

   if (ui.click("sel1")) {valSelect1 = ui.getInt("sel1");}  //Serial.print(test);//Serial.print(ui.clickNameSub(1));
   
    switch (valSelect1) { 
      case 0: sel2 = ""; sel3 = ""; sw = 0; break;
       case 1: sel2 = vehle; sel3 = ""; sw = 1; sel1 ="рейка"; break;
        case 2: sel2 = nasos; sel3 = ""; sw = 2; sel1 ="насос"; break;
         case 3: sel2 = column; sel3 = ""; sw = 3; sel1 ="колонка"; break;
          case 4: sel2 = blok; sel3 = ""; sw = 4; sel1 ="блоки"; break;
        }
         




    if (ui.click("sel2")) {  valSelect2 = ui.getInt("sel2"); }  
     switch(sw)  { 
      case 1:
     switch (valSelect2) {
       case 0: sel3 = Audi; break;
       case 1: sel3 = BMW; break;
       case 2: sel3 = Alfa; break;
       case 3: sel3 = Cadillac; break;
       case 4: sel3 = Cevrolet; break;
       case 5: sel3 = Citroen; break;case 6: sel3 = Dodge; break;case 7: sel3 = Renault; break;case 8: sel3 = Fiat; break;case 9: sel3 = Ford; break;case 10: sel3 = Honda; break;case 11: sel3 = Hyndai; break;
       case 12: sel3 = Infiniti; break;case 13: sel3 = JEEP; break;case 14: sel3 = LandRover; break;case 15: sel3 = Mazda; break;case 16: sel3 = Mercedes; break;case 17: sel3 = Mini; break;
       case 18: sel3 = Mitsubishi; break;case 19: sel3 = Opel; break;case 20: sel3 = Subaru; break;case 21: sel3 = Toyota; break;case 22: sel3 = Volvo; break;
       case 23: sel3 = VW; break;
      
      } 
        break;
        
      case 2:
        switch (valSelect2) { 
        case 0: sel3 = Nvolvo; break;
         case 1: sel3 = Nscoda; break; 
         case 2: sel3 = Nreno; break;
         case 3: sel3 = Npego; break;
         case 4: sel3 = Nopel; break;
        case 5: sel3 = Nmers; break; 
        case 6: sel3 = Nmazda; break;
        case 7: sel3 = Njp; break; 
        case 8: sel3 = Nford; break;
        case 9: sel3 = Nfiat; break;
        case 10: sel3 = Ndaca; break; 
        case 11: sel3 = Nsitr; break; }
        break;
      case 3: 
       switch (valSelect2)
      {case 0: sel3 = lada; break;}     // надо дорабатывать для передачи по лин шине 
      break;
      case 4:
       switch (valSelect2)
      {case 0: sel3 = bcitr; break;}
      break;
     }
   
   
   if (ui.click("sel3")) {  valSelect3 = ui.getInt("sel3"); }
   //===========================================================================================
   ui.updateInt("sld", valSlider);
//=======================  считываем файл с SD  =====================================================================================================================
  if (ui.click("btn")) // если приняли сигнал о чтении S
  {  btn1 = 1; stroka ="";
  stroka += "/"; stroka += sel1; stroka+="/";stroka += GPlistIdx(sel2,valSelect2); stroka+="/";stroka += GPlistIdx(sel3,valSelect3);stroka+="/"; 
  if (valSwitch2 == 1) {stroka+="k15_MOD_.trc";}  // k15_MOD_NO_Str.trc
   else {stroka+="k61_MOD_.trc";}  //k61_MOD_NO_Str.trc
   Serial.println(stroka);
   Serial.print("GPlistIdx(sel3,valSelect3)=");Serial.println(GPlistIdx(sel3,valSelect3));} }
//===========================================================================================
 void build() {
 GP.BUILD_BEGIN(GP_DARK,800); 
 //.................................................................................................................................
 GP.UPDATE("t1,lb,lbb,ch,led,sw,txt,num,num1,pass,sld,date,time,spn,col,sel1,sel2,sel3,rad");
 GP.RELOAD_CLICK("sel1,sel2,sel3"); 
   
 //.................................................................................................................................
 GP.SPOILER_BEGIN("CAN Controll v1.01.",GP_BLUE_B);
 GP.LABEL("Программа запуска ЭУР, насосов ЭГУР и других блоков управления.", "t1", GP_ORANGE_B, 15); GP.BREAK();
 GP.LABEL("**Produced by Labada Studio** ", "t2", GP_ORANGE_B, 15,0,0); GP.BREAK();
 GP.LABEL("EPS-Minsk.by", "t3", GP_ORANGE_B, 20);GP.SPOILER_END();    
 //.................................................................................................................................
 GP.GRID_RESPONSIVE(700);
 M_GRID( 
   GP.BLOCK_BEGIN(GP_TAB,"100%","Выбор", GP_YELLOW);
   M_BOX(GP.LABEL("Агрегат"); GP.SELECT("sel1", "Выбрать,Рейка,Насос,Колонка,Блоки", valSelect1); ) //GP.RELOAD_CLICK("sel1");
   M_BOX(GP.LABEL("Производитель"); GP.SELECT( "sel2",sel2 , valSelect2 ); ) //GP.RELOAD_CLICK("sel2");

   M_BOX(GP.LABEL("Авто"); GP.SELECT("sel3", sel3, valSelect3); ) //GP.RELOAD_CLICK("sel3"); 

   GP.BLOCK_END(); 
 
   GP.BLOCK_BEGIN(GP_TAB,"100%","Загрузить TRACE", GP_YELLOW);GP.BUTTON("btn", "Загрузка","",GP_BLUE_B,"40%");//GP.RELOAD_CLICK("btn");
   GP.LABEL("Loading");GP.BREAK(); GP.SLIDER("sld", valSlider, 0, 2000, 1, 0, GP_ORANGE_B);
   GP.BLOCK_END();
 );
//.................................................................................................................................
 M_GRID( 
   GP.BLOCK_BEGIN(GP_THIN,"100%","Генератор", GP_YELLOW );
   
   M_BOX(GP_RIGHT,GP.SPAN("Fr.",GP_RIGHT,"",GP_GREEN); GP.SPINNER("spn1", valSpin1, 0, 5000,5,0,GP_GREEN,"65px");
   GP.SPAN("  Dut.",GP_RIGHT,"",GP_GREEN); GP.SPINNER("spn2", valSpin2, 0, 255,1,0,GP_GREEN,"60px"););
   M_BOX(GP_CENTER,GP.SPAN("Gen. ON  ",GP_LEFT,"",GP_GREEN);GP.SWITCH("swG", valSwitchG,GP_GREEN_B););   
    GP.BLOCK_END();

   GP.BLOCK_BEGIN(GP_THIN,"100%","Питание", GP_YELLOW );
   M_BOX(GP_CENTER,GP.SPAN("НАПР. ",GP_LEFT,"",GP_YELLOW);GP.NUMBER_F("num", "Vbat.", vbat, 2,"70px");
   GP.SPAN("  ТОК. ",GP_LEFT,"",GP_YELLOW);GP.NUMBER_F("num1", "I.", tok, 2,"70px"););
   M_BOX(GP_CENTER,GP.SPAN("K30. ",GP_JUSTIFY,"",GP_YELLOW);GP.SWITCH("sw30", valSwitch30,GP_YELLOW_B);GP.SPAN("  K15. ",GP_JUSTIFY,"",GP_YELLOW);
   GP.SWITCH("sw15", valSwitch15,GP_YELLOW_B);   
   );
 
 GP.BLOCK_END();

 );
 //................................................................................................................................. 
 M_GRID(  GP.BLOCK_BEGIN(GP_THIN,"100%","Монитор CAN Tx", GP_YELLOW);
    M_BOX(GP.AREA_LOG(3,1000,"300px"););GP.BLOCK_END();  //GP.SPAN("TX",GP_LEFT);
   
 
  GP.BLOCK_BEGIN(GP_THIN,"100%","Запуск", GP_YELLOW);M_BOX( GP.SPAN("Без запуска двигателя.",GP_LEFT,"",GP_ORANGE);GP.SWITCH("sw2", valSwitch2,GP_ORANGE_B); );
   M_BOX(GP.SPAN("Запуск двигателя.",GP_LEFT,"",GP_ORANGE);GP.SWITCH("sw3", valSwitch3, GP_ORANGE_B););GP.BLOCK_END(););
   //.................................................................................................................................
 GP.SPOILER_BEGIN("Пакеты CAN",GP_YELLOW); GP.LABEL("CAN(ms)"); GP.SPINNER("spn", valSpin, 0, 1000,50,0,GP_BLUE); GP.SPOILER_END();
 //.................................................................................................................................
 GP.SPOILER_BEGIN("Update",GP_BLUE); GP.LABEL("Загрузить новую прошивку. ", "t2", GP_ORANGE_B, 20); GP.OTA_FIRMWARE(proshivka, GP_ORANGE_B); GP.SPOILER_END();
 //.................................................................................................................................
 GP.BUILD_END();}
 //============================================================================================
// void beforeRestart() {oled.clear(); oled.setScale(1);  oled.setCursor(5, 2); oled.print("   Update OK !!!  "); oled.setCursor(5, 5); oled.print("Restart.....");delay(5000);}