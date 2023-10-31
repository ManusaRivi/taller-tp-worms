#include "partida.h"
#include <unistd.h>


Partida::Partida(Queue<Comando> &acciones, BroadCaster &caster):acciones_a_realizar(acciones),broadcaster(caster){

}


void Partida::run(){
    std::cout << "Se inicializa la partida\n" << std::endl;
    while (true){
        Comando comando;
        bool pop = acciones_a_realizar.try_pop(comando);
        if (!pop){
                    mapa.Step();
        std::vector<std::vector<int>> vigas;
        Worm gusano1 = mapa.devolver_gusano(0);
        Worm gusano2 = mapa.devolver_gusano(1);
        Snapshot snap(vigas);
        snap.add_worm(gusano1);
        snap.add_worm(gusano2);
        broadcaster.broadcastSnap(snap);
        usleep(33333);  //Duerme 33.33ms (Para 30FPS)
        //sleep(1);     //Duerme 1s
        continue;
        }
        if (comando.get_tipo() == 0x01){
            std::cout << "Se obtuvo el tipo correctamente" << std::endl;
            int id;
            if (comando.responsable_id == 0x00){
                id = 0;
            }
            else{
                id = 1;
            }
            uint8_t dir = comando.get_direccion();
            int direccion;
            if (dir == 0x01){
                std::cout << "Se debe mover a la derecha" << std::endl;
                direccion = 0;
            }
            else{
                std::cout << "Se debe mover a la izquierda" << std::endl;
                direccion = 1;
            }
            mapa.MoveWorm(id,direccion);
        }
        mapa.Step();
        std::vector<std::vector<int>> vigas;
        Worm gusano1 = mapa.devolver_gusano(0);
        Worm gusano2 = mapa.devolver_gusano(1);
        Snapshot snap(vigas);
        snap.add_worm(gusano1);
        snap.add_worm(gusano2);
        broadcaster.broadcastSnap(snap);
        usleep(33333);  //Duerme 33.33ms (Para 30FPS)
        //sleep(1);     //Duerme 1s
    }
}