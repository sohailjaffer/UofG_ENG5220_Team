#include "main.h"
#include "ultrasound_sensor.h"
#include "pi_bluetooth.h"
#include "MotorController.h"
#include "wifi_pi.h"
#include "autoRevert.h"

void* acoustic(void* arg);
pthread_t thread1;
pthread_t thread2;

int main() {
	
	
	
	

	


	pthread_create(&thread1, NULL, ManageCarCommunication, NULL);
	//pthread_create(&thread1, NULL, reverseThread, NULL);
	//pthread_create(&thread2, NULL, ultSoundThread, NULL);


    // Wait for threads to finish
    pthread_join(thread1, NULL);
 //	pthread_join(thread2, NULL);


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
