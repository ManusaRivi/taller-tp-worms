#include "mortero.h"

Mortero::Mortero(b2World& world, int ammo, int fragments, int dmg, int radius) : 
                 world(world), ammo(ammo), fragments(fragments), dmg(dmg), radius(radius)
{
    cargando = false;
    tipo = Armas::MORTERO;
}

void Mortero::iniciarCarga() {
    cargando = true;
}

void Mortero::cargar() {
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

bool Mortero::estaCargando() { return cargando; }

void Mortero::Shoot(std::vector<std::shared_ptr<Projectile>>& projectiles, uint32_t& entity_id, float x_pos, float y_pos, float angle) {
    if (ammo == 0) return;
    --ammo;
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    nivel_carga = 0;
    cargando = false;
    std::shared_ptr<Rocket> rocket = std::make_shared<Rocket>(world, ProjectileType::MORTAR, x_pos, y_pos, angle, power, dmg, radius, fragments);
    rocket->insertar_id(entity_id);
    projectiles.push_back(rocket);
    entity_id++;
}
