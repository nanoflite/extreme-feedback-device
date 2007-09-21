USBFLAGS = `libusb-config --cflags`
USBLIBS = `libusb-config --libs` #-framework CoreFoundation
VERSION = 0.1
NAME = "efd_1"

#USBFLAGS = -I/usr/local/include
#USBLIBS = -L/usr/local/lib -lusb

.PHONY: all dist srcdist

all: EFD_1_LIB efd1

EFD_1_LIB=libefd1.so

EFD_1_LIB: efd.o
	gcc -shared -Wl,-soname,${EFD_1_LIB} -o ${EFD_1_LIB} efd.o -lusb

efd.o: efd.c efd.h
	gcc -fPIC -g -c -Wall efd.c

clean:
	rm -f *.o *.so test

test: efd1
	su -c ./test.sh

efd1: main.c ${EFD_1_LIB}
	gcc main.c -o efd1 -L. -lefd1

srcdist: clean
	tar zcvf $(NAME)-$(VERSION)-src.tgz efd.c efd.h main.c test.sh Makefile

dist: all
	tar zcvf $(NAME)-$(VERSION).tgz libefd1.so efd1
