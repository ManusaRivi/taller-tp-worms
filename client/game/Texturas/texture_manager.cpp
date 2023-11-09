#include "texture_manager.h"
#include <fstream>

using namespace SDL2pp;

TextureManager::TextureManager(Renderer& renderer) {
    // Cargo el YAML de superficies
    YAML::Node surfaces = YAML::LoadFile("superficies.yaml");

    // Establezco el color transparente
    // (Que tiene codigo RGB (128, 128, 192, 255))
	SDL_Color colorKey = {128, 128, 192, 255};


    for (const auto& nodo : surfaces) {
        std::string name = nodo["nombre"].as<std::string>();
        std::string rute = nodo["ruta"].as<std::string>();

        Surface surface(rute);
        Uint32 key = SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b);
        surface.SetColorKey(true, key);
        textures.emplace(name, Texture(renderer, surface));
    }
}

Texture& TextureManager::get_texture(std::string& texture_name) {
    return textures.at(texture_name);
}