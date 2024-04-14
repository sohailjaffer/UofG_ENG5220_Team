#include "wifi_pi.h"

void WiFiPi::initWiFi() {
    system("wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf");
    sleep(5); 
}

void WiFiPi::connectWiFi(const char* ssid, const char* password) {
    std::string command = "wpa_passphrase '" + std::string(ssid) + "' '" + std::string(password) + "' >> /etc/wpa_supplicant/wpa_supplicant.conf";
    system(command.c_str());
    system("sudo systemctl restart wpa_supplicant");
    sleep(5);
}

void WiFiPi::sendData(int clientSocket, const char* data) {
    send(clientSocket, data, strlen(data), 0);
}

std::string WiFiPi::receiveData(int clientSocket) {
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    return std::string(buffer);
}

bool WiFiPi::handleIncomingData(int clientSocket) {
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Received data: " << buffer << std::endl;

    if (std::string(buffer) == "stop server") {
        std::cout << "Received 'stop server'. Closing the socket." << std::endl;
        return true;
    }


    return false;
}

void WiFiPi::HelloPI() {
    initWiFi();
    connectWiFi("Sohail", "12345679");

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    std::cout << "Waiting for connection..." << std::endl;

    int clientSocket = accept(serverSocket, NULL, NULL);
    std::cout << "Client connected." << std::endl;

    bool closeSocket = false;

    while (!closeSocket) {
        closeSocket = handleIncomingData(clientSocket);
    }

    close(clientSocket);
    close(serverSocket);
}
void* WiFiPi::ManageCarCommunication(void* arg) {
    WiFiPi* wifiPi = static_cast<WiFiPi*>(arg);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    std::cout << "Waiting for connection..." << std::endl;

    int clientSocket = accept(serverSocket, NULL, NULL);
    std::cout << "Client connected." << std::endl;

    char buffer[1024] = {0};

    while (true) {

        if(threadKiller)
            break;
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead <= 0) {
            std::cout << "Client disconnected." << std::endl;
            break;
        }

        wifiPi->motorController.motorHandler(buffer);
    }

    close(clientSocket);
    close(serverSocket);
    threadKiller= true;
    pthread_exit(NULL);
}
