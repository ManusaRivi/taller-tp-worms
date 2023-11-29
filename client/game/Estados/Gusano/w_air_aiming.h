#ifndef W_AIR_AIMING_H
#define W_AIR_AIMING_H

#include "worm_state.h"

class WAirAiming: public WormState {
    public:
    WAirAiming(bool& facing_right, float& worm_angle);
};

#endif