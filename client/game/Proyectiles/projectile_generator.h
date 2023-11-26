#ifndef PROJECTILE_GENERATOR_H
#define PROJECTILE_GENERATOR_H

#include "../comunicacion/projectile.h"
#include "../../../common/projectile_types.h"
#include "fragment.h"
#include "dynamite.h"

class ProjectileGenerator {
    public:
/*
 * Devuelve el proyectil con el codigo pasado por parametro
 * Descripcion de parametros:
 * `proy_code`: Codigo de proyectil recibido por server.
 * `pos_x`: Posicion en x
 * `pos_y`: Posicion en y
 * `angle`: Angulo (angulo=0 => mira a derecha)
 */
    static std::unique_ptr<ProjectileClient> get_proyectile_with_code(int proy_type,
                                                            float& pos_x,
                                                            float& pos_y,
                                                            float& angle,
                                                            uint32_t id);
};

#endif