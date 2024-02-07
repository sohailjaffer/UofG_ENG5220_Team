#include "main.h"
#include "pigpio.h"
#include "unistd.h"
const int LED_PIN = 2;
int main() {
	
	if (gpioInitialise() < 0) 
	{
		printf("Doesn't Work");
		return 1;

	}	
	gpioSetMode(LED_PIN, PI_OUTPUT);

    	for (int i = 0; i < 10; ++i) {  // Blink the LED 10 times
        	
        gpioWrite(LED_PIN, 1);
        sleep(1); 

        gpioWrite(LED_PIN, 0);
        sleep(1);  
    }

    gpioTerminate();
		
 
}
