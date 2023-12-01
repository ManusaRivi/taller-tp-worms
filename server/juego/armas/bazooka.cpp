#include "bazooka.h"

Bazooka::Bazooka(b2World& world, int dmg, int radius) : world(world), dmg(dmg), radius(radius), nivel_carga(0) {
    cargando = false;
    tipo = Armas::BAZOOKA;
}

void Bazooka::iniciarCarga() {
    cargando = true;
}

void Bazooka::cargar() { // armas que no cargan, como bate, simplemente no hacen nada.
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

bool Bazooka::estaCargando() { return cargando; }

void Bazooka::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    nivel_carga = 0;
    cargando = false;
    projectiles.push_back(std::make_shared<Rocket>(world, ProjectileType::ROCKET,
                                                    entity_id++, x_pos, y_pos, dmg,
                                                    radius, 0, angle, power));
}
