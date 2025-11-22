#include "HAL/Led.h"


Led::Led(bool (*p_pin_on_state)(), float time_sample) :
    state(p_pin_on_state),
    _p_LED_on(0),
    _p_LED_off(0),
    _p_LED_toggle(0),
    _time_sample(time_sample),
    _blink_timer(0),
    _blink_counter(0)
{}


void Led::configure(void (*p_LED_on)(), void (*p_LED_off)(), void (*p_LED_toggle)()){
    _p_LED_on = p_LED_on;
    _p_LED_off = p_LED_off;
    _p_LED_toggle = p_LED_toggle;
}


void Led::set_on(){
    _p_LED_on();
}


void Led::set_off(){
    _p_LED_off();
}


void Led::toggle(){
    _p_LED_toggle();
}


void Led::blink_by_time(float led_on_time_sec, float led_off_time_sec){
    state.update_state();

    if (state.is_on()){
        if (_blink_timer >= led_on_time_sec){
            _blink_timer = 0;
            set_off();
            _blink_counter++;
        }
        else { _blink_timer += _time_sample; }
    }

    if (state.is_off()){
        if (_blink_timer >= led_off_time_sec){
            _blink_timer = 0;
            set_on();
        }
        else { _blink_timer += _time_sample; }
    }
}


void Led::reset(){
    set_off();
    state.update_state();
    _blink_counter = 0;
    _blink_timer = 0;
}


uint32_t Led::get_blink_counter() const{
    return _blink_counter;
}
