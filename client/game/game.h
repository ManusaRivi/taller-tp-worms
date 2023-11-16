#ifndef GAME_H
#define GAME_H

// Frame rate, 33 para 30FPS
#define FRAME_RATE 33

// Tamaño de la camara (en metros)
#define CAMERA_WIDTH 7.11
#define CAMERA_HEIGHT 4

#include <SDL2pp/SDL2pp.hh>
#include "Texturas/texture_manager.h"
#include "../protocolo/protocoloCliente.h"
#include <vector>
#include <unistd.h>
#include "../../common/queue.h"
#include "comunicacion/snapshot.h"
#include "../comandos/comando.h"
#include "../comandos/factory_comandos.h"
#include "../comandos/mensaje.h"
#include "../comandos/factory_mensajes.h"

class Game {
    private:
    Queue<std::shared_ptr<MensajeCliente>> &snapshots;
    Queue<std::shared_ptr<MensajeCliente>> &acciones;
    FactoryComandos factory;
    FactoryMensaje mensajes;
    

    public:
    Game(Queue<std::shared_ptr<MensajeCliente>> &snapshots, Queue<std::shared_ptr<MensajeCliente>> &acciones);

    int run();

};

#endif