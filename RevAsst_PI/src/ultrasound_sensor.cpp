

// KEVIN MADE CHANGES HERE
#include "ultrasound_sensor.h"
#include "studio.h"
#include "pigpio.h"


void InitUltrasound(){

int timeout = 50000;

void SetupPinFutions(unit trigPin, unit echoPin)
{
    Gpio_initialise(trigPin);
    Gpio_initialise(echoPin);
    Gpio_pin_set(trigPin, GPIO_OUT);
    Gpio_pin_set(ehcoPin, GPIO_IN);
}
int getCm(unit trigPin, unit echoPin);
{
    unite64_t pulseLength = getfeedback(trigPin, echoPin);
    return pulselength / 29/ 2;
}
}