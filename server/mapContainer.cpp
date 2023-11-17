#include <../../libs/yaml-cpp/include/yaml-cpp/yaml.h>
#include "mapContainer.h"

MapContainer::MapContainer() : mapas() {
    this->root = "server/mapas";
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
        for (const auto& entry : fs::directory_iterator(directorioPath)) {
            if (entry.is_regular_file()) {
                std::string archivoYAML = entry.path().string();

                try {
                    YAML::Node config = YAML::LoadFile(archivoYAML);

                    // Extraer los datos del archivo YAML
                    std::string nombreMapa = config["mapa"]["nombre"].as<std::string>();
                    //int ancho = config["mapa"]["tamaño"]["ancho"].as<int>();
                    //int alto = config["mapa"]["tamaño"]["alto"].as<int>();

                    // Crea una instancia de la clase Mapa
                    Mapa* mapa = new Mapa(); // ACA HAY QUE INICIALIZAR EL MAPA CON TODOS LOS DATOS

                    // Agrega el mapa al MapContainer utilizando el nombre del archivo como ID
                    this->addMap(nombreMapa, mapa);
                } catch (const std::exception& e) {
                    std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
                }
            }
        }
    } else {
        std::cerr << "El directorio no existe." << std::endl;
    }
}

void MapContainer::addMap(const std::string& id, Mapa* mapa) {
    this->mapas[id] = mapa;
}
