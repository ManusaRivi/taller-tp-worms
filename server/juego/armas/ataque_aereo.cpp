#include "ataque_aereo.h"

AtaqueAereo::AtaqueAereo(b2World& world, int rocket_num, int ammo, int dmg, int radius) :
        world(world), rocket_num(rocket_num), max_ammo(ammo), ammo(ammo), dmg(dmg), radius(radius) 
{
    tipo = Armas::ATAQUE_AEREO;
}

void AtaqueAereo::iniciarCarga() {}

void AtaqueAereo::cargar() {}

bool AtaqueAereo::estaCargando() { return false; }

void AtaqueAereo::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    if (this->ammo == 0) return;
    --this->ammo;
    for (auto i = 0; i < rocket_num; ++i) {
        projectiles.push_back(std::make_shared<Rocket>(world, ProjectileType::AIR_MISSILE, entity_id++,
                                                        x_pos, y_pos + ROCKET_ALTITUDE + (ROCKET_GAP * i),
                                                        dmg, radius, 0, angle, DOWNWARD_IMPULSE));
    }
}

int AtaqueAereo::get_ammo(){
    return this->ammo;
}
int AtaqueAereo::get_carga() {
    return 0;
}

void AtaqueAereo::reload() {
    this->ammo = this->max_ammo;
}
