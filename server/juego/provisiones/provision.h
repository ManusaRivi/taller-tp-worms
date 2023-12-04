#ifndef PROVISION_H
#define PROVISION_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../../common/provision_types.h"
#include "../collision_categories.h"
#include "../colisionable.h"
#include "../worm.h"

#define PROVISION_HEIGHT_SERVER 1
#define PROVISION_WIDTH_SERVER  1

#define PROVISION_DENSITY 0.5f

#define USADA       1
#define NO_USADA    0

class Provision : public Colisionable 
{
protected:
    b2World& world;
    b2Body* body;
    ProvisionType type;
    uint32_t id;
    Worm* interactor;
    bool taken = false;

public:
    Provision(b2World& world, ProvisionType type, uint32_t id, float x_pos, float y_pos) :
                Colisionable(bodyType::PROVISION), world(world), type(type), id(id), interactor(nullptr)
    {
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
        fixtureProvision.density = PROVISION_DENSITY;
        fixtureProvision.filter.categoryBits = CollisionCategories::PROVISION_COLL;
        fixtureProvision.filter.maskBits = (CollisionCategories::WORM_COLL | CollisionCategories::BOUNDARY_COLL);

        this->body->CreateFixture(&fixtureProvision);
    }

    void activar_provision(Worm* interactor) {
        this->taken = true;
        this->interactor = interactor;
    }
    
    virtual void usar() = 0;

    ProvisionType getType() {
        return type;
    }

    b2Vec2 getPosition() {
        return body->GetPosition();
    }

    uint32_t get_id() {
        return this->id;
    }

    uint8_t get_estado() {
        return taken == true ? USADA : NO_USADA;
    }

    bool fue_activada() {
        return taken;
    }

    Provision(const Provision&) = delete;

    Provision& operator=(const Provision&) = delete;

    virtual ~Provision() {
        body->GetWorld()->DestroyBody(body);
    }
};

#endif
