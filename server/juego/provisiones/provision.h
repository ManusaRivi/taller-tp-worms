#ifndef PROVISION_H
#define PROVISION_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../../common/provision_types.h"
#include "../collision_categories.h"
#include "../colisionable.h"
#include "../worm.h"

#define PROVISION_HEIGHT_SERVER 1
#define PROVISION_WIDTH_SERVER  1

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
        provisionDef.type = b2_dynamicBody;
        provisionDef.position.Set(x_pos, y_pos);
        provisionDef.userData.pointer = reinterpret_cast<uintptr_t> (this);
        b2Body* provision = world.CreateBody(&provisionDef);
        this->body = provision;

        b2PolygonShape provisionBox;
        provisionBox.SetAsBox(PROVISION_WIDTH_SERVER, PROVISION_HEIGHT_SERVER);


        b2FixtureDef fixtureProvision;
        fixtureProvision.shape = &provisionBox;
        fixtureProvision.filter.categoryBits = CollisionCategories::BOUNDARY_COLL;
        fixtureProvision.filter.maskBits = (CollisionCategories::WORM_COLL | CollisionCategories::PROVISION_COLL);

        this->body->CreateFixture(&fixtureProvision);
    }

    ProvisionType getType() {
        return type;
    }
    
    bool hasBeenTaken() {
        return taken;
    }

    std::vector<float> getPosition() {
        b2Vec2 position = body->GetPosition();
        return std::vector<float> {position.x, position.y};
    }

    uint32_t get_id(){
        return this->id;
    }

    virtual void usar(Worm* interactor) = 0;

    virtual ~Provision() {
        body->GetWorld()->DestroyBody(body);
    }
};

#endif
