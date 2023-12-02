#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "arma.h"

class Teleporter : public Arma {
public:
    Teleporter() { tipo = Armas::TELETRANSPORTACION; }
    virtual void iniciarCarga() override {}
    virtual void cargar() override {}
    virtual bool estaCargando() override { return false; }
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) override {}
    virtual int get_ammo(){
        return 1;
    }
    virtual int get_carga(){
        return 0;
    }
};


#endif
