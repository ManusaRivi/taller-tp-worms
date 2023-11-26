#ifndef GRANADA_VERDE_H
#define GRANADA_VERDE_H

#include "granada_arma.h"
#include "../proyectiles/grenade.h"

class GranadaVerde : public GranadaArma {
private:
    b2World& world;
    const int dmg;
    const int radius;
    int nivel_carga;
public:
    GranadaVerde(b2World& world, int dmg, int radius);
    virtual bool isGrenade() override;
    virtual bool isRocket() override;
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
    virtual ~GranadaVerde() {}
};

#endif
