#ifndef STATE_H
#define STATE_H

#include <Constants.h>

static const int OFF_STATE_TRESHOLD = 200;

struct AirQualityReadings {
    double pm0_5 = 20.2;
    double pm2_5 = 4.2;
    double pm10 = 1.3;
};


class State {
private:
    OpMode opMode = OpMode::LOCAL;
    MachineStatus status = MachineStatus::OFF;
    
public:
    AirQualityReadings airQuality;
    State();
    ~State();
    OpMode getOpMode();
    void setOpMode(OpMode opMode);
    MachineStatus getStatus();
    void setStatus(MachineStatus status);
    bool isInUserMode();
    void changeToUserMode();
};

#endif