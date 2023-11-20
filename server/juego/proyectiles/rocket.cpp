#include "rocket.h"

Rocket::Rocket(b2World& world, float x_pos, float y_pos, float angle, float power, int dmg, int radius) :
                dmg(dmg), radius(radius)
{
    b2BodyDef rocketDef;
    rocketDef.type = b2_dynamicBody;
    rocketDef.position.Set(x_pos, y_pos);
    rocketDef.userData.pointer = reinterpret_cast<uintptr_t> (this);
    rocketDef.angle = angle;
    b2Body* rocketBody = world.CreateBody(&rocketDef);
    body = rocketBody;

    b2PolygonShape rocketBox;
    rocketBox.SetAsBox(ROCKET_LENGTH, ROCKET_WIDTH);

    b2FixtureDef fixtureRocket;
    fixtureRocket.shape = &rocketBox;
    fixtureRocket.density = ROCKET_DENSITY;
    fixtureRocket.filter.categoryBits = CollisionCategories::PROJECTILE_COLL;
    fixtureRocket.filter.maskBits = (CollisionCategories::BOUNDARY_COLL | CollisionCategories::WORM_COLL);

    body->CreateFixture(&fixtureRocket);

    b2Vec2 impulseVec (power * cos(angle), power * sin(angle));
    body->ApplyLinearImpulse(impulseVec, body->GetWorldCenter(), true);
}
