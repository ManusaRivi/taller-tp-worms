#ifndef COLECCION_ARMAS_H
#define COLECCION_ARMAS_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../game_config.h"
#include "arma.h"
#include "bazooka.h"
#include "mortero.h"
#include "granada_verde.h"
#include "granada_roja.h"

#include <map>
#include <memory>


#define BAZOOKA_id 5
#define BASEBALL_id 6
#define TELEPORTACION_id 8
#define DINAMITA_id 9
#define ATAQUE_AEREO_id 11
#define GRANADA_SANTA_id 12
#define GRANADA_VERDE_id 14
#define BANANA_id 16
#define GRANADA_ROJA_id 18
#define MORTERO_id 20

enum Armas {
    BAZOOKA = BAZOOKA_id,
    MORTERO = MORTERO_id,
    GRANADA_VERDE = GRANADA_VERDE_id,
    GRANADA_ROJA = GRANADA_ROJA_id,
    DINAMITA = DINAMITA_id,
    BATE = BASEBALL_id
};


class ColeccionArmas
{
private:
    b2World& world;
    std::map<int, Arma*> armas;
public:
    ColeccionArmas(b2World& world);
    Arma* SeleccionarArma(uint8_t id_arma);
    ~ColeccionArmas();
};

#endif
