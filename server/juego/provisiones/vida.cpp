#include "vida.h"

VidaServer::VidaServer(b2World& world, uint32_t id, float x_pos, float y_pos, int healing) :
                        Provision(world, ProvisionType::VIDA, id, x_pos, y_pos), healing(healing) {}

void VidaServer::usar(Worm* interactor) {
    taken = true;
    interactor->heal(healing);
}
