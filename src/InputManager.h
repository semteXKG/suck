#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h>
#include <Bounce2.h>
#include <State.h>

class InputManager {
    private:
        Bounce2::Button* opModeButton;
        Bounce2::Button* machineStatusButton;
        State* state;
    public:
        InputManager(gpio_num_t opModeSelect, gpio_num_t machineStatusSelect, State* state);
        ~InputManager();
        void tick();
};

#endif