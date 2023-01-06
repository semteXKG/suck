#ifndef SUCK_WEBSERVER_H
#define SUCK_WEBSERVER_H

#include <Arduino.h>
#include <CredentialsManager.h>
#include <AsyncTCP.h>
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

Webserver::Webserver(CredentialsManager* credManager, MachineController* machineController, State* state) {
    this->credManager = credManager;
    this->machineController = machineController;
    this->state = state;
}

Webserver::~Webserver()
{
}

String processor(const String& var) {
    return var;    
}

void Webserver::start() {
    webserver = new AsyncWebServer(80);
    webserver->serveStatic("/", SPIFFS, "/");
    
    webserver->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    webserver->on("/status/manual", HTTP_GET, [&](AsyncWebServerRequest *request) {
        request->send(200, String(), state->isInUserMode() ? "Manual" : "Auto");
    });

    webserver->on("/status/deviceState", HTTP_GET, [&](AsyncWebServerRequest *request) {
        request->send(200, String(), OpModeStr[state->getOpMode()]);
    });

    webserver->on("/status/lightSensors", HTTP_GET, [&](AsyncWebServerRequest *request) {
        long start = millis();
        char buffer[50];
        int written = snprintf(buffer, 50, "<br>Low: %3.2f<br>Mid: %3.2f<br>High %3.2f", 
            state->lightSensor.sensorLowAsPercent(), 
            state->lightSensor.sensorMidAsPercent(), 
            state->lightSensor.sensorHighAsPercent());
       
        request->send(200, String(), buffer);
    });


    webserver->on("/operation/on_low", HTTP_GET, [&](AsyncWebServerRequest *request) {
        Serial.println("Triggering LOW");
        this->machineController->setTargetState(ON_LOW, true);
        request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    webserver->on("/operation/on_mid", HTTP_GET, [&](AsyncWebServerRequest *request) {
      this->machineController->setTargetState(ON_MID, true);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    webserver->on("/operation/on_high", HTTP_GET, [&](AsyncWebServerRequest *request) {
      this->machineController->setTargetState(ON_HIGH, true);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    webserver->on("/operation/off", HTTP_GET, [&](AsyncWebServerRequest *request) {
      this->machineController->setTargetState(OFF, true);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });


    webserver->begin();
}

#endif