#ifndef MAPA_H
#define MAPA_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include <vector>
#include "../worm_wrapper.h"
#include "./worm.h"

// Copyright (c) 2019 Erin Catto

#define MOVE_RIGHT 0
#define MOVE_LEFT 1

#define LONG_BEAM_LENGTH 3.0f
#define LONG_BEAM_HEIGHT 0.4f

#define WORM_WIDTH 0.15f
#define WORM_HEIGHT 0.4f

class Mapa {
private:
    b2World world;
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    std::vector<Worm*> worms;

    

public:
    Mapa();
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

    WormWrapper devolver_gusano(int idx);

    ~Mapa();
};

#endif
