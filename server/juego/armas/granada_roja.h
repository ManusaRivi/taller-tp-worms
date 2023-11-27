#ifndef GRANADA_ROJA_H
#define GRANADA_ROJA_H

#include "granada_arma.h"
#include "../proyectiles/grenade.h"

class GranadaRoja : public GranadaArma {
private:
    b2World& world;
    int ammo;
    const int fragments;
    const int dmg;
    const int radius;
    int nivel_carga;
public:
    GranadaRoja(b2World& world, int ammo, int fragments, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
    virtual ~GranadaRoja() {}
};

#endif
