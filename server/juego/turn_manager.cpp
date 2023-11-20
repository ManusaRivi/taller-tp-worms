#include "turn_manager.h"



TurnManager::TurnManager(){

}

std::map<uint32_t, std::vector<uint32_t>> TurnManager::repartir_turnos(uint32_t cantidad_players){
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

void TurnManager::cargar_cantidad_gusanos(uint32_t cant_gusanos){
    this->cantidad_gusanos = cant_gusanos;
}

std::pair<bool,uint32_t> TurnManager::avanzar_tiempo(uint32_t iteracion){
    std::pair<bool,uint32_t> par;
    if (acaba_de_pasar_turno){
        if(iteracion % (30 * 5) == 0 && iteracion > 0){
            printf("Pasaron 5 segundos desde el turno anterior y se debe para al gusano %u\n",gusano_turno_anterior);
            acaba_de_pasar_turno = false;
            par.first = true;
            par.second = gusano_turno_anterior;
            return par;
        }
    }
    if (iteracion % (30 * 30) == 0 && iteracion > 0) {
        par.first = true;
        gusano_turno_anterior = this->id_gusano_actual;
        
        // Llama a la función para cambiar de turno
        if(this->id_gusano_actual +1 == cantidad_gusanos){
            this->id_gusano_actual = 0;
            
        }
        else{
            this->id_gusano_actual++;
        }
        printf("Se pasa de turno del gusano_id = %u   al gusano id %u\n",gusano_turno_anterior,this->id_gusano_actual);
        this->id_player_actual = id_player_por_gusano[this->id_gusano_actual];
        acaba_de_pasar_turno = true;
        par.second = gusano_turno_anterior;
        return par;
    }
    else{
        par.first = false;
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
