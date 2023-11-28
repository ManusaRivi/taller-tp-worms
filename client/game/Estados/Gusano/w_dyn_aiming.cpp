#include "w_dyn_aiming.h"

WDynAiming::WDynAiming(bool& facing_right, float& worm_angle) {
    this->texture_name = "WAimDyn";
    this->frames = 1;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->finished = true;
}