#include "main.h"
#include "ultrasound_sensor.h"
#include "pi_bluetooth.h"
#include "blinky.h"

int main() {
	
	test(2);
	pi_ble_init();
	pi_ble_scan_print();

	// double output = ultrasound_distance(2,3);
    // std::cout << "Distance : " << output << std::endl;
		
 
}
