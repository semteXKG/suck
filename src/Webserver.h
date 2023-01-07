#ifndef SUCK_WEBSERVER_H
#define SUCK_WEBSERVER_H

#include <Arduino.h>
#include <CredentialsManager.h>
#include <AsyncTCP.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <MachineController.h>
#include <State.h>

class Webserver
{
private:
    CredentialsManager* credManager;
    AsyncWebServer* webserver;
    MachineController* machineController;
    State* state;
public:
    Webserver(CredentialsManager* credManager, MachineController* machineController, State* state);
    ~Webserver();
    void start();
};

#endif