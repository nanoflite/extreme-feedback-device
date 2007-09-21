/*
 * EFD 1 - Extreme Feedback Device One driver for libusb.
 *
 * (c) 2007 Johan Van den Brande
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "efd.h"

void do_cmd(efd_1_dev *handle, efd_1_cmd command, efd_1_param param) {
    efd_1_command(handle, command, param);
}

int main(int argc, char **argv)
{
    int i, j, p;
    efd_1_dev *handle;

    if (argc != 3) {
        puts("usage: efd1 on|off 1..7");
        puts("usage: efd1 cycle_on|cycle_off 1|2|3");
        return 0;
    }

    handle = efd_1_new();
    if (handle == NULL) {
        puts("ERROR");
        exit(1);
    }

    char *cmd_p = (char *) argv[1];
    efd_1_param param = (efd_1_param) atoi(argv[2]);

    efd_1_cmd cmd;
    if (strcmp(cmd_p, "on") == 0) {
        do_cmd(handle, ON, param);
    } else
    if (strcmp(cmd_p, "off") == 0) {
        do_cmd(handle, OFF, param);
    } else
    if (strcmp(cmd_p, "cycle_on") == 0) {
        do_cmd(handle, CYCLE_ON, param);
    } else
    if (strcmp(cmd_p, "cycle_off") == 0) {
        do_cmd(handle, CYCLE_OFF, param);
    } else {
        puts("WOOPS");
    }

    efd_1_close(handle);
    return 0;
}
