#ifndef GROUND_CONTACT_LISTENER_H
#define GROUND_CONTACT_LISTENER_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "./worm.h"

class GroundContactListener : public b2ContactListener {
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
};

#endif
