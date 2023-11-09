#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>
#include <map>
#include <string>

class TextureManager {
    private:
    std::map<std::string, SDL2pp::Texture> texturas;

    public:
    TextureManager(SDL2pp::Renderer& renderer);

    SDL2pp::Texture& get_texture(std::string& texture_name);
};

#endif