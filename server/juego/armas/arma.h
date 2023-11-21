#ifndef ARMA_H
#define ARMA_H

#include "../proyectiles/projectile.h"

class Arma
{
public:
    Arma() {};
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle, float power) = 0;
    virtual ~Arma() {}
};

#endif
