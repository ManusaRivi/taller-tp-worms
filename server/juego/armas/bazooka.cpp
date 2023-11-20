#include "bazooka.h"

Bazooka::Bazooka(b2World& world, int dmg, int radius) : world(world), dmg(dmg), radius(radius) {}

void Bazooka::Shoot(float x_pos, float y_pos, float angle, float power) {
    Rocket rocket(world, x_pos, y_pos, angle, dmg, radius);
    rocket.lanzar(angle, power);
}
