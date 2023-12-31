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

    uint32_t player_actual = queue_orden_players.front();
    queue_orden_players.pop_front();
    uint32_t gusano_actual = queue_siguiente_gusano_por_player[player_actual].front();
     queue_siguiente_gusano_por_player[player_actual].pop_front();

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

bool TurnManager::checkOnePlayerRemains(std::vector<std::shared_ptr<Worm>>& vectorWorms) {
    return queue_orden_players.empty();
}

void TurnManager::avanzar_tiempo(std::vector<std::shared_ptr<Worm>>& vectorWorms, bool perdio_turno){
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
        state = BONUS_TURN;
        bonus_turn_timer = 0;
    }
}

void TurnManager::terminar_espera(std::vector<std::shared_ptr<Worm>>& vectorWorms, bool& paso_de_turno) {
    if (state == WAITING) {
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
            queue_siguiente_gusano_por_player[c.first].push_back(w);
        }
    }
    std::vector<uint32_t> player_turns(this->cantidad_players) ; // vector with 100 ints.
    std::iota (std::begin(player_turns), std::end(player_turns), 0);
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(player_turns), std::end(player_turns), rng);
    auto it = player_turns.begin();
    while(it != player_turns.end()){
        queue_orden_players.push_back((*it));
        it++;
    }

}


void TurnManager::turno_siguiente_player(std::vector<std::shared_ptr<Worm>>& vectorWorms){
    uint32_t turno_actual = this->id_player_actual;
    if(gusano_esta_vivo(this->id_gusano_actual,vectorWorms)){ // Si el gusano esta vivo lo agrego a la queue (sera el ultimo gusano)
        queue_siguiente_gusano_por_player[this->id_player_actual].push_back(this->id_gusano_actual);
    }
    else{
        id_player_por_gusano.erase(this->id_gusano_actual); // Se elimina el gusano de la lista
    }
    if(queue_siguiente_gusano_por_player[turno_actual].empty()){

    }else{
        queue_orden_players.push_back(turno_actual);
    }

    uint32_t turno_;
    uint32_t id_gusano_siguiente;
    bool se_encontro_player = false;
    bool se_encontro_gusano = false;
    while(!queue_orden_players.empty()){
        turno_ = queue_orden_players.front();
        queue_orden_players.pop_front();
        while(!queue_siguiente_gusano_por_player[turno_].empty()){
            id_gusano_siguiente = queue_siguiente_gusano_por_player[turno_].front();
            queue_siguiente_gusano_por_player[turno_].pop_front();
            if(gusano_esta_vivo(id_gusano_siguiente,vectorWorms)){
                se_encontro_player = true;
                se_encontro_gusano = true;
                break;
            }else{
                id_player_por_gusano.erase(id_gusano_siguiente);
            }
        }
        if(!se_encontro_player){
            queue_siguiente_gusano_por_player.erase(turno_);
            continue;
        }
        if(se_encontro_player && se_encontro_gusano){
            break;
        }
        
    }
    if (!se_encontro_player){ // Buscar la forma de saber si todos los gusanos de un player estan muertos, eliminar ese players
        this->id_gusano_actual = 0;
    }
    else{
        this->id_gusano_actual = id_gusano_siguiente;
    }
    if(!se_encontro_player){
        this->id_player_actual = 0;
    }
    else{
        this->id_player_actual = turno_;
    }
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

bool TurnManager::fue_empate(std::vector<std::shared_ptr<Worm>>& vectorWorms){
    if(gusano_esta_vivo(this->id_gusano_actual,vectorWorms)){
        return false;
    }
    bool hay_gusano_vivo = false;
    for (auto c: queue_siguiente_gusano_por_player){
        while(!c.second.empty()){
            uint32_t id_worm = c.second.front();
            c.second.pop_front();
            if(gusano_esta_vivo(id_worm,vectorWorms)){
                hay_gusano_vivo = true;
            }
        }
        if(hay_gusano_vivo){
            break;
        }
        
    }
    if(!hay_gusano_vivo){
        return true;
    }
    else{
        return false;
    }
}

uint32_t TurnManager::equipo_ganador(){
    if(queue_siguiente_gusano_por_player.size() == 0){
        return 0;
    }
    else{
        return queue_siguiente_gusano_por_player.begin()->first;
    }
}

void TurnManager::eliminar_gusano(uint32_t id_gusano){
    uint32_t player = id_player_por_gusano[id_gusano];
    queue_siguiente_gusano_por_player[player].remove(id_gusano);

}