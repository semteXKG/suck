#ifndef LED_TRACKER
#define LED_TRACKER

#include <Arduino.h>
#include <State.h>

static const int ON_TRESHHOLD = 4096 / 8;

class LedTracker {
    private:
        gpio_num_t pinLow;
        gpio_num_t pinMid;
        gpio_num_t pinHigh;
        State* state;
        bool isTurnedOn(gpio_num_t pin);
        void logOutput();
    public:
        LedTracker(gpio_num_t pinLow, gpio_num_t pinMid, gpio_num_t pinHigh, State* state);
        void onTick();
};

#endif