#include "turn_manager.h"



TurnManager::TurnManager():state(TURN),turn_timer(0),bonus_turn_timer(0),acaba_de_pasar_turno(false){

}

std::map<uint32_t, std::vector<uint32_t>> TurnManager::repartir_turnos(uint32_t cantidad_players){
    this->cantidad_players = cantidad_players;
    for(uint32_t i =0; i < this->cantidad_gusanos;i++){
        int idx = i%cantidad_players;
        if (id_gusanos_por_player.find(idx) != id_gusanos_por_player.end()){
            id_gusanos_por_player[idx].push_back(i);
        }
        else{
            std::vector<uint32_t> id_gusanos;
            id_gusanos_por_player.insert({idx,id_gusanos});
            id_gusanos_por_player[idx].push_back(i);
        }
        id_player_por_gusano.insert({i,i%cantidad_players});
    }


    randomizar_queue_player();

    uint32_t player_actual = rand() % this->cantidad_players;
    uint32_t gusano_actual = queue_siguiente_gusano_por_player[player_actual].pop();

    this->id_gusano_actual = gusano_actual;
    this->id_player_actual = player_actual;
    return this->id_gusanos_por_player;
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
    
    bool sonTodosIguales = true;
    uint32_t primer_valor = id_player_por_gusano.begin()->second;

    for (const auto& par : id_player_por_gusano) {
        if (par.second != primer_valor) {
            sonTodosIguales = false;
            break;
        }
    }
    return sonTodosIguales;
}

void TurnManager::avanzar_tiempo(uint32_t iteracion, std::vector<std::shared_ptr<Worm>>& vectorWorms){
    /* Nuevo funcionamiento (completar) */
    if (state == WAITING) {
        return;
    }
    if (state == BONUS_TURN) {
        if (bonus_turn_timer == FRAME_RATE * 3) {
            printf("El tiempo bonus termina\n");
            state = WAITING;
        }
        else {
            bonus_turn_timer++;
        }
        return;
    }
    if (state == TURN) {
        if (turn_timer == FRAME_RATE * 60) {
            turno_siguiente_player(vectorWorms);
            turn_timer = 0;
        }
        else {
            turn_timer++;
        }
    } 
    /* Viejo funcionamiento */
    // std::pair<bool,uint32_t> par;
    // if (acaba_de_pasar_turno){
    //     if((iteracion % static_cast<int>(FRAME_RATE * MAX_SEGUNDOS_POR_TURNO)) == 0 && iteracion > 0){
    //         turno_siguiente_player(vectorWorms);
    //         printf("acaba de terminar los 5 segunods apra actualizar fisicas en la iteracion = %d\n",iteracion);
    //         // printf("Pasaron 5 segundos desde el turno anterior y se debe para al gusano %u\n",gusano_turno_anterior);
    //         acaba_de_pasar_turno = false;
    //         par.first = true;
    //         par.second = gusano_turno_anterior;
    //         return par;
    //     }
    // }
    // else{
    //     if ((iteracion % static_cast<int>(FRAME_RATE * MAX_SEGUNDOS_POR_TURNO)) == 0 && iteracion > 0) {
    //         printf("acaba de terminar el turno en la iteracion %d\n",iteracion);
    //         par.first = true;
    //         gusano_turno_anterior = this->id_gusano_actual;
        

    //         if(this->id_gusano_actual +1 == cantidad_gusanos){
    //         this->id_gusano_actual = 0;
            
    //         }
    //         else{
    //             this->id_gusano_actual++;
    //         }
    //         // printf("Se pasa de turno del gusano_id = %u   al gusano id %u\n",gusano_turno_anterior,this->id_gusano_actual);
    //         this->id_player_actual = id_player_por_gusano[this->id_gusano_actual];
    //         acaba_de_pasar_turno = true;
    //         par.second = gusano_turno_anterior;
    //         return par;
    //     }
    //     else{
    //         par.first = false;
    //     }
    // }
    
    return;
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

void TurnManager::terminar_espera(std::vector<std::shared_ptr<Worm>>& vectorWorms) {
    if (state == WAITING) {
        printf("El tiempo de espera termina\n");
        state = TURN;
        turn_timer = 0;
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
    printf("El turno era del player %u con el gusano %u\n",this->id_player_actual,this->id_gusano_actual);
    uint32_t turno_actual = this->id_player_actual;
    if(gusano_esta_vivo(vectorWorms)){
        queue_siguiente_gusano_por_player[this->id_player_actual].try_push(this->id_gusano_actual);
    }
    if(turno_actual +1 == static_cast<uint32_t>(this->cantidad_players)){
        turno_actual = 0;
    }else{
        turno_actual++;
    }
    uint32_t id_gusano_siguiente;
    // uint32_t cantidad_vueltas;
    for(uint32_t i = 0; i < static_cast<uint32_t>(this->cantidad_players);i++){
        if(queue_siguiente_gusano_por_player[(turno_actual + i)%cantidad_players].try_pop(id_gusano_siguiente)){
            turno_actual = turno_actual + i;
            break;
        }

    }
    if (id_gusano_siguiente > cantidad_gusanos){
        this->id_gusano_actual = 0;
    }
    else{
        this->id_gusano_actual = id_gusano_siguiente;
    }

    this->id_player_actual = turno_actual;
    printf("Y es lo entrego a %u con el gusano %u\n",this->id_player_actual,this->id_gusano_actual);

}

bool TurnManager::gusano_esta_vivo(std::vector<std::shared_ptr<Worm>>& vectorWorms){
    uint32_t gusano_actual = this->id_gusano_actual;
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