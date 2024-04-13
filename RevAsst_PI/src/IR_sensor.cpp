#include "IR_sensor.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

IR_sensor::IR_sensor(int gpio) : IRsensorGPIO(gpio) {
    // Initialize pigpio library
    if (gpioInitialise() < 0) {
        std::cout << "Sensor gpio init failed!!" << std::endl;
        return;
    }

    // Set up sensor GPIO
    gpioSetMode(IRsensorGPIO, PI_INPUT);
    gpioSetPullUpDown(IRsensorGPIO, PI_PUD_UP); // Set pull-up resistor

    // Register sensor callback function
    gpioSetISRFuncEx(IRsensorGPIO, EITHER_EDGE, 0, sensorCallback, this);
}

IR_sensor::~IR_sensor() {
    // Clean up pigpio library
    gpioTerminate();
}

void IR_sensor::setCallbackFunction(std::function<void(int)> callback) {
    callbackFunction = callback;
}

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
