#include "sound_manager.h"

#include <fstream>

using namespace SDL2pp;


SoundManager::SoundManager() {
    // Cargo el YAML de sonidos
    YAML::Node sounds_font = YAML::LoadFile(PROJECT_SOURCE_DIR "/client/game/Sonidos/sounds.yaml");


    for (const auto& nodo : sounds_font) {
        std::string name = nodo["nombre"].as<std::string>();
        std::string rute = PROJECT_SOURCE_DIR + nodo["ruta"].as<std::string>();

        std::shared_ptr<SDL2pp::Chunk> chunk = std::make_shared<Chunk>(rute);
        sounds.emplace(name, chunk);
    }
    
}

std::shared_ptr<SDL2pp::Chunk> SoundManager::get_sound(std::string& sound_name) {
    return sounds.at(sound_name);
}