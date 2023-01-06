#include <Arduino.h>
#include <MachineController.h>
#include <LedTracker.h>
#include <State.h>
#include <WebServer.h>
#include <WlanManager.h>
#include <CredentialsManager.h>
#include <Webserver.h>

State* state;
LedTracker* ledTracker;
MachineController* machineController;
WlanManager* wlanManager;
CredentialsManager* credManager;
Webserver* webserver;

void setup() {
  Serial.begin(115200);
  Serial.printf("\n\n");
  state = new State();
  credManager = new CredentialsManager();
  ledTracker = new LedTracker(GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_35, state);
  machineController = new MachineController(GPIO_NUM_20, GPIO_NUM_21, state);
  wlanManager = new WlanManager(credManager);
  wlanManager->start();
  webserver = new Webserver(credManager, machineController, state);
  webserver->start();
}

void loop() {
  ledTracker->onTick();
  machineController->onTick();
}