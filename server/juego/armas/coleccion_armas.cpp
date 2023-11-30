#include "./coleccion_armas.h"

ColeccionArmas::ColeccionArmas(b2World& world) : world(world)
{
    GameConfig& config = GameConfig::getInstance();
    armas[Armas::BAZOOKA] = std::make_shared<Bazooka>(world, config.bazooka_dmg, config.bazooka_radius);
    armas[Armas::MORTERO] = std::make_shared<Mortero>(world, config.mortar_ammo, config.frag_amount ,config.mortar_dmg, config.mortar_radius);
    armas[Armas::GRANADA_VERDE] = std::make_shared<GranadaVerde>(world, config.green_grenade_dmg, config.green_grenade_radius);
    armas[Armas::GRANADA_ROJA] = std::make_shared<GranadaRoja>(world, config.red_grenade_ammo, config.frag_amount, config.red_grenade_dmg, config.red_grenade_radius);
    armas[Armas::BANANA] = std::make_shared<Banana>(world, config.banana_ammo, config.banana_dmg, config.banana_radius);
    armas[Armas::GRANADA_SANTA] = std::make_shared<GranadaSanta>(world, config.holy_grenade_ammo, config.holy_grenade_dmg, config.holy_grenade_radius);
    armas[Armas::DINAMITA] = std::make_shared<Dinamita>(world, config.dynamite_ammo, config.dynamite_dmg, config.dynamite_radius);
    armas[Armas::BATE] = std::make_shared<Bate>(world, config.bat_dmg);
    armas[Armas::ATAQUE_AEREO] = std::make_shared<AtaqueAereo>(world, config.airstrike_rockets, config.airstrike_ammo, config.airstrike_dmg, config.airstrike_radius);
    armas[Armas::TELETRANSPORTACION] = std::make_shared<Teleporter>();
}

std::shared_ptr<Arma> ColeccionArmas::SeleccionarArma(uint8_t id_arma)
{
    return armas[id_arma];
}

ColeccionArmas::~ColeccionArmas()
{
    armas.clear();
}
