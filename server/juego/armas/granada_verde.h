#ifndef GRANADA_VERDE_H
#define GRANADA_VERDE_H

#include "granada_arma.h"
#include "../proyectiles/grenade.h"

class GranadaVerde : public GranadaArma {
private:
    b2World& world;
    const int dmg;
    const int radius;
    bool cargando;
    int nivel_carga;
public:
    GranadaVerde(b2World& world, int dmg, int radius);
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual bool estaCargando() override;
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override;
    virtual ~GranadaVerde() {}
};

#endif
