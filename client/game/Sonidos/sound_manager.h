#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include <string>

class SoundManager {
    private:
    std::map<std::string, SDL2pp::Mix_Chunk> sounds;

    public:
    SoundManager();

    SDL2pp::Mix_chunk* get_sound(std::string& sound_name);
};

#endif