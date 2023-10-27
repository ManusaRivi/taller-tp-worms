#include "../../common/socket.h"

struct Protocolo{

    Socket& skt;

    Protocolo(Socket& skt);

    void recibir_movimiento();

};