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
extern void WriteUserData(LogEntry& entry);
extern std::chrono::milliseconds starttime;
extern std::vector<std::string> ReadUserData();
extern void deleteFile(const std::string& filename);
std::chrono::milliseconds getTimeDifference(std::chrono::milliseconds curr_time);

