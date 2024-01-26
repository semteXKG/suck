#include <MachineController.h>

MachineController::MachineController(gpio_num_t lowRelayPower, gpio_num_t highRelayPower, State* state) {
    this->lowRelayPower = lowRelayPower;
    this->highRelayPower = highRelayPower;
    pinMode(lowRelayPower, OUTPUT);
    pinMode(highRelayPower, OUTPUT);
    this->state = state;
}

MachineController::~MachineController() {
}


void MachineController::onTick() {
    MachineStatus currenstStatus = state->getStatus();
    if(prevousStatus == currenstStatus) {
        return;
    }

    digitalWrite(lowRelayPower, HIGH);
    digitalWrite(highRelayPower, HIGH);
    delay(10);

    if(currenstStatus == MachineStatus::ON_LOW) {
        digitalWrite(lowRelayPower, LOW);
    } else if (currenstStatus == MachineStatus::ON_HIGH) {
        digitalWrite(highRelayPower, LOW);
    }
    prevousStatus = currenstStatus;
}