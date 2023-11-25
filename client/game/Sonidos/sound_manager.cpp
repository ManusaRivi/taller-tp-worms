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

std::shared_ptr<SDL2pp::Chunk> SoundManager::get_sound(SoundTypes sound_type) {
    std::string sound_name;
    switch (sound_type){
    case SoundTypes::AMBIENT_MUSIC:
        sound_name = "MusicaAmbiente";
        return sounds.at(sound_name);
    
    case SoundTypes::AIR_STRIKE:
        sound_name = "AirStrike";
        return sounds.at(sound_name);
    
    case SoundTypes::BANANA_BOUNCE:
        sound_name = "BananaImpact";
        return sounds.at(sound_name);
    
    case SoundTypes::GRENADE_BOUNCE:
        sound_name = "GreenGranadeImpact";
        return sounds.at(sound_name);
    
    case SoundTypes::HOLY_GRANADE_BOUNCE:
        sound_name = "HolyGranadeImpact";
        return sounds.at(sound_name);
    
    case SoundTypes::HOLY_GRANADE_CHOIR:
        sound_name = "HolyGranade";
        return sounds.at(sound_name);
    
    case SoundTypes::BAT_EQUIP:
        sound_name = "BaseBallBatJingle";
        return sounds.at(sound_name);
    
    case SoundTypes::BAT_ATTACK:
        sound_name = "BaseBallBatImpact";
        return sounds.at(sound_name);
    
    case SoundTypes::HURT_WORM:
        sound_name = "Cough";
        return sounds.at(sound_name);
    
    case SoundTypes::EXPLOSION:
        sound_name = "Explosion";
        return sounds.at(sound_name);
    
    case SoundTypes::FUSE:
        sound_name = "Fuse";
        return sounds.at(sound_name);
    
    case SoundTypes::SPLASH:
        sound_name = "Splash";
        return sounds.at(sound_name);
    
    case SoundTypes::TELEPORT:
        sound_name = "Teleport";
        return sounds.at(sound_name);
    
    case SoundTypes::GROUND_CONTACT:
        sound_name = "WormLanding";
        return sounds.at(sound_name);
    
    case SoundTypes::WORM_DEATH_CRY:
        sound_name = "AdiosMundoCruel";
        return sounds.at(sound_name);
    
    case SoundTypes::WORM_HURT_SHOUT:
        sound_name = "ComoTePilleVeras";
        return sounds.at(sound_name);
    
    case SoundTypes::WORM_GRENADE_SHOUT:
        sound_name = "Granada";
        return sounds.at(sound_name);
    
    case SoundTypes::WORM_BAZOOKA_SHOUT:
        sound_name = "Fuego";
        return sounds.at(sound_name);
    
    case SoundTypes::WIN:
        sound_name = "SomosLosMejores";
        return sounds.at(sound_name);

    default:
        throw std::runtime_error("El sonido que se pidio no existe");
    }
}