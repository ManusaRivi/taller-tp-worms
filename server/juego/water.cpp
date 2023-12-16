#include "water.h"

Water::Water(b2World& world):Colisionable(bodyType::WATER) {
    b2BodyDef waterDef;
    waterDef.position.Set(0, 0);
    waterDef.userData.pointer = reinterpret_cast<uintptr_t> (this);
    b2Body* water = world.CreateBody(&waterDef);
    this->body = water;

    b2PolygonShape waterBox;
    waterBox.SetAsBox(LENGTH, HEIGHT);

    b2FixtureDef fixtureWater;
    fixtureWater.shape = &waterBox;
    fixtureWater.filter.categoryBits = CollisionCategories::BOUNDARY_COLL;
    fixtureWater.filter.maskBits = (CollisionCategories::WORM_COLL | CollisionCategories::WATER_COLL);

    this->body->CreateFixture(&fixtureWater);
}

Water::~Water() {}
