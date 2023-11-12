#ifndef W_WALK_H
#define W_WALK_H

#include "worm_state.h"

class WWalk: public WormState {
    public:
    WWalk(bool& facing_right, float& worm_angle);
};

#endif