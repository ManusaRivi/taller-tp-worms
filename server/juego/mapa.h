#ifndef MAPA_H
#define MAPA_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include <vector>
#include "../worm.h"

// Copyright (c) 2019 Erin Catto

#define MOVE_RIGHT 0
#define MOVE_LEFT 1

class Mapa {
private:
    b2World world;
    std::vector<b2Body *> gusanos;
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    int32 jumpSteps;

    int32 steps = 0; // para debuggear.

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
    void JumpWorm(int idx);

    Worm devolver_gusano(int idx);
};

#endif
