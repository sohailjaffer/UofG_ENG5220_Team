#include "pi_bluetooth.h"
#include <iostream>

pi_ble_result pi_ble_init(void) {
    pi_ble_result result;
    result.device_id = hci_get_route(nullptr);
    result.socket = hci_open_dev(result.device_id);
    return result;
}

void pi_ble_scan_print(const pi_ble_result  &result) {
    inquiry_info* devices = nullptr;
    int num_devices = hci_inquiry(result.device_id, 8, 255, nullptr, &devices, IREQ_CACHE_FLUSH);
    for (int i = 0; i < num_devices; ++i) {
        bdaddr_t bdaddr = devices[i].bdaddr;
        char addr[19];
        ba2str(&bdaddr, addr);
        printf("Device %d: %s\n", i + 1, addr);
    }
}


void pi_ble_connection(const pi_ble_result& result, const char* targetDeviceAddress) {
    struct sockaddr_rc addr = {0};
    addr.rc_family = AF_BLUETOOTH;

    // Convert the target device address from string to bdaddr_t
    bdaddr_t targetBdaddr;
    str2ba(targetDeviceAddress, &targetBdaddr);
    addr.rc_bdaddr = targetBdaddr;

    int s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    bind(s, (struct sockaddr*)&addr, sizeof(addr));

    // Establish connection to the specific device
    if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Connection failed");
        close(s);
        return;
    }

    // Connection established, send and receive messages
    char buffer[1024];

    while (true) {
        // Get message from user
        std::cout << "Enter message to send (type 'exit' to close connection): ";
        std::string messageToSend;
        std::getline(std::cin, messageToSend);

        // Check if the user wants to exit
        if (messageToSend == "exit") {
            break;
        }

        // Send message
        write(s, messageToSend.c_str(), messageToSend.size());

        // Receive message
        int bytesRead = read(s, buffer, sizeof(buffer));

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';  // Null-terminate the received string
            std::cout << "Received message: " << buffer << std::endl;
        } else {
            std::cerr << "Failed to read message" << std::endl;
            break;
        }
    }

    // Close the socket when done
    close(s);
}


bool connectBluetooth(const std::string& deviceAddress, const std::string& serviceUUID) {
    // Initialize socket
    int socketDescriptor = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (socketDescriptor == -1) {
        std::cerr << "Error creating socket." << std::endl;
        return false;
    }

    // Set the connection parameters
    sockaddr_rc serverAddress{};
    serverAddress.rc_family = AF_BLUETOOTH;
    serverAddress.rc_channel = (uint8_t)strtol(serviceUUID.c_str(), nullptr, 16);
    str2ba(deviceAddress.c_str(), &serverAddress.rc_bdaddr);

    // Connect to the remote device
    if (connect(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error connecting to the remote device." << std::endl;
        close(socketDescriptor);
        return false;
    }

    // Connection successful
    std::cout << "Connected to the remote device." << std::endl;

    // Now, you can send/receive data through the socket

    // Remember to close the socket when done
    close(socketDescriptor);

    return true;
}

int Bluetooth_Simple_Connect(){

   struct sockaddr_rc loc_addr = {0}, rem_addr = {0};
    char buf[1024] = {0};
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // Allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // Bind socket to any available local Bluetooth adapter and port 1
    loc_addr.rc_family = AF_BLUETOOTH;
    memset(&loc_addr.rc_bdaddr, 0, sizeof(bdaddr_t)); // Set Bluetooth address to zero
    loc_addr.rc_channel = (uint8_t)1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // Put socket into listening mode
    listen(s, 1);

    printf("Bluetooth server is listening for connections...\n");

    // Accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str(&rem_addr.rc_bdaddr, buf);
    fprintf(stderr, "Accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // Read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if (bytes_read > 0) {
        printf("Received: [%s]\n", buf);
    }

    // Close connection
    close(client);
    close(s);

    return 0;

}