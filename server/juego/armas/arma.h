#ifndef ARMA_H
#define ARMA_H

#include "../proyectiles/projectile.h"
#include "../../common/armas.h"
#include <memory>

#define BASELINE_POWER 0.2f
#define POWER_PER_CHARGE 0.015f
#define MAX_CHARGE 40

class Arma
{
protected:
    Armas tipo;
public:
    Arma() {};
    virtual void iniciarCarga() = 0;
    virtual void cargar() = 0;
    virtual bool estaCargando() = 0;
    virtual int get_ammo() = 0;
    virtual int get_carga() = 0;
    virtual void reload() = 0;
    Armas obtenerTipo() {
        return tipo;
    }
    virtual void Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) = 0;
    virtual ~Arma() {}
};

#endif
