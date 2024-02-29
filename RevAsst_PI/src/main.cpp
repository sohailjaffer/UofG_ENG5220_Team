#include "main.h"
#include "ultrasound_sensor.h"
#include "pi_bluetooth.h"

int main() {
	
	test(2);
	pi_ble_init();
	pi_ble_scan_print();
		
 
}
