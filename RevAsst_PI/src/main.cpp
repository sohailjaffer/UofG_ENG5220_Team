#include "main.h"
#include "pigpio.h"
#include <iostream>
#include "unistd.h"
#include "ultrasound_sensor.h"
const int LED_PIN = 2;
int main() {
	
	if (gpioInitialise() < 0) 
	{
		printf("E");
		return 1;

	}	
	gpioSetMode(LED_PIN, PI_OUTPUT);

    	for (int i = 0; i < 10; ++i) {  
        	
        gpioWrite(LED_PIN, 1);
        sleep(1); 
		double distance= ultrasound_distance(2,3);
        gpioWrite(LED_PIN, 0);
        sleep(1);  
    }

	double output = ultrasound_distance(2,3);
	std::cout << "Distance : " << output << std::endl;

    gpioTerminate();


		
 
}
