#include "dinamita.h"

Dinamita::Dinamita(b2World& world, int ammo, int dmg, int radius) : world(world), max_ammo(ammo), ammo(ammo), dmg(dmg), radius(radius) { tipo = Armas::DINAMITA; }

void Dinamita::iniciarCarga() {}

void Dinamita::cargar() {}

bool Dinamita::estaCargando() { return false; }

void Dinamita::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    if (ammo == 0) return;
    --ammo;
    std::shared_ptr<Grenade> grenade = std::make_shared<Grenade>(world, ProjectileType::DYNAMITE,
                                                                entity_id++, x_pos, y_pos, dmg, radius,
                                                                0, angle, DYNAMITE_IMPULSE, 0, seconds);
    grenade->sounds.push(SoundTypes::FUSE);
    projectiles.push_back(grenade);
}

int Dinamita::get_ammo(){
    return this->ammo;
}

int Dinamita::get_carga() {
    return 0;
}

void Dinamita::reload() {
    this->ammo = this->max_ammo;
}
