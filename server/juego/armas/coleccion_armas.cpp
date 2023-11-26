#include "./coleccion_armas.h"

ColeccionArmas::ColeccionArmas(b2World& world) : world(world)
{
    GameConfig& config = GameConfig::getInstance();
    armas[Armas::BAZOOKA] = new Bazooka(world, config.bazooka_dmg, config.bazooka_radius);
    armas[Armas::MORTERO] = new Mortero(world, config.mortar_dmg, config.mortar_radius);
    armas[Armas::GRANADA_VERDE] = new GranadaVerde(world, config.green_grenade_dmg, config.green_grenade_radius);
    armas[Armas::GRANADA_ROJA] = new GranadaRoja(world, config.red_grenade_ammo, config.frag_amount, config.red_grenade_dmg, config.red_grenade_radius);
}

Arma* ColeccionArmas::SeleccionarArma(uint8_t id_arma)
{
    return armas[id_arma];
}

ColeccionArmas::~ColeccionArmas()
{
    for (auto arma : armas) {
        delete arma.second;
    }
}
