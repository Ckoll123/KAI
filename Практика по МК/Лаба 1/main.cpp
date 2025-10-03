#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

void idle_loop();

volatile uint16_t idle_counter = 0;

int main(){
    InitSysCtrl();

    DINT;

    EINT;

    idle_loop();

    return 0;
}

void idle_loop(){
    while(true){
        idle_counter++;
    }
}



