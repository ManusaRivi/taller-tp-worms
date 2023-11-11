#include "partida.h"
#include <unistd.h>


Partida::Partida(uint32_t id, std::string nombre):id_partida(id),nombre_partida(nombre){
    posibles_id_gusanos.push_back(0);
    posibles_id_gusanos.push_back(1);
}


void Partida::run(){
    std::cout << "Se inicializa la partida\n" << std::endl;
    Mensaje msg;
    broadcaster.broadcastSnap(msg);
    while (true){
        std::shared_ptr<Comando> comando;
        bool pop = acciones_a_realizar.try_pop(comando);
        //TODO:aglo = factory.create_command(comado);
        // algo.ejecutate(mundo de box2d);
        // o que el protocolo devuelva el comando directamente como uniqe_ptr 
        // Un if para verificar si el jugador que hizo la accion es correcto
        if (!pop || !comando){
            mapa.Step();
            Snapshot snap = generar_snapshot();
            Mensaje broadcast(snap);
            broadcaster.broadcastSnap(broadcast);
            usleep(33333);  //Duerme 33.33ms (Para 30FPS)
            //sleep(1);     //Duerme 1s
        }
        else{
            comando->realizar_accion(mapa);
            mapa.Step();
            Snapshot snap = generar_snapshot();
            Mensaje broadcast(snap);
            broadcaster.broadcastSnap(broadcast); // TODO:que snapshot sea un shared-ptr
            usleep(33333);  //Duerme 33.33ms (Para 30FPS)
            //sleep(1);     //Duerme 1s
        }

    }
}

Snapshot Partida::generar_snapshot(){
    std::vector<std::vector<int>> vigas;
    WormWrapper gusano1 = mapa.devolver_gusano(0);
    WormWrapper gusano2 = mapa.devolver_gusano(1);
    Snapshot snap(vigas);
    snap.add_worm(gusano1);
    snap.add_worm(gusano2);
    return snap;
}


std::string Partida::get_nombre(){
    return this->nombre_partida;
}

void Partida::add_queue(Queue<Mensaje>* snapshots){
    broadcaster.add_queue(snapshots);
}

Queue<std::shared_ptr<Comando>>& Partida::get_queue(){
    return this->acciones_a_realizar;
}

uint8_t Partida::add_player(uint8_t id_player){
    std::vector<uint8_t> gusanos;
    uint8_t id_gusano = posibles_id_gusanos.back();
    gusanos.push_back(id_gusano);
    posibles_id_gusanos.pop_back();
    vector_gusanos_player.insert({id_player,gusanos});
    return id_gusano;
}