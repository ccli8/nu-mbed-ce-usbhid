/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include "mbed.h"
#include "usb/USBHID.h"

#define SEND_REPORT_SIZE 8
#define RECV_REPORT_SIZE 8

// Declare a USBHID device
USBHID HID(true, RECV_REPORT_SIZE, SEND_REPORT_SIZE, 0x1234, 0x0006, 0x0001);

HID_REPORT send_report;
HID_REPORT recv_report;

DigitalOut led_out(LED1);

int main(void)
{
    while (1) {

        // Fill the report
        send_report.length = SEND_REPORT_SIZE;
        for (int i = 0; i < send_report.length; i++) {
            //send_report.data[i] = rand() & UINT8_MAX;
            send_report.data[i] = i + 1;
        }

        // Send the report
        HID.send(&send_report);

        // Try to read a msg
        if (HID.read_nb(&recv_report)) {
            led_out = !led_out;
            for (int i = 0; i < recv_report.length; i++) {
                printf("%d ", recv_report.data[i]);
            }
            printf("\r\n");
        }
    }
}
