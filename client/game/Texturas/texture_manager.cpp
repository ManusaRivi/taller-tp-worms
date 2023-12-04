#include "texture_manager.h"
#include <fstream>

using namespace SDL2pp;


TextureManager::TextureManager(Renderer& renderer) {
    // Cargo el YAML de superficies
    YAML::Node surfaces = YAML::LoadFile(PROJECT_SOURCE_DIR "/client/game/Texturas/superficies.yaml");

    // Establezco el color transparente
    // (Que tiene codigo RGB (128, 128, 192, 255))
	SDL_Color colorKey = {128, 128, 192, 255};


    for (const auto& nodo : surfaces) {
        std::string name = nodo["nombre"].as<std::string>();
        std::string rute = PROJECT_SOURCE_DIR + nodo["ruta"].as<std::string>();

        Surface surface(rute);
        Uint32 key = SDL_MapRGB(surface.Get()->format, colorKey.r, colorKey.g, colorKey.b);
        surface.SetColorKey(true, key);
        textures.emplace(name, Texture(renderer, surface));
    }

    // Cargo las texturas de los textos de los timers
    Font font(PROJECT_SOURCE_DIR "/client/game/Texturas/data/Vera.ttf", 24);
    SDL_Color timer_color = {255, 255, 255, 255};
    for (int i = 1; i <= 5; i++) {
        std::string text = "Explosion en " + std::to_string(i) + " segundos";
        std::string name = "Explosion " + std::to_string(i);
        textures.emplace(name, Texture(renderer, font.RenderText_Blended(text, timer_color)));
    }
}

Texture& TextureManager::get_texture(std::string& texture_name) {
    return textures.at(texture_name);
}