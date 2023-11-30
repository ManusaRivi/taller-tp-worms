#include "dinamita.h"

Dinamita::Dinamita(b2World& world, int ammo, int dmg, int radius) : world(world), dmg(dmg), radius(radius) { tipo = Armas::DINAMITA; }

void Dinamita::iniciarCarga() {}

void Dinamita::cargar() {}

bool Dinamita::estaCargando() { return false; }

void Dinamita::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    if (ammo == 0) return;
    --ammo;
    std::shared_ptr<Grenade> grenade = std::make_shared<Grenade>(world, ProjectileType::DYNAMITE, x_pos, y_pos, angle, DYNAMITE_IMPULSE, dmg, radius, 0, 0, seconds);
    grenade->sounds.push(SoundTypes::FUSE);
    grenade->insertar_id(entity_id);
    projectiles.push_back(grenade);
    entity_id++;
}
