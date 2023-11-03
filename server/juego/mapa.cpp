#include "./mapa.h"


#include <iomanip>
#include <iostream>

Mapa::Mapa() : world(b2Vec2(0.0f, -10.0f)) {
    // Creo la viga (Suelo)
    b2BodyDef vigaBody;

    b2Body *viga = world.CreateBody(&vigaBody);

    b2PolygonShape vigaBox;
    vigaBox.SetAsBox(LONG_BEAM_LENGTH, LONG_BEAM_HEIGHT);

    viga->CreateFixture(&vigaBox, 0.0f);

    // Creo un primer gusano
    b2BodyDef gusano1Def;
    gusano1Def.type = b2_dynamicBody;
    gusano1Def.position.Set(-1.5f, 0.82f);
    b2Body *gusano1 = world.CreateBody(&gusano1Def);

    b2PolygonShape gusano1Box;
    gusano1Box.SetAsBox(WORM_WIDTH, WORM_HEIGHT);

    b2FixtureDef fixtureGusano1;
    fixtureGusano1.shape = &gusano1Box;
    fixtureGusano1.density = 1.0f;
    fixtureGusano1.friction = 0.0f;

    gusano1->CreateFixture(&fixtureGusano1);

    worms.push_back(new Worm (gusano1, RIGHT));

    // Creo un segundo gusano
    b2BodyDef gusano2Def;
    gusano2Def.type = b2_dynamicBody;
    gusano2Def.position.Set(1.5f, 0.82f);
    b2Body *gusano2 = world.CreateBody(&gusano2Def);

    b2PolygonShape gusano2Box;
    gusano2Box.SetAsBox(WORM_WIDTH, WORM_HEIGHT);

    b2FixtureDef fixtureGusano2;
    fixtureGusano2.shape = &gusano2Box;
    fixtureGusano2.density = 1.0f;
    fixtureGusano2.friction = 0.0f;

    gusano2->CreateFixture(&fixtureGusano2);

    worms.push_back(new Worm (gusano2, LEFT));
}

void Mapa::Step() {
    for(auto worm : worms) {
        if (worm->jumpSteps == 1) {
            worm->Stop();
            worm->jumpSteps = 0;
        }
        else if (worm->jumpSteps > 0) {
            worm->jumpSteps--;
        }
    }
    world.Step(timeStep, velocityIterations, positionIterations);
}

void Mapa::MoveWorm(int idx, int dir) {
    worms[idx]->Move(dir);
}

void Mapa::StopWorm(int idx) {
    worms[idx]->Stop();
}

void Mapa::JumpWormForward(int idx) {
    worms[idx]->JumpForward();
}

void Mapa::JumpWormBackward(int idx) {
    worms[idx]->JumpBackward();
}

WormWrapper Mapa::devolver_gusano(int idx){
    b2Vec2 position = worms[idx]->GetPosition();
    std::vector<float> posicion;
    posicion.push_back(position.x);
    posicion.push_back(position.y);
    return WormWrapper (posicion, 0, 0);
}

Mapa::~Mapa() {
    for (auto worm : worms) {
        delete worm;
    }
}
