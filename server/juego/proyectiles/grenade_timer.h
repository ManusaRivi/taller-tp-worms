#ifndef GRENADE_TIMER_H
#define GRENADE_TIMER_H

#define TICKS_PER_SECOND 30

class GrenadeTimer {
private:
    int seconds;
    int ticks;
public:
    GrenadeTimer(int seconds) : seconds(seconds) {}
    bool advance_time() {
        ++ticks;
        if (ticks == (seconds * TICKS_PER_SECOND)) return true;
        return false;
    }
};

#endif
