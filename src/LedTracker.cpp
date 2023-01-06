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
    if(lastUpdate + 2000 < millis()) {
        logOutput();
        lastUpdate = millis();
    }
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
    logField(pinLow, state->lightSensor.sensorLow);
    logField(pinMid, state->lightSensor.sensorMid);
    logField(pinHigh, state->lightSensor.sensorHigh);
    Serial.printf("\n");
}

void LedTracker::logField(gpio_num_t pin, int& store) {
    int val = analogRead(pinLow);
    double percent = ((4096 - val) / 4096.0) * 100.0;
    store = val;
    Serial.printf("Pin: %d - %3.2f percent (%d)\n", pin, percent, val);
}