#include "beam.h"

Beam::Beam(b2World& world, int type, float x_pos, float y_pos, float angle) {
    b2BodyDef vigaDef;
    vigaDef.position.Set(x_pos, y_pos);
    vigaDef.angle = angle;
    b2Body *viga = world.CreateBody(&vigaDef);
    this->body = viga;

    b2PolygonShape vigaBox;
    float length = (type == SMALL) ? SMALL_LENGTH : LARGE_LENGTH;
    this->len = length;
    vigaBox.SetAsBox(length, HEIGHT);
    

    b2FixtureDef fixtureViga;
    fixtureViga.shape = &vigaBox;
    fixtureViga.density = BEAM_DENSITY;
    fixtureViga.friction = BEAM_FRICTION;
    fixtureViga.filter.categoryBits = CollisionCategories::BOUNDARY;
    fixtureViga.filter.maskBits = (CollisionCategories::WORM | CollisionCategories::PROJECTILE);

    this->body->CreateFixture(&fixtureViga);
}

std::vector<float> Beam::get_pos(){
     std::vector<float> viga({body->GetPosition().x,body->GetPosition().y,body->GetAngle(),this->len});
     return viga;
}