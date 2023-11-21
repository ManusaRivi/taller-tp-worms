#ifndef ROCKET_H
#define ROCKET_H

#include "../../../box2d/include/box2d/box2d.h"
#include "../collision_categories.h"
#include "../worm_query.h"
#include "./projectile.h"

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
    Rocket(b2World& world, float x_pos, float y_pos, float angle, float power, int dmg, int radius);
    virtual void explotar() override;
};

#endif
