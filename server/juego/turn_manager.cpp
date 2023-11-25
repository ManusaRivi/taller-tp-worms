#include "turn_manager.h"



TurnManager::TurnManager():acaba_de_pasar_turno(false){

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
    uint32_t turno_gusano = rand() % this->cantidad_gusanos;
    uint32_t player_actual = id_player_por_gusano[turno_gusano];

    this->id_gusano_actual = turno_gusano;
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

std::pair<bool,uint32_t> TurnManager::avanzar_tiempo(uint32_t iteracion){
    std::pair<bool,uint32_t> par;
    if (acaba_de_pasar_turno){
        if(iteracion % (30 * 5) == 0 && iteracion > 0){
            // printf("Pasaron 5 segundos desde el turno anterior y se debe para al gusano %u\n",gusano_turno_anterior);
            acaba_de_pasar_turno = false;
            par.first = true;
            par.second = gusano_turno_anterior;
            return par;
        }
    }
    else{
        if (iteracion % (30 * 30) == 0 && iteracion > 0) {
            par.first = true;
            gusano_turno_anterior = this->id_gusano_actual;
        

            if(this->id_gusano_actual +1 == cantidad_gusanos){
            this->id_gusano_actual = 0;
            
            }
            else{
                this->id_gusano_actual++;
            }
            // printf("Se pasa de turno del gusano_id = %u   al gusano id %u\n",gusano_turno_anterior,this->id_gusano_actual);
            this->id_player_actual = id_player_por_gusano[this->id_gusano_actual];
            acaba_de_pasar_turno = true;
            par.second = gusano_turno_anterior;
            return par;
        }
        else{
            par.first = false;
        }
    }
    
    return par;
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
