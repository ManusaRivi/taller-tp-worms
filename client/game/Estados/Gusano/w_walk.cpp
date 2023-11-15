#include "w_walk.h"

WWalk::WWalk(bool& facing_right, float& worm_angle){
    this->texture_name = "wwalk";
    this->frames = 15;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->is_finished = true;
}