#include "main.h"
#include "pigpio.h"
int main() {
	
	if (gpioInitialise() < 0) 
	{
		printf("Doesn't Work");
	}	
	else
		printf("Works");
 
}
