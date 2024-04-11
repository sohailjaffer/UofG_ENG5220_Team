#include "autoRevert.h"
#include "DataLogger.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

void startReversing (){

    // Get the user data stored in the txt file into the list
    std::vector<std::string> UserInputData = ReadUserData();
    auto starttime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());

    for(auto& line : UserInputData){
        std::stringstream ss(line);
        std:: string timestamp, linedata;
        std:: getline(ss,timestamp, ','); // extract the time for each input
        std:: getline(ss,linedata, ','); // extract the data for each input

               // Convert timestamp string to milliseconds
        auto inputTime = std::chrono::milliseconds(std::stoll(timestamp));

        // Calculate the time difference
        std::chrono::milliseconds time_diff = (inputTime - starttime);

        // Wait until the desired timestamp is reached
        while (true) {
            // Calculate current time
            auto currentTime = std::chrono::high_resolution_clock::now();

            // Calculate duration since start time
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());

            // Check if desired time is reached
            if (elapsedTime >= time_diff) {
                break; // Exit the loop when desired time is reached
            }

            // Sleep for a short duration before checking again
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // Output data
        std::cout << "Output data: " << linedata << std::endl;


    }


}

void * reverseThread(void * arg){

    startReversing();

}

