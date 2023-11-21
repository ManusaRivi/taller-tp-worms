#ifndef ROCKET_H
#define ROCKET_H

#include "../../../box2d/include/box2d/box2d.h"
#include "../collision_categories.h"
#include "../worm_query.h"
#include "./projectile.h"

#define ROCKET_LENGTH 0.3
#define ROCKET_WIDTH 0.15

#define ROCKET_DENSITY 0.2

#define ROCKET_BLAST_POWER 1.0

class Rocket : public Projectile
{
private:
    b2World& world;
    int dmg;
    int radius;
public:
    Rocket(b2World& world, float x_pos, float y_pos, float angle, int dmg, int radius);
    virtual void lanzar(float angle, float power) override;
    virtual void explotar() override;
};

#endif
