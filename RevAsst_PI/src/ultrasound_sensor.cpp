#include "ultrasound_sensor.h"
#include <main.h>


//int TriggerPin = 2;
//int EchoPin= 3
#include <iostream>
#include <pigpio.h>
#include <unistd.h>

int ultrasound_init() {
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed" << std::endl;
        return 1;
    }
    return 0;
}

double ultrasound_distance(int TrigPin, int EchoPin) {
    gpioSetMode(TrigPin, PI_OUTPUT);
    gpioSetMode(EchoPin, PI_INPUT);

    gpioWrite(TrigPin, 0);
    gpioDelay(2);  // Ensure trigger pin is low for at least 2 microseconds

    gpioWrite(TrigPin, 1);
    gpioDelay(10); // Send a 10 microsecond pulse on the trigger pin
    gpioWrite(TrigPin, 0);

    uint32_t startTime, endTime;
    int timeout = 50000;  // Timeout in microseconds (50ms)
    
    // Wait for the echo pin to go high
    while (gpioRead(EchoPin) == 0 && timeout > 0) {
        startTime = gpioTick();
        timeout--;
    }
    
    // Wait for the echo pin to go low
    while (gpioRead(EchoPin) == 1 && timeout > 0) {
        endTime = gpioTick();
        timeout--;
    }

    if (timeout == 0) {
        std::cerr << "Ultrasound sensor timeout" << std::endl;
        return -1.0;  // Return negative value to indicate error
    }

    double pulseDuration = static_cast<double>(endTime - startTime);
    double distance = (pulseDuration * 0.0343) / 2; // Speed of sound is approximately 343 m/s

    return distance;
}

void * ultSoundThread(void * arg) {
    int echo = 11;  // Example pin numbers, replace with actual pin numbers
    int trig = 6;
    ultrasound_init();

    std::cout << "Ultrasound starting....  : "  << std::endl;

    while (true) {
        double distance = ultrasound_distance(trig, echo);
        if (distance >= 0) {
            std::cout << "Distance  : " << distance << " cm" << std::endl;
        } else {
            std::cerr << "Error measuring distance" << std::endl;
        }
        sleep(1);
    }

    pthread_exit(NULL);
}


