#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "HAL/GPIO.h"


volatile uint16_t idle_counter = 0;
volatile bool led1_turn_on = false;
volatile bool led1_turn_off = false;
volatile bool led1_turn_toggle = false;

void idle_loop();


int main(){
    InitSysCtrl();

    DINT;

    GPIO::GPIO_setup();

    EINT;

    idle_loop();

    return 0;
}

void idle_loop(){
    while(true){
        if (led1_turn_on) {
            GPIO::LED1_on();
            led1_turn_on = false;
        }

        if (led1_turn_off) {
            GPIO::LED1_off();
            led1_turn_off = false;
        }

        if (led1_turn_toggle) {
            GPIO::LED1_toggle();
            led1_turn_off = false;
        }

        if (GPIO::LED1_state()) {
            idle_counter++;
        }
    }
}



