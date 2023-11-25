#ifndef GAME_H
#define GAME_H

// Frame rate, 33 para 30FPS
#define FRAME_RATE 33

// Tamaño de la camara (7.11, 4)
#define CAMERA_WIDTH 16
#define CAMERA_HEIGHT 9

#define GAME_MIX_FORMAT 0x00008010


#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_audio.h>
#include "Texturas/texture_manager.h"
#include "Sonidos/sound_manager.h"
#include "../protocolo/protocoloCliente.h"
#include <vector>
#include <unistd.h>
#include "../../common/queue.h"
#include "../../common/armas.h"
#include "comunicacion/snapshot.h"
#include "../comandos/comando.h"
#include "../comandos/factory_comandos.h"
#include "../comandos/mensaje.h"
#include "world.h"
#include "../comandos/factory_mensajes.h"
#include <chrono>
#include "camara.h"

#include "Proyectiles/projectile_generator.h"

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