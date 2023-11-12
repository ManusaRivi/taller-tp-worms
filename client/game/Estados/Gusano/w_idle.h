#ifndef W_IDLE_H
#define W_IDLE_H

#include "worm_state.h"
// Gusano Quieto
class WIdle: public WormState {
    public:
    //Constructor
    WIdle(bool& facing_right, float& worm_angle);
};

#endif