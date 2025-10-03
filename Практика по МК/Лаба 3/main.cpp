#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "HAL/GPIO.h"
#include "HAL/State.h"


volatile uint16_t idle_counter = 0;
volatile bool led1_turn_on = false;
volatile bool led1_turn_off = false;
volatile bool led1_turn_toggle = false;

State led1_state(GPIO::LED1_state);
volatile uint16_t led1_turn_on_counter = 0;

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

        if (led1_state.is_on()) {
            idle_counter++;
        }

        if (led1_state.is_switched_on()) {
            led1_turn_on_counter++;
        }
    }
}



