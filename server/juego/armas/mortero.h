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
    bool cargando;
    int nivel_carga;
public:
    Mortero(b2World& world, int ammo, int fragments, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual bool estaCargando() override;
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual int get_ammo() override;
    virtual int get_carga() override;
    virtual ~Mortero() {}
};

#endif
