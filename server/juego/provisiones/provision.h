#ifndef PROVISION_H
#define PROVISION_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../../common/provision_types.h"
#include "../collision_categories.h"
#include "../colisionable.h"

#define PROVISION_HEIGHT 1
#define PROVISION_WIDTH 1

class Provision : public Colisionable 
{
protected:
    b2World& world;
    b2Body* body;
    ProvisionType type;
    uint32_t id;
    bool taken = false;

public:
    Provision(b2World& world, ProvisionType type, uint32_t id, float x_pos, float y_pos) : Colisionable(bodyType::PROVISION), world(world), type(type), id(id) {
        b2BodyDef provisionDef;
        provisionDef.position.Set(x_pos, y_pos);
        provisionDef.userData.pointer = reinterpret_cast<uintptr_t> (this);
        b2Body* provision = world.CreateBody(&provisionDef);
        this->body = provision;

        b2PolygonShape provisionBox;
        provisionBox.SetAsBox(PROVISION_WIDTH, PROVISION_HEIGHT);


        b2FixtureDef fixtureProvision;
        fixtureProvision.shape = &provisionBox;
        fixtureProvision.filter.categoryBits = CollisionCategories::BOUNDARY_COLL;
        fixtureProvision.filter.maskBits = (CollisionCategories::WORM_COLL | CollisionCategories::PROVISION_COLL);

        this->body->CreateFixture(&fixtureProvision);
    }
    ProvisionType getType() {
        return type;
    }
    virtual bool hasBeenTaken() {
        return taken;
    }

    virtual b2Vec2 getPosition() {
        return body->GetPosition();
    }

    virtual void usar() = 0;

    uint32_t get_id(){
        return this->id;
    }

    virtual ~Provision() {
        body->GetWorld()->DestroyBody(body);
    }
};

#endif
