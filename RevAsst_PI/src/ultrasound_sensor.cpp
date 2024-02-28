#include "ultrasound_sensor.h"


//int TriggerPin = 2;
//int EchoPin= 3

int ultrasound_init(){

    if (gpioInitialise() < 0) 
	{
        // std::cerr << "pigpio initialization failed" << std::endl;
		return 1;

	}	
    return 0;
}


double ultrasound_distance(int TrigPin,int EchoPin){

    gpioWrite(TrigPin, 1);
    gpioDelay(10);
    gpioWrite(TrigPin, 0);

    while (gpioRead(EchoPin) == 0);
    uint32_t startTime = gpioTick();

    while (gpioRead(EchoPin) == 1);
    uint32_t endTime = gpioTick();

    double distance = static_cast<double>(endTime - startTime) / 58.0;

    return distance;
}