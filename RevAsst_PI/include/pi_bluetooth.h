
#pragma once
#include <stdio.h>
#include "pigpio.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

extern int pi_ble_init(void);
extern void pi_ble_scan_print(void);
extern void pi_ble_connection(void);


