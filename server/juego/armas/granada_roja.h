#ifndef GRANADA_ROJA_H
#define GRANADA_ROJA_H

#include "granada_arma.h"

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
    virtual void Shoot(std::vector<Projectile*>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual ~GranadaRoja() {}
};

#endif
