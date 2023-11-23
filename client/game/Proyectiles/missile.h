#ifndef MISSILE_H
#define MISSILE_H

#include "../comunicacion/projectile.h"

class Missile: public Projectile {
    public:
    Missile(float& pos_x, float& pos_y, float& angle);
};

#endif