#ifndef CREDENTIALS_MANAGER_H
#define CREDENTIALS_MANAGER_H

#include <Arduino.h>
#include <SPIFFS.h>

static const char* SSID_FILE = "/ssid.txt";
static const char* PASSWORD = "/password.txt";
static const char* IPADDR = "/ipaddr.txt";
static const char* GATEWAY = "/gateway.txt";

class CredentialsManager
{
private:
    
public:
    CredentialsManager();
    ~CredentialsManager();
    String readFile(const char* filename);
    void writeFile(const char* filename, char* content);
};

CredentialsManager::CredentialsManager() {
    SPIFFS.begin(true);
}

CredentialsManager::~CredentialsManager() {
}

String CredentialsManager::readFile(const char* filename) {
    fs::File file = SPIFFS.open(filename, "r");
    if (!file) {
        return "";
    }

    String retVal;

    while  (file.available()) {
        String content = file.readString();
        retVal += content;
    }
    file.close();
    return retVal;
}

void CredentialsManager::writeFile(const char* filename, char* content) {
    fs::File file = SPIFFS.open(filename, "w", true);
    if(!file) {
        Serial.printf("Cannot write to file %s", filename);
        return;
    }

    if (!file.print(content)) {
        Serial.printf("Cannot write to file %s", filename);
        file.close();
        return;
    }
    file.close();
}

#endif