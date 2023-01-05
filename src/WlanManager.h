#ifndef WLAN_MANAGER_H
#define WLAN_MANAGER_H

#include <Arduino.h>
#include <CredentialsManager.h>
#include <WiFi.h>

class WlanManager {
private:
    CredentialsManager* credManager;
    void createAdHocAp();
    bool connectToWlan(const char* ssid, const char* password);
public:
    WlanManager(CredentialsManager* credManager);
    ~WlanManager();

    void start();
};

WlanManager::WlanManager(CredentialsManager* credManager) {
    this->credManager = credManager;
}

WlanManager::~WlanManager() {
}

void WlanManager::start() {
    String ssid = credManager->readFile(SSID_FILE);
    String password = credManager->readFile(PASSWORD);

    if (ssid == "" && password == "") {
        createAdHocAp();
    } else {
        if (!connectToWlan(ssid.c_str(), password.c_str())) {
            createAdHocAp();
        }
    }

}

bool WlanManager::connectToWlan(const char* ssid, const char* password) {
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    
    Serial.printf("Connecting to %s with pass %s\n", ssid, password);

    WiFi.begin(ssid, password);

  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= 15000) {
      Serial.println("Failed to connect.");
      return false;
    }
  } 
  Serial.printf("\n\nConnected to wifi at: %s\n\n", WiFi.localIP().toString());
  return true;
}

void WlanManager::createAdHocAp() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32-ADHOC");
    IPAddress address = WiFi.softAPIP();

    Serial.printf("Created AP under: %s", address.toString());
}

#endif