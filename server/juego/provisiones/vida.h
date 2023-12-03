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
    int healing;
public:
    VidaServer(b2World& world, uint32_t id, float x_pos, float y_pos, int healing);
    virtual void usar(Worm* interactor) override;
};
    
#endif
