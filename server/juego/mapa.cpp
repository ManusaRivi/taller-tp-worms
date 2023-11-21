#include "./mapa.h"

#include <iomanip>
#include <iostream>

Mapa::Mapa(std::string map_filepath) : world(b2Vec2(0.0f, -10.0f)), contactListener(ContactListener()) {
    world.SetContactListener(&contactListener);
    Load_Map_File(map_filepath);
}

void Mapa::Load_Map_File(std::string filepath) {
    YAML::Node map = YAML::LoadFile(filepath);

    nombre = map["nombre"].as<std::string>();

    const YAML::Node& viga_list = map["vigas"];
    for (YAML::const_iterator it = viga_list.begin(); it != viga_list.end(); ++it) {
        const YAML::Node& beam = *it;
        std::string tipo = beam["tipo"].as<std::string>();
        int size;
        if (tipo == "larga") {
            size = beamSize::LARGE;
        }
        else if (tipo == "corta") {
            size = beamSize::SMALL;
        }
        float x_pos = beam["pos_x"].as<float>();
        float y_pos = beam["pos_y"].as<float>();
        float angle = beam["angulo"].as<float>();
        
        vigas.push_back(new BeamServer (world, size, x_pos, y_pos, angle));
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
    turnManager.cargar_cantidad_gusanos(worms.size());

    this->water = new Water(world);
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
    std::pair<bool,uint32_t> manager = turnManager.avanzar_tiempo(iteracion);
    if(manager.first){
        this->detener_worm(manager.second);
    }
    world.Step(timeStep, velocityIterations, positionIterations);
}

void Mapa::MoveWorm(uint32_t idx, int dir) {
    if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(idx != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;

    }
    worms[turnManager.get_gusano_actual()]->Move(dir);
}

void Mapa::StopWorm(uint32_t idx) {
        if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(idx != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;
    }
    worms[turnManager.get_gusano_actual()]->Stop();
}

void Mapa::JumpWormForward(uint32_t idx) {
        if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(idx != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;
    }
    worms[turnManager.get_gusano_actual()]->JumpForward();
}

void Mapa::JumpWormBackward(uint32_t idx) {
        if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(idx != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;
    }
    worms[turnManager.get_gusano_actual()]->JumpBackward();
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

    delete water;
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
    for(auto worm: this->worms){
        std::vector<float> posicion = worm->GetPosition();
        // printf("la posicion del gusano que se envia es %f   %f\n",posicion[0],posicion[1]);
        vec_worms.push_back(WormWrapper(posicion, worm->get_facing_direction(), worm->get_status(), worm->get_id(), worm->get_angulo(), worm->aiming_angle(), worm->get_vida()));
    }
    return vec_worms;
}

void Mapa::cambiar_arma(uint32_t id, uint8_t tipo_arma){
        if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(id != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;

    }
    worms[turnManager.get_gusano_actual()]->cambiar_arma(tipo_arma);
}

void Mapa::apuntar_para(uint32_t id, int dir){
        if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(id != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;

    }
    worms[turnManager.get_gusano_actual()]->esta_apuntando_para(dir);
}
// std::vector<float> Mapa::get_size(){
//     this->world.
// }

void Mapa::detener_worm(uint32_t id){
    worms[id]->detener_acciones();
}

void Mapa::detener_angulo(uint32_t id){
    if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(id != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;

    }
    worms[turnManager.get_gusano_actual()]->parar_angulo();
}

std::map<uint32_t, std::vector<uint32_t>> Mapa::repartir_ids(uint32_t cantidad_jugadores){
    return this->turnManager.repartir_turnos(cantidad_jugadores);
}

uint32_t Mapa::gusano_actual(){
    return this->turnManager.get_gusano_actual();
}

void Mapa::cambiar_direccion(uint32_t id, uint8_t dir){
    if(turnManager.acaba_de_cambiar_turno()){
        // printf("Se esta esperando a que todos los events termiene\n");
        return;
    }
    if(id != turnManager.get_player_actual()){
        // printf("NO ES EL TURNO DE ESTE PLAYER!!!!!\n");
        return;
    }
    worms[turnManager.get_gusano_actual()]->cambiar_direccion(dir);
}