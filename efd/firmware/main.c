/*
 * EFD 1 - Extreme Feedback Device One firmware
 *
 * (c) 2007 Johan Van den Brande
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "usbdrv.h"
#include "oddebug.h"

#define LED_DDR DDRB
#define LED_PORT    PORTB
#define LED_PIN PINB
#define LED_R_BIT   0
#define LED_G_BIT   1
#define LED_B_BIT   2

#define WAIT_DURATION 20000


#define LED_ON(LED_BIT) LED_PORT |= _BV(LED_BIT)
#define LED_OFF(LED_BIT)    LED_PORT &= ~_BV(LED_BIT)
#define LED_TOGGLE(LED_BIT) LED_PORT ^= _BV(LED_BIT)

uchar cycle;

void init(void)
{
    // Configure LEDs as output
    LED_DDR |= _BV(LED_R_BIT) | _BV(LED_G_BIT) | _BV(LED_B_BIT);
}


uchar   usbFunctionSetup(uchar data[8])
{
    uchar param = data[2];
    switch (data[1]) {
        case 0: // ON
            LED_PORT |= param;
            break;
        case 1: // OFF
            LED_PORT &= ~param;
            break;
        case 2: // CYCLE ON
            cycle = param;
            break;
        case 3: // CYCLE OFF
            cycle = 0;
            LED_PORT = 0;
            break;
    }

    return 0;
}

int main(void)
{
    uchar   i, j;
    int c;
    j = 0;
    while(--j){         /* USB Reset by device only required on Watchdog Reset */
        i = 0;
        while(--i);     /* delay >10ms for USB reset */
    }
    usbInit();
    init();
    sei();
    c = 0;
    i = 0;
    for(;;){
        usbPoll();
        c++;
        if (c > WAIT_DURATION) {
            c = 0;
            switch (cycle) {
                case 1:
                    LED_PORT ^= 7;  // toggle all leds
                    break;
                case 2:
                    LED_OFF(i);
                    i++;
                    i &= 3;
                    LED_ON(i);
                    break;
                case 3:
                    LED_TOGGLE(0);
                    break;
            }
        }
    }
    return 0;
}
