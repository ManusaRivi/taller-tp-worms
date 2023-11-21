#ifndef MAPA_H
#define MAPA_H

#include "../../libs/box2d/include/box2d/box2d.h"

#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>

#include "./game_config.h"
#include "../worm_wrapper.h"
#include "../projectile_wrapper.h"
#include "./worm.h"
#include "./beam.h"
#include "./proyectiles/projectile.h"
#include "./contact_listener.h"
#include "turn_manager.h"

// Copyright (c) 2019 Erin Catto



class Mapa {
private:
    b2World world;
    ContactListener contactListener;

    const float timeStep = 1.0f / 30.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    std::vector<Beam*> vigas;
    std::vector<Worm*> worms;
    std::vector<Projectile*> projectiles;

    std::string nombre;
    TurnManager turnManager;

public:
    explicit Mapa(std::string map_filepath);
    void Load_Map_File(std::string filepath);
    void Step(int iteracion);
    /*
    * Setea la velocidad del gusano dado por idx, que es el
    * indice en el vector gusanos del gusano a mover.
    * Si dir es 0, se mueve a la derecha. Si es 1, a la izquierda.
    * */
    void MoveWorm(uint32_t idx, int dir);
    /*
    * Setea la velocidad en x del gusano cuyo indice es idx a 0.
    * Mantiene la velocidad en y, para que si esta cayendo y se detiene,
    * siga cayendo con la misma velocidad hacia abajo.
    * */
    void StopWorm(uint32_t idx);
    void JumpWormForward(uint32_t idx);
    void JumpWormBackward(uint32_t idx);

    std::string GetName();

    WormWrapper devolver_gusano(int idx);
    std::vector<std::vector<float>> get_vigas();
    uint16_t gusanos_totales();

    std::vector<WormWrapper> get_gusanos();

    std::vector<ProjectileWrapper> get_projectiles();

    void cambiar_arma(uint32_t id, uint8_t tipo);

    void apuntar_para(uint32_t id,int);
    // std::vector<float> get_size();

    void usar_arma(uint32_t idx);

    void detener_worm(uint32_t id);

    void detener_angulo(uint32_t id);

    std::map<uint32_t, std::vector<uint32_t>> repartir_ids(uint32_t cantidad_jugadores);

    uint32_t gusano_actual();

    void cambiar_direccion(uint32_t id,uint8_t dir);

    ~Mapa();
};

#endif
