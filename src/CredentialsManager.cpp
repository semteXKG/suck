#include <CredentialsManager.h>

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