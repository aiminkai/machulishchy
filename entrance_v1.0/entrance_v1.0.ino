#include <IRremote.h>

boolean lamp_flag=false;
boolean lamp_bra_flag=false;
boolean led_flag=false;
boolean btn_flag=false;
boolean btn;


long btn_Press_time=0;
long btn_Release_time=0;

#define  hold_time 500  // время удержания кнопки для второй функиции
#define  dbc 300        // время дребезга
#define  wait 50        // время задержки между условиями для правильной отработки всего


#define  pin_Relay_Lamp       2  // реле лампы основоного коридора
#define  pin_btn   7             // кнопка (второй контакт на земле, первый на пине 7 через подтягивающий резистор к питанию
#define  pin_Relay_Lamp_bra   4  // реле бра
#define  pin_Led   6             // led

#define RECV_PIN  12
#define IR_gnd_pin  9
#define IR_vcc_pin  10 
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
 
pinMode(pin_btn, INPUT_PULLUP);              // кнопка Lamp
pinMode(pin_Relay_Lamp, OUTPUT);             // реле Lamp 
pinMode(pin_Relay_Lamp_bra, OUTPUT);         // реле Lamp 
digitalWrite(pin_Relay_Lamp, HIGH);
lamp_flag=true; 

pinMode(pin_Led, OUTPUT);

pinMode(13, OUTPUT);
digitalWrite(13, LOW);


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
   delay (300);
//========================================= включение всего =================================================================================================================   
if (results.value == 0x2C80A857 || results.value == 0x6D79949 || results.value == 0xFA918620)

  {
  digitalWrite(pin_Relay_Lamp,HIGH);
  lamp_flag=true;
  digitalWrite(pin_Led,LOW);
  led_flag=false;
  digitalWrite(pin_Relay_Lamp_bra, HIGH); 
  lamp_bra_flag=true; 
 
  }

if  (results.value == 0x2C806A95 || results.value == 0x89211467 || results.value == 0x9593FCC || results.value == 0x78480B02)

  {
  digitalWrite(pin_Relay_Lamp,LOW);
  lamp_flag=false;
  digitalWrite(pin_Relay_Lamp_bra, LOW); 
  lamp_bra_flag=false; 
 
  }
//========================================= включение люстры =================================================================================================================
 if (results.value == 0x2C8012ED || results.value == 0x634A88E7 || results.value == 0x9C59C84C || results.value == 0x9E1E9682 || results.value == 0x650F571D)

  {digitalWrite(pin_Relay_Lamp,HIGH);
  lamp_flag=true;
  digitalWrite(pin_Led,LOW);
  led_flag=false;
  
 }

 
 if (results.value == 0x2C80F20D || results.value == 0xAFD60AA0 || results.value == 0x519314C9)
   
 {  digitalWrite(pin_Relay_Lamp,LOW);
  lamp_flag=false;

  }

//========================================= включение бра =================================================================================================================
 if (results.value == 0x2C80AA55 || results.value == 0xAC6DDC64 || results.value == 0x54FB4305 || results.value == 0x9593FCC || results.value == 0x89211467)
 
 {
  digitalWrite(pin_Relay_Lamp_bra, HIGH); 
  lamp_bra_flag=true; 
  digitalWrite(pin_Led,LOW);
  led_flag=false;
 
 }

 if (results.value == 0x5ACBE564 || results.value == 0xA69D3A05 || results.value == 0x2C80827D)
 
  {digitalWrite(pin_Relay_Lamp_bra,0); 
  lamp_bra_flag=false;  
   
  }  

//========================================= включение led =====================================================================================================================
 if (results.value == 0x40F1FA2B || results.value == 0x40F1FA2B || results.value == 0xC077253E || results.value == 0xE0B32FD9 || results.value == 0x2C806897)
 {
  digitalWrite(pin_Led, HIGH); 
  }
 if (results.value == 0xDDAD9E88 || results.value == 0x2C80B04F || results.value == 0x23BB80E1 || results.value == 0xF5088BC4)
  {
    digitalWrite(pin_Led,0); 
   }   
delay (50);
 irrecv.resume(); // считать следующее значение
   }     
//==================================== обработка кнопки Lamp ============================================================================================================================= 
   
  btn = !digitalRead(pin_btn); // считать текущее положение кнопки
  
  if (btn == 1 && btn_flag == 0 && millis() - btn_Press_time > dbc) // кнопка нажата, выставляю флаг
  {       
    btn_flag=1;
    btn_Press_time=millis();
    delay(wait);
  }

  if (btn==0 && btn_flag == 1)                      // кнопка отжата, начинаем обработку
  {
       Serial.println("0");
      btn_flag=0;
      btn_Release_time=millis();
      delay(wait);
      
    if (btn_Release_time - btn_Press_time < hold_time)
        {                                                     // если кратковременное нажатие
         lamp_bra_flag=!lamp_bra_flag;
         digitalWrite(pin_Relay_Lamp_bra,lamp_bra_flag);    // переключаю бра                  
         delay(wait);
       
        }
     else {if (btn_Release_time - btn_Press_time > hold_time)
        {                                                     // если удерживали больше hold_time
         lamp_flag=!lamp_flag;
         digitalWrite(pin_Relay_Lamp,lamp_flag);                        // переключаю лампу осн. коридора
         delay(wait);
         } 
       }
     } 
//======================= включение/выключение LED подсветки по флагам релюшек ================================================     
if (lamp_bra_flag==false && lamp_flag==false && led_flag==false)
  {
    digitalWrite(pin_Led, HIGH);
     led_flag=true;
  }
if ((lamp_bra_flag==true || lamp_flag==true) && led_flag==true)
{
    digitalWrite(pin_Led, LOW);
     led_flag=false;
  }
  
//==================================================== конец =======================================================================

}






