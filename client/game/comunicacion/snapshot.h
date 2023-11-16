#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include "../Texturas/texture_manager.h"
#include "../world.h"
#include "worm.h"
#include <memory>

using namespace SDL2pp;

// Simula la "imagen" del estado del juego.
class Snapshot {
    private:
    std::map<int, std::shared_ptr<Worm>> worms;
    uint32_t id_turno_actual;

/*
 * La idea es, mas adelante, que este Snapshot tenga:
 * - El vector de posiciones de las vigas encapsulado en una clase.
 */

    public:
    //Constructor
    Snapshot();

    //Agrega un gusano a la lista de gusanos
    void add_worm(std::shared_ptr<Worm> worm, int id);

    void apply_to_world(World& world);

    void agregar_turno_actual(uint32_t id);

    void imprimir_posiciones();
};

#endif
