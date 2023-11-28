#ifndef W_TELEPORT_AIMING_H
#define W_TELEPORT_AIMING_H

#include "worm_state.h"

class WTeleportAiming: public WormState {
    public:
    WTeleportAiming(bool& facing_right, float& worm_angle);
};

#endif