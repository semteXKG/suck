#include <MachineController.h>

MachineController::MachineController(gpio_num_t pinOn, gpio_num_t pinOff, State* state) {
    this->pinOff = pinOff;
    this->pinOn = pinOn;
    this->state = state;
    pinMode(pinOff, OUTPUT);
    pinMode(pinOn, OUTPUT);
    targetMode = state->getOpMode();
    lastOffImpulse = 0;
    lastOnImpulse = 0;
}

MachineController::~MachineController() {
}

bool MachineController::setTargetState(OpMode targetMode) {
    if(!isStateChangeAllowed()) {
        return false;
    }
    this->targetMode = targetMode;
    return true;
}

bool MachineController::isStateChangeAllowed() {
    return !state->isInUserMode();
}

void MachineController::triggerOffRelais() {
    if(lastOffImpulse + IMPULSE_DELAY > millis()) {
        return;
    }
    digitalWrite(pinOff, HIGH);
    delay(IMPULSE_DURATION);
    digitalWrite(pinOff, LOW);
    lastOffImpulse = millis();
}

void MachineController::triggerOnRelais() {
    if(lastOnImpulse + IMPULSE_DELAY > millis()) {
        return;
    }
    digitalWrite(pinOn, HIGH);
    delay(IMPULSE_DURATION);
    digitalWrite(pinOn, LOW);
    lastOnImpulse = millis();
}

void MachineController::onTick() {
    if(state->getOpMode() == targetMode) {
        return;
    }

    if(targetMode == OFF) {
        triggerOffRelais();
        return;
    }
    
    triggerOnRelais();
}