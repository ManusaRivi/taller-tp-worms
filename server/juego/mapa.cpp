#include "./mapa.h"

#include <iomanip>
#include <iostream>

Mapa::Mapa(const char* map_filepath) : world(b2Vec2(0.0f, -10.0f)), contactListener(GroundContactListener()) {
    world.SetContactListener(&contactListener);
    Load_Map_File(map_filepath);
}

void Mapa::Load_Map_File(const char* filepath) {
    YAML::Node map = YAML::LoadFile(filepath);

    nombre = map["nombre"].as<std::string>();

    const YAML::Node& viga_list = map["vigas"];
    for (YAML::const_iterator it = viga_list.begin(); it != viga_list.end(); ++it) {
        const YAML::Node& viga = *it;
        std::string tipo = viga["tipo"].as<std::string>();
        int size;
        if (tipo == "larga") {
            size = beamSize::LARGE;
        }
        else if (tipo == "corta") {
            size = beamSize::SMALL;
        }
        float x_pos = viga["pos_x"].as<float>();
        float y_pos = viga["pos_y"].as<float>();
        float angle = viga["angulo"].as<float>();
        
        vigas.push_back(new Viga (world, size, x_pos, y_pos, angle));
    }

    const YAML::Node& worm_list = map["gusanos"];
    for (YAML::const_iterator it = worm_list.begin(); it != worm_list.end(); ++it) {
        const YAML::Node& worm = *it;
        float x_pos = worm["pos_x"].as<float>();
        float y_pos = worm["pos_y"].as<float>();
        int dir = worm["direccion"].as<int>();

        worms.push_back(new Worm (world, dir, x_pos, y_pos));
    }
}

void Mapa::Step() {
    for(auto worm : worms) {
        if (worm->jumpSteps > 0) {
            if (worm->jumpSteps == 1) worm->Stop();
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

std::vector<WormWrapper> Mapa::devolver_gusanos(){
    std::vector<WormWrapper> wrappers;
    for (auto worm : worms) {
        std::vector<float> position = worm->GetPosition();
        uint8_t facingDirection = worm->get_facing_direction();
        uint8_t status = 0;
        uint32_t id = worm->get_id(); 
        float angle = worm->GetAngle();
        wrappers.push_back(WormWrapper(position, facingDirection, status, id, angle));
    }
    return wrappers;
}

Mapa::~Mapa() {
    for (auto worm : worms) {
        delete worm;
    }
    for (auto viga: vigas) {
        delete viga;
    }
}
