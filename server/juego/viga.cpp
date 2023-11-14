#include "viga.h"

Viga::Viga(b2World& world, beamSize type, float x_pos, float y_pos, float angle, uint16 collisionCategory, uint16 collisionMask) {
    b2BodyDef vigaDef;
    vigaDef.position.Set(x_pos, y_pos);
    vigaDef.angle = angle;
    b2Body *viga = world.CreateBody(&vigaDef);
    this->body = viga;

    b2PolygonShape vigaBox;
    float length = (type == SMALL) ? SMALL_LENGTH : LARGE_LENGTH;
    vigaBox.SetAsBox(length, HEIGHT);

    b2FixtureDef fixtureViga;
    fixtureViga.shape = &vigaBox;
    fixtureViga.density = BEAM_DENSITY;
    fixtureViga.friction = BEAM_FRICTION;
    fixtureViga.filter.categoryBits = collisionCategory;
    fixtureViga.filter.maskBits = collisionMask;

    this->body->CreateFixture(&fixtureViga);
}