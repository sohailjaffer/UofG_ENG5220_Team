
#include "main.h"
#include "MotorController.h"
#include "DataLogger.h"
#include "autoRevert.h"

   
int MotorController::gpioInit()
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "PIGPIO Initialization failed." << std::endl;
        return 1;
    }
    return 0;
}

void MotorController::test(int LED_PIN)
{

    gpioInit();

    gpioSetMode(LED_PIN, PI_OUTPUT);

    for (int i = 0; i < 10; ++i)
    {

        gpioWrite(LED_PIN, 1);
        sleep(1);
        gpioWrite(LED_PIN, 0);
        sleep(1);
    }



    gpioTerminate();
}



void MotorController::testHbridge(void){
 if (gpioInitialise() < 0) {
        // Initialization failed
        return;
    }


    gpioSetMode(input1, PI_OUTPUT);
    gpioSetMode(input2, PI_OUTPUT);
    gpioSetMode(speedA, PI_OUTPUT);
    gpioSetMode(speedB, PI_OUTPUT);

    gpioWrite(input1, 1);  // Set input1 to HIGH
    gpioWrite(input2, 0);  // Set input2 to LOW
    gpioPWM(speedA, 255);  // Set speedA to a value between 0 and 255


    gpioWrite(input3, 1);  // Set input1 to HIGH
    gpioWrite(input4, 0);  // Set input2 to LOW
    gpioPWM(speedB, 255);  // Set speedA to a value between 0 and 255


     sleep(1);
    
    gpioWrite(input1, 0);  // Set input1 to HIGH
    gpioWrite(input2, 1);  // Set input2 to LOW
    gpioPWM(speedA, 255);  // Set speedA to a value between 0 and 255

    gpioWrite(input3, 0);  // Set input1 to HIGH
    gpioWrite(input4, 1);  // Set input2 to LOW
    gpioPWM(speedB, 255);  // Set speedA to a value between 0 and 255

    sleep(1);


    gpioWrite(input1, 0);  // Turn off input1
    gpioWrite(input2, 0);  // Turn off input2
    gpioPWM(speedA, 0);    // Turn off the motor

    gpioWrite(input3, 0);  // Turn off input1
    gpioWrite(input4, 0);  // Turn off input2
    gpioPWM(speedB, 0);    // Turn off the motor

    gpioTerminate();



}
void MotorController::resetMotors(){

    gpioWrite(input1, 0);  // Turn off input1
    gpioWrite(input2, 0);  // Turn off input2
    gpioPWM(speedA, 0);    // Turn off the motor

    gpioWrite(input3, 0);  // Turn off input1
    gpioWrite(input4, 0);  // Turn off input2
    gpioPWM(speedB, 0);    // Turn off the motor

   // gpioTerminate();
}

void MotorController::beep(int time){
  
     gpioSetMode(buzzer, PI_OUTPUT);
     gpioWrite(buzzer, 1);  // Turn off input1
     sleep(time);
     gpioWrite(buzzer, 0);  // Turn off input1


}





void MotorController::terminateGPIO() {
    gpioTerminate();
}

void MotorController::setMotorDirection(int input1Pin, int input2Pin, int speedPin, int direction, int speed) {
    gpioSetMode(input1Pin, PI_OUTPUT);
    gpioSetMode(input2Pin, PI_OUTPUT);
    gpioSetMode(speedPin, PI_OUTPUT);

    gpioWrite(input1Pin, direction);
    gpioWrite(input2Pin, !direction);  // Invert direction
    gpioPWM(speedPin, speed);
}

void MotorController::stopMotor(int speedPin) {
    gpioPWM(speedPin, 0);  // Turn off the motor
}

void MotorController::forward(int speed) {
    setMotorDirection(input1, input2, speedA, 1, speed);
    beep(0.1);

    usleep(100000);  // Sleep for 1 second (in microseconds)
    stopMotor(speedA);
}

void MotorController::backward(int speed) {
    setMotorDirection(input1, input2, speedA, 0, speed);
    usleep(100000);
    stopMotor(speedA);
}

void MotorController::left(int speed) {
    setMotorDirection(input3, input4, speedB, 0, speed);

    usleep(100000);
    stopMotor(speedB);
}

void MotorController::right(int speed) {
    setMotorDirection(input3, input4, speedB, 1, speed);
     usleep(100000);
     stopMotor(speedB);
   // testHbridge();

}

void MotorController::forwardRight(int speed){

        setMotorDirection(input1, input2, speedA, 1, speed);
        setMotorDirection(input3, input4, speedB, 1, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);


    
}

void MotorController::forwardLeft(int speed){
        setMotorDirection(input1, input2, speedA, 1, speed);
        setMotorDirection(input3, input4, speedB, 0, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);
    
}

void MotorController::backwardRight(int speed){
        setMotorDirection(input1, input2, speedA, 0, speed);
        setMotorDirection(input3, input4, speedB, 1, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);

    
}void MotorController::backwardLeft(int speed){

        setMotorDirection(input1, input2, speedA, 0, speed);
        setMotorDirection(input3, input4, speedB, 0, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);


    
}
bool record=false;
void MotorController::motorCallback(char * buffer){

DataLogger datalogger;
AutoRevert autorevert;


   // Print the received data
       // std::cout << "Received command: " << buffer << std::endl;

        // Compare the received command
        if (strcmp(buffer, "$1") == 0) {
            // Handle $1 command (e.g., call forward(255))
             gpioInit();
             backward(255);


        } else if (strcmp(buffer, "$2") == 0) {
            // Handle $2 command (e.g., call backward(255))
            gpioInit();
            forward(255);
         
            //sleep(0.1);
           // wait(100);
        } else if (strcmp(buffer, "$3") == 0) {
            // Handle $3 command (e.g., call left(255))
            gpioInit();
            left(255);
         
            //sleep(0.1);
            //wait(100);
        } else if (strcmp(buffer, "$4") == 0) {
            gpioInit();
            right(255);
     
        }else if (strcmp(buffer,"$5")==0){

            gpioInit();
            backwardRight(255);


        } 
        else if (strcmp(buffer,"$6")==0){

            gpioInit();
            backwardLeft(255);


        } else if (strcmp(buffer,"$7")==0){

            gpioInit();
            forwardRight(255);


        } 
        else if (strcmp(buffer,"$8")==0){

            gpioInit();
            forwardLeft(255);


        } 

         else if (strcmp(buffer,"$9")==0){
            datalogger.deleteFile("UserDataLog.txt");
            datalogger.starttime= std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::high_resolution_clock::now().time_since_epoch());
            record = true;
            


        }  
        else if (strcmp(buffer,"$10")==0){

              //  pthread_join(thread2, NULL);
              bool filefound = datalogger.fileExists("UserDataLog.txt");
              if(filefound){
                 std::cout << "Starting AutoRevert " << std::endl;
              autorevert.startReversing();
              record =false;
              }else {
                 std::cout << "Cannot Reverse No Saved Data Available " << std::endl;

              }


    }  
        
        
        else {
            // Unknown command
            std::cout << "Unknown command: " << buffer << std::endl;
        }

        if(record&&strcmp(buffer,"$10")!=0){
            LogEntry userLog;
            std::strcpy(userLog.buffer, buffer);
            userLog.timestamp =  std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            );

            datalogger.WriteUserData(userLog);
        }

        memset(buffer, 0, sizeof(buffer));
}

// this functions performs the opposite functions to that of MotorCallback 

void MotorController::reverseAssistCallback(char * buffer){

        DataLogger datalogger;


  
        if (strcmp(buffer, "$1") == 0) {
            // Handle $1 command (e.g., call forward(255))
             gpioInit();
            forward(255);



        } else if (strcmp(buffer, "$2") == 0) {
            // Handle $2 command (e.g., call backward(255))
            gpioInit();
            backward(255);

         
            //sleep(0.1);
           // wait(100);
        } else if (strcmp(buffer, "$3") == 0) {
            // Handle $3 command (e.g., call left(255))
            gpioInit();
            right(255);

         
            //sleep(0.1);
            //wait(100);
        } else if (strcmp(buffer, "$4") == 0) {
            gpioInit();
            left(255);

     
        }else if (strcmp(buffer,"$5")==0){

            gpioInit();
           forwardRight(255);



        } 
        else if (strcmp(buffer,"$6")==0){

            gpioInit();
            forwardLeft(255);



        } else if (strcmp(buffer,"$7")==0){

            gpioInit();
            backwardRight(255);


        } 
        else if (strcmp(buffer,"$8")==0){

            gpioInit();
            backwardLeft(255);


        } 

        
        else {
            // Unknown command
            std::cout << "Unknown command: " << buffer << std::endl;
        }

}
