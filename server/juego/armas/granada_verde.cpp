#include "granada_verde.h"

GranadaVerde::GranadaVerde(b2World& world, int dmg, int radius) : world(world), dmg(dmg), radius(radius), nivel_carga(0) {
    cargando = false;
}

bool GranadaVerde::isGrenade() {
    return true;
}

bool GranadaVerde::isRocket() {
    return false;
}

void GranadaVerde::iniciarCarga() {
    cargando = true;
}

void GranadaVerde::cargar() {
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

Projectile* GranadaVerde::Shoot(float x_pos, float y_pos, float angle) {
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    nivel_carga = 0;
    cargando = false;
    return new Grenade (world, ProjectileType::GREEN_GRANADE, x_pos, y_pos, angle, power, dmg, radius, 0, seconds);
}
