#ifndef BANANA_H
#define BANANA_H

#include "granada_arma.h"

#define BANANA_RESTITUTION 0.8f

class Banana : public GranadaArma {
private:
    b2World& world;
    int ammo;
    const int dmg;
    const int radius;
    int nivel_carga;
public:
    Banana(b2World& world, int ammo, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
    virtual ~Banana() {}
};

#endif
