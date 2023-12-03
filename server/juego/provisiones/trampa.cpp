#include "trampa.h"

Trampa::Trampa(b2World& world, uint32_t id, float x_pos, float y_pos, int dmg) :
                Provision(world, ProvisionType::EXPLOSIONES, id, x_pos, y_pos), dmg(dmg) {}

void Trampa::usar() {
    if (!interactor) return;
    interactor->takeDamage(dmg);
}
