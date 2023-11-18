#ifndef MAPA_H
#define MAPA_H

#include "../../libs/box2d/include/box2d/box2d.h"

#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>

#include "./game_config.h"
#include "../worm_wrapper.h"
#include "./worm.h"
#include "./viga.h"
#include "./ground_contact_listener.h"

// Copyright (c) 2019 Erin Catto

enum collisionCategories{
    BOUNDARY = 0x0001,
    WORM = 0x0002,
};

class Mapa {
private:
    b2World world;
    GroundContactListener contactListener;

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    std::vector<Viga*> vigas;
    std::vector<Worm*> worms;

    std::string nombre;

public:
    explicit Mapa(std::string map_filepath);
    void Load_Map_File(std::string filepath);
    void Step();
    /*
    * Setea la velocidad del gusano dado por idx, que es el
    * indice en el vector gusanos del gusano a mover.
    * Si dir es 0, se mueve a la derecha. Si es 1, a la izquierda.
    * */
    void MoveWorm(int idx, int dir);
    /*
    * Setea la velocidad en x del gusano cuyo indice es idx a 0.
    * Mantiene la velocidad en y, para que si esta cayendo y se detiene,
    * siga cayendo con la misma velocidad hacia abajo.
    * */
    void StopWorm(int idx);
    void JumpWormForward(int idx);
    void JumpWormBackward(int idx);

    std::string GetName();

    WormWrapper devolver_gusano(int idx);
    std::vector<std::vector<float>> get_vigas();
    uint16_t gusanos_totales();

    std::vector<WormWrapper> get_gusanos();

    void cambiar_arma(uint32_t id, uint8_t tipo);

    void apuntar_para(uint32_t id,int);
    // std::vector<float> get_size();

    void detener_worm(uint32_t id);

    void detener_angulo(uint32_t id);

    ~Mapa();
};

#endif
