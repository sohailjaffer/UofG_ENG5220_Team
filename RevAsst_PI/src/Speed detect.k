#include <studio.h>
import RPi.GPIO as GPIO
int flag1 = 0;
int flag2 = 0;

void setup()
{
GPIO.setup(trigPin, OUTPUT);
GPIO.setup(echoPin, INPUT);
Serial(115200);
}
void loop()
{
if(DigitalRead(trigpin == 0 LOW && flag1 == 0))
{
timer1 = millis();
flag1 = 1
}
else if(DigitalRead(echoPin == 0 LOW && flag2 == 0))
{
timer2 = millis();
flag2 = 1;
}
}

if (flag1 = 1 && flag2 = 1){
if(timer1 > time2){
Time = time1 - timer2
}
else if (time1 < time2 ){
Time = time2 - timer1
}
}
Time = Time / 1000;
speed = (distance / Time);
print("Speed: %.20f cm/s" % speed)
