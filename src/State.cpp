#include <Arduino.h>
#include <State.h>

State::State() {
}

State::~State() {
}

OpMode State::getOpMode() {
    return opMode;
}


void State::setOpMode(OpMode opMode) {
    if(this->opMode == opMode) {
        return;
    }

    if(opMode == OFF) {
        if(offStateSince == -1) {
            offStateSince = millis();
        }

        if(offStateSince > millis() - OFF_STATE_TRESHOLD) {
            return; 
        }
        offStateSince = -1;
        inUserMode = false;
    } else {
        if(!stateChangeExpected) {
            inUserMode = true;
        }
    }

    Serial.print("Switching to: ");
    Serial.println(OpModeStr[opMode]);

    this->opMode = opMode;
    stateChangeExpected = false;
}

bool State::isInUserMode() {
    return inUserMode;
}

void State::changeToUserMode() {
    inUserMode = true;
}