#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "./worm.h"

class ContactListener : public b2ContactListener {
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
};

#endif
