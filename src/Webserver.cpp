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
        doc["mode"] = OpModeStr[state->getOpMode()];
        doc["machineStatus"] = MachineStatusStr[state->getStatus()];
         
        JsonArray pmSensorArray = doc.createNestedArray("pmSensors");
        pmSensorArray.add(state->airQuality.pm0_5);
        pmSensorArray.add(state->airQuality.pm2_5);
        pmSensorArray.add(state->airQuality.pm10);

        response->setLength();
        request->send(response);
    });

    webserver->on("/operation/on_low", HTTP_GET, [&](AsyncWebServerRequest *request) {
        Serial.println("Triggering LOW");
        if(this->state->getOpMode() != OpMode::API) {
          request->send(SPIFFS, "/index.html", "text/html", false, processor);
        }
        
        this->state->setStatus(MachineStatus::ON_LOW);
        request->send(SPIFFS, "/index.html", "text/html", true, processor);
    });

    webserver->on("/operation/on_high", HTTP_GET, [&](AsyncWebServerRequest *request) {
      Serial.println("Triggering LOW");
      if(this->state->getOpMode() != OpMode::API) {
        request->send(SPIFFS, "/index.html", "text/html", false, processor);
      }
        this->state->setStatus(MachineStatus::ON_HIGH);
        request->send(SPIFFS, "/index.html", "text/html", true, processor);
    });

    webserver->on("/operation/off", HTTP_GET, [&](AsyncWebServerRequest *request) {
      Serial.println("Triggering OFF");
      if(this->state->getOpMode() != OpMode::API) {
        request->send(SPIFFS, "/index.html", "text/html", false, processor);
      }
        this->state->setStatus(MachineStatus::OFF);
        request->send(SPIFFS, "/index.html", "text/html", true, processor);
    });

    webserver->begin();
}
