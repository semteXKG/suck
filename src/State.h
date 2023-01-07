#ifndef STATE_H
#define STATE_H

#include <OpMode.h>

static const int OFF_STATE_TRESHOLD = 200;

struct LightSensorReadings
{
    int sensorLow;
    int sensorMid;
    int sensorHigh;

    double sensorLowAsPercent() {
        return sensorAsPercent(sensorLow);
    }

    double sensorMidAsPercent() {
        return sensorAsPercent(sensorMid);
    }

    double sensorHighAsPercent() {
        return sensorAsPercent(sensorHigh);
    }


    double sensorAsPercent(int measurement) {
        return ((4096 - measurement) / 4096.0) * 100.0;
    }
};

struct AirQualityReadings {
    double pm0_5 = 20.2;
    double pm2_5 = 4.2;
    double pm10 = 1.3;
};


class State {
private:
    bool stateChangeExpected = false;;
    bool inUserMode = false;
    OpMode opMode = OFF;
    long offStateSince = -1;
public:
    LightSensorReadings lightSensor;
    AirQualityReadings airQuality;
    State();
    ~State();
    OpMode getOpMode();
    void setOpMode(OpMode opMode);
    bool isInUserMode();
    void changeToUserMode();
};

#endif