
#include "main.h"
#include "MotorController.h"
#include "DataLogger.h"
#include "autoRevert.h"
#include <gpiod.h>


int MotorController::gpioInit()
{

#ifdef USE_GPIOd

     return 0;



#else
        if (gpioInitialise() < 0)
        {
            std::cerr << "PIGPIO Initialization failed." << std::endl;
            return 1;
        }
        return 0;

#endif




}

void MotorController::test(int LED_PIN)
{

#ifndef USE_GPIOd
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
#endif
}

void MotorController::testHbridge(void)
{

#ifndef USE_GPIOd
    if (gpioInitialise() < 0)
    {
        // Initialization failed
        return;
    }

    gpioSetMode(input1, PI_OUTPUT);
    gpioSetMode(input2, PI_OUTPUT);
    gpioSetMode(speedA, PI_OUTPUT);
    gpioSetMode(speedB, PI_OUTPUT);

    gpioWrite(input1, 1); // Set input1 to HIGH
    gpioWrite(input2, 0); // Set input2 to LOW
    gpioPWM(speedA, 255); // Set speedA to a value between 0 and 255

    gpioWrite(input3, 1); // Set input1 to HIGH
    gpioWrite(input4, 0); // Set input2 to LOW
    gpioPWM(speedB, 255); // Set speedA to a value between 0 and 255

    sleep(1);

    gpioWrite(input1, 0); // Set input1 to HIGH
    gpioWrite(input2, 1); // Set input2 to LOW
    gpioPWM(speedA, 255); // Set speedA to a value between 0 and 255

    gpioWrite(input3, 0); // Set input1 to HIGH
    gpioWrite(input4, 1); // Set input2 to LOW
    gpioPWM(speedB, 255); // Set speedA to a value between 0 and 255

    sleep(1);

    gpioWrite(input1, 0); // Turn off input1
    gpioWrite(input2, 0); // Turn off input2
    gpioPWM(speedA, 0);   // Turn off the motor

    gpioWrite(input3, 0); // Turn off input1
    gpioWrite(input4, 0); // Turn off input2
    gpioPWM(speedB, 0);   // Turn off the motor

    gpioTerminate();

#endif
}
void MotorController::resetMotors()
{
#ifndef USE_GPIOd


    gpioWrite(input1, 0); // Turn off input1
    gpioWrite(input2, 0); // Turn off input2
    gpioPWM(speedA, 0);   // Turn off the motor

    gpioWrite(input3, 0); // Turn off input1
    gpioWrite(input4, 0); // Turn off input2
    gpioPWM(speedB, 0);   // Turn off the motor

    // gpioTerminate();
#endif
}

void MotorController::beep(int time)
{
#ifndef USE_GPIOd

    gpioSetMode(buzzer, PI_OUTPUT);
    gpioWrite(buzzer, 1); // Turn off input1
    sleep(time);
    gpioWrite(buzzer, 0); // Turn off input1
#endif
}

void MotorController::terminateGPIO()
{
#ifndef USE_GPIOd

    gpioTerminate();
#endif
}

void MotorController::setMotorDirection(int input1Pin, int input2Pin, int speedPin, int direction, int speed)
{
#ifdef USE_GPIOd

    struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip1");
    if (!chip)
    {
        perror("GPIOchip0 failed\n");
        return;
    }

    struct gpiod_line *line1 = gpiod_chip_get_line(chip, input1Pin);
    struct gpiod_line *line2 = gpiod_chip_get_line(chip, input2Pin);
    struct gpiod_line *lineSpeed = gpiod_chip_get_line(chip, speedPin);

    gpiod_line_request_output(line1, "H-bridge1", 0);
    gpiod_line_request_output(line2, "H-bridge2", 0);
    gpiod_line_request_output(lineSpeed, "H-bridge-speed", 0);

    gpiod_line_set_value(line1, direction);
    gpiod_line_set_value(line2, !direction); // Invert direction

    for (int i = 0; i < 10; ++i)
    {
        gpiod_line_set_value(lineSpeed, speed);
        usleep(speed * 1000); 
        gpiod_line_set_value(lineSpeed, !speed);
        usleep((100 - speed) * 1000); 
    }
// reset the pins 
    gpiod_line_release(line1);
    gpiod_line_release(line2);
    gpiod_line_release(lineSpeed);
    gpiod_chip_close(chip);
#else
// --- PIGPIO CODE  -------------
    gpioSetMode(input1Pin, PI_OUTPUT);
    gpioSetMode(input2Pin, PI_OUTPUT);
    gpioSetMode(speedPin, PI_OUTPUT);

    gpioWrite(input1Pin, direction);
    gpioWrite(input2Pin, !direction); // Invert direction
    gpioPWM(speedPin, speed);
#endif
}




void MotorController::stopMotor(int speedPin)
{
#ifndef USE_GPIOd

    gpioPWM(speedPin, 0); // Turn off the motor
#endif 
}

/**
 * @brief This activates the H bridge which has 4 inputs. 
 * input 1 and 2 are for Main motor 
 * input 3 and 4 for steering motor. 
 *                    H Bridge Control Table 
 * ----------------------------------------------------------
 *            Input1  Input2  Input3 Input4  Speed A   SpeedB
 *   forward    1       0      0        0       1         0
 *   Backwards  0       1      0        0       1         0
 *   Right      0       0      1        0       0         1
 *   Left       0       0      0        1       0         1
 *   FWR        1       0      1        0       1         1  
 *   FWL        1       0      0        1       1         1  
 *   BWR        0       1      1        0       1         1  
 *   BWL        0       1      0        1       1         1  
 * ----------------------------------------------------------
 * @param speed - The Duty cycle of the Motor for Motor Speed.
*/ 
void MotorController::forward(int speed)
{
    setMotorDirection(input1, input2, speedA, 1, speed); 
    beep(0.1);

    usleep(100000); // Sleep for 1 second (in microseconds)
    stopMotor(speedA);
}

void MotorController::backward(int speed)
{
    setMotorDirection(input1, input2, speedA, 0, speed);
    usleep(100000);
    stopMotor(speedA);
}

void MotorController::left(int speed)
{
    setMotorDirection(input3, input4, speedB, 0, speed);

    usleep(100000);
    stopMotor(speedB);
}

void MotorController::right(int speed)
{
    setMotorDirection(input3, input4, speedB, 1, speed);
    usleep(100000);
    stopMotor(speedB);
    // testHbridge();
}

void MotorController::forwardRight(int speed)
{

    setMotorDirection(input1, input2, speedA, 1, speed);
    setMotorDirection(input3, input4, speedB, 1, speed);
    usleep(100000);
    stopMotor(speedB);
    stopMotor(speedA);
}

void MotorController::forwardLeft(int speed)
{
    setMotorDirection(input1, input2, speedA, 1, speed);
    setMotorDirection(input3, input4, speedB, 0, speed);
    usleep(100000);
    stopMotor(speedB);
    stopMotor(speedA);
}

void MotorController::backwardRight(int speed)
{
    setMotorDirection(input1, input2, speedA, 0, speed);
    setMotorDirection(input3, input4, speedB, 1, speed);
    usleep(100000);
    stopMotor(speedB);
    stopMotor(speedA);
}
void MotorController::backwardLeft(int speed)
{

    setMotorDirection(input1, input2, speedA, 0, speed);
    setMotorDirection(input3, input4, speedB, 0, speed);
    usleep(100000);
    stopMotor(speedB);
    stopMotor(speedA);
}
bool record = false;

/**
 * @brief This functions acts as a stub, which handles the request from the user and
 * runs particular functions. Then the data along with timestamp is logged into a textfile to be used later.
 * 
 * @param buffer Contains the raw Data recieved by User via network sockets. 
 * "$1": Moves the motor backward at full speed if the 'frontFlag' is not set.
 * "$2": Moves the motor forward at full speed if the 'backFlag' is not set.
 * "$3": Rotates the motor to the left at full speed.
 * "$4": Rotates the motor to the right at full speed.
 * "$5": Moves the motor diagonally backward-right at full speed if the 'frontFlag' is not set.
 * "$6": Moves the motor diagonally backward-left at full speed if the 'frontFlag' is not set.
 * "$7": Moves the motor diagonally forward-right at full speed if the 'backFlag' is not set.
 * "$8": Moves the motor diagonally forward-left at full speed if the 'backFlag' is not set.
 * "$9": Deletes the "UserDataLog.txt" file and starts recording user commands for logging.
 * "$10": Checks if the "UserDataLog.txt" file exists, and if found, starts the AutoRevert process.
 * 
 * 
 * 
*/

void MotorController::motorHandler(char *buffer)
{

    DataLogger datalogger;
    AutoRevert autorevert;

   
    if (strcmp(buffer, "$1") == 0)
    {
        gpioInit();
        if (!frontFlag)
            backward(255);
    }
    else if (strcmp(buffer, "$2") == 0)
    {
        gpioInit();
        if (!backFlag)

            forward(255);

        // sleep(0.1);
        // wait(100);
    }
    else if (strcmp(buffer, "$3") == 0)
    {
        gpioInit();
        left(255);

        // sleep(0.1);
        // wait(100);
    }
    else if (strcmp(buffer, "$4") == 0)
    {
        gpioInit();
        right(255);
    }
    else if (strcmp(buffer, "$5") == 0)
    {

        gpioInit();
        if (!frontFlag)
            backwardRight(255);
    }
    else if (strcmp(buffer, "$6") == 0)
    {

        gpioInit();
        if (!frontFlag)
            backwardLeft(255);
    }
    else if (strcmp(buffer, "$7") == 0)
    {

        gpioInit();
        if (!backFlag)
            forwardRight(255);
    }
    else if (strcmp(buffer, "$8") == 0)
    {

        gpioInit();
        if (!backFlag)
            forwardLeft(255);
    }

    else if (strcmp(buffer, "$9") == 0)
    {
        datalogger.deleteFile("UserDataLog.txt");
        datalogger.starttime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());
        record = true;
    }
    else if (strcmp(buffer, "$10") == 0)
    {

        //  pthread_join(thread2, NULL);
        bool filefound = datalogger.fileExists("UserDataLog.txt");
        if (filefound)
        {
            std::cout << "Starting AutoRevert " << std::endl;
            autorevert.startReversing();
            record = false;
        }
        else
        {
            std::cout << "Cannot Reverse No Saved Data Available " << std::endl;
        }
    }

    else
    {
        // Unknown command
        std::cout << "Unknown command: " << buffer << std::endl;
    }

    if (record && strcmp(buffer, "$10") != 0)
    {
        LogEntry userLog;
        std::strcpy(userLog.buffer, buffer);
        userLog.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());

        datalogger.WriteUserData(userLog);
    }

    memset(buffer, 0, sizeof(buffer));
}

// this functions performs the opposite functions to that of MotorCallback


/**
 * @brief This function 
 * 
 * @param buffer Contains the raw Data recieved by User via network sockets. 
 * "$1": Moves the motor forward at full speed if the 'frontFlag' is not set.
 * "$2": Moves the motor backward at full speed if the 'backFlag' is not set.
 * "$3": Rotates the motor to the right at full speed.
 * "$4": Rotates the motor to the left at full speed.
 * "$5": Moves the motor diagonally forward-right at full speed if the 'frontFlag' is not set.
 * "$6": Moves the motor diagonally forward-left at full speed if the 'frontFlag' is not set.
 * "$7": Moves the motor diagonally backward-right at full speed if the 'backFlag' is not set.
 * "$8": Moves the motor diagonally backward-left at full speed if the 'backFlag' is not set.
 * "$9": Deletes the "UserDataLog.txt" file and starts recording user commands for logging.
 * "$10": Checks if the "UserDataLog.txt" file exists, and if found, starts the AutoRevert process.
 * 
 * 
 * 
*/

void MotorController::reverseAssistHandler(char *buffer)
{

    DataLogger datalogger;

    if (strcmp(buffer, "$1") == 0)
    {
        gpioInit();
        if (!backFlag)

            forward(255);
    }
    else if (strcmp(buffer, "$2") == 0)
    {
        gpioInit();
        if (!frontFlag)

            backward(255);

        // sleep(0.1);
        // wait(100);
    }
    else if (strcmp(buffer, "$3") == 0)
    {
        gpioInit();
        left(255);

        // sleep(0.1);
        // wait(100);
    }
    else if (strcmp(buffer, "$4") == 0)
    {
        gpioInit();
        right(255);

    }
    else if (strcmp(buffer, "$5") == 0)
    {

        gpioInit();
        if (!backFlag)

            forwardRight(255);
    }
    else if (strcmp(buffer, "$6") == 0)
    {

        gpioInit();
        if (!backFlag)

            forwardLeft(255);
    }
    else if (strcmp(buffer, "$7") == 0)
    {

        gpioInit();
        if (!frontFlag)

            backwardRight(255);
    }
    else if (strcmp(buffer, "$8") == 0)
    {

        gpioInit();
        if (!frontFlag)

            backwardLeft(255);
    }

    else
    {
        // Unknown command
        std::cout << "Unknown command: " << buffer << std::endl;
    }
}
