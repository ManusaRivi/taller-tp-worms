#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "worm.h"

using namespace SDL2pp;

// Simula la "imagen" del estado del juego.
class Snapshot {
    private:
    std::vector<Worm> worms;
    std::vector<std::vector<int>> vigas;

/*
 * La idea es, mas adelante, que este Snapshot tenga:
 * - El vector de posiciones de las vigas encapsulado en una clase.
 */

    public:
    //Constructor
    Snapshot(std::vector<std::vector<int>> vigas);

    //Agrega un gusano a la lista de gusanos
    void add_worm(Worm worm);

    void present(int run_phase,
                Renderer& renderer,
                Texture& wwalk,
                int& vcenter);
};

#endif
