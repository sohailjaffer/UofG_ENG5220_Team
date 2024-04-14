#pragma once

#include <string>
#include <vector>

class AutoRevert {
public:
    // Constructor and destructor
    AutoRevert();
    ~AutoRevert();

    /**
     * 
     * @brief This function gets the stored Data from the text file line by line.
     * It extracts the timestamp and Buffer data from txt. The timestamp is used for reference 
     * with the actual time, to tell the system when to start reversing. The function will sleep for till
     * the time stamp, mimicing the original user input but in reverse order.
    */

    void startReversing();


    /**
     * 
     * @brief This is the thread fucntion which will be invoked by pthreads to call the above function
    */

    static void* reverseThread(void* arg);

private:
    // Private member functions
    /**
     * @brief Converts str from txt and converts it to int for calculating the time
    */
    int getIntfromStr(const std::string& timestampString);

    // Extracts the buffer data by looking for $ and passes this to the handler function.
    void extractCommand(const std::string& line, char* command);
};
