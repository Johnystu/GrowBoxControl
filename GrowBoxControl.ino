#include <EEPROM.h>
#include <iarduino_Encoder_tmr.h>             //  Подключаем библиотеку iarduino_Encoder_tmr для работы с энкодерами через аппаратный таймер
iarduino_Encoder_tmr enc(4,3);   
int    i = 0;  
int _i = 0;
#include <SPI.h>
#include <Wire.h>

#include <Time.h>
#include <DS1307RTC.h>
tmElements_t tm;

#include "DHT.h"
#define DHTPIN 6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//ds1820 temp
#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 3
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
//float in_tempC;
//float out_tempC;
//--ds1820


#define I2C_ADDRESS 0x3C
//#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

SSD1306AsciiAvrI2c display;


#define buttonPin  2     // кнопка эенкодера
#define Btn digitalRead(buttonPin)

unsigned long updateSensorTime;
unsigned long stopTime;

struct eepromStatusByte{ //битовое поле
  
};


struct sensor
{
  int SensorPin;
  byte SensorPin_E; //eeprom 
  
  int RelePin;
  byte RelePin_E;
  
  int ContactL;
  int ContactL_E;
  
  int ContactH;
  int ContactH_E;
  
  int PV;
  int timePV_Update;
  int timePV_Update_E; //time to update sensor
  
  unsigned long prevTime;

//  String Name;
  
  bool Mode; //1 бит адресса CSAdress_E
  bool Start; //2 бит адресса CSAdress_E
  bool IsRun; 
  bool dryRunProtec; //3 бит адресса CSAdress_E
  byte CSAdress_E;  
  bool dryRunAlmIsActive;
 
//  bool Stop;

  
  bool flagIsRun;
  int almEmptyTank;
  int almEmptyTank_E;
  unsigned long prevTimeEmptyTank;
  
  void stop(){
    Start = write_bit_E(0, 2);
    IsRun = 0;

    
  }

  void dryRunProtection()
  {
    if(dryRunProtec)
    {
      if (!Mode)
      {
        if (IsRun)
        {
          if(flagIsRun)
          {
            if((millis()-prevTimeEmptyTank)>(almEmptyTank*1000))
            {
              stop();
              dryRunAlmIsActive = 1;
            }
          }else{flagIsRun = 1; prevTimeEmptyTank = millis();}
        }else {flagIsRun = 0;}
      }
    }
  }
    
  
  void CV()
  {
   if (Start){
     if (!Mode){
       if (PV < ContactL){
         IsRun = true;
       }
       if (PV > ContactH){
         IsRun = false;
       }
     }else{IsRun = true;}
   }else{IsRun = false;}
  dryRunProtection(); 
  


  }


  void write_value_analog(int addres, int &par)
  {
  
 //   digitalWrite(13, HIGH);
    unsigned int memEncoder_position = i; //запоминаем значение энкодера
    unsigned int x;//вводим новую переменную
    //i = EEPROM.read(addres);
    i = EEPROM_uint_read(addres);
    display.print(i);     
    
    while(!Btn)
    {
      x = i;
      unsigned int a=enc.read();                         //  Читаем состояние энкодера в переменную a
      if(a){i=i+a;}                     //  Если энкодер зафиксировал поворот, то ...
         /* i+=a*/                    //  Меняем значение переменной i на 1, т.к. в переменной a находится -1 (при повороте влево), или +1 (при повороте вправо).
     unsigned int s;
     if (s!=x){  display.clear(); s=x;}
    //  display.clearDisplay();
      display.setCursor(0,0);
      
      //EEPROM.update(addres, x);
      EEPROM_uint_write(addres, x);
      display.println(x);
   //   display.display();
      
    }//while
    par = EEPROM_uint_read(addres);
    i=memEncoder_position; //возвращаем значение энкодера в исходное значение
  
//    digitalWrite(13, LOW);
  
  }
  
  bool write_bit_E(bool par, byte n_bit) //метод записи бита в память EEPROM
  {
    byte eeprom_byte = EEPROM.read(CSAdress_E); // читем байт из памяти  
    bool eeprom_bit = bitRead(eeprom_byte, n_bit); 
  
    bitWrite(eeprom_byte, n_bit, par);
    EEPROM.update(CSAdress_E, eeprom_byte);
    return par;
  }

  bool read_bit_E(int n_bit)
  {
    byte r_byte = EEPROM.read(CSAdress_E); 
    bool x = bitRead(r_byte, n_bit);
    return x;

  }
  
}; sensor poliv, heating;

sensor *_poliv = &poliv; 
sensor *_heating = &heating; 

struct timer : sensor{
int timeOnMinute;
int timeOffMinute;

int timeOnHour;
int timeOffHour;

int timeOnMinute_E;
int timeOffMinute_E;

int timeOnHour_E;
int timeOffHour_E;


//int timeOn;
int TimeOFF;

int duration;
int FullMinutesTimerOn;
int FullMinutesTimerOff; 

bool flagIsRun;
//  int Hour = RTC.get(DS1307_HR, true); 
//  int Minute = RTC.get(DS1307_MIN, false); 
//  int Second = RTC.get(DS1307_SEC, false); 

  void CT()
  {
   if (Start){
     if (!Mode){
       if ((tm.Hour >= timeOnHour && tm.Minute >= timeOnMinute) && !flagIsRun){
         IsRun = true;
         flagIsRun = true;
       }
       if ((tm.Hour >= timeOffHour && tm.Minute >= timeOffMinute) && flagIsRun){
         IsRun = false;
         flagIsRun = false;
       }
     }else{IsRun = true;}
   }else{IsRun = false;}
  }




}; timer timer1;
timer *_timer1 = &timer1;

void setup() {
  dht.begin();
  enc.begin(); 
 
  digitalWrite(5,HIGH);
  delay(4);   
  poliv.PV =+ map(analogRead(poliv.SensorPin), 900, 100, 0, 100);
  digitalWrite(5,LOW);

  heating.PV = dht.readTemperature();

  display.begin(&Adafruit128x64, I2C_ADDRESS);
  display.setFont(Adafruit5x7);

  initialization_eeprom();

  pinMode(buttonPin, INPUT); 
  pinMode(5, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT);
  digitalWrite(8,HIGH);

  digitalWrite(buttonPin, HIGH);

  display.clear();
}

void loop() {

//  display.setCursor(0,0);
//  display.println("PRESS BTN");
//
//
//  display.print("PV= "); 
//  display.print(poliv.PV);
//  display.println(" "); 
// 
  display.print("H air: "); 
  display.println(dht.readHumidity());

  display.print("T air: "); 
  display.println(heating.PV);
//  
if (poliv.dryRunAlmIsActive)  {display.println("ALARM_DRY_RUN");} 


  heating.CV();
  poliv.CV();
  timer1.CT();
//  poliv.dryRunProtection(); 
  encoder();
 
    if ((millis()- heating.prevTime)>(heating.timePV_Update*1000)){
    heating.PV = dht.readTemperature();
    heating.prevTime = millis();
  }

 
   if ((millis()- poliv.prevTime)>(poliv.timePV_Update*1000)){
    digitalWrite(5,HIGH);
    delay(2);   
    poliv.PV =+ map(analogRead(poliv.SensorPin), 900, 100, 0, 100);
    digitalWrite(5,LOW);
    poliv.prevTime = millis();
  }
  
  digitalWrite(poliv.RelePin, poliv.IsRun);
  digitalWrite(heating.RelePin, !heating.IsRun);
  digitalWrite(timer1.RelePin, !timer1.IsRun);  
  
  
  display.print("PV:"); 
  display.print(poliv.PV);
  display.println("%"); 
  
    RTC.read(tm);
    print2digits(tm.Hour);
    display.print(':');
    print2digits(tm.Minute);
    display.print(':');
    print2digits(tm.Second);
    display.print(" ");
    display.print(tm.Day);
    display.print('/');
    display.print(tm.Month);
    display.print('/');
    display.print(tmYearToCalendar(tm.Year));
    display.println();
// 
//  if (_i != i) {display.clear(); _i=i;} 
//  if (i > count_recipe-1){i=0;}
//  if (i < 0){i= count_recipe - 1;}   
  
//  if (!Btn){
//    delay(500);
    screen_menu();
    //screen_sensor((*_poliv));
//    }

}//loop

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    display.write('0');
  }
  display.print(number);
}
