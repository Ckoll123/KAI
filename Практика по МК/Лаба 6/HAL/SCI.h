#pragma once

#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

enum SCI_VARIANT{ SCIa, SCIb, SCIc };

enum SCI_BAUDRATE { BR2400, BR4800, BR9600, BR19200, BR38400 };
enum SCI_PARITY { NO, ODD, EVEN };
enum SCI_STOP_BITS { ONE, TWO };
enum SCI_WORD_LENGTH { LEN1, LEN2, LEN3, LEN4, LEN5, LEN6, LEN7, LEN8 };

struct SCI_configuration{
    SCI_BAUDRATE baudrate;
    SCI_PARITY parity;
    SCI_STOP_BITS stopbits;
    SCI_WORD_LENGTH lenght;

    SCI_configuration() :
        baudrate(BR2400),
        parity(NO),
        stopbits(ONE),
        lenght(LEN1)
    {}
};

struct SCI_port_config{
    SCI_configuration sci_config;
    bool self_test_mode;

    SCI_port_config() :
        sci_config(),
        self_test_mode(false)
    {}
};


class SCI_port{
public:
    SCI_port(SCI_VARIANT sci_port_variant);
    void initGPIO();
    void config(const SCI_port_config& config);

    void transmit_message(uint16_t tx_data);
    bool is_new_message();
    uint16_t receive_message();
    bool is_tx_buffer_empty() const;

private:
    void _init_scia_gpio();
    void _init_scib_gpio();
    void _init_scic_gpio();

private:
    SCI_VARIANT _variant;
    volatile SCI_REGS* _p_SCI_regs;
};
