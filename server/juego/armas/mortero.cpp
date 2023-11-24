#include "mortero.h"

Mortero::Mortero(b2World& world, int dmg, int radius) : 
                 world(world), dmg(dmg), radius(radius) {
    cargando = false;
}

void Mortero::iniciarCarga() {
    cargando = true;
}

void Mortero::cargar() {
    if (nivel_carga < MAX_CHARGE)
        nivel_carga++;
}

Projectile* Mortero::Shoot(float x_pos, float y_pos, float angle) {
    GameConfig& config = GameConfig::getInstance();
    float power = BASELINE_POWER + (POWER_PER_CHARGE * nivel_carga); // a nivel carga = 1, el power es 0.5. a nivel carga = 40, el power es 2.0.
    Rocket *rocket = new Rocket (world, x_pos, y_pos, angle, power, dmg, radius, config.frag_amount);
    nivel_carga = 0;
    cargando = false;
    return rocket;
}
