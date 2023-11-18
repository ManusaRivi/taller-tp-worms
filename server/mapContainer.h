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
    std::map<uint32_t, Mapa*> mapas;
    std::string root;

    public:
    MapContainer();
    ~MapContainer();
    void getMaps();
    void addMap(uint32_t id, Mapa*);
    Mapa* getMap(uint32_t id);
    std::map<uint32_t, Mapa*>::iterator begin() {
        return mapas.begin();
    }

    std::map<uint32_t, Mapa*>::iterator end() {
        return mapas.end();
    }
};

#endif
