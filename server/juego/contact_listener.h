#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "../../common/projectile_types.h"
#include "./proyectiles/projectile.h"
#include "./colisionable.h"
#include "./worm.h"

enum CollisionType {
    WORM_VIGA,
    VIGA_WORM,
    PROYECTIL_WORM,
    WORM_PROYECTIL,
    PROYECTIL_VIGA,
    VIGA_PROYECTIL,
    WATER_WORM,
    WORM_WATER
};

class ContactListener : public b2ContactListener {
private:
    CollisionType getCollisionType(Colisionable* bodyA, Colisionable* bodyB);
public:
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
};

#endif
