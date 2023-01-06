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

bool MachineController::setTargetState(OpMode targetMode, boolean overrideCommand) {
    if (overrideCommand) {
        state->changeToUserMode();
    }
    Serial.println("BEEP BEEP");
    if(!isStateChangeAllowed() && !overrideCommand) {
        return false;
    }
    Serial.println("BOOP BOOP");
    Serial.printf("Requesting new state %s, manual override = %d", OpModeStr[targetMode], overrideCommand);
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
    Serial.println("Triggering OFF relais");
    digitalWrite(pinOff, HIGH);
    delay(IMPULSE_DURATION);
    digitalWrite(pinOff, LOW);
    lastOffImpulse = millis();
}

void MachineController::triggerOnRelais() {
    if(lastOnImpulse + IMPULSE_DELAY > millis()) {
        return;
    }
    Serial.println("Triggering ON relais");
    digitalWrite(pinOn, HIGH);
    delay(IMPULSE_DURATION);
    digitalWrite(pinOn, LOW);
    lastOnImpulse = millis();
}

void MachineController::onTick() {
    if (targetMode == UNTRACKED) {
        return;
    }
    if(state->getOpMode() == targetMode) {
        targetMode = UNTRACKED;
        return;
    }

    if(targetMode == OFF) {
        triggerOffRelais();
        return;
    }
    
    triggerOnRelais();
}