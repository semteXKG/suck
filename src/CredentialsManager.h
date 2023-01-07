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


#endif