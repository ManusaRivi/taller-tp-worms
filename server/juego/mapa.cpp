#include "./mapa.h"


#include <iomanip>
#include <iostream>

Mapa::Mapa() : world(b2Vec2(0.0f, -10.0f)), jumpSteps(0) {
    // Creo la viga (Suelo)
    b2BodyDef vigaBody;

    b2Body *viga = world.CreateBody(&vigaBody);

    b2PolygonShape vigaBox;
    vigaBox.SetAsBox(3.0f, 0.4f);

    viga->CreateFixture(&vigaBox, 0.0f);

    // Creo un primer gusano
    b2BodyDef gusano1Def;
    gusano1Def.type = b2_dynamicBody;
    gusano1Def.position.Set(-1.5f, 1.0f);
    b2Body *gusano1 = world.CreateBody(&gusano1Def);

    b2PolygonShape gusano1Box;
    gusano1Box.SetAsBox(0.15f, 0.4f);

    b2FixtureDef fixtureGusano1;
    fixtureGusano1.shape = &gusano1Box;
    fixtureGusano1.density = 1.0f;
    fixtureGusano1.friction = 0.0f;

    gusano1->CreateFixture(&fixtureGusano1);

    gusanos.push_back(gusano1);

    // Creo un segundo gusano
    b2BodyDef gusano2Def;
    gusano2Def.type = b2_dynamicBody;
    gusano2Def.position.Set(1.5f, 0.8f);
    b2Body *gusano2 = world.CreateBody(&gusano2Def);

    b2PolygonShape gusano2Box;
    gusano2Box.SetAsBox(0.15f, 0.4f);

    b2FixtureDef fixtureGusano2;
    fixtureGusano2.shape = &gusano2Box;
    fixtureGusano2.density = 1.0f;
    fixtureGusano2.friction = 0.0f;

    gusano2->CreateFixture(&fixtureGusano2);

    gusanos.push_back(gusano2);
}

void Mapa::Step() {
    world.Step(timeStep, velocityIterations, positionIterations);
}

void Mapa::MoveWorm(int idx, int dir) {
    b2Vec2 velocity = gusanos[idx]->GetLinearVelocity();
    if (dir == MOVE_RIGHT)
        velocity.x = 0.2f;
    else if (dir == MOVE_LEFT)
        velocity.x = -0.2f;
    gusanos[idx]->SetLinearVelocity(velocity);
}

void Mapa::StopWorm(int idx) {
    b2Vec2 velocity = gusanos[idx]->GetLinearVelocity();
    velocity.x = 0.0f;
    gusanos[idx]->SetLinearVelocity(velocity);
}

void Mapa::JumpWorm(int idx) {
    float impulse = gusanos[idx]->GetMass() * 4.55;
    gusanos[idx]->ApplyLinearImpulse(b2Vec2(0, impulse), gusanos[idx]->GetWorldCenter(), true);
}

Worm Mapa::devolver_gusano(int idx){
    b2Vec2 position = gusanos[idx]->GetPosition();
    std::vector<float> posicion;
    posicion.push_back(position.x);posicion.push_back(position.y);
    Worm worm(posicion,0,0);
    return worm;
}
