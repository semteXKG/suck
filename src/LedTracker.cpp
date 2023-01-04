#include <LedTracker.h>
#include <Arduino.h>

LedTracker::LedTracker(gpio_num_t pinLow, gpio_num_t pinMid, gpio_num_t pinHigh, State* state) {  
    this->pinLow = pinLow;
    this->pinMid = pinMid;
    this->pinHigh = pinHigh;
    this->state = state;
    pinMode(pinLow, INPUT);
    pinMode(pinMid, INPUT);
    pinMode(pinHigh, INPUT);
}

bool LedTracker::isTurnedOn(gpio_num_t pin) {
    int value = analogRead(pinLow);
    return value < ON_TRESHHOLD;
}

void LedTracker::onTick() {
    logOutput();
    if(isTurnedOn(pinLow)) {
        state->setOpMode(ON_LOW);
    } else if (isTurnedOn(pinMid)) {
        state->setOpMode(ON_MID);
    } else if (isTurnedOn(pinHigh)) {
        state->setOpMode(ON_HIGH);
    } else {
        state->setOpMode(OFF);
    }
}

void LedTracker::logOutput() {
    Serial.print("Pin: ");
    Serial.print(pinLow);
    Serial.print(" - ");
    Serial.println(analogRead(pinLow));

    Serial.print("Pin: ");
    Serial.print(pinMid);
    Serial.print(" - ");
    Serial.println(analogRead(pinMid));

    Serial.print("Pin: ");
    Serial.print(pinHigh);
    Serial.print(" - ");
    Serial.println(analogRead(pinHigh));

}