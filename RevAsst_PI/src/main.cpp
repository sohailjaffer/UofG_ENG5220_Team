#include "main.h"
#include "ultrasound_sensor.h"
#include "pi_bluetooth.h"
#include "blinky.h"

int main() {
	
	test(2);
	//changes done on PI to setup github on it 
	pi_ble_result result =pi_ble_init();
	pi_ble_scan_print(result);



	// double output = ultrasound_distance(2,3);
    // std::cout << "Distance : " << output << std::endl;
		
 
}
