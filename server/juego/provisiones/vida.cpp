#include "vida.h"

VidaServer::VidaServer(b2World& world, float x_pos, float y_pos) : Provision(world, ProvisionType::VIDA, x_pos, y_pos) {

}

std::vector<float> VidaServer::get_pos() {
     std::vector<float> vida({body->GetPosition().x,body->GetPosition().y});
     return vida;
}

void VidaServer::usar() {

}
