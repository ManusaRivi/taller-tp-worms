#include "turn_manager.h"



TurnManager::TurnManager():state(TURN),turn_timer(0),bonus_turn_timer(0),waiting_timer(0),acaba_de_pasar_turno(false){

}

std::map<uint32_t, std::vector<uint32_t>> TurnManager::repartir_turnos(uint32_t cantidad_players,std::vector<std::shared_ptr<Worm>>& vectorWorms){
    this->cantidad_players = cantidad_players;
    for(uint32_t i =0; i < this->cantidad_gusanos;i++){
        int idx = i%cantidad_players;
        if (id_gusanos_por_player.find(idx) != id_gusanos_por_player.end()){
            id_gusanos_por_player[idx].push_back(i); // Se agrega a cada player los ids de todos los gusanos
        }
        else{
            std::vector<uint32_t> id_gusanos;
            id_gusanos_por_player.insert({idx,id_gusanos});
            id_gusanos_por_player[idx].push_back(i);
        }
        id_player_por_gusano.insert({i,i%cantidad_players}); // A cada gusano se le asigna un player;
    }


    randomizar_queue_player();

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> proba_un_player(0,cantidad_players-1); 

    uint32_t player_actual = proba_un_player(rng);
    uint32_t gusano_actual = queue_siguiente_gusano_por_player[player_actual].pop();

    this->id_gusano_actual = gusano_actual;
    this->id_player_actual = player_actual;
    balance_de_fuerza(vectorWorms);
    return this->id_gusanos_por_player;
}

void TurnManager::balance_de_fuerza(std::vector<std::shared_ptr<Worm>>& vectorWorms){

    std::map<uint32_t,std::vector<uint32_t>>::iterator best = std::max_element(id_gusanos_por_player.begin(),id_gusanos_por_player.end(),[] (const std::pair<uint32_t,std::vector<uint32_t>>& a, const std::pair<uint32_t,std::vector<uint32_t>>& b)->bool{ return a.second.size() < b.second.size(); } );

    uint32_t maximo = best->second.size();

    std::vector<uint32_t> gusanos_a_mejorar;
    for(auto c : id_gusanos_por_player){
        if ( c.second.size() < maximo){
            std::copy(c.second.begin(), c.second.end(), std::back_inserter(gusanos_a_mejorar)); 
        }
    }
    
    for (auto &c :vectorWorms){
        uint32_t id = c->get_id();
        if (std::find(gusanos_a_mejorar.begin(), gusanos_a_mejorar.end(), id) != gusanos_a_mejorar.end()){
            c->aumentar_vida(25);
        }
    }
}

void TurnManager::deleteWorm(int idx) {
    // Verificar si el índice dado es válido
    if (idx >= (int)cantidad_gusanos) {
        std::cerr << "Error: Índice de gusano no válido" << std::endl;
        return;
    }

    // Obtener el id del jugador actual del gusano que se va a eliminar
    uint32_t id_player_gusano_a_eliminar = id_player_por_gusano[idx];

    // Eliminar el gusano de la lista del jugador actual
    auto& gusanos_jugador_actual = id_gusanos_por_player[id_player_gusano_a_eliminar];
    gusanos_jugador_actual.erase(std::remove(gusanos_jugador_actual.begin(), gusanos_jugador_actual.end(), idx), gusanos_jugador_actual.end());

    // Eliminar el gusano de la lista general de gusanos
    id_player_por_gusano.erase(idx);

    // Reducir la cantidad total de gusanos
    cantidad_gusanos--;

    // Verificar si el gusano eliminado es el gusano actual del jugador actual
    if (idx == (int)id_gusano_actual) {
        // Obtener el siguiente gusano del siguiente jugador
        uint32_t next_player = (id_player_gusano_a_eliminar + 1) % cantidad_players;
        
        gusano_turno_anterior = id_gusano_actual;
        id_gusano_actual = getNextWorm(next_player);

        id_player_actual = next_player;
        }

    // Indicar que acaba de cambiar el turno
    acaba_de_pasar_turno = true;
}

uint32_t TurnManager::getNextWorm(uint32_t id_player) const {
    for (const auto& entry : id_gusanos_por_player) {
        if (entry.first == id_player) {
            const auto& gusanos_jugador = entry.second;
            if (!gusanos_jugador.empty()) {
                for (long unsigned int i = 0; i < gusanos_jugador.size(); i++) {
                    if (gusanos_jugador[i] > id_gusano_actual) {
                        return gusanos_jugador[i];
                    }
                }
                // Si no se encuentra un gusano mayor que id_gusano_actual,
                // devolver el primer gusano del jugador (cíclico)
                return gusanos_jugador[0];
            }
        }
    }
    return id_gusano_actual;  // Si no se encuentra un gusano válido, devolver el actual
}


void TurnManager::cargar_cantidad_gusanos(uint32_t cant_gusanos){
    this->cantidad_gusanos = cant_gusanos;
}

bool TurnManager::checkOnePlayerRemains() {
    return queue_siguiente_gusano_por_player.size() == 1;
}

void TurnManager::avanzar_tiempo(uint32_t iteracion, std::vector<std::shared_ptr<Worm>>& vectorWorms, bool perdio_turno){
    if (perdio_turno && state == TURN) {
        detener_gusano_actual(vectorWorms);
        turno_siguiente_player(vectorWorms);
        turn_timer = 0;
        return;
    }
    if (state == WAITING) {
        waiting_timer++;
        return;
    }
    if (state == BONUS_TURN) {
        if (bonus_turn_timer == FRAME_RATE * BONUS_SECONDS) {
            printf("El tiempo bonus termina\n");
            detener_gusano_actual(vectorWorms);
            state = WAITING;
        }
        else {
            bonus_turn_timer++;
        }
        return;
    }
    if (state == TURN) {
        turn_timer++;
        if (turn_timer == FRAME_RATE * MAX_SEGUNDOS_POR_TURNO) {
            detener_gusano_actual(vectorWorms);
            turno_siguiente_player(vectorWorms);
            turn_timer = 0;
        }
    } 
    
    return;
}

bool TurnManager::es_gusano_actual(uint32_t idx) {
    return idx == id_gusano_actual;
}

uint32_t TurnManager::get_gusano_actual(){
    return this->id_gusano_actual;
}

uint32_t TurnManager::get_player_actual(){
    return this->id_player_actual;
}

bool TurnManager::acaba_de_cambiar_turno(){
    return acaba_de_pasar_turno;
}

uint32_t TurnManager::get_equipo(uint32_t id) {
    return id_player_por_gusano[id];
}

GameStates TurnManager::get_state() { return state; }

void TurnManager::activar_bonus_turn() {
    if (state == TURN) {
        printf("Se activa el bonus turn\n");
        state = BONUS_TURN;
        bonus_turn_timer = 0;
    }
}

void TurnManager::terminar_espera(std::vector<std::shared_ptr<Worm>>& vectorWorms, bool& paso_de_turno) {
    if (state == WAITING) {
        printf("El tiempo de espera termina\n");
        state = TURN;
        turn_timer = 0;
        waiting_timer = 0;
        paso_de_turno = true;
        turno_siguiente_player(vectorWorms);
    }
}

void TurnManager::randomizar_queue_player(){
    for (auto&c: id_gusanos_por_player){
        std::vector<uint32_t> copia_vector = c.second;
        auto rd = std::random_device {}; 
        auto rng = std::default_random_engine { rd() };
        std::shuffle(std::begin(copia_vector), std::end(copia_vector), rng);
        for (auto&w : copia_vector){
            printf("Se le entrega al player %u: el gusano %u\n",c.first,w);
            queue_siguiente_gusano_por_player[c.first].push(w);
        }
    }
}


void TurnManager::turno_siguiente_player(std::vector<std::shared_ptr<Worm>>& vectorWorms){
    printf("Es el turno de %u  con gusano  %u", this->id_player_actual, id_gusano_actual);
    uint32_t turno_actual = this->id_player_actual;
    if(gusano_esta_vivo(this->id_gusano_actual,vectorWorms)){ // Si el gusano esta vivo lo agrego a la queue (sera el ultimo gusano)
        queue_siguiente_gusano_por_player[this->id_player_actual].try_push(this->id_gusano_actual);
    }
    else{
        id_player_por_gusano.erase(this->id_gusano_actual); // Se elimina el gusano de la lista
    }
    if(turno_actual +1 == static_cast<uint32_t>(this->cantidad_players)){
        turno_actual = 0;
    }else{
        turno_actual++;
    }
    uint32_t id_gusano_siguiente;
    // uint32_t cantidad_vueltas;
    bool se_encontro_player = false;
    for(uint32_t i = 0; i < static_cast<uint32_t>(this->cantidad_players);i++){ // Si todos los gusanos de un player estan muertos busco al siguiente player
        uint32_t id_jugador = (turno_actual + i) %cantidad_players; // Este es el id del jugador que estoy intentando
        if(std::find(players_eliminados.begin(), players_eliminados.end(), id_jugador) != players_eliminados.end()){
           continue; //  (turno_actual+i)%cantidad_players) devuelve un numero entre 0 y cantidad_players, iterando desde el player actual hasta el anterior
        }
        else{
            while(queue_siguiente_gusano_por_player[id_jugador].try_pop(id_gusano_siguiente)){
                if(gusano_esta_vivo(id_gusano_siguiente,vectorWorms)){
                    turno_actual = id_jugador;
                    se_encontro_player = true;
                    break;
                }else{
                    id_player_por_gusano.erase(id_gusano_siguiente);
                    continue;
                }

            }
            if(!se_encontro_player){ // Quiere decir que este player se qudo sin gusano par jugar
                queue_siguiente_gusano_por_player.erase(id_jugador);
                continue;
            }else{
                break;
            }
                
            }
    }

    if (!se_encontro_player){ // Buscar la forma de saber si todos los gusanos de un player estan muertos, eliminar ese players
        this->id_gusano_actual = 0;
    }
    else{
        this->id_gusano_actual = id_gusano_siguiente;
    }

    this->id_player_actual = turno_actual;
    printf("Y es lo entrego a %u con el gusano %u\n",this->id_player_actual,this->id_gusano_actual);

}

bool TurnManager::gusano_esta_vivo(uint32_t id,std::vector<std::shared_ptr<Worm>>& vectorWorms){
    uint32_t gusano_actual = id;
    for (auto c: vectorWorms){
        if(c->get_id() == gusano_actual){
            if(c->isDead()){
                return false;
            }
            else{
                return true;
            }
        }
    }
    return false;
}


void TurnManager::detener_gusano_actual(std::vector<std::shared_ptr<Worm>>& vectorWorms){
    for (auto c: vectorWorms){
        if(c->get_id() == this->id_gusano_actual){
            if(c->isDead()){
                return;
            }
            else{
                c->detener_acciones();
            }
        }
    }
}

void TurnManager::pasar_turno_si_muerto(int idx, std::vector<std::shared_ptr<Worm>>& vectorWorms){
    if(idx == static_cast<int>(id_gusano_actual)){
        turno_siguiente_player(vectorWorms);
    }
}

uint32_t TurnManager::get_tiempo_actual(){
    if(state == WAITING){
        return (waiting_timer)/30;
    }
    if(state == WAITING){
        return (bonus_turn_timer+turn_timer)/30;
    }
    else{
        return turn_timer/30;
    }
}