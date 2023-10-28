#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <vector>

// Simula la "imagen" del estado del juego.
class Snapshot {
    private:
    std::vector<std::vector<int>> posiciones;
    std::vector<int> direcciones;   // 1 = DER; 0 = IZQ
    std::vector<int> estados;       // 1 = MOVIENDOSE; 0 = QUIETO
    std::vector<std::vector<int>> vigas;

/*
 * La idea es, mas adelante, que este Snapshot tenga:
 * - El vector de posiciones de las vigas encapsulado en una clase.
 * - Un vector de una clase "Gusano" que contendra, para
 * cada gusano, su posicion, direccion, y estado (que va a tener mas 
 * que 2, otro estado puede ser, por ejemplo "SALTANDO", o "VOLANDO" cuando
 * recibe una explosion y debe salir disparado).
 * 
 * Pero esto cuando avancemos un poco mas.
 */

    public:
    //Constructor
    Snapshot(   std::vector<std::vector<int>> posiciones,
                std::vector<int> direcciones,
                std::vector<int> estados,
                std::vector<std::vector<int>> vigas);
};

#endif
