#include <InputManager.h>


InputManager::InputManager(gpio_num_t opModeSelect, gpio_num_t machineStatusSelect, State* state) {
    this->opModeButton = new Bounce2::Button();
    this->machineStatusButton = new Bounce2::Button();
    this->state = state;
    opModeButton->attach(opModeSelect, INPUT_PULLDOWN);
    machineStatusButton->attach(machineStatusSelect, INPUT_PULLDOWN);
    opModeButton->interval(5);
    machineStatusButton->interval(5);
}
        
InputManager::~InputManager() {

}

void InputManager::tick() {
    opModeButton->update();
    machineStatusButton->update();

    if(opModeButton->pressed()) {
        state->setOpMode(static_cast<OpMode>((state->getOpMode() + 1) % 3));
    }

    if(machineStatusButton->pressed()) {
        state->setOpMode(OpMode::LOCAL);
        state->setStatus(static_cast<MachineStatus>((state->getStatus() + 1) %3));
    }
}