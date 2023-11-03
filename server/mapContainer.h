#ifndef MAP_CONTAINER_H
#define MAP_CONTAINER_H

#include <iostream> //BORRAR
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <../../libs/yaml-cpp/include/yaml-cpp/yaml.h>
#include <filesystem>

#include "juego/mapa.h"

namespace fs = std::filesystem;

class MapContainer {
    private:
    std::map<std::string, Mapa*> mapas;
    std::string root;

    public:
    MapContainer();
    ~MapContainer();
    void getMaps();
    void addMap(const std::string&, Mapa*);
};

#endif
