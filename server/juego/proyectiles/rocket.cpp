#include "rocket.h"

Rocket::Rocket(b2World& world, float x_pos, float y_pos, float angle, float power, int dmg, int radius) :
                world(world), dmg(dmg), radius(radius)
{
    b2Vec2 positionOffset (ROCKET_POSITION_OFFSET * cos(angle), ROCKET_POSITION_OFFSET * sin(angle));
    b2Vec2 position (x_pos, y_pos);
    b2Vec2 finalPos = positionOffset + position;

    b2BodyDef rocketDef;
    rocketDef.type = b2_dynamicBody;
    rocketDef.position.Set(finalPos.x, finalPos.y);
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

void Rocket::explotar()
{
    exploded = true;
    WormQuery wormQuery;
    b2AABB aabb;
    b2Vec2 explosionCenter = body->GetWorldCenter();
    aabb.lowerBound = explosionCenter - b2Vec2(radius, radius);
    aabb.upperBound = explosionCenter + b2Vec2(radius, radius);
    world.QueryAABB(&wormQuery, aabb);

    for (size_t i = 0; i < wormQuery.foundBodies.size(); ++i) {
        b2Body* wormBody = wormQuery.foundBodies[i];
        b2Vec2 wormCenter = wormBody->GetWorldCenter();

        float distanceToCenter = (wormCenter - explosionCenter).Length();

        if (distanceToCenter >= radius)
            continue;
        
        applyBlastImpulse(wormBody, explosionCenter, wormCenter, ROCKET_BLAST_POWER);

        float inverseNormalizedDistanceToCenter = 1 - (distanceToCenter / radius);  // 0: en el radio. 1: en el centro.
        Worm* worm = (Worm*) wormBody->GetUserData().pointer;
        worm->takeDamage(inverseNormalizedDistanceToCenter * dmg);
    }
}
