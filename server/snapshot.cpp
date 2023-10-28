#include "snapshot.h"

Snapshot::Snapshot(std::vector<std::vector<int>> posiciones,
                std::vector<int> direcciones,
                std::vector<int> estados,
                std::vector<std::vector<int>> vigas): 
                
                posiciones(posiciones),
                direcciones(direcciones),
                estados(estados),
                vigas(vigas) {}
