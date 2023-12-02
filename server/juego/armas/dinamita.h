#ifndef DINAMITA_H
#define DINAMITA_H

#include "granada_arma.h"
#include "../proyectiles/grenade.h"

#define DYNAMITE_IMPULSE 0.05f

class Dinamita : public GranadaArma
{
private:
    b2World& world;
    int ammo;
    const int dmg;
    const int radius;
public:
    Dinamita(b2World& world, int ammo, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual bool estaCargando() override;
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual int get_ammo() override;
    virtual int get_carga() override;
};

#endif
