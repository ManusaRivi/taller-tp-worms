#ifndef W_DYN_AIMING_H
#define W_DYN_AIMING_H

#include "worm_state.h"

class WDynAiming: public WormState {
    public:
    WDynAiming(bool& facing_right, float& worm_angle);
};

#endif