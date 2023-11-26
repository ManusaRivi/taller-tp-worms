#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../proyectiles/rocket.h"
#include "./arma.h"

class Bazooka : public Arma
{
private:
    b2World& world;
    const int dmg; // dmg en epicentro
    const int radius; // int mts
    int nivel_carga;
public:
    Bazooka(b2World& world, int dmg, int radius);
    virtual bool isGrenade() override;
    virtual bool isRocket() override;
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
    virtual ~Bazooka() {}
};

#endif
