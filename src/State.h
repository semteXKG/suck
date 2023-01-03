#ifndef STATE
#define STATE

enum OP_MODE {
    OFF,
    ON_LOW,
    ON_MID,
    ON_HIGH
};

class State {
private:
    bool stateChangeExpected = false;;
    bool inUserMode = false;;
    OP_MODE opMode = OFF;
public:
    State();
    ~State();
};

State::State() {
    


}

State::~State()
{
}

#endif