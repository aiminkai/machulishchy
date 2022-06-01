#include <IRremote.h>

boolean flag_led_B=false;     // флаг синего
boolean flag_led_W=false;     // флаг led обычного
boolean flag_lamp=false;      // флаг ламп 220В

int a = 5;

#define  pin_led_W       6         // реле led обычной + ШИМ
#define  pin_led_B       5         // реле led синий  + ШИМ
#define  pin_lamp        3         // лампы 220В

#define RECV_PIN       11
#define IR_gnd_pin      8
#define IR_vcc_pin     9 
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
 
pinMode(pin_led_W, OUTPUT);             // реле led W 
pinMode(pin_led_B, OUTPUT);             // реле led B 
pinMode(pin_lamp, OUTPUT);              // реле Lamp

digitalWrite(pin_lamp, HIGH);           // включить лампу по старту
flag_lamp=true; 
analogWrite(pin_led_W, 255);           // включить led W по старту
flag_led_W=true; 
digitalWrite(pin_led_B, LOW);           // выключить синюю
flag_led_B=false; 

pinMode(IR_gnd_pin, OUTPUT); 
pinMode(IR_vcc_pin, OUTPUT);
digitalWrite(IR_gnd_pin, LOW);
digitalWrite(IR_vcc_pin, HIGH);
irrecv.enableIRIn();


Serial.begin(9600);

}

void loop() 
{
   
   if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
   
//========================================= включение/выключение всего =================================================================================================================   
if (results.value == 0x2C80A857 || results.value == 0x6D79949 || results.value == 0xFA918620)

  {
  a=5;

  digitalWrite(pin_led_B,HIGH);
  flag_led_B=true;
  }

if  (results.value == 0x2C806A95 || results.value == 0x89211467 || results.value == 0x9593FCC || results.value == 0x78480B02 || results.value == 0xF80FDF9D)

  {
  a=0;
  
  digitalWrite(pin_led_B,LOW);
  flag_led_B=false;
 
  }

//========================================= включение дневного (выключение синего), кнопка R =================================================================================================================

if (results.value == 0x2C80708F || results.value == 0xC4B41C8B || results.value == 0x3CB502DE || results.value == 0x3A9901F0)
{
  a=5;
  
  digitalWrite(pin_led_B,LOW);
  flag_led_B=false;  
}
//========================================= выключение всего, кнопка L =================================================================================================================

if (results.value == 0x2C8048B7 || results.value == 0x7367DA67 || results.value == 0xE26D9CC || results.value == 0x8E014502 || results.value == 0xF342459D)
{
  a=0;
 
  digitalWrite(pin_led_B,LOW);
  flag_led_B=false;  
}

//========================================= включение синего, кнопка вверх =================================================================================================================

if (results.value == 0x2C8042BD || results.value == 0xB2B712A7 || results.value == 0x4EB20CC2 || results.value == 0x9C806D5D || results.value == 0x64E8B20C)
{
  a=0;

  digitalWrite(pin_led_B,HIGH);
  flag_led_B=true;  
}

/* кнопка вниз
if (results.value == 0x2C80D02F || results.value == 0x1561E060 || results.value == 0xEC073F09)
{
 digitalWrite(pin_led_W,HIGH);
  flag_led_W=true;
  digitalWrite(pin_led_B,LOW);
  flag_led_B=false;  
}
*/

//========================================= включение лампы, диммирование led на увеличение, кнопка вправо =================================================================================================================

if (results.value == 0xAA792E0F || results.value == 0x2C8050AF || results.value == 0xDB591D74 || results.value == 0x56EFF15A)
{ a=a+1;}

if (results.value == 0x2C80E21D || results.value == 0xF5088BC4 || results.value == 0xC6093A5)
{ a=a-1;}

if (a==0) 
  {analogWrite(pin_led_W,0);
  Serial.println('0');
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
   }

  if (a==1) 
  {analogWrite(pin_led_W,10);
  Serial.println('1');
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
   }
  if (a==2)
  {analogWrite(pin_led_W,63);
  Serial.println('2');
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
  }
  
  if (a==3)
  {analogWrite(pin_led_W,150);
  Serial.println('3');
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
  }
  
  if (a==4)
  {analogWrite(pin_led_W,255);
  Serial.println('4');
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
  }
   
  if (a==5)
  {
    analogWrite(pin_led_W, 255);
    digitalWrite(pin_lamp,HIGH);
    flag_lamp=true; 
    digitalWrite(pin_led_B,LOW);
    flag_led_B=false; 
    Serial.println('5');
  }

  if (a>5)
  {a=5;} 
   if (a<0)
  {a=0;}
 

//====================================================
irrecv.resume(); // считать следующее значение
   }  


//==================================================== конец =======================================================================
}








