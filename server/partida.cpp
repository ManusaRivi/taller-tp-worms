#include "partida.h"
#include <unistd.h>
#include <chrono>


Partida::Partida(uint32_t id, std::string nombre):id_partida(id),nombre_partida(nombre){
    posibles_id_gusanos.push_back(0);
    posibles_id_gusanos.push_back(1);
}

double now() {
    using namespace std::chrono;
    return duration_cast<duration< double>>(high_resolution_clock::now().time_since_epoch()).count();
}

void Partida::run(){
    bool partida_iniciada = false;
    while(!partida_iniciada){
        std::shared_ptr<Comando> comando = acciones_a_realizar.pop();
        if(comando->get_comando() == COMANDO::CMD_HANDSHAKE){
            enviar_id_gusanos();
            partida_iniciada = true;
        }

        if(comando->get_comando() == COMANDO::CMD_EMPEZAR_PARTIDA){
            Mensaje msg;
            printf("Se esta por broadcaster mensaje de que la partida esta por comenzar\n");
            broadcaster.broadcastSnap(msg);
            printf("Se esta por broadcastear el handshake\n");
            enviar_id_gusanos();
            partida_iniciada = true;
        }
    }
    std::cout << "Se inicializa la partida\n" << std::endl;
    //Mensaje msg;
    //broadcaster.broadcastSnap(msg);
    double rate = 1/60;
    double t1 = now();
    int it = 0;
    uint32_t turno_gusano = rand() % posibles_id_gusanos.size() + 1;
    uint32_t player_actual = id_player_por_gusano[turno_gusano];
    double startTime = now();
    double currentTime;

    while (true){
        currentTime = now();
        float elapsed = currentTime - startTime;
        std::vector<std::shared_ptr<Comando>> comandos_a_ejecutar;
        std::shared_ptr<Comando> comando;
        while(acciones_a_realizar.try_pop(comando)){
            if(!comando){
                continue;
            }
            if(comando.get()->responsable_id != player_actual){
                printf("{!!!!!!!} El turno no es de este player {!!!!!!}\n");
                continue;
            }
            comandos_a_ejecutar.push_back(comando);
        }
        //TODO:aglo = factory.create_command(comado);
        // algo.ejecutate(mundo de box2d);
        // o que el protocolo devuelva el comando directamente como uniqe_ptr 
        // Un if para verificar si el jugador que hizo la accion es correcto
        if(comandos_a_ejecutar.size() == 0){
            mapa->Step();
            Snapshot snap = generar_snapshot(elapsed,turno_gusano);
            Mensaje broadcast(snap);
            broadcaster.broadcastSnap(broadcast);
        }
        std::shared_ptr<Comando> comando_ejecutable;
        for( auto &c: comandos_a_ejecutar){
            c->realizar_accion(mapa,turno_gusano);
            mapa->Step();
            Snapshot snap = generar_snapshot(elapsed,turno_gusano);
            Mensaje broadcast(snap);
            broadcaster.broadcastSnap(broadcast); // TODO:que snapshot sea un shared-ptr
            printf("Se leyo un comando\n");
        }
        // if (!comando){
        //     mapa.Step();
        //     Snapshot snap = generar_snapshot();
        //     Mensaje broadcast(snap);
        //     broadcaster.broadcastSnap(broadcast);
        //     //usleep(33333);
        //     //sleep(1);     //Duerme 1s
        // }
        // else{
        //     comando->realizar_accion(mapa);
        //     mapa.Step();
        //     Snapshot snap = generar_snapshot();
        //     Mensaje broadcast(snap);
        //     broadcaster.broadcastSnap(broadcast); // TODO:que snapshot sea un shared-ptr
        //     printf("Se leyo un comando\n");
        //     //sleep(1);     //Duerme 1s
        //     //usleep(33333);
        // }
        double t2 = now();
        double rest = rate - (t2 - t1);
        elapsed = currentTime - startTime;
        if (rest < 0) {
            double behind = -rest;  // this is always positive
            double lost = behind - fmod(behind, rate);
            t1 += lost;
            it += static_cast<int>(lost / rate);  // floor division
        } else {
            usleep(std::chrono::duration<double>(rest).count());
        }


        t1 += rate;
        it++;
        if (elapsed>= 10) {
            turno_gusano = proximo_turno(turno_gusano);
            player_actual = id_player_por_gusano[turno_gusano];
            std::cout << "El id del gusano jugando actualmente es : " << unsigned(turno_gusano) << std::endl;
            startTime = now();
            std::cout << "Message after 10 seconds" << std::endl;
        }
    }
}

Snapshot Partida::generar_snapshot(float tiempo_turno, uint32_t id_gusano_current_turn){
    std::vector<std::vector<int>> vigas;
    std::vector<WormWrapper> worms = mapa->devolver_gusanos();
    Snapshot snap(worms, vigas);
    snap.add_condiciones_partida(tiempo_turno,id_gusano_current_turn);
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
    return id_gusano;
}


void Partida::enviar_id_gusanos(){
    uint16_t gusanos_disponibles = posibles_id_gusanos.size();
    uint16_t cantidad_players = broadcaster.cantidad_jugadores();

    for(uint32_t i =1; i <= gusanos_disponibles;i++){
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
    broadcaster.informar_gusanos_propios(id_gusanos_por_player);
}


uint32_t Partida::proximo_turno(uint32_t turno_actual){
    if(turno_actual == posibles_id_gusanos.size()){
        return 1;
    }
    else{
        return turno_actual+1;
    }
}