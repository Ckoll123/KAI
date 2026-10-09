#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "HAL/GPIO.h"
#include "HAL/State.h"
#include "HAL/Button.h"
#include "HAL/Led.h"

#define INTERRUPT_PERIOD_US 100000
#define INTERRUPT_PERIOD_SEC (INTERRUPT_PERIOD_US / 1e6f)   // 1e6f = static_cast<float>(1000000)

interrupt void CPU_Timer0();

volatile uint16_t idle_counter = 0;
volatile bool led1_turn_on = false;
volatile bool led1_turn_off = false;
volatile bool led1_turn_toggle = false;

State led1_state;
volatile uint16_t led1_on_counter = 0;
volatile uint16_t led1_sw_on_counter = 0;

Button button_K1(K1_state, static_cast<float>(INTERRUPT_PERIOD_SEC), 0.1);
Led led1(LED1_state, static_cast<float>(INTERRUPT_PERIOD_SEC));

void idle_loop();


int main(){
    InitSysCtrl();

    DINT;

    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    
    EALLOW;
    PieVectTable.TINT0 = &CPU_Timer0;
    EDIS;

    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    IER |= M_INT1;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, INTERRUPT_PERIOD_US);
    CpuTimer0Regs.TCR.all = 0x4010;

    GPIO_setup();
    led1.configure(LED1_on, LED1_off, LED1_toggle);

    EINT;

    CpuTimer0Regs.TCR.bit.TSS = 0;  // 0 - start, 1 - stop

    idle_loop();

    return 0;
}


void idle_loop(){
    while(true){
        // led1_state.update_state(LED1_state());

        // if (led1_turn_on) {
        //     LED1_on();
        //     led1_turn_on = false;
        // }

        // if (led1_turn_off) {
        //     LED1_off();
        //     led1_turn_off = false;
        // }

        // if (led1_turn_toggle) {
        //     LED1_toggle();
        //     led1_turn_off = false;
        // }

        // if (led1_state.is_on()) {
        //     led1_on_counter++;
        // }

        // if (led1_state.is_switched_on()) {
        //     led1_sw_on_counter++;
        // }
    }
}



void CPU_Timer0(){
    CpuTimer0.InterruptCount++;

    button_K1.update_state();
    if (button_K1.state.is_switched_on()) {
        LED1_toggle();
    }

    led1.blink_by_time(5, 5);

    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
}
