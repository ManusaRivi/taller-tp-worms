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

    worms.push_back(new Worm (world, RIGHT, -1.5f, 1.0f));

    worms.push_back(new Worm (world, LEFT, 1.5f, 0.8f));
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
