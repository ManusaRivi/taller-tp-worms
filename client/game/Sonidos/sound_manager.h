#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include <string>

class SoundManager {
    private:
    std::map<std::string, std::shared_ptr<SDL2pp::Chunk>> sounds;

    public:
    SoundManager();

    std::shared_ptr<SDL2pp::Chunk> get_sound(std::string& sound_name);
};

#endif