#ifndef COLECCION_ARMAS_H
#define COLECCION_ARMAS_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../game_config.h"
#include "arma.h"
#include "bazooka.h"
#include "mortero.h"
#include "granada_verde.h"
#include "granada_roja.h"
#include "banana.h"
#include "granada_santa.h"
#include "dinamita.h"
#include "bate.h"
#include "ataque_aereo.h"
#include "teleporter.h"

#include <map>
#include <memory>
#include "../../../common/armas.h"


class ColeccionArmas
{
private:
    b2World& world;
    std::map<int, std::shared_ptr<Arma>> armas;
public:
    ColeccionArmas(b2World& world);
    std::shared_ptr<Arma> SeleccionarArma(uint8_t id_arma);
    std::vector<std::pair<int,int>> obtener_municion_armas();
    void recargar_armas();
    ~ColeccionArmas();
};

#endif
