#include <Arduino.h>
#include <MachineController.h>
#include <LedTracker.h>
#include <State.h>
#include <WebServer.h>
#include <SPIFFS.h>
State* state;
LedTracker* ledTracker;
MachineController* machineController;

void setup() {
  Serial.begin(115200);
  state = new State();
  ledTracker = new LedTracker(GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_35, state);
  machineController = new MachineController(GPIO_NUM_20, GPIO_NUM_21, state);
}

void loop() {
  ledTracker->onTick();
  machineController->onTick();
  delay(3000);
}