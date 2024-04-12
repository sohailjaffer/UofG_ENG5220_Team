#include "DataLogger.h"

std::chrono::milliseconds starttime{0};

void WriteUserData(LogEntry& entry){

     std::ofstream userInputLog("UserDataLog.txt", std::ios_base::app);
    if (!userInputLog.is_open()) {
        std::cerr << "Error opening user data file" << std::endl;
        return;
    }
    std::chrono::milliseconds time_diff = (entry.timestamp-starttime);
    userInputLog << "Timestamp: " << time_diff.count() << ", Buffer data: " << entry.buffer  << std::endl;
    userInputLog.close();


}


std::vector<std::string> ReadUserData() {
    std::ifstream userInputLog("UserDataLog.txt");
    std::vector<std::string> lines;

    if (!userInputLog.is_open()) {
        std::cerr << "Error opening user data file" << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(userInputLog, line)) {
        lines.push_back(line);
    }

    userInputLog.close();
    return lines;
}


void deleteFile(const std::string& filename) {
    if (std::remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting file: " << filename << std::endl;
    } else {
        std::cout << "File deleted successfully: " << filename << std::endl;
    }
}
