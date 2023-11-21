#include "mensaje_accion_jugador.h"


MensajeAccionJugador::MensajeAccionJugador(std::shared_ptr<ComandoCliente> cmd_):MensajeCliente(COMANDO::CMD_ACCION_JUGADOR),cmd(cmd_){

}


 std::shared_ptr<ComandoCliente> MensajeAccionJugador::get_accion(){
    return this->cmd;
 }