#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <vector>
#include "worm_wrapper.h"

// Simula la "imagen" del estado del juego.
class Snapshot {
    private:
    std::vector<WormWrapper> worms;
    std::vector<std::vector<int>> vigas;

/*
 * La idea es, mas adelante, que este Snapshot tenga:
 * - El vector de posiciones de las vigas encapsulado en una clase.
 */

    public:
    //Constructor
    Snapshot(std::vector<std::vector<int>> vigas);

    //Agrega un gusano a la lista de gusanos
    void add_worm(WormWrapper worm);

    std::vector<WormWrapper> get_worms();
};

#endif
