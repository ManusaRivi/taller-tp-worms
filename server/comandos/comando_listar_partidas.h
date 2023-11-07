#include "comando.h"
#include <map>
#include "../lobby.h"

struct ListarPartidas:public Comando{

    
    ListarPartidas();

    void realizar_accion(Lobby &lobby,Queue<Snapshot>* snapshots, uint8_t responsable);

};