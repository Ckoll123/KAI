#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "HAL/GPIO.h"
#include "HAL/State.h"
#include "HAL/Button.h"
#include "HAL/Led.h"
#include "HAL/SCI.h"

#define INTERRUPT_PERIOD_US 1000
#define INTERRUPT_PERIOD_SEC (INTERRUPT_PERIOD_US / 1e6f)   // 1e6f = static_cast<float>(1000000)

interrupt void CPU_Timer0();

volatile uint16_t idle_counter = 0;
volatile bool led1_turn_on = false;
volatile bool led1_turn_off = false;
volatile bool led1_turn_toggle = false;

State led1_state(GPIO::LED1_state);
volatile uint16_t led1_turn_on_counter = 0;

Button button_K1(GPIO::K1_state, static_cast<float>(INTERRUPT_PERIOD_SEC), 0.1);
Led led1(GPIO::LED1_state, static_cast<float>(INTERRUPT_PERIOD_SEC));
SCI_port sci_a(SCIa);

volatile bool sendBit = false;
volatile uint16_t SendChar = 0;
volatile uint16_t ReceivedChar = 0;
volatile uint16_t ErrorCount = 0;

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

    GPIO::GPIO_setup();
    sci_a.initGPIO();

    led1.configure(GPIO::LED1_on, GPIO::LED1_off, GPIO::LED1_toggle);

    SCI_port_config config;
    config.self_test_mode = true;
    config.sci_config.baudrate = BR9600;
    config.sci_config.lenght = LEN8;
    config.sci_config.parity = NO;
    config.sci_config.stopbits = ONE;
    sci_a.config(config);

    EINT;

    CpuTimer0Regs.TCR.bit.TSS = 0;  // 0 - start, 1 - stop

    idle_loop();

    return 0;
}


void idle_loop(){
    while(true){
        if (sci_a.is_new_message()){
            ReceivedChar = sci_a.receive_message();
            if(ReceivedChar != SendChar) ErrorCount++;
        }

        if (sendBit) {
            sendBit = false;
            sci_a.transmit_message(led1.get_blink_counter());
        }
    }
}



void CPU_Timer0(){
    CpuTimer0.InterruptCount++;

    led1.blink_by_time(1, 1);


     {
        sci_a.transmit_message(SendChar);
//        sci_a.transmit_message(led1.get_blink_counter());

        // Check received character
        while (!sci_a.is_new_message()) {}
        ReceivedChar = sci_a.receive_message();

        if (ReceivedChar != SendChar) ErrorCount++;

        // Move to the next character and repeat the test
        SendChar++;
        if (SendChar > 0x00FF) { SendChar = 0; }
     }

    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
}

