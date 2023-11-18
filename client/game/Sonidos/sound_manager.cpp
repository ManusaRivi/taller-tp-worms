#include "sound_manager.h"

#include <fstream>

using namespace SDL2pp;


SoundManager::SoundManager() {
    // Cargo el YAML de sonidos
    YAML::Node sounds = YAML::LoadFile(PROJECT_SOURCE_DIR "/client/game/Sonidos/sounds.yaml");


    for (const auto& nodo : sounds) {
        std::string name = nodo["nombre"].as<std::string>();
        std::string rute = PROJECT_SOURCE_DIR + nodo["ruta"].as<std::string>();

        Mix_Chunk chunk(rute); 
        sounds.emplace(name, chunk);
    }
}

Mix_chunk& SoundManager::get_sound(std::string& sound_name) {
    return sounds.at(sound_name);
}