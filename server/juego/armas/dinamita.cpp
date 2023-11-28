#include "dinamita.h"

Dinamita::Dinamita(b2World& world, int ammo, int dmg, int radius) : world(world), dmg(dmg), radius(radius) { tipo = Armas::DINAMITA; }

void Dinamita::iniciarCarga() {}

void Dinamita::cargar() {}

Projectile* Dinamita::Shoot(float x_pos, float y_pos, float angle) {
    if (ammo == 0) return NULL;
    --ammo;
    Grenade* grenade = new Grenade (world, ProjectileType::DYNAMITE, x_pos, y_pos, angle, DYNAMITE_IMPULSE, dmg, radius, 0, 0, seconds);
    grenade->sounds.push(SoundTypes::FUSE);
    return grenade;
}
