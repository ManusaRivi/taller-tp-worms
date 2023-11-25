#include "grave.h"

using namespace SDL2pp;

Grave::Grave(bool& facing_right, float& worm_angle){
    this->texture_name = "Grave";
    this->frames = 16;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->finished = true;
}
