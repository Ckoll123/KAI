#include "HAL/State.h"

State::State(bool (*p_pin_on_state)()) :
    _p_pin_on_state(p_pin_on_state),
    _previous_state(false),
    _on(false),
    _off(false),
    _sw_off(false),
    _sw_on(false)
{}

void State::update_state() {
    _on = _p_pin_on_state();
    _off = !_on;
    _sw_on = (!_previous_state && _on);
    _sw_off = (_previous_state && !_on);
    _previous_state = _on;
}

bool State::is_on() const{
    return _on;
}

bool State::is_off() const{
    return _off;
}

bool State::is_switched_on() const{
    return _sw_on;
}

bool State::is_switched_off() const{
    return _sw_off;
}
