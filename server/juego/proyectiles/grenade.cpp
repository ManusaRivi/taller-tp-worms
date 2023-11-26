#include "grenade.h"

Grenade::Grenade(b2World& world, ProjectileType type, float x_pos, float y_pos,
                float angle, float power, int dmg, int radius, int fragments, int seconds) :
                world(world), timer(GrenadeTimer (seconds))
{
    this->type = type;
    this->fragments = fragments;
    this->dmg = dmg;
    this->radius = radius;

    b2Vec2 positionOffset (GRENADE_POSITION_OFFSET * cos(angle), GRENADE_POSITION_OFFSET * sin(angle));
    b2Vec2 position (x_pos, y_pos);
    b2Vec2 finalPos = positionOffset + position;

    b2BodyDef grenadeDef;
    grenadeDef.type = b2_dynamicBody;
    grenadeDef.position.Set(finalPos.x, finalPos.y);
    grenadeDef.angle = angle;
    grenadeDef.userData.pointer = reinterpret_cast<uintptr_t> (this);
    b2Body* grenadeBody = world.CreateBody(&grenadeDef);
    body = grenadeBody;

    b2PolygonShape grenadeBox;
    grenadeBox.SetAsBox(GRENADE_LENGTH, GRENADE_WIDTH);

    b2FixtureDef fixtureGrenade;
    fixtureGrenade.shape = &grenadeBox;
    fixtureGrenade.density = GRENADE_DENSITY;
    fixtureGrenade.restitution = GRENADE_RESTITUTION;
    fixtureGrenade.filter.categoryBits = CollisionCategories::PROJECTILE_COLL;
    fixtureGrenade.filter.maskBits = (CollisionCategories::BOUNDARY_COLL | CollisionCategories::WORM_COLL);

    body->CreateFixture(&fixtureGrenade);

    b2Vec2 impulseVec (power * cos(angle), power * sin(angle));
    body->ApplyTorque(power, true);
    body->ApplyLinearImpulse(impulseVec, body->GetWorldCenter(), true);
}

void Grenade::advance_time() {
    if (timer.advance_time()) this->explotar();
}

void Grenade::bounce() {
    this->sounds.push(SoundTypes::GRENADE_BOUNCE);
}

bool Grenade::isGrenade() {
    return true;
}

void Grenade::explotar()
{
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
        
        applyBlastImpulse(wormBody, explosionCenter, wormCenter, GRENADE_BLAST_POWER);

        float inverseNormalizedDistanceToCenter = 1 - (distanceToCenter / radius);  // 0: en el radio. 1: en el centro.
        Worm* worm = (Worm*) wormBody->GetUserData().pointer;
        worm->takeDamage(inverseNormalizedDistanceToCenter * dmg);
    }
}
