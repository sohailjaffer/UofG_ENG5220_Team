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


extern void forwardright(int speed);
extern void forwardleft(int speed);
extern void backwardleft(int speed);
extern void backwardright(int speed);

extern void resetMotors();

extern void beep(int time);

void terminateGPIO();

extern void MotorCallback(char * buffer);
extern void ReverseAssistCallback(char * buffer);




