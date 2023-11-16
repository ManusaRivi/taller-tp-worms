#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "../Texturas/texture_manager.h"
#include "worm.h"

using namespace SDL2pp;

// Simula la "imagen" del estado del juego.
class SnapshotCliente {
    private:
    std::vector<std::shared_ptr<Worm>> worms;
    std::vector<std::vector<float>> vigas;
    uint32_t id_turno_actual;

/*
 * La idea es, mas adelante, que este SnapshotCliente tenga:
 * - El vector de posiciones de las vigas encapsulado en una clase.
 */

    public:
    //Constructor
    SnapshotCliente(std::vector<std::vector<float>> vigas);

    //Agrega un gusano a la lista de gusanos
    void add_worm(std::shared_ptr<Worm> worm);

    void present(int& it,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale);
    
    void agregar_turno_actual(uint32_t id);

    void imprimir_posiciones();

    void agregar_vigas(std::vector<std::vector<float>> vigas);
};

#endif
