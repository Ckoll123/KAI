#pragma once

#include "DSP28x_Project.h"

class GPIO
{
public:
    static void GPIO_setup();

    static void LED1_on();
    static void LED1_off();
    static void LED1_toggle();
    static bool LED1_state();

    static void LED2_on();
    static void LED2_off();
    static void LED2_toggle();
    static bool LED2_state();

    static bool K1_state();
};
