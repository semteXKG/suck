#ifndef CONSTANTS_H
#define CONSTANTS_H

static const char *OpModeStr[] = { "LOCAL", "SENSOR", "API" };
static const char *MachineStatusStr[] = { "OFF", "ON_LOW", "ON_HIGH" };

enum OpMode {
    LOCAL,
    SENSOR,
    API
};

enum MachineStatus {
    OFF,
    ON_LOW,
    ON_HIGH
};

#endif