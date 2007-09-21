/*
 * EFD 1 - Extreme Feedback Device One driver for libusb.
 *
 * (c) 2007 Johan Van den Brande
 *
 */
#ifndef __EFD_H_
#define __EFD_H_

#include "usb.h"

#define EFD_1_VENDOR    0x16C0  /* VOTI */
#define EFD_1_PRODUCT   0x05DC  /* Obdev's free shared PID */

typedef enum {
    ON = 0,
    OFF,
    CYCLE_ON,
    CYCLE_OFF
} efd_1_cmd;

typedef unsigned char efd_1_param;

#define EFD_1_LED_RED   1
#define EFD_1_LED_GREEN 2
#define EFD_1_LED_BLUE  4

#define EFD_1_WILD      1
#define EFD_1_PSYCH     2
#define EFD_1_FLOWER    3

typedef struct {
    usb_dev_handle *device;
    efd_1_cmd last_command;
} efd_1_dev;

//** Returns the last error as string.
char *efd_1_strerror();

/** Initialize the library
 *
 * Return -1 when not successfull - efd_1_strerror contains details.
 */
efd_1_dev *efd_1_new();

//** Close
void efd_1_close(efd_1_dev *handle);

//** Command
int efd_1_command(efd_1_dev *handle, efd_1_cmd command, efd_1_param param);

#endif // __EFD_H_
