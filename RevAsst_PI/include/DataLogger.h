#pragma once

#include "main.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

struct LogEntry {
    char buffer[1024];
    std::chrono::milliseconds timestamp;
};

class DataLogger {
public:
    DataLogger();
    void setStartTime(const std::chrono::milliseconds& time); // Setter function for starttime
    std::chrono::milliseconds getStartTime() const; // Getter function for starttime
  /**
     * @brief Writes the User inputs recieved into a textfile along with the timestamp.
     * @param entry - Is the log file and structures the data into log format 
    */
    void WriteUserData(LogEntry& entry);

 /**
     * @brief Reads user inputs and timestamp 
     * @return String Vector List. 
    */

    std::vector<std::string> ReadUserData();
    // Deletes the textfile, to prevent previous data everytime record is pressed
    void deleteFile(const std::string& filename);
    std::chrono::milliseconds starttime;
    
    /**
     * @brief Check for file name existance
     * @return True if found and false not found.
    */
    bool fileExists(const std::string& filename);


private:
    
};
