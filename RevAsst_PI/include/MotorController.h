#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#undef USE_GPIOd 

#include <stdio.h>
#include "pigpio.h"
#include "gpiod.h"

 // For forward and backward motor control for H bridge

#define  input1     24
#define  input2     23
#define  speedA     12
#define  buzzer     26

 // For left and right motor control for H bridge
#define  input3     25
#define  input4     5
#define  speedB     13

class MotorController {
public:


        void forward(int speed);
        void backward(int speed);
        void left(int speed);
        void right(int speed);
        void forwardRight(int speed);
        void forwardLeft(int speed);
        void backwardRight(int speed);
        void backwardLeft(int speed);
        void resetMotors();
        void beep(int time);
        void terminateGPIO();
        void motorHandler(char *buffer);
        void reverseAssistHandler(char *buffer);


private:
   

        int gpioInit(void);
        void test(int LED_PIN);
        void testHbridge();
        void setMotorDirection(int input1Pin, int input2Pin, int speedPin, int direction, int speed);
        void stopMotor(int speedPin);
    };

#endif // MOTORCONTROLLER_H
