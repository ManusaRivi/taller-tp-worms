#ifndef MORTERO_H
#define MORTERO_H

#include "arma.h"
#include "../game_config.h"
#include "../proyectiles/rocket.h"
#include "../../box2d/include/box2d/box2d.h"

class Mortero : public Arma {
private:
    b2World& world;
    const int dmg; // dmg en epicentro
    const int radius; // int mts
    int nivel_carga;
public:
    Mortero(b2World& world, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
    virtual ~Mortero() {}
};

#endif
