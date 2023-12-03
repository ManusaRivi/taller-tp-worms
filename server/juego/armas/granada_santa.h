#ifndef GRANADA_SANTA_H
#define GRANADA_SANTA_H

#include "granada_arma.h"
#include "../proyectiles/grenade.h"

class GranadaSanta : public GranadaArma {
private:
    b2World& world;
    const int max_ammo;
    int ammo;
    const int dmg;
    const int radius;
    bool cargando;
    int nivel_carga;
public:
    GranadaSanta(b2World& world, int ammo, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual bool estaCargando() override;
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual int get_ammo() override;
    virtual int get_carga() override;
    virtual void reload() override;
    virtual ~GranadaSanta() {}
};

#endif
