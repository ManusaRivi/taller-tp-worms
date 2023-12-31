#ifndef GAME_H
#define GAME_H

// Frame rate, 33 para 30FPS
#define FRAME_RATE 16

// Tamaño de la camara (16, 9)
#define CAMERA_WIDTH 32
#define CAMERA_HEIGHT 18

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
#include "world.h"
#include "../comandos/factory_mensajes.h"
#include <chrono>
#include "camara.h"
#include "../../common/cheats.h"
#include "Proyectiles/projectile_generator.h"

class Game {
    private:
    Queue<std::shared_ptr<MensajeCliente>> &snapshots;
    Queue<std::shared_ptr<MensajeCliente>> &acciones;
    FactoryComandos factory;
    FactoryMensaje mensajes;
    bool is_active;

    public:
    Game(Queue<std::shared_ptr<MensajeCliente>> &snapshots, Queue<std::shared_ptr<MensajeCliente>> &acciones);

    int run();
    void drawGameOverScreen(Renderer& renderer, uint32_t equipo_ganador, bool fue_empate);
    void get_mouse_position(int& mouse_rel_x, int& mouse_rel_y, float& scale_x,
                            float& scale_y, World& world, float& mouse_x, float& mouse_y);

};

#endif