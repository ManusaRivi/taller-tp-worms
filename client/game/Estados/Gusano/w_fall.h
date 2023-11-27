#ifndef W_FALL_H
#define W_FALL_H

#include "worm_state.h"

class WFall: public WormState {
    public:
    WFall(bool& facing_right, float& worm_angle);
};

#endif