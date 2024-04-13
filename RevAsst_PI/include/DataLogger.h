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
    void WriteUserData(LogEntry& entry);
    std::vector<std::string> ReadUserData();
    void deleteFile(const std::string& filename);
    std::chrono::milliseconds starttime;
    bool fileExists(const std::string& filename);


private:
    
};
