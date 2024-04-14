#include "IR_sensor.h"
#include "MotorController.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

IR_sensor::IR_sensor(int gpio) : IRsensorGPIO(gpio) {


#ifdef USE_GPIOd

struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        perror("GPIOchip0 failed\n");
        return;
    }

    struct gpiod_line *lineIR = gpiod_chip_get_line(chip, IRsensorGPIO);
    if (!lineIR) {
        perror("Get line for IR sensor failed\n");
        gpiod_chip_close(chip);
        return;
    }

    gpiod_line_request_input(lineIR, "IR-sensor");

    gpiod_line_request_both_edges_events(lineIR, "IR-sensor-events");

    gpiod_line_release(lineIR);
    gpiod_chip_close(chip);


#else
    // Initialize pigpio library
    if (gpioInitialise() < 0) {
        std::cout << "Sensor gpio init failed!!" << std::endl;
        return;
    }

    gpioSetMode(IRsensorGPIO, PI_INPUT);
    gpioSetPullUpDown(IRsensorGPIO, PI_PUD_UP); // Set pull-up resistor

    gpioSetISRFuncEx(IRsensorGPIO, EITHER_EDGE, 20, sensorCallback, this); // Debounce set to 20ms 

#endif
}

IR_sensor::~IR_sensor() {
#ifndef USE_GPIOd
    gpioTerminate();
#endif
}

// function to set the callback function of the IR sensor

void IR_sensor::setCallbackFunction(std::function<void(int)> callback) {
    callbackFunction = callback;
}
// GPIO ISR callback function 
void IR_sensor::sensorCallback(int gpio, int level, uint32_t tick, void* userData) {
    IR_sensor* sensor = static_cast<IR_sensor*>(userData);

    // Call the callback function with sensor GPIO
    if (sensor->callbackFunction) {
        sensor->callbackFunction(sensor->IRsensorGPIO);
    }
}

int IR_sensor::getIRsensorGPIO() const {
    return IRsensorGPIO;
}
