#include "w_fall.h"

WFall::WFall(bool& facing_right, float& worm_angle){
    this->texture_name = "WFall";
    this->frames = 2;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->finished = true;
}