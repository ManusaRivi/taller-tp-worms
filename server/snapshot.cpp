#include "snapshot.h"

Snapshot::Snapshot(std::vector<WormWrapper> worms, std::vector<std::vector<int>> vigas) : worms(worms), vigas(vigas), snapshot_de_la_partida(true) {}

Snapshot::Snapshot(std::vector<std::vector<int>> vigas) : vigas(vigas), snapshot_de_la_partida(true) {}

Snapshot::Snapshot(std::map<uint32_t,std::string> lista) : snapshot_de_la_partida(false) {}

std::vector<WormWrapper> Snapshot::get_worms(){
    return worms;
}

bool Snapshot::snap_partida(){
    return snapshot_de_la_partida;
}

std::vector<std::vector<int>> Snapshot::get_vigas(){
    return this->vigas;
}

void Snapshot::add_condiciones_partida(float tiempo_turno, uint32_t id_gusano_current_turn){
    this->tiempo_partida = tiempo_turno;
    this->id_gusano_jugando = id_gusano_current_turn;
}


uint32_t Snapshot::get_gusano_jugador(){
    return this->id_gusano_jugando;
}