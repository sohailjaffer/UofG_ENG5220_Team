#include "autoRevert.h"
#include "DataLogger.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include "MotorController.h"



int getIntfromStr(const std::string& timestampString) {
    std::string numericPart;
    for (char c : timestampString) {
        if (std::isdigit(c)) {
            numericPart += c;
        }
    }
    return std::stoi(numericPart);
}

void extractCommand(const std::string& line, char* command) {
    // Find the position of the first occurrence of "$"
    size_t pos = line.find("$");
    if (pos != std::string::npos) {
        // Copy the substring starting from "$" to the end of the line into the provided char array
        size_t length = line.copy(command, line.size() - pos, pos);
        // Add null terminator to the char array
        command[length] = '\0';
    } else {
        // If "$" is not found, set the command as an empty string
        command[0] = '\0';
    }
}


void startReversing (){

    MotorController motorController;

    // Get the user data stored in the txt file into the list
    std::vector<std::string> UserInputData = ReadUserData();
    auto starttime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());
    int prev_time=0;
    for(auto& line : UserInputData){
        std::stringstream ss(line);
        std:: string timestamp, linedata;
        std:: getline(ss,timestamp, ','); // extract the time for each input
        std:: getline(ss,linedata, ','); // extract the data for each input

        int delay = getIntfromStr(timestamp);


         if (delay > 0) {
            // Sleep for the calculated duration
            std::this_thread::sleep_for(std::chrono::milliseconds(delay-prev_time));
        }
        prev_time= delay;
        char data[100];

        extractCommand(linedata,data);

        if (data[0] != '\0') {
            motorController.reverseAssistCallback(data);
        }
        
       
       

        // Output data
        std::cout << "Output data: " << linedata << std::endl;



    }
    deleteFile("UserDataLog.txt");



}

void * reverseThread(void * arg){

    startReversing();

    pthread_exit(NULL);


}

