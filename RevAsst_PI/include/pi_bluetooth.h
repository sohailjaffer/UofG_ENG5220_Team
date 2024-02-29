#ifndef PI_BLUETOOTH_H
#define PI_BLUETOOTH_H

    #include <stdio.h>
    #include "pigpio.h"

    #include <bluetooth/bluetooth.h>
    #include <bluetooth/hci.h>
    #include <bluetooth/hci_lib.h>

    struct pi_ble_result {
    int device_id;
    int socket;
    };

    extern int pi_ble_init(void);
    extern void pi_ble_scan_print(void);
    extern void pi_ble_connection(void);

#endif
