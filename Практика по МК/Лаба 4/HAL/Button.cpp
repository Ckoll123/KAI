#include "HAL/Button.h"

Button::Button(bool (*p_pin_on_state)(), float time_sample, float debounce_period_sec) :
    state(p_pin_on_state),
    _prev_raw_state(false),
    _time_sample(time_sample),
    _debounce_period(debounce_period_sec),
    _counter(0.0)
{}


void Button::update_state() {
    bool pin_state = state.get_pin_state();
    bool stable_state = state.is_on();
    
    if (pin_state != _prev_raw_state) {
        _counter = 0.0;
        _prev_raw_state = pin_state;
    }else {
        if(_counter < _debounce_period) {
            _counter += _time_sample;
        }
    }

    if(_counter >= _debounce_period){
        stable_state = pin_state;
    }

    state.update_state(stable_state);
}
