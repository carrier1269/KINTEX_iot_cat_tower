//best length 7cm ,, 40~45cm 55 decibel detected & another noising sounds like 0~120decibel not detected

#include<SoftwareSerial.h>
#include "HX711.h" 
#include <SPI.h>
#define SoundSensorPin A1
#define VREF 5.0 
#define calibration_factor -51500.0 //7050 
#define OBJECT  0xA0      // 대상 온도 커맨드
#define SENSOR  0xA1      // 센서 온도 커맨드
#define WINDOW_SIZE 5

const int chipSelectPin  = 10;
unsigned char Timer1_Flag = 0;
int  iOBJECT, iSENSOR;  // 부호 2byte 온도 저장 변수 

int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
unsigned int AVERAGED = 0;
int count = 0;
int timez = 0;
int timecount = 0;
int mbreath = 0;
int breathtime = 0;


HX711 scale(5, 4);

SoftwareSerial bt(2,3);

void setup(){
  bt.begin(9600);
  
  scale.set_scale(calibration_factor);
  scale.tare(); 
  digitalWrite(chipSelectPin , HIGH);    // SCE High Level
  pinMode(chipSelectPin , OUTPUT);        // SCE OUTPUT Mode
  SPI.setDataMode(SPI_MODE3);            // SPI Mode 
  SPI.setClockDivider(SPI_CLOCK_DIV16);  // 16MHz/16 = 1MHz
  SPI.setBitOrder(MSBFIRST);             // MSB First
  SPI.begin();                           // Initialize SPI
    
  delay(500);                             // Sensor initialization time 
  Timer1_Init();                          // Timer1 setup : 500ms(2Hz) interval
  interrupts();                           // enable all interrupts

}

int SPI_COMMAND(unsigned char cCMD)
{
    unsigned char T_high_byte, T_low_byte;
    digitalWrite(chipSelectPin , LOW);  // SCE Low Level
    delayMicroseconds(10);              // delay(10us)
    SPI.transfer(cCMD);                // transfer  1st Byte
    delayMicroseconds(10);              // delay(10us)        
    T_low_byte = SPI.transfer(0x22);   // transfer  2nd Byte
    delayMicroseconds(10);              // delay(10us) 
    T_high_byte = SPI.transfer(0x22);  // transfer  3rd Byte
    delayMicroseconds(10);              // delay(10us)
    digitalWrite(chipSelectPin , HIGH); // SCE High Level 
    
    return (T_high_byte<<8 | T_low_byte); // 온도값 return 
}
ISR(TIMER1_OVF_vect){        // interrupt service routine (Timer1 overflow)
  TCNT1 = 34286;            // preload timer : 이 값을 바꾸지 마세요.
  Timer1_Flag = 1;          // Timer 1 Set Flag
}
void Timer1_Init(void){
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 34286;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
}

void loop(){

 float voltageValue,SoundSensorRizing;
    voltageValue = analogRead(SoundSensorPin) / 256.0 * VREF;

  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = voltageValue;       // Read the next sensor value
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;
    
  SoundSensorRizing =   1.0 * AVERAGED; //NOT THE DECIBEL .. RISING THE MOMENT FROM THE SOUND SENSOR

if(SoundSensorRizing > 0)
{
  breathtime++;
    if(breathtime >= 20)
    {
      count ++;
     breathtime = 0;
    }
}

timez++;
if(timez % 10 == 0)
{
  timecount ++;
}

if(timecount >= 60)
{
  timecount = 0;
  mbreath = count;
  count = 0;
}

  double x = scale.get_units()*0.476;

   if(x >= 0 && x<=10)
   {
    x = 0.0;
   }

 
  if(Timer1_Flag){                                       // 500ms마다 반복 실행(Timer 1 Flag check)
    Timer1_Flag = 0;                                    // Reset Flag
    iOBJECT = SPI_COMMAND(OBJECT);      // 대상 온도 Read 
    delayMicroseconds(10);                              // 10us : 이 라인을 지우지 마세요 
    iSENSOR = SPI_COMMAND(SENSOR);      // 센서 온도 Read
    
   }

   bt.print(mbreath);
   bt.print("/");
   bt.print(abs(x));
   bt.print("kg");
   bt.print("/");
   bt.print(iOBJECT/100);
   bt.print("℃");
   bt.println("/");

delay(10);
}

  
