#include "autoRevert.h"
#include "MotorController.h"
#include "DataLogger.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

//.

AutoRevert::AutoRevert()
{
}

AutoRevert::~AutoRevert()
{
}

void AutoRevert::startReversing()
{
    MotorController motorController;
    DataLogger dataLogger;

    // Get the user data stored in the txt file into the list
    std::vector<std::string> userInputData = dataLogger.ReadUserData();
    auto startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch());
    int prevTime = 0;
    for (auto &line : userInputData)
    {
        std::stringstream ss(line);
        std::string timestamp, linedata;
        std::getline(ss, timestamp, ','); // extract the time for each input
        std::getline(ss, linedata, ',');  // extract the data for each input

        int delay = getIntfromStr(timestamp);

        if (delay > 0)
        {
            // Sleep for the calculated duration
            std::this_thread::sleep_for(std::chrono::milliseconds(delay - prevTime));
        }
        prevTime = delay;
        char data[100];

        extractCommand(linedata, data);

        if (data[0] != '\0')
        {
            for (int i = 0; i < 1; i++)
            {
                motorController.reverseAssistHandler(data);
                //usleep(100);
            }
        }

        // Output data
        std::cout << "Output data: " << linedata << std::endl;
    }
    dataLogger.deleteFile("UserDataLog.txt");
}

void *AutoRevert::reverseThread(void *arg)
{

    AutoRevert *autoRevertObj = static_cast<AutoRevert *>(arg);

    autoRevertObj->startReversing();

    pthread_exit(NULL);
}

int AutoRevert::getIntfromStr(const std::string &timestampString)
{
    std::string numericPart;
    for (char c : timestampString)
    {
        if (std::isdigit(c))
        {
            numericPart += c;
        }
    }
    return std::stoi(numericPart);
}

void AutoRevert::extractCommand(const std::string &line, char *command)
{
    // Find the position of the first occurrence of "$"
    size_t pos = line.find("$");
    if (pos != std::string::npos)
    {
        // Copy the substring starting from "$" to the end of the line into the provided char array
        size_t length = line.copy(command, line.size() - pos, pos);
        // Add null terminator to the char array
        command[length] = '\0';
    }
    else
    {
        // If "$" is not found, set the command as an empty string
        command[0] = '\0';
    }
}
