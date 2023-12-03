#ifndef GRANADA_ROJA_H
#define GRANADA_ROJA_H

#include "granada_arma.h"
#include "../proyectiles/grenade.h"

class GranadaRoja : public GranadaArma {
private:
    b2World& world;
    const int max_ammo;
    int ammo;
    const int fragments;
    const int dmg;
    const int radius;
    bool cargando;
    int nivel_carga;
public:
    GranadaRoja(b2World& world, int ammo, int fragments, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual bool estaCargando() override;
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual int get_ammo() override;
    virtual int get_carga() override;
    virtual void reload() override;
    virtual ~GranadaRoja() {}
};

#endif
