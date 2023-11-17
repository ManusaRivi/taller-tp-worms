#include "partida.h"
#include <unistd.h>
#include <chrono>

using namespace SDL2pp;
#define FRAME_RATE 30

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
        if(comando->get_comando() == COMANDO::CMD_EMPEZAR_PARTIDA){
            Mensaje msg;
            printf("Se esta por broadcaster mensaje de que la partida esta por comenzar\n");
            broadcaster.broadcastSnap(msg);
            printf("Se esta por broadcastear el handshake\n");
            enviar_primer_snapshot();
            partida_iniciada = true;
        }
    }
    std::cout << "Se inicializa la partida\n" << std::endl;
    //Mensaje msg;
    //broadcaster.broadcastSnap(msg);
    //double rate = 1;
    unsigned int t1 = SDL_GetTicks();
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


        std::shared_ptr<Comando> comando_ejecutable;
        for( auto &c: comandos_a_ejecutar){
            c->realizar_accion(mapa,turno_gusano);
        }

        mapa.Step();
        Snapshot snap = generar_snapshot(elapsed,turno_gusano);
        Mensaje broadcast(snap);
        broadcaster.broadcastSnap(broadcast);



        unsigned int t2 = SDL_GetTicks();
		int rest = FRAME_RATE - (t2 - t1);
		elapsed = currentTime - startTime;
		if (rest < 0) {
			int behind = -rest;
			rest = FRAME_RATE - behind % FRAME_RATE;
			int lost = behind + rest;
			t1 += lost;
			it += int(lost / FRAME_RATE);
		}

        // Limitador de frames: Duermo el programa durante un tiempo para no consumir
        // El 100% del CPU.
		SDL_Delay(rest);
		t1 += FRAME_RATE;
		it += 1;
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
    WormWrapper gusano1 = mapa.devolver_gusano(0);
    WormWrapper gusano2 = mapa.devolver_gusano(1);
    Snapshot snap(vigas);
    snap.add_condiciones_partida(tiempo_turno,id_gusano_current_turn);
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


void Partida::enviar_primer_snapshot(){
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
    std::vector<std::vector<float>> vigas = mapa.get_vigas();
    broadcaster.informar_primer_snapshot(id_gusanos_por_player,vigas);
}


uint32_t Partida::proximo_turno(uint32_t turno_actual){
    if(turno_actual == posibles_id_gusanos.size()){
        return 1;
    }
    else{
        return turno_actual+1;
    }
}