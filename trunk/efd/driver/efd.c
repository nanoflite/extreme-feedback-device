/*
 * EFD 1 - Extreme Feedback Device One driver for libusb.
 *
 * (c) 2007 Johan Van den Brande
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "efd.h"

#define DEBUG(message)
// #define DEBUG(message)   puts(message)

int efd_1_claim(usb_dev_handle *dev)
{
    int interface = 0x00;

#   if defined(LIBUSB_HAS_GET_DRIVER_NP) && defined(LIBUSB_HAS_DETACH_KERNEL_DRIVER_NP)

    char name[512];

    memset(name, 0, 512);

    if (usb_get_driver_np( dev, interface, name, sizeof(name)) == 0) {

        DEBUG("Got driver.");

        if (usb_detach_kernel_driver_np( dev, interface ) < 0) {
            DEBUG(usb_strerror());
            return -1;
        }
        usb_set_altinterface(dev, interface);
    }

#   endif

    if (usb_claim_interface(dev, interface) < 0) {
        DEBUG(usb_strerror());
        return -1;
    }

    DEBUG("Claimed.\n");

    return 0;
}

efd_1_dev* efd_1_new()
{
    struct usb_bus *bus, *busses;
    struct usb_device *dev;
    usb_dev_handle *device_handle = NULL;
    int found = 0;
    efd_1_dev* handle;

    handle = malloc(sizeof(efd_1_dev));
    if (handle == NULL)
        return NULL;

    memset(handle, 0, sizeof(efd_1_dev));

    DEBUG("Trying to initialize device\n");

    usb_init();
    usb_find_busses();
    usb_find_devices();

    busses = usb_get_busses();
    for (bus = busses; bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {
            if ( (dev->descriptor.idVendor == EFD_1_VENDOR) && (dev->descriptor.idProduct == EFD_1_PRODUCT ) ) {
                found++;
                DEBUG("Found device\n");
                device_handle = usb_open(dev);
                if (device_handle == NULL) {
                    free(handle);
                    DEBUG("Could not open device\n");
                    return NULL;
                }
                if (efd_1_claim(device_handle) < 0) {
                    DEBUG(usb_strerror());
                    usb_close(device_handle);
                    free(handle);
                    return NULL;
                }
                DEBUG("Claimed device\n");
                handle->device = device_handle;
                DEBUG("Handle prepared, ready for return\n");
            }
        }
    }

    if (found == 0) {
        DEBUG("Could not find device.\n");
        free(handle);
        return NULL;
    }

    return handle;
}

void efd_1_close(efd_1_dev *handle)
{
    if (handle->device) {
        usb_release_interface(handle->device, 0x00);
        usb_close(handle->device);
    }
    if (handle)
        free(handle);
}

int efd_1_command(efd_1_dev *handle, efd_1_cmd command, efd_1_param param)
{
    unsigned char       buffer[8];
    return usb_control_msg(handle->device, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, command, param, 0, (char *)buffer, sizeof(buffer), 5000);
}
