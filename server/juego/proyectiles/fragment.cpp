#include "fragment.h"

Fragment::Fragment(b2World& world, float x_pos, float y_pos, int dmg, int radius) : world(world), dmg(dmg), radius(radius) {
    type = ProjectileType::FRAGMENT;

    b2BodyDef fragDef;
    fragDef.type = b2_dynamicBody;
    fragDef.position.Set(x_pos, y_pos);
    fragDef.userData.pointer = reinterpret_cast<uintptr_t> (this);
    b2Body* fragBody = world.CreateBody(&fragDef);
    body = fragBody;

    b2PolygonShape fragBox;
    fragBox.SetAsBox(FRAG_WIDTH, FRAG_HEIGHT);

    b2FixtureDef fixtureFrag;
    fixtureFrag.shape = &fragBox;
    fixtureFrag.density = FRAG_DENSITY;
    fixtureFrag.filter.categoryBits = CollisionCategories::PROJECTILE_COLL;
    fixtureFrag.filter.maskBits = (CollisionCategories::BOUNDARY_COLL | CollisionCategories::WORM_COLL);
    body->CreateFixture(&fixtureFrag);

    b2Vec2 impulseVec (RandomFloat(MIN_X_IMPULSE, MAX_X_IMPULSE), Y_IMPULSE);
    body->ApplyLinearImpulse(impulseVec, body->GetWorldCenter(), true);
}

ProjectileType Fragment::getType() {
    return type;
}

void Fragment::explotar() {
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
        
        applyBlastImpulse(wormBody, explosionCenter, wormCenter, FRAG_BLAST_POWER);

        float inverseNormalizedDistanceToCenter = 1 - (distanceToCenter / radius);  // 0: en el radio. 1: en el centro.
        Worm* worm = (Worm*) wormBody->GetUserData().pointer;
        worm->takeDamage(inverseNormalizedDistanceToCenter * dmg);
    }
}
