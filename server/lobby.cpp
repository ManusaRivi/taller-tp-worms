#include "lobby.h"
#include "mapContainer.h"

Lobby::Lobby():id_actual(1){

}

uint32_t Lobby::crear_partida(std::string nombre, Queue<Mensaje>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    Partida *partida = new Partida(id_actual,nombre);
    partida->add_queue(snapshots);
    uint32_t id_actuali = this->id_actual;
    this->id_actual++;
    lista_partidas.insert({id_actuali,partida});
    partida->start();
    printf("Se crea una partida nueva\n");
    return id_actuali;
}


void Lobby::listar_partidas(Queue<Mensaje>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    MapContainer mapContainer;
    std::map<uint32_t,std::string> lista;
    int id = 1;

    for (auto it = mapContainer.begin(); it != mapContainer.end(); ++it) {
        // Accede a cada par clave-valor en el mapa aquí
        const std::string& nombre = it->first;
        // Realiza las operaciones que desees con el mapa
        lista.insert({id, nombre});
        id++;
    }
    Mensaje msg(lista);
    snapshots->push(msg);
    /*std::map<uint32_t,std::string> lista;
    for (auto i = lista_partidas.begin(); i != lista_partidas.end(); i++){
        std::string nombre = i->second->get_nombre();
        std::cout << "El nombre de la partida es : " << nombre << std::endl;
        lista.insert({i->first,nombre});
    }
    Snapshot snap(lista);
    Mensaje msg(lista);
    snapshots->push(msg);*/
}

Queue<std::shared_ptr<Comando>>& Lobby::get_queue(uint32_t id_pedido){
    std::lock_guard<std::mutex> lock(lck);
    return lista_partidas.at(id_pedido)->get_queue();
}

// void Lobby::empezar_partida(uint32_t id){
//     std::lock_guard<std::mutex> lock(lck);
//     lista_partidas.at(id)->start();
// }

uint8_t Lobby::unirse_a_partida(uint32_t id_partida, Queue<Mensaje>* snapshots, uint8_t id_player){
    std::lock_guard<std::mutex> lock(lck);
    printf("Se pide unirse un player\n");
    std::cout << "a la partida = <" << unsigned(id_partida) << "> por el id : " << unsigned(id_player) << std::endl;
    lista_partidas.at(id_partida)->add_queue(snapshots);
    return 0;

}