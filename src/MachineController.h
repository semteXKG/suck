#ifndef MACHINECONTROLLER_H
#define MACHINECONTROLLER_H

#include <Arduino.h>
#include <OpMode.h>
#include <State.h>

static const int IMPULSE_DURATION = 100;
static const int IMPULSE_DELAY = 1000;

class MachineController {
private:
    gpio_num_t pinOn, pinOff;
    
    State* state;
    OpMode targetMode;
    
    long lastOnImpulse;
    long lastOffImpulse;

    void triggerOffRelais();
    void triggerOnRelais();
public:
    MachineController(gpio_num_t pinOn, gpio_num_t pinOff, State* state);
    ~MachineController();

    bool isStateChangeAllowed();
    bool setTargetState(OpMode targetMode, boolean overrideCommand);
    
    void onTick();

};



#endif