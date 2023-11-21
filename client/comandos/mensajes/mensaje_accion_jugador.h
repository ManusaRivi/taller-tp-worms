#include "mensaje_cliente.h"
#include "../comando.h"


class MensajeAccionJugador:public MensajeCliente{

    std::shared_ptr<ComandoCliente> cmd;

    public:
    MensajeAccionJugador(std::shared_ptr<ComandoCliente> cmd);

     std::shared_ptr<ComandoCliente> get_accion();

};