#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <pigpio.h>
#include <functional>
#define IRFrontSensor 9
#define IRBackSensor 11


/**
 * 
 * @brief This class offers functionality to implement IR sensor via interrupts 
*/

class IR_sensor {
private:
    int IRsensorGPIO;
    std::function<void(int)> callbackFunction;
    /**
     * 
     * @brief Callback invoked by the GPIO interrupt
     * 
     * @param gpio gpio pin number
     * @param level priority level 
     * @param tick The system tick during intterupt
     * @param userData IR distance data 
     *
     * 
    */

    static void sensorCallback(int gpio, int level, uint32_t tick, void* userData);

public:
    IR_sensor(int gpio);
    ~IR_sensor();

      /**
     * @brief Sets the callback function for IR sensor events.
     * This function sets the callback function to be invoked when an event
     * occurs on the IR sensor GPIO pin.
     * 
     * @param callback The callback function to be set.
     */

    void setCallbackFunction(std::function<void(int)> callback);
    int getIRsensorGPIO() const; 

};

#endif
