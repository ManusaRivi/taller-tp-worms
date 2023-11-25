#ifndef GRAVE_H
#define GRAVE_H

#include "worm_state.h"

class Grave: public WormState {
    public:
    //Constructor
    Grave(bool& facing_right, float& worm_angle);
};

#endif