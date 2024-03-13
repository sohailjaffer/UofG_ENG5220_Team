#pragma once
#include <stdio.h>
#include "pigpio.h"


extern int gpio_init(void);
extern void test(int LED_PIN);
void testHbridge(void);


extern void forward(int speed);
extern void backward(int speed);
extern void right(int speed);
extern void left(int speed);
extern void resetMotors();
void terminateGPIO();


