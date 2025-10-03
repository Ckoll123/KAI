#pragma once

#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

class State{
public:
    State(bool (*p_pin_on_state)());
    
    void update_state();
    bool is_on() const;
    bool is_off() const;
    bool is_switched_on() const;
    bool is_switched_off() const;

protected:
    bool (*_p_pin_on_state)();
    bool _previous_state;
    bool _on;
    bool _off;
    bool _sw_on;
    bool _sw_off;
};
