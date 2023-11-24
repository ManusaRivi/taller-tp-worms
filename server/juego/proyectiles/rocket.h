#ifndef ROCKET_H
#define ROCKET_H

#include "../../../../libs/box2d/include/box2d/box2d.h"
#include "../worm_query.h"
#include "./projectile.h"

#define ROCKET_POSITION_OFFSET 2.0

#define ROCKET_LENGTH 0.5f
#define ROCKET_WIDTH 0.5f

#define ROCKET_DENSITY 0.05

#define ROCKET_BLAST_POWER 1.0

class Rocket : public Projectile
{
private:
    b2World& world;
    int dmg;
    int radius;
public:
    Rocket(b2World& world, float x_pos, float y_pos, float angle, float power, int dmg, int radius, int fragments);
    virtual ProjectileType getType() override;
    virtual void explotar() override;
};

#endif
