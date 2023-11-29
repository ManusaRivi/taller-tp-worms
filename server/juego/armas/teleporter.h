#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "arma.h"

class Teleporter : public Arma {
public:
    Teleporter() { tipo = Armas::TELETRANSPORTACION; }
    virtual void iniciarCarga() override {}
    virtual void cargar() override {}
    virtual bool estaCargando() override {}
    virtual void Shoot(std::vector<Projectile*>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override {}
};

#endif
