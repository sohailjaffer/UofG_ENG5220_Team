#include "studio.h"
#include "WritingPi.h"


void InitUltrasound()
{

int timeout = 50000;

void SetupPinFutions(uint8_t trigPin, uint8_t echoPin)
{
    digitalWrite(trigPin, GPIO_OUT);
    digitalWrite(ehcoPin, GPIO_IN);
}
While()
{
digtalwrite(TRIG_PIN, LOW);
gpio.tick(10);
digitalwrite(TRIG_PIN, HIGH);
gpio.tick(50);

while (digitalRead(ECHO_PIN) == LOW);
        long startTime = micros();

while (digitalRead(ECHO_PIN) == HIGH);
long endTime = micros();
}
int getCm(uint8_t trigPin, uint8_t echoPin);
{
    unite64_t pulseLength = getfeedback(trigPin, echoPin);
    return pulselength / 29/ 2;
}

}
