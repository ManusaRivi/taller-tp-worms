#ifndef BANANA_H
#define BANANA_H

#include "granada_arma.h"
#include "../proyectiles/grenade.h"

#define BANANA_RESTITUTION 0.8f

class Banana : public GranadaArma {
private:
    b2World& world;
    int ammo;
    const int dmg;
    const int radius;
    bool cargando;
    int nivel_carga;
public:
    Banana(b2World& world, int ammo, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual bool estaCargando() override;
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    int get_ammo() override;
    int get_carga() override;
    virtual ~Banana() {}
};

#endif
