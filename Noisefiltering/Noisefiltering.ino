//best length 7cm ,, 40~45cm 55 decibel detected & another noising sounds like 0~120decibel not detected

#define SoundSensorPin A1
#define VREF 5.0 //voltage on AREF pin, default:operating voltage 5볼트 전압값
#define WINDOW_SIZE 5

//////

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


void setup()
{
Serial.begin(9600);
}

void loop()
{

float voltageValue,SoundSensorRizing;
voltageValue = analogRead(SoundSensorPin) / 256.0 * VREF;


  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = voltageValue;       // Read the next sensor value
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;
  
SoundSensorRizing =   1.0 * AVERAGED; //NOT THE DECIBEL .. RISING THE MOMENT FROM THE SOUND SENSOR

/*if(SoundSensorRizing >= 0.0 && SoundSensorRizing <=150.0)
{
  SoundSensorRizing = 0.0;
}*/


if(SoundSensorRizing > 0)
{
    breathtime++;
  if(breathtime >= 40)
  {
    count ++;
    breathtime = 0;
  }
}

timez++;
if(timez % 12 == 0)
{
  timecount ++;
}

if(timecount >= 60)
{
  timecount = 0;
  mbreath = count;
  count = 0;
}

Serial.print("  소리상승 횟수");
Serial.print(count);
Serial.print("  ");
Serial.println(SoundSensorRizing);

delay(10);
}
