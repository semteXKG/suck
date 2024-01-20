#include <Arduino.h>
#include <MachineController.h>
#include <State.h>
#include <WebServer.h>
#include <WlanManager.h>
#include <CredentialsManager.h>
#include <Webserver.h>
#include <DustTracker.h>
#include <InputManager.h>

State* state;
MachineController* machineController;
WlanManager* wlanManager;
CredentialsManager* credManager;
Webserver* webserver;
DustTracker* dustTracker;
InputManager* inputManager;


void setup() {
  Serial.begin(115200);
  Serial.printf("\n\n");
  state = new State();
  credManager = new CredentialsManager();
  credManager->writeFile(SSID_FILE, "");
  credManager->writeFile(PASSWORD, "");
  machineController = new MachineController(GPIO_NUM_25, GPIO_NUM_26, state);
  wlanManager = new WlanManager(credManager);
  wlanManager->start();
  webserver = new Webserver(credManager, machineController, state);
  webserver->start();
  dustTracker = new DustTracker(state);
  inputManager = new InputManager(GPIO_NUM_12, GPIO_NUM_14, state);
}

void loop() {
  machineController->onTick();
  dustTracker->onTick(); 
  inputManager->tick();
  delay(50);
}