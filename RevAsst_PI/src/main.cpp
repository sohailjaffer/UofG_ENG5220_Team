#include "main.h"
#include "ultrasound_sensor.h"
#include "pi_bluetooth.h"
#include "MotorController.h"
#include "wifi_pi.h"
void* acoustic(void* arg);

int main() {
	
	//test(2);
	//changes done on PI to setup github on it 

	

	pi_ble_result result =pi_ble_init();

	 if (result.device_id >= 0 && result.socket >= 0) {

		
       // pi_ble_scan_print(result);
  	    const std::string targetDeviceAddress = "C4:6E:33:2C:60:28";
    	const std::string UID = "00001101-0000-1000-8000-00805F9B34FB";
       // Bluetooth_Simple_Connect();
		// ultrasound_init();
		// for (int i=0;i<10;i++){
		// 	double output = ultrasound_distance(1,10);
    	// 	std::cout << "Distance : " << output << std::endl;
		// }


    } else {
        // Handle the initialization failure
    }
	

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, DriveCar, NULL);
	pthread_create(&thread2, NULL, ultSoundThread, NULL);


    // Wait for threads to finish
    pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);


	//testHbridge();
	//HelloPI();

	//test(16);



	// double output = ultrasound_distance(2,3);
    // std::cout << "Distance : " << output << std::endl;
		
 
}

void* acoustic(void* arg) {
   int i=0;
	while(true){

	  std::cout << "Thead2  : " << i << std::endl;
		i++;
		sleep(1);

	}
    pthread_exit(NULL);
}
