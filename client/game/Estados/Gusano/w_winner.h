#ifndef W_WINNER_H
#define W_WINNER_H

#include "worm_state.h"
class WWinner: public WormState {
    public:
    WWinner(bool& facing_right, float& worm_angle);
};

#endif