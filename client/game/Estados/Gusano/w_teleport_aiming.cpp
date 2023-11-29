#include "w_teleport_aiming.h"

WTeleportAiming::WTeleportAiming(bool& facing_right, float& worm_angle) {
    this->texture_name = "WAimTel";
    this->frames = 1;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->finished = true;
}