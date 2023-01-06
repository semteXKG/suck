#ifndef asdf
#define asdf

static const char *OpModeStr[] = { "UNTRACKED", "Off", "Low", "Mid", "High" };

enum OpMode {
    UNTRACKED,
    OFF,
    ON_LOW,
    ON_MID,
    ON_HIGH
};

#endif