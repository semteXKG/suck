#ifndef MACHINECONTROLLER_H
#define MACHINECONTROLLER_H

#include <Arduino.h>
#include <Constants.h>
#include <State.h>

static const int IMPULSE_DURATION = 100;
static const int IMPULSE_DELAY = 1000;

class MachineController {
private:
    gpio_num_t lowRelayPower;
    gpio_num_t lowRelayCommon; 
    gpio_num_t highRelayPower;
    gpio_num_t highRelayCommon; 
    State* state;
    MachineStatus prevousStatus = MachineStatus::OFF;
public:
    MachineController(gpio_num_t lowRelayPower, gpio_num_t highRelayPower, State* state);
    ~MachineController();
    
    void onTick();
};



#endif