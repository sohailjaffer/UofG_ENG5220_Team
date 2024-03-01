#include "main.h"
#include "ultrasound_sensor.h"
#include "pi_bluetooth.h"
#include "blinky.h"

int main() {
	
	//test(2);
	//changes done on PI to setup github on it 



	pi_ble_result result =pi_ble_init();

	 if (result.device_id >= 0 && result.socket >= 0) {
        //pi_ble_scan_print(result);
       // pi_ble_connection(result);
		const char* targetDeviceAddress = "C4:6E:33:2C:60:28";
		//const char* messageToSend = "Hello, Bluetooth World!";
		pi_ble_connection(result, targetDeviceAddress);



    } else {
        // Handle the initialization failure
    }



	// double output = ultrasound_distance(2,3);
    // std::cout << "Distance : " << output << std::endl;
		
 
}
