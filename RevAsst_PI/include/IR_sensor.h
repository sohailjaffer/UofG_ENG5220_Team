#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <pigpio.h>
#include <functional>
#define IRFrontSensor 9
#define IRBackSensor 11

class IR_sensor {
private:
    int IRsensorGPIO;
    std::function<void(int)> callbackFunction;

    static void sensorCallback(int gpio, int level, uint32_t tick, void* userData);

public:
    IR_sensor(int gpio);
    ~IR_sensor();
    void setCallbackFunction(std::function<void(int)> callback);
    int getIRsensorGPIO() const; 

};

#endif
