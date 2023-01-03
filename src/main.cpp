#include <Arduino.h>
#include <LedTracker.h>
#include <State.h>

State* state;
LedTracker* ledTracker;

void setup() {
  state = new State();
  ledTracker = new LedTracker(GPIO_NUM_0, GPIO_NUM_1, GPIO_NUM_2, state);
}

void loop() {
  // put your main code here, to run repeatedly:
}