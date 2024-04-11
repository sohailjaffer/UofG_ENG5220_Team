#include "DataLogger.h"

std::chrono::milliseconds starttime{0};

void WriteUserData(LogEntry& entry){

     std::ofstream userInputLog("UserDataLog.txt", std::ios_base::app);
    if (!userInputLog.is_open()) {
        std::cerr << "Error opening user data file" << std::endl;
        return;
    }
    std::chrono::milliseconds time_diff = getTimeDifference(entry.timestamp);
    userInputLog << "Timestamp: " << time_diff.count() << ", Buffer data: " << entry.buffer  << std::endl;
    userInputLog.close();


}
std::chrono::milliseconds getTimeDifference(std::chrono::milliseconds curr_time){

    return curr_time - starttime;
}



