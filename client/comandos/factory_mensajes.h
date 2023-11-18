#ifndef _FactoryMensajeClientes
#define _FactoryMensajeClientes

#include "factory_comandos.h"
#include "mensaje.h"

using namespace std;

class FactoryMensaje{

    private:
    FactoryComandos factory;

    public:
    FactoryMensaje();

    std::shared_ptr<MensajeCliente> moverse(uint8_t dir);
    std::shared_ptr<MensajeCliente> disparar();
    std::shared_ptr<MensajeCliente> saltar(uint8_t dir);
    std::shared_ptr<MensajeCliente> cargar_arma();
    std::shared_ptr<MensajeCliente> cambiar_arma(uint8_t id_arma);
    std::shared_ptr<MensajeCliente> cambiar_angulo(uint8_t direccion);
    std::shared_ptr<MensajeCliente> detener_movimiento();
    std::shared_ptr<MensajeCliente> detener_angulo();


};




#endif