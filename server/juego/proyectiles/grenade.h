#ifndef GRENADE_H
#define GRENADE_H

#include "projectile.h"
#include "grenade_timer.h"
#include "../worm.h"

#define GRENADE_POSITION_OFFSET 2.0

#define GRENADE_LENGTH 0.3f
#define GRENADE_WIDTH 0.3f

#define GRENADE_DENSITY 0.05f

#define GRENADE_BLAST_POWER 1.0

class Grenade : public Projectile {
private:
    GrenadeTimer timer;
public:
    Grenade(b2World& world, ProjectileType type, uint32_t id, float x_pos, float y_pos,
            int dmg, int radius, int fragments, float angle, float power, float restitution, int timer);
    void advance_time();
    void bounce();
    virtual bool isGrenade() override;
    virtual void explotar() override;
};

#endif
