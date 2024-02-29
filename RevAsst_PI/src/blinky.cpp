
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
        double distance = ultrasound_distance(2, 3);
        gpioWrite(LED_PIN, 0);
        sleep(1);
    }

    // double output = ultrasound_distance(2,3);
    // std::cout << "Distance : " << output << std::endl;

    gpioTerminate();
}
