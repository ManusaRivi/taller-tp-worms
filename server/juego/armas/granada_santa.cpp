#include "granada_santa.h"

GranadaSanta::GranadaSanta(b2World& world, int ammo, int dmg, int radius) :
                        world(world), ammo(ammo), dmg(dmg), radius(radius), nivel_carga(0)
{
    cargando = false;
}

void GranadaSanta::iniciarCarga() {
    cargando = true;
}

void GranadaSanta::cargar() {
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

Projectile* GranadaSanta::Shoot(float x_pos, float y_pos, float angle) {
    if (ammo == 0) return NULL;
    --ammo;
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    nivel_carga = 0;
    cargando = false;
    return new Grenade (world, ProjectileType::HOLY_GRANADE, x_pos, y_pos, angle, power, dmg, radius, 0, GRENADE_BASE_RESTITUTION, seconds);
}
