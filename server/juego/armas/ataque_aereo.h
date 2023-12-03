#ifndef ATAQUE_AEREO_H
#define ATAQUE_AEREO_H

#include "../proyectiles/rocket.h"
#include "arma.h"

#define ROCKET_ALTITUDE 100.0f
#define ROCKET_GAP 5.0f
#define DOWNWARD_IMPULSE 0.5f

class AtaqueAereo : public Arma {
private:
    b2World& world;
    const int rocket_num;
    const int max_ammo;
    int ammo;
    const int dmg;
    const int radius;
public:
    AtaqueAereo(b2World& world, int rocket_num, int ammo, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual bool estaCargando() override;
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual int get_ammo() override;
    virtual int get_carga() override;
    virtual void reload() override;
};

#endif
