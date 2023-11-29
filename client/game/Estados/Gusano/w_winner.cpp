#include "w_winner.h"

using namespace SDL2pp;

WWinner::WWinner(bool& facing_right, float& worm_angle){
    this->texture_name = "WWinner";
    this->frames = 14;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->finished = true;
}