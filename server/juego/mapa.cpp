#include "./mapa.h"

#include <iomanip>
#include <iostream>

Mapa::Mapa(std::string map_filepath) : world(b2Vec2(0.0f, -10.0f)), contactListener(ContactListener()), water(Water(world)), identificador_entidades(0) {
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
        
        vigas.push_back(std::make_shared<BeamServer> (world, size, x_pos, y_pos, angle));
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
        worms.push_back(std::make_shared<Worm> (world, config.puntos_de_vida, dir, x_pos, y_pos, id++));
    }
    turnManager.cargar_cantidad_gusanos(worms.size());

    provisiones.push_back(std::make_shared<VidaServer>(world, 1, 16.0, 12.0)); // PROVISION HARDCODEADA
}

void Mapa::Step(int iteracion) {
    int idx = 0;
    bool terminar_espera = true;
    auto it = worms.begin();
    while (it != worms.end()) {
        if ((*it)->isDead() && (*it)->get_status() != WormStates::DEAD) {
            // printf("Se murio un gusano\n");
            (*it)->kill();
            this->turnManager.pasar_turno_si_muerto(idx,worms);
            // it = worms.erase(it);
            idx++;
            it++;
            continue;
        }
        while(!(*it)->sounds.empty()) {
            SoundTypes sound = (*it)->sounds.front();
            sounds.push(sound);
            (*it)->sounds.pop();
        }
        if ((*it)->jumpSteps > 0) {
            if ((*it)->jumpSteps == 1) (*it)->Stop();
            (*it)->jumpSteps--;
        }
        if ((*it)->isMoving()) {
            (*it)->Move();
        }
        if ((*it)->esta_apuntando()){
            (*it)->incrementar_angulo_en(0.1);
        }
        if ((*it)->esta_cargando_arma()) {
            (*it)->cargar_arma();
        }
        if (!(*it)->esta_quieto()) {
            terminar_espera = false;
        }
        idx++;
        it++;
    }
    if (!projectiles.empty()) {
        terminar_espera = false;
    } 
    for (auto projectile : projectiles) {
        if(!projectile){
            continue;
        }
        while(!projectile->sounds.empty()) {
            SoundTypes sound = projectile->sounds.front();
            sounds.push(sound);
            projectile->sounds.pop();
        }
        if (projectile->hasExploded()) {
            projectile->explotar();
            b2Vec2 position = projectile->getPosition();
            // Se añade el proyectil que exploto a la lista de proyectiles pasados
            explosions.push(ExplosionWrapper (position.x, position.y, projectile->getRadius(),this->identificador_entidades++));
            sounds.push(SoundTypes::EXPLOSION);

            int frag_amount = projectile->getFragCount();
            if (frag_amount > 0) {
                GameConfig& config = GameConfig::getInstance();
                for (auto i = 0; i < frag_amount; ++i) {
                    projectiles.push_back(std::make_shared<Fragment> (world, ProjectileType::FRAGMENT, this->identificador_entidades++,
                                                                        position.x, position.y, config.frag_dmg, config.frag_radius, 0));
                }
            }

            std::vector<std::shared_ptr<Projectile>>::iterator it = std::find(projectiles.begin(), projectiles.end(), projectile);
            if (it != projectiles.end())
                projectiles.erase(it);
        }
        else {
            if (!projectile->isGrenade()) {
                projectile->updateAngle();
            }
            else {
                std::shared_ptr<Grenade> grenade = std::dynamic_pointer_cast<Grenade>(projectile);
                grenade->advance_time();
            }
        }
    }
    for (auto provision : provisiones) {
        if (!provision) {
            continue;
        }
        if (provision->usada()) {
            std::vector<std::shared_ptr<Provision>>::iterator it = std::find(provisiones.begin(), provisiones.end(), provision);
            if (it != provisiones.end()) {
                provisiones.erase(it);
            }
        }

    }
    if (terminar_espera) {
        turnManager.terminar_espera(worms);
    }
    turnManager.avanzar_tiempo(iteracion, worms);
    world.Step(timeStep, velocityIterations, positionIterations);
}

/*
 * Metodos de MOVIMIENTO del gusano.
 * Como tales, son validos de realizar cuando el juego
 * esta en los estados TURN o BONUS_TURN.
 * */

void Mapa::MoveWorm(uint32_t id, int dir) {
    GameStates status = turnManager.get_state();
    if (status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->StartMovement(dir);
}

void Mapa::StopWorm(uint32_t id) {
    GameStates status = turnManager.get_state();
    if (status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->Stop();
}

void Mapa::JumpWormForward(uint32_t id) {
    GameStates status = turnManager.get_state();
    if (status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->JumpForward();
}

void Mapa::JumpWormBackward(uint32_t id) {
    GameStates status = turnManager.get_state();
    if (status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->JumpBackward();
}

void Mapa::cambiar_direccion(uint32_t id, uint8_t dir){
    GameStates status = turnManager.get_state();
    if (status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->cambiar_direccion(dir);
}

/*
 * Metodos de COMBATE del gusano.
 * Como tales, son validos de realizar cuando el juego
 * esta en el estado TURN.
 * Si esta en BONUS_TURN, solo se permite MOVIMIENTO.
 * */

void Mapa::cambiar_arma(uint32_t id, uint8_t tipo_arma){
    GameStates status = turnManager.get_state();
    if (status == BONUS_TURN || status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->cambiar_arma(tipo_arma);
    // printf("Se llega a cambiar de arma al id %u\n",tipo_arma);
}

void Mapa::apuntar_para(uint32_t id, int dir){
    GameStates status = turnManager.get_state();
    // printf("el status del worm es : %i\n",status);
    // printf("El id es %u   y el player actual es %u\n",id,turnManager.get_player_actual());
    if (status == BONUS_TURN || status == WAITING) return;
    // printf("El Player que pide aumentar el angulo es %u   y el ID el player actual es %u\n", id,turnManager.get_player_actual());
    if(id != turnManager.get_player_actual()) return;
    // printf("Y es permitido cambiar el angulo\n");
    worms[turnManager.get_gusano_actual()]->esta_apuntando_para(dir);
}

void Mapa::cargar_arma(uint32_t id) {
    GameStates status = turnManager.get_state();
    if (status == BONUS_TURN || status == WAITING) return;
    if (id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->iniciar_carga();
    printf("Se empieza a cargar el arma\n");
}

void Mapa::usar_arma(uint32_t id) {
    GameStates status = turnManager.get_state();
    if (status == BONUS_TURN || status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    if(worms[turnManager.get_gusano_actual()]->usar_arma(projectiles, this->identificador_entidades)){
        turnManager.activar_bonus_turn();
        worms[turnManager.get_gusano_actual()]->Stop();
        // printf("Se dispara el arma\n");
    }

}

void Mapa::set_grenade_time(uint32_t id, int seconds) {
    GameStates status = turnManager.get_state();
    if (status == BONUS_TURN || status == WAITING) return;
    if (id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->set_grenade_timer(seconds);
}

void Mapa::set_target(uint32_t id, float x, float y) {
    GameStates status = turnManager.get_state();
    if (status == BONUS_TURN || status == WAITING) return;
    if (id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->set_target(x, y);
}

void Mapa::detener_angulo(uint32_t id){
    GameStates status = turnManager.get_state();
    if (status == BONUS_TURN || status == WAITING) return;
    if(id != turnManager.get_player_actual()) return;
    worms[turnManager.get_gusano_actual()]->parar_angulo();
}

void Mapa::detener_worm(uint32_t id){
    worms[turnManager.get_gusano_actual()]->detener_acciones();
}

/*
 * Metodos de manejo de turnos de gusanos.
 * Derivan a turnManager.
 * */

std::map<uint32_t, std::vector<uint32_t>> Mapa::repartir_ids(uint32_t cantidad_jugadores){
    this->identificador_entidades = cantidad_jugadores + 1;
    return this->turnManager.repartir_turnos(cantidad_jugadores);
}

bool Mapa::checkOnePlayerRemains() {
    return this->turnManager.checkOnePlayerRemains();
}

uint32_t Mapa::gusano_actual(){
    return this->turnManager.get_gusano_actual();
}

/* 
 * Metodos getter para obtener informacion del estado
 * de la partida, para comunicacion con los clientes.
 * Se piden datos necesarios para enviar un snapshot.
 * */

std::string Mapa::GetName() {
    return nombre;
}

void Mapa::get_vigas(std::vector<std::vector<float>>& beam_vector){
    for (auto viga:vigas){
        std::vector<float> viga_pos = viga->get_pos();
        beam_vector.push_back(viga_pos);
    }
}

uint16_t Mapa::gusanos_totales(){
    return this->worms.size();
}

void Mapa::get_gusanos(std::vector<WormWrapper>& worm_vector){
    for(auto worm: this->worms){
        std::vector<float> posicion = worm->GetPosition();
        // printf("la posicion del gusano que se envia es %f   %f\n",posicion[0],posicion[1]);
        worm_vector.push_back(WormWrapper(posicion, worm->get_facing_direction(),
                                            worm->get_status(), worm->get_id(),
                                            worm->get_angulo(), worm->get_aiming_angle(),
                                            worm->get_vida(), turnManager.get_equipo(worm->get_id())));
    }
}

void Mapa::get_projectiles(std::vector<ProjectileWrapper>& projectile_vector) {
    for (auto projectile : projectiles) {
        if(!projectile){
            continue;
        }
        b2Vec2 position = projectile->getPosition();
        float angle = projectile->getAngle();
        
        angle += 1.57;
        // printf("los angulos que se devuelven son %f\n",angle);
        projectile_vector.push_back(ProjectileWrapper(position.x, position.y, angle, projectile->getType(),projectile->get_id()));
    }
}

void Mapa::get_provisiones(std::vector<ProvisionWrapper>& provision_vector) {
    for (auto provision : provisiones) {
        if(!provision){
            continue;
        }
        b2Vec2 position = provision->getPosition();

        provision_vector.push_back(ProvisionWrapper(position.x, position.y, provision->getType(), provision->get_id(), provision->get_estado()));
    }
}

void Mapa::get_explosions(std::vector<ExplosionWrapper>& explosion_vector) {
    while (!explosions.empty()) {
        explosion_vector.push_back(explosions.front());
        explosions.pop();
    }
}


void Mapa::get_sounds(std::vector<SoundTypes>& sound_vector) {
    while (!sounds.empty()) {
        sound_vector.push_back(sounds.front());
        sounds.pop();
    }
}


void Mapa::esta_usando_armas_especiales(std::vector<std::pair<uint8_t,std::vector<float>>>& armas_especiales){
    if(worms[this->turnManager.get_gusano_actual()]->using_teleportacion()){
        std::vector<float> posicion = worms[this->turnManager.get_gusano_actual()]->posicion_marcada();
        armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0x01,posicion}));
    }
    else{
        armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0x00,{0,0}}));
    }
    if(worms[this->turnManager.get_gusano_actual()]->using_ataque_aereo()){
        std::vector<float> posicion = worms[this->turnManager.get_gusano_actual()]->posicion_marcada();
        armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0x01,posicion}));
    }
    else{
        armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0x00,{0,0}}));
    }
    if(worms[this->turnManager.get_gusano_actual()]->using_timer()){
        armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0x01, {worms[this->turnManager.get_gusano_actual()]->get_timer()}}));
    }
    else{
        armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0x00,{0}}));
    }
}

void Mapa::get_municiones_worm(std::vector<std::pair<int,int>>& municiones){
    municiones = worms[turnManager.get_gusano_actual()]->get_municiones();
}

uint32_t Mapa::get_tiempo_turno_actual(){
    return this->turnManager.get_tiempo_actual();
}

uint16_t Mapa::get_carga_actual(){
    return worms[this->turnManager.get_gusano_actual()]->get_carga_actual();
}
