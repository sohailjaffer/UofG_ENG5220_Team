#include "pi_bluetooth.h"




pi_ble_result pi_ble_init(void){

    pi_ble_result result;
    result.device_id = hci_get_route(nullptr);
    result.socket = hci_open_dev(device_id);
    return pi_ble_result;
}

/**
 * 
 * 
 * 
*/
void pi_ble_scan_print(pi_ble_result result){

    inquiry_info* devices = nullptr;
    int num_devices = hci_inquiry(device_id, 8, 255, nullptr, &devices, IREQ_CACHE_FLUSH);
    for (int i = 0; i < num_devices; ++i) {
    bdaddr_t bdaddr = devices[i].bdaddr;
    char addr[19];
    ba2str(&bdaddr, addr);
    printf("Device %d: %s\n", i + 1, addr);

}


}

void pi_ble_connection(void){
    
    struct sockaddr_rc addr = {0};
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t)1;  // Replace with your desired channel

    int s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    bind(s, (struct sockaddr*)&addr, sizeof(addr));
    listen(s, 1);

    int client = accept(s, nullptr, nullptr);

}
