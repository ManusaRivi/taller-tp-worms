#ifndef ARMA_H
#define ARMA_H

#include "../proyectiles/projectile.h"

#define BASELINE_POWER 0.5f
#define MAX_POWER 2.0f
#define POWER_PER_CHARGE 0.0375f
#define MAX_CHARGE 40

class Arma
{
protected:
    bool cargando;
    Armas tipo;
public:
    Arma() {};
    virtual void iniciarCarga() = 0;
    virtual void cargar() = 0;
    bool estaCargando() {
        return cargando;
    }
    Armas obtenerTipo() {
        return tipo;
    }
    virtual void Shoot(std::vector<Projectile*>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) = 0;
    virtual ~Arma() {}
};

#endif
