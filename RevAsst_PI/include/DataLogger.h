#pragma once
#include "main.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>


struct LogEntry {
    char buffer[1024]; 
    std::chrono::milliseconds timestamp;
    
};
extern void WriteUserData(LogEntry& entry);
