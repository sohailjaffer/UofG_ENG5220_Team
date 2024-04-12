
#include "main.h"
#include "MotorController.h"
#include "DataLogger.h"
#include "autoRevert.h"

    int input1 = 24;
    int input2 = 23;
    int speedA = 12;
    int buzzer = 26;

    int input3 = 25;
    int input4 = 5;
    int speedB = 13;

int gpio_init(void)
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "GPIO Initialization failed." << std::endl;
        return 1;
    }
    return 0;
}

void test(int LED_PIN)
{

    gpio_init();

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



void testHbridge(void){
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
void resetMotors(){

    gpioWrite(input1, 0);  // Turn off input1
    gpioWrite(input2, 0);  // Turn off input2
    gpioPWM(speedA, 0);    // Turn off the motor

    gpioWrite(input3, 0);  // Turn off input1
    gpioWrite(input4, 0);  // Turn off input2
    gpioPWM(speedB, 0);    // Turn off the motor

   // gpioTerminate();
}

void beep(int time){
  
     gpioSetMode(buzzer, PI_OUTPUT);
     gpioWrite(buzzer, 1);  // Turn off input1
     sleep(time);
     gpioWrite(buzzer, 0);  // Turn off input1


}





void terminateGPIO() {
    gpioTerminate();
}

void setMotorDirection(int input1Pin, int input2Pin, int speedPin, int direction, int speed) {
    gpioSetMode(input1Pin, PI_OUTPUT);
    gpioSetMode(input2Pin, PI_OUTPUT);
    gpioSetMode(speedPin, PI_OUTPUT);

    gpioWrite(input1Pin, direction);
    gpioWrite(input2Pin, !direction);  // Invert direction
    gpioPWM(speedPin, speed);
}

void stopMotor(int speedPin) {
    gpioPWM(speedPin, 0);  // Turn off the motor
}

void forward(int speed) {
    setMotorDirection(input1, input2, speedA, 1, speed);
    beep(0.1);

    usleep(100000);  // Sleep for 1 second (in microseconds)
    stopMotor(speedA);
}

void backward(int speed) {
    setMotorDirection(input1, input2, speedA, 0, speed);
    usleep(100000);
    stopMotor(speedA);
}

void left(int speed) {
    setMotorDirection(input3, input4, speedB, 0, speed);

    usleep(100000);
    stopMotor(speedB);
}

void right(int speed) {
    setMotorDirection(input3, input4, speedB, 1, speed);
     usleep(100000);
     stopMotor(speedB);
   // testHbridge();

}

void forwardright(int speed){

        setMotorDirection(input1, input2, speedA, 1, speed);
        setMotorDirection(input3, input4, speedB, 1, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);


    
}

void forwardleft(int speed){
        setMotorDirection(input1, input2, speedA, 1, speed);
        setMotorDirection(input3, input4, speedB, 0, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);
    
}

void backwardright(int speed){
        setMotorDirection(input1, input2, speedA, 0, speed);
        setMotorDirection(input3, input4, speedB, 1, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);

    
}void backwardleft(int speed){

        setMotorDirection(input1, input2, speedA, 0, speed);
        setMotorDirection(input3, input4, speedB, 0, speed);
        usleep(100000);
        stopMotor(speedB);
        stopMotor(speedA);


    
}

void MotorCallback(char * buffer){



   // Print the received data
       // std::cout << "Received command: " << buffer << std::endl;

        // Compare the received command
        if (strcmp(buffer, "$1") == 0) {
            // Handle $1 command (e.g., call forward(255))
             gpio_init();
             backward(255);


        } else if (strcmp(buffer, "$2") == 0) {
            // Handle $2 command (e.g., call backward(255))
            gpio_init();
            forward(255);
         
            //sleep(0.1);
           // wait(100);
        } else if (strcmp(buffer, "$3") == 0) {
            // Handle $3 command (e.g., call left(255))
            gpio_init();
            left(255);
         
            //sleep(0.1);
            //wait(100);
        } else if (strcmp(buffer, "$4") == 0) {
            gpio_init();
            right(255);
     
        }else if (strcmp(buffer,"$5")==0){

            gpio_init();
            backwardright(255);


        } 
        else if (strcmp(buffer,"$6")==0){

            gpio_init();
            backwardleft(255);


        } else if (strcmp(buffer,"$7")==0){

            gpio_init();
            forwardright(255);


        } 
        else if (strcmp(buffer,"$8")==0){

            gpio_init();
            forwardleft(255);


        } 

         else if (strcmp(buffer,"$9")==0){
            deleteFile("UserDataLog.txt");
            starttime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());

        }  
        else if (strcmp(buffer,"$10")==0){

              //  pthread_join(thread2, NULL);
              startReversing();



    }  
        
        
        else {
            // Unknown command
            std::cout << "Unknown command: " << buffer << std::endl;
        }

        LogEntry userLog;

        std::strcpy(userLog.buffer, buffer);
        userLog.timestamp =  std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
         );

        WriteUserData(userLog);

        memset(buffer, 0, sizeof(buffer));
}

// this functions performs the opposite functions to that of MotorCallback 

void ReverseAssistCallback(char * buffer){



  
        if (strcmp(buffer, "$1") == 0) {
            // Handle $1 command (e.g., call forward(255))
             gpio_init();
            forward(255);



        } else if (strcmp(buffer, "$2") == 0) {
            // Handle $2 command (e.g., call backward(255))
            gpio_init();
            backward(255);

         
            //sleep(0.1);
           // wait(100);
        } else if (strcmp(buffer, "$3") == 0) {
            // Handle $3 command (e.g., call left(255))
            gpio_init();
            right(255);

         
            //sleep(0.1);
            //wait(100);
        } else if (strcmp(buffer, "$4") == 0) {
            gpio_init();
            left(255);

     
        }else if (strcmp(buffer,"$5")==0){

            gpio_init();
           forwardright(255);



        } 
        else if (strcmp(buffer,"$6")==0){

            gpio_init();
            forwardleft(255);



        } else if (strcmp(buffer,"$7")==0){

            gpio_init();
            backwardright(255);


        } 
        else if (strcmp(buffer,"$8")==0){

            gpio_init();
            backwardleft(255);


        } 

        
        else {
            // Unknown command
            std::cout << "Unknown command: " << buffer << std::endl;
        }

}
