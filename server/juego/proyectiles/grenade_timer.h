#ifndef GRENADE_TIMER_H
#define GRENADE_TIMER_H

#define TICKS_PER_SECOND 30

class GrenadeTimer {
private:
    int seconds;
    int ticks;
public:
    GrenadeTimer(int seconds) : seconds(seconds) {}
    bool is_about_to_explode() {
        return (ticks == (seconds * TICKS_PER_SECOND - 10));
    }
    bool advance_time() {
        ++ticks;
        return (ticks == (seconds * TICKS_PER_SECOND));
    }
};

#endif
