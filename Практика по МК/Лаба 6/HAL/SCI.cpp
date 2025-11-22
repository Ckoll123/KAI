#include "HAL/SCI.h"
#include "DSP2833x_Sci.h"


SCI_port::SCI_port(SCI_VARIANT sci_port_variant) :
    _variant(sci_port_variant)
{}


void SCI_port::_init_scia_gpio(){
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled disabled by the user.  
    // This will enable the pullups for the specified pins.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;  // Enable pull-up for GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	 // Enable pull-up for GPIO29 (SCITXDA)

    //
    // Set qualification for selected pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.  
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
    
    //
    // Configure SCI-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SCI functional
    // pins.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 to SCIRXDA 
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 to SCITXDA 

    EDIS;
}


void SCI_port::_init_scib_gpio(){
    EALLOW;

    //
    // Enable internal pull-up for the selected pins 
    // Pull-ups can be enabled or disabled disabled by the user.  
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;  //Enable pull-up for GPIO9  (SCITXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0; //Enable pull-up for GPIO14 (SCITXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	 //Enable pull-up for GPIO18 (SCITXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0; //Enable pull-up for GPIO22 (SCITXDB)

    //GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0; //Enable pull-up for GPIO11 (SCIRXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0; //Enable pull-up for GPIO15 (SCIRXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	 //Enable pull-up for GPIO19 (SCIRXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0; //Enable pull-up for GPIO23 (SCIRXDB)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDB)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)

    //
    // Configure SCI-B pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SCI functional 
    // pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;  //Configure GPIO9 to SCITXDB 
    //GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2; //Configure GPIO14 to SCITXDB
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;  //Configure GPIO18 to SCITXDB
    //GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3; //Configure GPIO22 to SCITXDB

    //GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;  //Configure GPIO11 for SCIRXDB
    //GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;  //Configure GPIO15 for SCIRXDB
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   //Configure GPIO19 for SCIRXDB
    //GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;  //Configure GPIO23 for SCIRXDB

    EDIS;
}


void SCI_port::_init_scic_gpio(){
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled disabled by the user.  
    // This will enable the pullups for the specified pins.
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;  // Enable pull-up for GPIO62 (SCIRXDC)
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;	 // Enable pull-up for GPIO63 (SCITXDC)

    //
    // Set qualification for selected pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.  
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)

    //
    // Configure SCI-C pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SCI functional 
    // pins.
    //
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 to SCIRXDC
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 to SCITXDC

    EDIS;
}


void SCI_port::initGPIO(){
    if (_variant == SCIa) { _init_scia_gpio(); }
    else if (_variant == SCIb) { _init_scib_gpio(); }
    else { _init_scic_gpio(); }
}


void SCI_port::config(const SCI_port_config& config){
    if (_variant == SCIa) { _p_SCI_regs = &SciaRegs; }
    else if (_variant == SCIb) { _p_SCI_regs = &ScibRegs; }
    else { _p_SCI_regs = &ScicRegs; }

    // SCICTL1.5 - Software reset 0/1-reset/active state
    _p_SCI_regs->SCICTL1.bit.SWRESET = 0;
    
    // SCICCR.7 - Number of stop bits
    if(config.sci_config.stopbits == ONE){ _p_SCI_regs->SCICCR.bit.STOPBITS = 0;}
    if(config.sci_config.stopbits == TWO){ _p_SCI_regs->SCICCR.bit.STOPBITS = 1;}

    // SCICCR.5 - Parity enable
    // SCICCR.6 - Parity odd/even
    if(config.sci_config.parity == NO){   _p_SCI_regs->SCICCR.bit.PARITYENA = 0x00; _p_SCI_regs->SCICCR.bit.PARITY = 0x00;}
    if(config.sci_config.parity == ODD){  _p_SCI_regs->SCICCR.bit.PARITYENA = 0x01; _p_SCI_regs->SCICCR.bit.PARITY = 0x00;}
    if(config.sci_config.parity == EVEN){ _p_SCI_regs->SCICCR.bit.PARITYENA = 0x01; _p_SCI_regs->SCICCR.bit.PARITY = 0x01;}

    // SCICCR.2-0 - Character-length
    if(config.sci_config.lenght == LEN1){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x00;}
    if(config.sci_config.lenght == LEN2){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x01;}
    if(config.sci_config.lenght == LEN3){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x02;}
    if(config.sci_config.lenght == LEN4){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x03;}
    if(config.sci_config.lenght == LEN5){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x04;}
    if(config.sci_config.lenght == LEN6){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x05;}
    if(config.sci_config.lenght == LEN7){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x06;}
    if(config.sci_config.lenght == LEN8){ _p_SCI_regs->SCICCR.bit.SCICHAR = 0x07;}
    
    // SCICCR.4 - Loop Back test mode enable
    _p_SCI_regs->SCICCR.bit.LOOPBKENA = config.self_test_mode;

    _p_SCI_regs->SCICTL1.bit.RXENA = 1; // Receiver enable
    _p_SCI_regs->SCICTL1.bit.TXENA = 1; // Transmitter enable

    // Ideal Baud       BRR             Actual Baud     Error, %
    //  2400            1952(07A0h)     2400            0
    //  4800            976(03D0h)      4798            -0,04
    //  9600            487(01E7h)      9606            0.06
    //  19200           243(00F3h)      19211           0.06
    //  38400           121(0079h)      38422           0.006

    if(config.sci_config.baudrate == BR2400){ _p_SCI_regs->SCIHBAUD = 0x0007; _p_SCI_regs->SCILBAUD = 0x00A0;}
    if(config.sci_config.baudrate == BR4800){ _p_SCI_regs->SCIHBAUD = 0x0003; _p_SCI_regs->SCILBAUD = 0x00D0;}
    if(config.sci_config.baudrate == BR9600){ _p_SCI_regs->SCIHBAUD = 0x0001; _p_SCI_regs->SCILBAUD = 0x00E7;}
    if(config.sci_config.baudrate == BR19200){ _p_SCI_regs->SCIHBAUD = 0x0000; _p_SCI_regs->SCILBAUD = 0x00F3;}
    if(config.sci_config.baudrate == BR38400){ _p_SCI_regs->SCIHBAUD = 0x0000; _p_SCI_regs->SCILBAUD = 0x0079;}

    // SCICTL1.5 - Relinquish SCI from Reset
    _p_SCI_regs->SCICTL1.bit.SWRESET = 1;
}


void SCI_port::transmit_message(uint16_t tx_data){
    if (_p_SCI_regs->SCICTL2.bit.TXRDY) {
        tx_data &= 0x00FF;
        _p_SCI_regs->SCITXBUF = tx_data;
    }
}


bool SCI_port::is_new_message(){
    if (_p_SCI_regs->SCIRXST.bit.RXRDY) { return true; }
    else { return false; }
}


uint16_t SCI_port::receive_message(){
    return _p_SCI_regs->SCIRXBUF.all;
}


bool SCI_port::is_tx_buffer_empty() const{
    return _p_SCI_regs->SCICTL2.bit.TXRDY;
}
