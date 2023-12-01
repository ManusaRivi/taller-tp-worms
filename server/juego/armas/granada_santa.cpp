#include "granada_santa.h"

GranadaSanta::GranadaSanta(b2World& world, int ammo, int dmg, int radius) :
                        world(world), ammo(ammo), dmg(dmg), radius(radius), nivel_carga(0)
{
    cargando = false;
    tipo = Armas::GRANADA_SANTA;
}

void GranadaSanta::iniciarCarga() {
    cargando = true;
}

void GranadaSanta::cargar() {
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

bool GranadaSanta::estaCargando() { return cargando; }

void GranadaSanta::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    if (ammo == 0) return;
    --ammo;
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    nivel_carga = 0;
    cargando = false;
    projectiles.push_back(std::make_shared<Grenade>(world, ProjectileType::HOLY_GRENADE,
                                                    entity_id++, x_pos, y_pos, dmg, radius,
                                                    0, angle, power, GRENADE_BASE_RESTITUTION, seconds));
}
