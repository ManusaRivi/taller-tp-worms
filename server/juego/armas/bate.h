#ifndef BATE_H
#define BATE_H

#include "arma.h"
#include "../worm.h"
#include "../worm_query.h"

#define HITBOX_OFFSET 1.5f
#define HITBOX_HALF_SIDE 0.75f

#define IMPULSE 3.5f

class Bate : public Arma {
private:
    b2World& world;
    const int dmg;
public:
    Bate(b2World& world, int dmg);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
};

#endif
