#include "HAL/GPIO.h"


void GPIO::GPIO_setup(){
    EALLOW;

    // GPIO 58 (K1) as input
    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;     // Enable pullup on GPIO58
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;    // GPIO58 = GPIO58
    GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;     // GPIO58 = input

    // GPIO 60 (LED1) as output
    GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;     // Enable pullup on GPIO60
    GpioDataRegs.GPBSET.bit.GPIO60 = 1;     // Load output latch
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0;    // GPIO60 = GPIO60
    GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;     // GPIO60 = output

    // GPIO 61 (LED2) as output
    GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0;     // Enable pullup on GPIO61
    GpioDataRegs.GPBSET.bit.GPIO61 = 1;     // Load output latch
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;    // GPIO61 = GPIO61
    GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;     // GPIO61 = output

    EDIS;
}   // GPIO_setup


void GPIO::LED1_on(){
    GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
}   // LED1_on


void GPIO::LED1_off(){
    GpioDataRegs.GPBSET.bit.GPIO60 = 1;
}   // LED1_off


void GPIO::LED1_toggle(){
    GpioDataRegs.GPBTOGGLE.bit.GPIO60 = 1;
}   // LED1_toggle


bool GPIO::LED1_state(){
    return !GpioDataRegs.GPBDAT.bit.GPIO60;
}   // LED1_state


void GPIO::LED2_on(){
    GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
}   // LED2_on


void GPIO::LED2_off(){
    GpioDataRegs.GPBSET.bit.GPIO61 = 1;
}   // LED2_off


void GPIO::LED2_toggle(){
    GpioDataRegs.GPBTOGGLE.bit.GPIO61 = 1;
}   // LED2_toggle


bool GPIO::LED2_state(){
    return !GpioDataRegs.GPBDAT.bit.GPIO61;
}   // LED2_state


bool GPIO::K1_state(){
    return !GpioDataRegs.GPBDAT.bit.GPIO58;
}   // K1_state
