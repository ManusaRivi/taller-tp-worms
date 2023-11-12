#include "comando.h"
#include <map>
#include "../lobby.h"

class ListarPartidas:public Comando{

    
    ListarPartidas();

    void realizar_accion(Lobby &lobby,Queue<Snapshot>* snapshots, uint8_t responsable);

    uint8_t get_comando() override;

};