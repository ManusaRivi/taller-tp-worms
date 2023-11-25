#ifndef PROJECTILE_WRAPPER_H
#define PROJECTILE_WRAPPER_H

#include "../common/projectile_types.h"
#include <cstdint>

class ProjectileWrapper {
private:
    float x_pos;
    float y_pos;
    float angulo;
    ProjectileType tipo;
public:
    ProjectileWrapper(float x_pos, float y_pos, float angulo, ProjectileType tipo) :
            x_pos(x_pos), y_pos(y_pos), angulo(angulo), tipo(tipo) {}

    float get_x(){
        return this->x_pos;
    }

    float get_y(){
        return this->y_pos;
    }

    float get_angulo(){
        return this->angulo;
    }

    uint8_t get_tipo(){
        return this->tipo;
    }
};

#endif
