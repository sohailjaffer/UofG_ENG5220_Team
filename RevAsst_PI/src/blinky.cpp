
#include "main.h"
#include "blinky.h"

int gpio_init(void)
{
    if (gpioInitialise() < 0)
    {
        printf("E");
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

    int input1 = 24;
    int input2 = 23;
    int speedA = 12;

    int input3 = 25;
    int input4 = 5;
    int speedB = 13;


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


     sleep(5);
    
    gpioWrite(input1, 0);  // Set input1 to HIGH
    gpioWrite(input2, 1);  // Set input2 to LOW
    gpioPWM(speedA, 255);  // Set speedA to a value between 0 and 255

    gpioWrite(input3, 0);  // Set input1 to HIGH
    gpioWrite(input4, 1);  // Set input2 to LOW
    gpioPWM(speedB, 255);  // Set speedA to a value between 0 and 255

    sleep(10);


    gpioWrite(input1, 0);  // Turn off input1
    gpioWrite(input2, 0);  // Turn off input2
    gpioPWM(speedA, 0);    // Turn off the motor

    gpioWrite(input3, 0);  // Turn off input1
    gpioWrite(input4, 0);  // Turn off input2
    gpioPWM(speedB, 0);    // Turn off the motor

    gpioTerminate();



}
