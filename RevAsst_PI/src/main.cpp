#include "main.h"
#include "MotorController.h"
#include "wifi_pi.h"
#include "autoRevert.h"
#include "IR_sensor.h"

static IR_sensor sensor(IRFrontSensor);
static IR_sensor sensor2(IRBackSensor);
pthread_t thread1;
pthread_t thread2;
pthread_t Revthread;
 bool threadKiller = false;

bool frontFlag=false;
bool backFlag=false;

pthread_mutex_t frontFlagMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t backFlagMutex = PTHREAD_MUTEX_INITIALIZER;

 
 void SensorCallback(int gpio){

	 if (gpio == sensor.getIRsensorGPIO())
	 {
		 pthread_mutex_lock(&frontFlagMutex);
		 frontFlag = true; // Reset frontFlag
		 pthread_mutex_unlock(&frontFlagMutex);
		 std::cout<<"Sensor Front Triggered"<<std::endl;
		
	 }
	 else if (gpio == sensor2.getIRsensorGPIO())
	 {
		 pthread_mutex_lock(&backFlagMutex);
		 backFlag = true; // Reset backFlag
		 pthread_mutex_unlock(&backFlagMutex);
		std::cout<<"Sensor Back Triggered"<<std::endl;

	 }
 }




int main() {
	
	WiFiPi wpi;

	sensor.setCallbackFunction(SensorCallback);
	sensor2.setCallbackFunction(SensorCallback);
	 
	pthread_create(&thread1, NULL, wpi.ManageCarCommunication, NULL);
	pthread_create(&thread2, NULL, SensorReset, NULL);


    // Wait for threads to finish
    pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);


	while(1)
	{
		usleep(100000);

	}

 
}
void resetFlags() {
    //pthread_mutex_lock(&frontFlagMutex);
    frontFlag = false;
    //pthread_mutex_unlock(&frontFlagMutex);

    //pthread_mutex_lock(&backFlagMutex);
    backFlag = false;
    //pthread_mutex_unlock(&backFlagMutex);
}

void* SensorReset(void* arg) {

	while(true){

		sleep(3); // Periodic tiemer to reset the sensors flags
		resetFlags();
		if( threadKiller )
			break;
		
	}

	pthread_exit(NULL);


}




