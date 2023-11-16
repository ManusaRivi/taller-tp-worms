#include "./mapa.h"

#include <iomanip>
#include <iostream>

Mapa::Mapa() : world(b2Vec2(0.0f, -10.0f)), contactListener(GroundContactListener()) {
    world.SetContactListener(&contactListener);
    float counter = 0;
    for(float i = 0; i < 10;i++){

        vigas.push_back(new Viga (world, LARGE, counter, 0.0f, 0.0f, BOUNDARY, WORM));
        counter += 3;
    }


    worms.push_back(new Worm (world, 100, RIGHT, 1.5f, 1.0f, WORM, BOUNDARY));

    worms.push_back(new Worm (world, 100, LEFT, 1.5f, 0.8f, WORM, BOUNDARY));
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
    return WormWrapper (posicion, worms[idx]->get_facing_direction(), 0, worms[idx]->get_id(),0);
}

Mapa::~Mapa() {
    for (auto worm : worms) {
        delete worm;
    }
    for (auto viga: vigas) {
        delete viga;
    }
}

std::vector<std::vector<float>> Mapa::get_vigas(){
    std::vector<std::vector<float>> vec_vigas;
    for (auto viga:vigas){
        std::vector<float> viga_pos = viga->get_pos();
        vec_vigas.push_back(viga_pos);
    }
    return vec_vigas;
}