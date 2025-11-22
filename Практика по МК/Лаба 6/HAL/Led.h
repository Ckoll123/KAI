#pragma once

#include <stdint.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "HAL/State.h"


class Led{
public:
    Led(bool (*p_pin_on_state)(), float time_sample);
    void configure(void (*p_LED_on)(), void (*p_LED_off)(), void (*p_LED_toggle)());

    void set_on();
    void set_off();
    void toggle();

    void blink_by_time(float led_on_time_sec, float led_off_time_sec);
    uint32_t get_blink_counter() const;

    void reset();

public:
    State state;

private:
    void (*_p_LED_on)();
    void (*_p_LED_off)();
    void (*_p_LED_toggle)();

    float _time_sample;
    float _blink_timer;
    float _blink_counter;
};
