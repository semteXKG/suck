#ifndef DUST_TRACKER_H
#include <Arduino.h>
#include <SdsDustSensor.h>
#include <State.h>

class DustTracker
{
private:
    SdsDustSensor* dustSensor;
    State* state;
    long lastUpdate = 0;
public:
    DustTracker(State* state);
    ~DustTracker();
    void onTick();
};

DustTracker::DustTracker(State* state) {
  dustSensor = new SdsDustSensor(Serial2);
  dustSensor->begin();
  this->state = state;
  Serial.println(dustSensor->queryFirmwareVersion().toString()); 
  Serial.println(dustSensor->setQueryReportingMode().toString());
}

DustTracker::~DustTracker() {
}

void DustTracker::onTick() {
    if(millis() - lastUpdate > 1000000) {
        PmResult result = dustSensor->queryPm();
        Serial.printf("PM2.5: %f, PM10: %f\n\n", result.pm25, result.pm10);
        state->airQuality.pm10 = result.pm10;
        state->airQuality.pm2_5 = result.pm25;
        lastUpdate = millis();
    }
}

#endif