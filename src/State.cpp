#include <Arduino.h>
#include <State.h>

State::State() {
    status = MachineStatus::OFF;
    opMode = OpMode::LOCAL;
}

State::~State() {
}

OpMode State::getOpMode() {
    return opMode;
}


void State::setOpMode(OpMode opMode) {
    if(opMode == this->opMode) {
        return;
    }

    Serial.print("Switching OpMode: ");
    Serial.print(OpModeStr[this->opMode]);
    Serial.print(" -> ");
    Serial.println(OpModeStr[opMode]);

    this->opMode = opMode;
}

void State::setStatus(MachineStatus status) {
    if(status == this->status) {
        return;
    }
    
    Serial.print("Switching Status: ");
    Serial.print(MachineStatusStr[this->status]);
    Serial.print(" -> ");
    Serial.println(MachineStatusStr[status]);
    this->status = status;
}

MachineStatus State::getStatus() {
    return this->status;
}