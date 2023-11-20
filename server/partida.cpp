#include "partida.h"
#include <unistd.h>
#include <chrono>

#define FRAME_RATE 30.0f

using Clock = std::chrono::steady_clock;

Partida::Partida(uint32_t id, std::string nombre, Mapa *mapa_):mapa(mapa_),id_partida(id),nombre_partida(nombre){
    posibles_id_gusanos.push_back(0);
    posibles_id_gusanos.push_back(1);
}

double now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now().time_since_epoch()).count();
}

void Partida::run()try{{
    uint32_t turno_gusano = rand() % mapa->gusanos_totales();
    uint32_t player_actual = id_player_por_gusano[turno_gusano];

    is_alive = true;
    bool partida_iniciada = false;
    while(!partida_iniciada){
        std::shared_ptr<Comando> comando = acciones_a_realizar.pop();
        if(comando->get_comando() == COMANDO::CMD_EMPEZAR_PARTIDA){
            Mensaje msg;
            printf("Se esta por broadcaster mensaje de que la partida esta por comenzar\n");
            broadcaster.broadcastSnap(msg);
            printf("Se esta por broadcastear el handshake\n");
            enviar_primer_snapshot(turno_gusano);
            partida_iniciada = true;
        }
    }
    if(!is_alive){
        return;
    }
    std::cout << "Se inicializa la partida\n" << std::endl;
    //Mensaje msg;
    //broadcaster.broadcastSnap(msg);
    //double rate = 1;
    // auto t1 = std::chrono::high_resolution_clock::now();
    int it = 0;

    double rate = 1.0f/FRAME_RATE;
    // auto startTime = std::chrono::high_resolution_clock::now();
    // int elapsed = 0;
    while (is_alive){
        auto t1 = std::chrono::high_resolution_clock::now();
        //float elapsed = currentTime - startTime;
        std::vector<std::shared_ptr<Comando>> comandos_a_ejecutar;
        std::shared_ptr<Comando> comando;
        while(acciones_a_realizar.try_pop(comando)){
            if(!comando){
                continue;
            }
            if(comando->get_responsable() != player_actual){
                printf("{!!!!!!!} El turno no es de este player {!!!!!!}\n");
                continue;
            }
            comandos_a_ejecutar.push_back(comando);
        }


        std::shared_ptr<Comando> comando_ejecutable;
        for( auto &c: comandos_a_ejecutar){
            uint32_t estado = c->get_comando();
            printf("estado: %d\n", estado);
            c->realizar_accion(mapa,0);
        }

        mapa->Step(it);
        Snapshot snap = generar_snapshot(0,0);
        Mensaje broadcast(snap);
        broadcaster.broadcastSnap(broadcast);



        auto t2 = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> duration = t2 - t1;
		double seconds = duration.count();
		double rest = rate - seconds;
        // printf("el rate es de %f y la diferencia de tiempo es de %f\n",rate,seconds);
		if(rest < 0) {
            
			double behind = -rest;
        	double lost = behind - std::fmod(behind, rate);
        	t1 += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>
                                                        (std::chrono::duration<double>(lost));
            it+=int(lost/rate);
        } else {
			std::this_thread::sleep_for(std::chrono::duration<double>(rest));
		}

        it++;

        // Limitador de frames: Duermo el programa durante un tiempo para no consumir
        // El 100% del CPU.
    }
}}catch(const ClosedQueue& e){
        is_alive = false;
}

Snapshot Partida::generar_snapshot(float tiempo_turno, uint32_t id_gusano_current_turn){
    Snapshot snap(mapa->get_gusanos());
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


void Partida::enviar_primer_snapshot(uint32_t id){
    uint16_t gusanos_disponibles = mapa->gusanos_totales();
    uint16_t cantidad_players = broadcaster.cantidad_jugadores();

    for(uint32_t i =0; i < gusanos_disponibles;i++){
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
    Snapshot snap(mapa->get_gusanos(), mapa->get_vigas());
    snap.add_condiciones_partida(0,id);
    // std::vector<float> tamanio_mapa = mapa->get_size();
    broadcaster.informar_primer_snapshot(id_gusanos_por_player, snap);
}


uint32_t Partida::proximo_turno(uint32_t turno_actual){
    turno_actual++;
    if(turno_actual == mapa->gusanos_totales()){
        return 0;
    }
    else{
        return turno_actual;
    }
}

void Partida::remover_player(Queue<Mensaje>* snapshots){
    broadcaster.remover_player(snapshots);
}

void Partida::kill(){
    acciones_a_realizar.close();
    is_alive = false;
}