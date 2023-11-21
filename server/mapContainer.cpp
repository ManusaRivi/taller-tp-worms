#include <../../libs/yaml-cpp/include/yaml-cpp/yaml.h>
#include "mapContainer.h"

MapContainer::MapContainer() : mapas() {
    this->root = PROJECT_SOURCE_DIR "/server/mapas";
    this->getMaps();
}

MapContainer::~MapContainer() {
    for (auto it = mapas.begin(); it != mapas.end(); ++it) {
        delete it->second; // Elimina cada objeto Mapa
    }
    mapas.clear(); // Limpia el contenedor
}

void MapContainer::getMaps() {

    std::filesystem::path directorioPath = this->root;

    

    if (fs::is_directory(directorioPath)) {
        uint32_t id = 0;
        for (const auto& entry : fs::directory_iterator(directorioPath)) {
            if (entry.is_regular_file()) {
                std::string archivoYAML = entry.path().string();

                try {
                    // Crea una instancia de la clase Mapa
                    Mapa* mapa = new Mapa(archivoYAML); // ACA HAY QUE INICIALIZAR EL MAPA CON TODOS LOS DATOS

                    // Agrega el mapa al MapContainer utilizando el nombre del archivo como ID
                    this->addMap(id, mapa);
                    id++;
                    std::cout << "Ya me cargue un mapa\n";

                } catch (const std::exception& e) {
                    std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
                }
            }
        }
    } else {
        std::cerr << "El directorio no existe." << std::endl;
    }
}

Mapa* MapContainer::getMap(uint32_t id) {
    return mapas[id];
}

void MapContainer::addMap(uint32_t id, Mapa* mapa) {
    this->mapas[id] = mapa;
}
