#ifndef LED_TRACKER
#define LED_TRACKER

#include <Arduino.h>
#include <State.h>

class LedTracker {
    private:
        gpio_num_t pinLow;
        gpio_num_t pinMid;
        gpio_num_t pinHigh;
        State* state;
    public:
        LedTracker(gpio_num_t pinLow, gpio_num_t pinMid, gpio_num_t pinHigh, State* state);
        void onTick();
};

LedTracker::LedTracker(gpio_num_t pinLow, gpio_num_t pinMid, gpio_num_t pinHigh, State* state) {
    this->pinLow = pinLow;
    this->pinMid = pinMid;
    this->pinHigh = pinHigh;
    this->state = state;
}

void LedTracker::onTick() {

}

#endif