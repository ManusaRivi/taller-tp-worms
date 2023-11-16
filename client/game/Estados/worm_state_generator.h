#ifndef WORM_STATE_GENERATOR_H
#define WORM_STATE_GENERATOR_H

#include <memory>
#include "Gusano/worm_state.h"
#include "Gusano/w_idle.h"
#include "Gusano/w_walk.h"
#include "Gusano/w_aiming.h"

#define WORM_STATE_IDLE 0
#define WORM_STATE_WALKING 1

#define WORM_STATE_BAZOOKA_AIMING 5
#define WORM_STATE_HOLY_GRANADE_AIMING 12
#define WORM_STATE_GRANADE_AIMING 14
#define WORM_STATE_BANANA_AIMING 16
#define WORM_STATE_RED_GRANADE_AIMING 18


class WormStateGenerator {
    public:
/*
 * Devuelve el estado con el codigo pasado por parametro
 * Descripcion de parametros:
 * `status_code`: Codigo de estado recibido por server.
 * `facing_right`: True si el gusano mira a la derecha, False en caso contrario.
 * `worm_angle`: Angulo del gusano (cambia si se para en una pendiente inclinada). 0 si no se especifica.
 * `shot_angle`: Angulo de disparo (para estados con armas). 0 si no se especifica.
 */
    static std::unique_ptr<WormState> get_state_with_code(int status_code,
                                                            bool facing_right,
                                                            float worm_angle = 0,
                                                            float shot_angle = 0);
};

#endif