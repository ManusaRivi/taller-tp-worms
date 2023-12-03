#ifndef ROCKET_H
#define ROCKET_H

#include "../../../../libs/box2d/include/box2d/box2d.h"
#include "../worm_query.h"
#include "./projectile.h"

#define ROCKET_POSITION_OFFSET 2.0

#define ROCKET_LENGTH 0.3f
#define ROCKET_WIDTH 0.3f

#define ROCKET_DENSITY 0.05

#define ROCKET_BLAST_POWER 1.0

class Rocket : public Projectile
{
public:
    Rocket(b2World& world, ProjectileType type, uint32_t id, float x_pos, float y_pos, int dmg, int radius, int fragments, float angle, float power);
    virtual bool isGrenade() override;
    virtual void explotar() override;
};

#endif
