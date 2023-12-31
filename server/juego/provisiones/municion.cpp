#include "municion.h"

Municion::Municion(b2World& world, uint32_t id, float x_pos, float y_pos) :
                    Provision(world, ProvisionType::MUNICION, id, x_pos, y_pos) {}

void Municion::usar() {
    if (!interactor) return;
    interactor->reload_weapons();
}
