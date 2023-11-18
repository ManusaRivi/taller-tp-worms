#ifndef COLECCION_ARMAS_H
#define COLECCION_ARMAS_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../game_config.h"
#include "./arma.h"
#include "bazooka.h"

#include <map>
#include <memory>

enum Armas {
    BAZOOKA,
    GRANADA,
    DINAMITA,
    BATE
};

class ColeccionArmas
{
private:
    b2World& world;
    std::map<int, Arma*> armas;
public:
    ColeccionArmas(b2World& world);
    Arma* SeleccionarArma(Armas arma);
    ~ColeccionArmas();
};

#endif
