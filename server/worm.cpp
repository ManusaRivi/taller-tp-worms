#include "worm.h"

Worm::Worm(std::vector<float> position, int dir, int status): 
            position(position), dir(dir), status(status) {}



std::vector<float> Worm::get_position(){
    return position;
}