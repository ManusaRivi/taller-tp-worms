#ifndef MORTERO_H
#define MORTERO_H

#include "arma.h"
#include "../game_config.h"
#include "../proyectiles/rocket.h"
#include "../../../libs/box2d/include/box2d/box2d.h"

class Mortero : public Arma {
private:
    b2World& world;
    int ammo;
    const int fragments;
    const int dmg; // dmg en epicentro
    const int radius; // int mts
    int nivel_carga;
public:
    Mortero(b2World& world, int ammo, int fragments, int dmg, int radius);
    virtual bool isGrenade() override;
    virtual bool isRocket() override;
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
    virtual ~Mortero() {}
};

#endif
