#ifndef VIDA_H
#define VIDA_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../collision_categories.h"
#include "../colisionable.h"
#include "./provision.h"
#include <vector>

class VidaServer : public Provision {
private:
    b2Body* body;
public:
    VidaServer(b2World& world, uint32_t id, float x_pos, float y_pos);
    std::vector<float> get_pos();
    void usar() override;
};
    
#endif
