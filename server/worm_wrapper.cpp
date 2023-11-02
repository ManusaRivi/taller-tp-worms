#include "worm_wrapper.h"

WormWrapper::WormWrapper(std::vector<float> position, int dir, int status): 
            position(position), dir(dir), status(status) {}

std::vector<float> WormWrapper::get_position(){
    return position;
}
