#include "lobby.h"
#include "mapContainer.h"

Lobby::Lobby(MapContainer& mapas):lista_mapas(mapas),id_actual(1){

}

uint32_t Lobby::crear_partida(std::string& nombre, Queue<std::shared_ptr<MensajeServer>>* snapshots,uint16_t& id_mapa){
    std::lock_guard<std::mutex> lock(lck);
    Partida *partida = new Partida(id_actual,nombre,lista_mapas.getMap(id_mapa).second);
    
    partida->add_queue(snapshots);
    uint32_t id_actuali = this->id_actual;
    this->id_actual++;
    
    lista_partidas.insert({id_actuali,partida});
    partida->start();
    this->reap_dead();
    return id_actuali;
}



std::map<uint32_t,std::string> Lobby::listar_partidas(Queue<std::shared_ptr<MensajeServer>>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    std::map<uint32_t,std::string> lista;
    for (auto i = lista_partidas.begin(); i != lista_partidas.end(); i++){
        uint8_t accesibilidad = i->second->partida_accesible();
        if(accesibilidad == PARTIDA_ACCESIBLE){
            std::string nombre = i->second->get_nombre();
            lista.insert({i->first,nombre});
        }

    }
    return lista;
}

std::map<uint32_t,std::string> Lobby::listar_mapas(Queue<std::shared_ptr<MensajeServer>>* cliente){
    std::lock_guard<std::mutex> lock(lck);
    std::map<uint32_t,std::string> lista;
    

    for (auto it = lista_mapas.begin(); it != lista_mapas.end(); ++it) {
        // Accede a cada par clave-valor en el mapa aquí
        std::string nombre = it->second.first;
        // Realiza las operaciones que desees con el mapa
        lista.insert({it->first, nombre});
    }
    return lista;
}

Queue<std::shared_ptr<Comando>>& Lobby::get_queue(uint32_t& id_pedido){
    return lista_partidas.at(id_pedido)->get_queue();
}

uint8_t Lobby::unirse_a_partida(uint32_t& id_partida, Queue<std::shared_ptr<MensajeServer>>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    uint8_t estado = lista_partidas.at(id_partida)->partida_accesible();
    if(estado == PARTIDA_ACCESIBLE){
        lista_partidas.at(id_partida)->add_queue(snapshots);
        return estado;
    }
    else{
        return estado;
    }
}

void Lobby::desconectarse_partida(uint32_t& id,Queue<std::shared_ptr<MensajeServer>>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    if(this->lista_partidas.find(id) != this->lista_partidas.end()){
        this->lista_partidas.at(id)->remover_player(snapshots);
    }
}


void Lobby::kill(){
    std::lock_guard<std::mutex> lock(lck);
    auto it = lista_partidas.begin();
    while(it != lista_partidas.end()){
        it->second->kill();
        it->second->join();
        delete it->second;
        it = lista_partidas.erase(it);
    }
}

void Lobby::reap_dead(){
    auto it = lista_partidas.begin();
    while (it != lista_partidas.end()){
        if(it->second->terminada()){
            it->second->join();
            delete it->second;
            it = lista_partidas.erase(it);
        }else{
            it++;
        }
    }
}
