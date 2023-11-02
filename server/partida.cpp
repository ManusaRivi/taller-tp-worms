#include "partida.h"
#include <unistd.h>


Partida::Partida(Queue<std::shared_ptr<Comando>> &acciones, BroadCaster &caster):acciones_a_realizar(acciones),broadcaster(caster){

}


void Partida::run(){
    std::cout << "Se inicializa la partida\n" << std::endl;
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
            broadcaster.broadcastSnap(snap);
            usleep(33333);  //Duerme 33.33ms (Para 30FPS)
            //sleep(1);     //Duerme 1s
        }
        else{
            comando.get()->realizar_accion(mapa);
            mapa.Step();
            Snapshot snap = generar_snapshot();
            broadcaster.broadcastSnap(snap); // TODO:que snapshot sea un shared-ptr
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
