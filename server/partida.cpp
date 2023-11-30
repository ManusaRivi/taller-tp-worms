#include "partida.h"
#include <unistd.h>
#include <chrono>

#define FRAME_RATE 30.0f

using Clock = std::chrono::steady_clock;

Partida::Partida(uint32_t id, std::string nombre,std::string archivo_yaml):mapa(archivo_yaml),id_partida(id),nombre_partida(nombre){
    posibles_id_gusanos.push_back(0);
    posibles_id_gusanos.push_back(1);
}

double now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now().time_since_epoch()).count();
}

void Partida::run()try{{

    is_alive = true;
    partida_empezada = false;
    while(!partida_empezada){
        std::shared_ptr<Comando> comando = acciones_a_realizar.pop();
        if(comando->get_comando() == COMANDO::CMD_EMPEZAR_PARTIDA){
            std::shared_ptr<MensajeServer> msg = mensajes.empezar_partida();
            broadcaster.broadcastSnap(msg);
            enviar_primer_snapshot();
            partida_empezada = true;
        }
    }
    if(!is_alive){
        return;
    }
    int it = 0;

    double rate = 1.0f/FRAME_RATE;
    
    while (is_alive){

        auto t1 = std::chrono::high_resolution_clock::now();
        //float elapsed = currentTime - startTime;
        std::vector<std::shared_ptr<Comando>> comandos_a_ejecutar;
        std::shared_ptr<Comando> comando;
        while(acciones_a_realizar.try_pop(comando)){
            if(!comando){
                continue;
            }
            comandos_a_ejecutar.push_back(comando);
        }


        std::shared_ptr<Comando> comando_ejecutable;
        for( auto &c: comandos_a_ejecutar){
            c->realizar_accion(mapa);
        }
        mapa.Step(it);

        if(mapa.checkOnePlayerRemains()) {
            printf("La partida termino\n");
            is_alive = false;
            partida_terminada = true;
        }
        std::shared_ptr<Snapshot> snap = generar_snapshot(it);
        std::shared_ptr<MensajeServer> broadcast = mensajes.snapshot(snap);
        broadcaster.broadcastSnap(broadcast);

        auto t2 = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> duration = t2 - t1;
		double seconds = duration.count();
		double rest = rate - seconds;
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
        partida_terminada = true;

}

std::shared_ptr<Snapshot> Partida::generar_snapshot(int iteraccion){
    std::vector<WormWrapper> vector_gusanos;
    mapa.get_gusanos(vector_gusanos);
    std::vector<ProjectileWrapper> vector_proyectiles;
    mapa.get_projectiles(vector_proyectiles);
    std::vector<ExplosionWrapper> vector_explosiones;
    mapa.get_explosions(vector_explosiones);
    uint32_t tiempo_del_turno = iteraccion % static_cast<int>(FRAME_RATE * MAX_SEGUNDOS_POR_TURNO); // ESTO SERA EL TURN_TIMER!!!
    uint32_t gusano_jugando_actualmente = mapa.gusano_actual();
    std::vector<ProjectileWrapper> cementerio_projectiles;
    mapa.get_cementerio_proyectiles(cementerio_projectiles);
    std::vector<ExplosionWrapper> cementerio_explosiones;
    mapa.get_cementerio_explosiones(cementerio_explosiones);
    std::vector<SoundTypes> sonidos;
    mapa.get_sounds(sonidos);

    // Snapshot snap(mapa.get_gusanos());
    // snap.add_condiciones_partida(iteraccion % (30 * 10),mapa.gusano_actual());
    std::shared_ptr<SnapshotPartida> snap = std::make_shared<SnapshotPartida>(vector_gusanos,
                                                                            vector_proyectiles,
                                                                            vector_explosiones,
                                                                            tiempo_del_turno,
                                                                            gusano_jugando_actualmente,
                                                                            cementerio_explosiones,
                                                                            cementerio_projectiles,
                                                                            sonidos);
    return snap;
}

std::string Partida::get_nombre(){
    return this->nombre_partida;
}

void Partida::add_queue(Queue<std::shared_ptr<MensajeServer>>* snapshots){
    broadcaster.add_queue(snapshots);
}

Queue<std::shared_ptr<Comando>>& Partida::get_queue(){
    return this->acciones_a_realizar;
}


void Partida::enviar_primer_snapshot(){
    std::map<uint32_t, std::vector<uint32_t>> id_gusanos_por_player = mapa.repartir_ids(broadcaster.cantidad_jugadores());
    // Snapshot snap(mapa.get_gusanos(), mapa.get_vigas());
    std::vector<WormWrapper> worms;
    mapa.get_gusanos(worms);
    std::vector<std::vector<float>> beams;
    mapa.get_vigas(beams);
    std::shared_ptr<SnapshotHandshake> snap = std::make_shared<SnapshotHandshake>(worms, beams, mapa.gusano_actual());
    //snap.add_condiciones_partida(0,mapa.gusano_actual());
    // std::vector<float> tamanio_mapa = mapa.get_size();
    broadcaster.informar_primer_snapshot(id_gusanos_por_player, snap);
}




void Partida::remover_player(Queue<std::shared_ptr<MensajeServer>>* snapshots){
    broadcaster.remover_player(snapshots);
}

void Partida::kill(){
    acciones_a_realizar.close();
    is_alive = false;
}

bool Partida::partida_accesible(){
    return !partida_empezada;
}

bool Partida::terminada(){
    return partida_terminada;
}
