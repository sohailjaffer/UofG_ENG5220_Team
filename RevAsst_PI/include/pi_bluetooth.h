#ifndef PI_BLUETOOTH_H
#define PI_BLUETOOTH_H

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <unistd.h>
#include "main.h"
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>



struct pi_ble_result {
    int device_id;
    int socket;
};

// struct sockaddr_rc {
//     sa_family_t rc_family;
//     bdaddr_t rc_bdaddr;
//     uint8_t rc_channel;
// };
extern pi_ble_result pi_ble_init(void);
extern bool connectBluetooth(const std::string& deviceAddress, const std::string& serviceUUID);

extern void pi_ble_scan_print(const pi_ble_result& result);
extern void pi_ble_connection(const pi_ble_result& result, const char* targetDeviceAddress);
extern int Bluetooth_Simple_Connect();


#endif // PI_BLUETOOTH_H
