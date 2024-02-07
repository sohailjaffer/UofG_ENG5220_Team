#include "bluetooth.h"

int bluetooth_tester(){
    // Open a Bluetooth socket
    int dev_id = hci_get_route(nullptr);
    int sock = hci_open_dev(dev_id);

    if (dev_id < 0 || sock < 0) {
        std::cerr << "Error opening Bluetooth socket" << std::endl;
        return 1;
    }

    // Set up inquiry parameters
    inquiry_info* devices = nullptr;
    inquiry_info* ii = nullptr;
    int max_rsp = 255;
    int num_rsp = 0;
    int len = 8; // Inquiry length (seconds)
    int flags = IREQ_CACHE_FLUSH;

    // Perform device inquiry
    devices = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    num_rsp = hci_inquiry(dev_id, len, max_rsp, nullptr, &devices, flags);

    // Print the discovered devices
    for (ii = devices; num_rsp > 0; --num_rsp, ++ii) {
        char addr[19] = { 0 };
        ba2str(&(ii->bdaddr), addr);
        std::cout << "Device Address: " << addr << std::endl;
    }

    // Clean up
    free(devices);
    close(sock);

    return 0;
}


