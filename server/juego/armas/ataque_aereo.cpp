#include "ataque_aereo.h"

AtaqueAereo::AtaqueAereo(b2World& world, int rocket_num, int ammo, int dmg, int radius) :
        world(world), rocket_num(rocket_num), ammo(ammo), dmg(dmg), radius(radius) 
{
    tipo = Armas::ATAQUE_AEREO;
}

void AtaqueAereo::iniciarCarga() {}

void AtaqueAereo::cargar() {}

void AtaqueAereo::Shoot(std::vector<Projectile*>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    for (auto i = 0; i < rocket_num; ++i) {
        Rocket* rocket = new Rocket (world, ProjectileType::AIR_MISSILE, x_pos, y_pos + ROCKET_ALTITUDE + ROCKET_GAP * i, angle, DOWNWARD_IMPULSE, dmg, radius, 0);
        rocket->insertar_id(entity_id);
        projectiles.push_back(rocket);
        entity_id++;
    }
}
