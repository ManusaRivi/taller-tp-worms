#include "missile.h"

Missile::Missile(float& pos_x, float& pos_y, float& angle) {
    this->texture_name = "Missile";
    this->frames = 32;
    this->_pos_x = pos_x;
    this->_pos_y = pos_y;
    this->_angle = angle;
}