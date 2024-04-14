#pragma once

#include <string>
#include <vector>

class AutoRevert {
public:
    // Constructor and destructor
    AutoRevert();
    ~AutoRevert();

    // Public member functions
    void startReversing();

    static void* reverseThread(void* arg);

private:
    // Private member functions
    int getIntfromStr(const std::string& timestampString);
    void extractCommand(const std::string& line, char* command);
};
