#include "wifi_pi.h"
#include "blinky.h"

#define PORT 12345 // Change this to the desired port

// Function to initialize Wi-Fi using wpa_supplicant
void initWiFi() {
    // Assuming wpa_supplicant is already installed and configured
    // You may need to modify this based on your specific Wi-Fi setup
    system("wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf");
    sleep(5); // Allow time for Wi-Fi initialization
}

// Function to connect to a Wi-Fi network
void connectWiFi(const char* ssid, const char* password) {
    // Modify wpa_supplicant.conf dynamically
    std::string command = "wpa_passphrase '" + std::string(ssid) + "' '" + std::string(password) + "' >> /etc/wpa_supplicant/wpa_supplicant.conf";
    system(command.c_str());

    // Restart wpa_supplicant to apply changes
    system("sudo systemctl restart wpa_supplicant");
    sleep(5); // Allow time for Wi-Fi connection
}


void sendData(int clientSocket, const char* data) {
    send(clientSocket, data, strlen(data), 0);
}


std::string receiveData(int clientSocket) {
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    return std::string(buffer);
}



bool handleIncomingData(int clientSocket) {
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Received data: " << buffer << std::endl;

    // Check if received data is "stop server"
    if (std::string(buffer) == "stop server") {
        std::cout << "Received 'stop server'. Closing the socket." << std::endl;
        return true; // Signal to close the socket
    }

    // Process the received data as needed...

    return false; // Continue normal operation
}

void HelloPI(){


    initWiFi();
    connectWiFi("Sohail", "12345679");
    // Set up a socket for communication
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

    

    // Clean up
    close(clientSocket);
    close(serverSocket);

}

void DriveCar(){

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
        // Receive data from the client
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead <= 0) {
            // Connection closed or error occurred
            std::cout << "Client disconnected." << std::endl;
            break;
        }

   // Print the received data
        std::cout << "Received command: " << buffer << std::endl;

        // Compare the received command
        if (strcmp(buffer, "$1") == 0) {
            // Handle $1 command (e.g., call forward(255))
             gpio_init();
             forward(255);

        } else if (strcmp(buffer, "$2") == 0) {
            // Handle $2 command (e.g., call backward(255))
            gpio_init();
            backward(255);
         
            //sleep(0.1);
           // wait(100);
        } else if (strcmp(buffer, "$3") == 0) {
            // Handle $3 command (e.g., call left(255))
            gpio_init();
            left(255);
         
            //sleep(0.1);
            //wait(100);
        } else if (strcmp(buffer, "$4") == 0) {
            gpio_init();
            right(255);
     
        }else if (strcmp(buffer,"$5")==0){

            gpio_init();
            forwardright(255);

        } 
        else if (strcmp(buffer,"$6")==0){

            gpio_init();
            forwardleft(255);

        } else if (strcmp(buffer,"$7")==0){

            gpio_init();
            backwardright(255);

        } 
        else if (strcmp(buffer,"$8")==0){

            gpio_init();
            backwardleft(255);

        } 
        
        
        else {
            // Unknown command
            std::cout << "Unknown command: " << buffer << std::endl;
        }




        // Process the command as needed...

        // Clear the buffer for the next iteration
        memset(buffer, 0, sizeof(buffer));
    }

    // Clean up
    close(clientSocket);
    close(serverSocket);

}