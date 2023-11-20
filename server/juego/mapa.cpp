#include "./mapa.h"

#include <iomanip>
#include <iostream>

Mapa::Mapa(std::string map_filepath) : world(b2Vec2(0.0f, -10.0f)), contactListener(GroundContactListener()) {
    world.SetContactListener(&contactListener);
    Load_Map_File(map_filepath);
}

void Mapa::Load_Map_File(std::string filepath) {
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

    GameConfig& config = GameConfig::getInstance();

    const YAML::Node& worm_list = map["gusanos"];
    uint32_t id = 0;
    for (YAML::const_iterator it = worm_list.begin(); it != worm_list.end(); ++it) {
        const YAML::Node& worm = *it;
        float x_pos = worm["pos_x"].as<float>();
        float y_pos = worm["pos_y"].as<float>();
        int dir = worm["direccion"].as<int>();
        // printf("La posicion del gusano es : %f   %f\n",x_pos,y_pos);
        worms.push_back(new Worm (world, config.puntos_de_vida, dir, x_pos, y_pos, id++));
    }
}

void Mapa::Step(int iteracion) {
    for(auto worm : worms) {
        if (worm->jumpSteps > 0) {
            if (worm->jumpSteps == 1) worm->Stop();
            worm->jumpSteps--;
        }
        if(worm->esta_apuntando()){
            worm->incrementar_angulo_en(0.1);
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

std::string Mapa::GetName() {
    return nombre;
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

uint16_t Mapa::gusanos_totales(){
    return this->worms.size();
}

std::vector<WormWrapper> Mapa::get_gusanos(){
    std::vector<WormWrapper> vec_worms;
    for(auto *worm: this->worms){
        std::vector<float> posicion = worm->GetPosition();
        // printf("la posicion del gusano que se envia es %f   %f\n",posicion[0],posicion[1]);
        vec_worms.push_back(WormWrapper(posicion, worm->get_facing_direction(), worm->get_status(), worm->get_id(), worm->get_angulo(), worm->aiming_angle()));
    }
    return vec_worms;
}

void Mapa::cambiar_arma(uint32_t id, uint8_t tipo_arma){
    worms[id]->cambiar_arma(tipo_arma);
}

void Mapa::apuntar_para(uint32_t id, int dir){
    worms[id]->esta_apuntando_para(dir);
}
// std::vector<float> Mapa::get_size(){
//     this->world.
// }

void Mapa::detener_worm(uint32_t id){
    worms[id]->detener_acciones();
}

void Mapa::detener_angulo(uint32_t id){
    worms[id]->parar_angulo();
}