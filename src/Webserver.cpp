#include <Webserver.h>

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

    webserver->on("/status", HTTP_GET, [&](AsyncWebServerRequest* request) {
        AsyncJsonResponse * response = new AsyncJsonResponse();
        response->addHeader("Server","ESP Async Web Server");
        JsonVariant& root = response->getRoot();
        JsonObject doc = root.to<JsonObject>();
        doc["manual"] = state->isInUserMode() ? "Manual" : "Auto";
        doc["deviceState"] = OpModeStr[state->getOpMode()];

        JsonArray lightSensorArray = doc.createNestedArray("lightSensors");
        lightSensorArray.add(state->lightSensor.sensorLowAsPercent());
        lightSensorArray.add(state->lightSensor.sensorMidAsPercent());
        lightSensorArray.add(state->lightSensor.sensorHighAsPercent());
          
        JsonArray pmSensorArray = doc.createNestedArray("pmSensors");
        pmSensorArray.add(state->airQuality.pm0_5);
        pmSensorArray.add(state->airQuality.pm2_5);
        pmSensorArray.add(state->airQuality.pm10);

        response->setLength();
        request->send(response);
    });

    webserver->on("/status/lightSensors", HTTP_GET, [&](AsyncWebServerRequest *request) {

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
