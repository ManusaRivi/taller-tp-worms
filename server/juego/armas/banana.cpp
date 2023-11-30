#include "banana.h"

Banana::Banana(b2World& world, int ammo, int dmg, int radius) : world(world), ammo(ammo), dmg(dmg), radius(radius), nivel_carga(0) {
    cargando = false;
    tipo = Armas::BANANA;
}

void Banana::iniciarCarga() {
    cargando = true;
}

void Banana::cargar() {
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

bool Banana::estaCargando() { return cargando; }

void Banana::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    if (ammo == 0) return;
    --ammo;
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    nivel_carga = 0;
    cargando = false;
    std::shared_ptr<Grenade> grenade = std::make_shared<Grenade>(world, ProjectileType::BANANA_GRENADE, x_pos, y_pos, angle, power, dmg, radius, 0, BANANA_RESTITUTION, seconds);
    grenade->insertar_id(entity_id);
    projectiles.push_back(grenade);
    entity_id++;
}
