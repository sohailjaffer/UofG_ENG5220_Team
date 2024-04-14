#ifndef WIFI_PI_H
#define WIFI_PI_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "MotorController.h"
#include "main.h"

#define PORT  12345

class WiFiPi {
private:
   
    MotorController motorController;

    void initWiFi();
    void connectWiFi(const char* ssid, const char* password);
    void sendData(int clientSocket, const char* data);
    std::string receiveData(int clientSocket);
    bool handleIncomingData(int clientSocket);

public:
    void HelloPI();
    static void* ManageCarCommunication(void* arg);
};

#endif
