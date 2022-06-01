#include <IRremote.h>

boolean flag_ON=false;     // флаг включена подсветка


#define  pin_rele        5         // реле для подсветки
#define RECV_PIN        7

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
 
pinMode(pin_rele, OUTPUT);             // реле 
digitalWrite(pin_rele, LOW);           // включить подсветку по старту
flag_ON=true; 

irrecv.enableIRIn();

}

void loop() 
{
   
   if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
   
//========================================= включение/выключение всего =================================================================================================================   
if (results.value == 0x2C80A857 || results.value == 0x6D79949 || results.value == 0xFA918620)
  {
    digitalWrite(pin_rele, LOW);           // включить подсветку 
    flag_ON=true; 
  }

if  (results.value == 0x2C806A95 || results.value == 0x89211467 || results.value == 0x9593FCC || results.value == 0x78480B02 || results.value == 0xF80FDF9D)
  {
   digitalWrite(pin_rele, HIGH);           // выключить подсветку 
   flag_ON=false; 
  }

//========================================= включение дневного (выключение синего), кнопка R =================================================================================================================
if (results.value == 0x2C80708F || results.value == 0xC4B41C8B || results.value == 0x3CB502DE || results.value == 0x3A9901F0)
{
   digitalWrite(pin_rele, LOW);           // включить подсветку 
   flag_ON=true; 
}

//========================================= выключение всего, кнопка L =================================================================================================================
if (results.value == 0x2C8048B7 || results.value == 0x7367DA67 || results.value == 0xE26D9CC || results.value == 0x8E014502 || results.value == 0xF342459D)
{
   digitalWrite(pin_rele, HIGH);           // выключить подсветку 
   flag_ON=false; 
 }

//========================================= включение кнопка вверх =================================================================================================================
if (results.value == 0x2C8042BD || results.value == 0xB2B712A7 || results.value == 0x4EB20CC2 || results.value == 0x9C806D5D || results.value == 0x64E8B20C)
{
   digitalWrite(pin_rele, LOW);           // включить подсветку 
   flag_ON=true; 
}

//========================================= выключение всего, кнопка вниз =================================================================================================================
if (results.value == 0x2C80D02F || results.value == 0x1561E060 || results.value == 0xEC073F09 || results.value == 0x8E014502 || results.value == 0xF342459D)
{
    digitalWrite(pin_rele, HIGH);           // выключить подсветку 
    flag_ON=false; 
}



//====================================================
irrecv.resume(); // считать следующее значение

   }  


//==================================================== конец =======================================================================
}

//==================================================== функции ===============================================================
