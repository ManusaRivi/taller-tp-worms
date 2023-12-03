#include "granada_verde.h"

GranadaVerde::GranadaVerde(b2World& world, int dmg, int radius) : world(world), dmg(dmg), radius(radius), nivel_carga(0) {
    cargando = false;
    tipo = Armas::GRANADA_VERDE;
}

void GranadaVerde::iniciarCarga() {
    cargando = true;
}

void GranadaVerde::cargar() {
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

bool GranadaVerde::estaCargando() { return cargando; }

void GranadaVerde::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    nivel_carga = 0;
    cargando = false;
    projectiles.push_back(std::make_shared<Grenade>(world, ProjectileType::GREEN_GRENADE,
                                                    entity_id++, x_pos, y_pos, dmg, radius,
                                                    0, angle, power, GRENADE_BASE_RESTITUTION, seconds));
}

int GranadaVerde::get_ammo(){
    return 999;
}
int GranadaVerde::get_carga() {
    return this->nivel_carga;
}
