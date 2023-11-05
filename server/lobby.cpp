#include "lobby.h"


Lobby::Lobby():id_actual(1){

}


std::pair<uint32_t,uint8_t> Lobby::crear_partida(std::string nombre, uint8_t id_creador,Queue<Mensaje>* snapshots){
    printf("Se crea una partida nueva\n");
    Partida *partida = new Partida(id_actual,nombre);
    partida->add_queue(snapshots);
    uint32_t id_actuali = this->id_actual;
    this->id_actual++;
    lista_partidas.insert({id_actuali,partida});
    uint8_t id_gusano = partida->add_player(id_creador);
    std::pair<uint32_t,uint8_t> id_partida_gusano({id_actuali,id_gusano});
    return id_partida_gusano;
}

void Lobby::start_lobby(){
    bool comando_cerrar = false;
    while (!comando_cerrar) {
        std::string comando;
        std::cin >> comando;

        if (comando == "q") {
            comando_cerrar = true;
            break;
        }
    }
}

void Lobby::listar_partidas(Queue<Mensaje>* snapshots){
    std::map<uint32_t,std::string> lista;
    for (auto i = lista_partidas.begin(); i != lista_partidas.end(); i++){
        std::string nombre = i->second->get_nombre();
        std::cout << "El nombre de la partida es : " << nombre << std::endl;
        lista.insert({i->first,nombre});
    }
    Snapshot snap(lista);
    Mensaje msg(lista);
    snapshots->push(msg);
}

Queue<std::shared_ptr<Comando>>& Lobby::get_queue(uint32_t id_pedido){
    return lista_partidas.at(id_pedido)->get_queue();
}

void Lobby::empezar_partida(uint32_t id){
    lista_partidas.at(id)->start();
}

uint8_t Lobby::unirse_a_partida(uint32_t id_partida, Queue<Mensaje>* snapshots, uint8_t id_player){
    printf("Se pide unirse un player\n");
    std::cout << "a la partida = <" << unsigned(id_partida) << "> por el id : " << unsigned(id_player) << std::endl;
    lista_partidas.at(id_partida)->add_queue(snapshots);
    return lista_partidas.at(id_partida)->add_player(id_player);

}