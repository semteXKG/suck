#ifndef STATE_H
#define STATE_H

#include <OpMode.h>

static const int OFF_STATE_TRESHOLD = 200;

class State {
private:
    bool stateChangeExpected = false;;
    bool inUserMode = false;
    OpMode opMode = OFF;
    long offStateSince = -1;
public:
    State();
    ~State();
    OpMode getOpMode();
    void setOpMode(OpMode opMode);
    bool isInUserMode();
};

#endif