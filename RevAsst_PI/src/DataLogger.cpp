#include "DataLogger.h"



void WriteUserData(LogEntry& entry){

     std::ofstream userInputLog("UserDataLog.txt", std::ios_base::app);
    if (!userInputLog.is_open()) {
        std::cerr << "Error opening user data file" << std::endl;
        return;
    }

    userInputLog << "Timestamp: " << entry.timestamp.count() << ", Buffer data: " << entry.buffer  << std::endl;
    userInputLog.close();


}




