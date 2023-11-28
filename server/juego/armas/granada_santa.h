#ifndef GRANADA_SANTA_H
#define GRANADA_SANTA_H

#include "granada_arma.h"

class GranadaSanta : public GranadaArma {
private:
    b2World& world;
    int ammo;
    const int dmg;
    const int radius;
    int nivel_carga;
public:
    GranadaSanta(b2World& world, int ammo, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual void Shoot(std::vector<Projectile*>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual ~GranadaSanta() {}
};

#endif
