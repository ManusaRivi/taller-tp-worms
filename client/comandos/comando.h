#ifndef _COMANDO_CLIENTE
#define _COMANDO_CLIENTE
#include <iostream>
#include "../protocolo/protocoloCliente.h"

struct ClienteProtocolo;

class ComandoCliente{

    private:
    uint8_t tipo_comando;
    uint8_t dir;

    public:

    ComandoCliente();
    virtual void enviar_accion(ClienteProtocolo &ptcl) = 0;


    private:
    void agregar_tipo(uint8_t tipo);

    void agregar_direccion(uint8_t dir);


    

};


#endif