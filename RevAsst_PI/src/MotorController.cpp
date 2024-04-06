
#include "main.h"
#include "MotorController.h"

    int input1 = 24;
    int input2 = 23;
    int speedA = 12;
    int buzzer = 26;

    int input3 = 25;
    int input4 = 5;
    int speedB = 13;

int gpio_init(void)
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "GPIO Initialization failed." << std::endl;
        return 1;
    }
    return 0;
}

void test(int LED_PIN)
{

    gpio_init();

    gpioSetMode(LED_PIN, PI_OUTPUT);

    for (int i = 0; i < 10; ++i)
    {

        gpioWrite(LED_PIN, 1);
        sleep(1);
        gpioWrite(LED_PIN, 0);
        sleep(1);
    }



    gpioTerminate();
}



void testHbridge(void){
 if (gpioInitialise() < 0) {
        // Initialization failed
        return;
    }


    gpioSetMode(input1, PI_OUTPUT);
    gpioSetMode(input2, PI_OUTPUT);
    gpioSetMode(speedA, PI_OUTPUT);
    gpioSetMode(speedB, PI_OUTPUT);

    gpioWrite(input1, 1);  // Set input1 to HIGH
    gpioWrite(input2, 0);  // Set input2 to LOW
    gpioPWM(speedA, 255);  // Set speedA to a value between 0 and 255


    gpioWrite(input3, 1);  // Set input1 to HIGH
    gpioWrite(input4, 0);  // Set input2 to LOW
    gpioPWM(speedB, 255);  // Set speedA to a value between 0 and 255


     sleep(1);
    
    gpioWrite(input1, 0);  // Set input1 to HIGH
    gpioWrite(input2, 1);  // Set input2 to LOW
    gpioPWM(speedA, 255);  // Set speedA to a value between 0 and 255

    gpioWrite(input3, 0);  // Set input1 to HIGH
    gpioWrite(input4, 1);  // Set input2 to LOW
    gpioPWM(speedB, 255);  // Set speedA to a value between 0 and 255

    sleep(1);


    gpioWrite(input1, 0);  // Turn off input1
    gpioWrite(input2, 0);  // Turn off input2
    gpioPWM(speedA, 0);    // Turn off the motor

    gpioWrite(input3, 0);  // Turn off input1
    gpioWrite(input4, 0);  // Turn off input2
    gpioPWM(speedB, 0);    // Turn off the motor

    gpioTerminate();



}
void resetMotors(){

    gpioWrite(input1, 0);  // Turn off input1
    gpioWrite(input2, 0);  // Turn off input2
    gpioPWM(speedA, 0);    // Turn off the motor

    gpioWrite(input3, 0);  // Turn off input1
    gpioWrite(input4, 0);  // Turn off input2
    gpioPWM(speedB, 0);    // Turn off the motor

   // gpioTerminate();
}

void beep(int time){
  
     gpioSetMode(buzzer, PI_OUTPUT);
     gpioWrite(buzzer, 1);  // Turn off input1
     sleep(time);
     gpioWrite(buzzer, 0);  // Turn off input1


}





void terminateGPIO() {
    gpioTerminate();
}

void setMotorDirection(int input1Pin, int input2Pin, int speedPin, int direction, int speed) {
    gpioSetMode(input1Pin, PI_OUTPUT);
    gpioSetMode(input2Pin, PI_OUTPUT);
    gpioSetMode(speedPin, PI_OUTPUT);

    gpioWrite(input1Pin, direction);
    gpioWrite(input2Pin, !direction);  // Invert direction
    gpioPWM(speedPin, speed);
}

void stopMotor(int speedPin) {
    gpioPWM(speedPin, 0);  // Turn off the motor
}

void forward(int speed) {
    setMotorDirection(input1, input2, speedA, 1, speed);
    beep(0.1);

    usleep(100000);  // Sleep for 1 second (in microseconds)
    stopMotor(speedA);
}

void backward(int speed) {
    setMotorDirection(input1, input2, speedA, 0, speed);
    usleep(100000);
    stopMotor(speedA);
}

void left(int speed) {
    setMotorDirection(input3, input4, speedB, 0, speed);

    usleep(100000);
    stopMotor(speedB);
}

void right(int speed) {
    setMotorDirection(input3, input4, speedB, 1, speed);
     usleep(100000);
     stopMotor(speedB);
   // testHbridge();

}

void forwardright(int speed){

        setMotorDirection(input1, input2, speedA, 1, speed);
        setMotorDirection(input3, input4, speedB, 1, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);


    
}

void forwardleft(int speed){
        setMotorDirection(input1, input2, speedA, 1, speed);
        setMotorDirection(input3, input4, speedB, 0, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);
    
}

void backwardright(int speed){
        setMotorDirection(input1, input2, speedA, 0, speed);
        setMotorDirection(input3, input4, speedB, 1, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);

    
}void backwardleft(int speed){

        setMotorDirection(input1, input2, speedA, 0, speed);
        setMotorDirection(input3, input4, speedB, 0, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);


    
}