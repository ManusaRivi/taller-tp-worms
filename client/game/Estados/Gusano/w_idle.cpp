#include "w_idle.h"

using namespace SDL2pp;

WIdle::WIdle(bool& facing_right, float& worm_angle){
    this->texture_name = "wwalk";
    this->frames = 1;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
}