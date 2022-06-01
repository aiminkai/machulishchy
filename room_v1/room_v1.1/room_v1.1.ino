#include <IRremote.h>

boolean flag_led_B=false;     // флаг синего
boolean flag_led_W=false;     // флаг led обычного
boolean flag_lamp=false;      // флаг ламп 220В

int a = 5;

#define  pin_led_W       6         // реле led обычной + ШИМ
#define  pin_led_B       5         // реле led синий  + ШИМ
#define  pin_lamp        17         // лампы 220В a3

#define RECV_PIN        12
//#define IR_gnd_pin       8
//#define IR_vcc_pin       9 
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
 
pinMode(pin_led_W, OUTPUT);             // реле led W 
pinMode(pin_led_B, OUTPUT);             // реле led B 
pinMode(pin_lamp, OUTPUT);              // реле Lamp

digitalWrite(pin_lamp, HIGH);           // включить лампу по старту
flag_lamp=true; 
analogWrite(pin_led_W, 130);           // включить led W по старту
flag_led_W=true; 
digitalWrite(pin_led_B, LOW);           // выключить синюю
flag_led_B=false; 

//pinMode(IR_gnd_pin, OUTPUT); 
//pinMode(IR_vcc_pin, OUTPUT);
//digitalWrite(IR_gnd_pin, LOW);
//digitalWrite(IR_vcc_pin, HIGH);
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
    W_ON ();
    //B_switch (1);
  }

if  (results.value == 0x2C806A95 || results.value == 0x89211467 || results.value == 0x9593FCC || results.value == 0x78480B02 || results.value == 0xF80FDF9D)

  {
    W_OFF ();
    B_switch (0);
  }

//========================================= включение дневного (выключение синего), кнопка R =================================================================================================================

if (results.value == 0x2C80708F || results.value == 0xC4B41C8B || results.value == 0x3CB502DE || results.value == 0x3A9901F0)
{
  W_ON ();
  B_switch (0);
}
//========================================= выключение всего, кнопка L =================================================================================================================

if (results.value == 0x2C8048B7 || results.value == 0x7367DA67 || results.value == 0xE26D9CC || results.value == 0x8E014502 || results.value == 0xF342459D)
{
  W_OFF ();
  B_switch (0); 
}

//========================================= включение синего, кнопка вверх =================================================================================================================

if (results.value == 0x2C8042BD || results.value == 0xB2B712A7 || results.value == 0x4EB20CC2 || results.value == 0x9C806D5D || results.value == 0x64E8B20C)
{
  W_OFF ();
  B_switch (1);
}

//========================================= включение лампы, диммирование led на увеличение/уменьшение, кнопка вправо/влево =================================================================================================================

if (results.value == 0xAA792E0F || results.value == 0x2C8050AF || results.value == 0xDB591D74 || results.value == 0x56EFF15A)
    { 
     a=a+1;
     PWM ();
    }

if (results.value == 0x2C80E21D || results.value == 0xF5088BC4 || results.value == 0xC6093A5)
    { 
    a=a-1;   
    PWM();
    }

 Serial.println(a);
//====================================================
irrecv.resume(); // считать следующее значение

   }  


//==================================================== конец =======================================================================
}

//==================================================== функции ===============================================================
void PWM ()
{
if (a==0) 
   {
    W_OFF ();
    B_switch (0);
   }

  if (a==1) 
  { analogWrite(pin_led_W,0);
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
  B_switch (1);
   }
  if (a==2)
  {analogWrite(pin_led_W,10);
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
  B_switch (1);
  }
  
  if (a==3)
  {analogWrite(pin_led_W,60);
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
  B_switch (1);
  }
  
  if (a==4)
  {analogWrite(pin_led_W,150);
  digitalWrite(pin_lamp,LOW);
  flag_lamp=false; 
  B_switch (0);
  }
   
  if (a==5)
  {
   W_ON ();
   B_switch (0);
  }

  if (a>5)
  {a=5;} 
   if (a<0)
  {a=0;}
   
}
//================================================================ вкл/выкл ВСЕ дневное ====================================

void W_ON ()
 {
    analogWrite(pin_led_W, 130);
    digitalWrite(pin_lamp,HIGH);
    flag_lamp=true; 
    a=5;
 }

void W_OFF ()
  {
    analogWrite(pin_led_W,0);
    digitalWrite(pin_lamp,LOW);
    flag_lamp=false; 
    a=0;
   }

//============================================================= вкл/выкл синего =================================

void B_switch (boolean mode)
 {
    digitalWrite(pin_led_B,mode);
    flag_led_B=mode;
 }




