#include "DataLogger.h"

DataLogger::DataLogger() {
    //starttime = std::chrono::milliseconds(0);
}

void DataLogger::setStartTime(const std::chrono::milliseconds& time) {
    starttime = time;
}
 
void DataLogger::WriteUserData(LogEntry& entry) {


    std::ofstream userInputLog("UserDataLog.txt", std::ios_base::app);
    if (!userInputLog.is_open()) {
        std::cerr << "Error opening user data file" << std::endl;
        return;
    }
    std::chrono::milliseconds time_diff = (entry.timestamp - starttime);
    userInputLog << "Timestamp: " << time_diff.count() << ", Buffer data: " << entry.buffer << std::endl;
    userInputLog.close();
}

std::vector<std::string> DataLogger::ReadUserData() {

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

void DataLogger::deleteFile(const std::string& filename) {

    if (std::remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting file: " << filename << std::endl;
    }
    else {
        std::cout << "File deleted successfully: " << filename << std::endl;
    }
}

bool DataLogger::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good(); // Returns true if the file exists and is accessible
}



