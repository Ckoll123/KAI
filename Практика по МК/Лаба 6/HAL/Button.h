#pragma once

#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "HAL/State.h"

class Button{
public:
    Button(bool (*p_pin_on_state)(), float time_sample, float debounce_period_sec);
    void update_state();
    State state;
    
private:
    bool _prev_raw_state;

    float _time_sample;
    float _debounce_period;
    float _counter;
};
