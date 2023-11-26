#ifndef GRENADE_H
#define GRENADE_H

#include "projectile.h"
#include "grenade_timer.h"
#include "../worm.h"

#define GRENADE_POSITION_OFFSET 2.0

#define GRENADE_LENGTH 0.5f
#define GRENADE_WIDTH 0.5f

#define GRENADE_DENSITY 0.05f
#define GRENADE_RESTITUTION 0.5f

#define GRENADE_BLAST_POWER 1.0

class Grenade : public Projectile {
private:
    b2World& world;
    GrenadeTimer timer;
public:
    Grenade(b2World& world, ProjectileType type, float x_pos, float y_pos,
            float angle, float power, int dmg, int radius, int fragments, int seconds);
    void advance_time();
    void bounce();
    virtual bool isGrenade() override;
    virtual void explotar() override;
};

#endif
