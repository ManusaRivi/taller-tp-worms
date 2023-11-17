#include "world.h"

using namespace SDL2pp;

World::World(float map_width, float map_height): _map_width(map_width), _map_height(map_height) {}

void World::add_worm(std::shared_ptr<Worm> worm, int id) {
    worms.emplace(id, worm);
}

void World::add_beam(Beam beam) {
    beams.push_back(beam);
}

void World::update_camera(int id_camera) {
    _id_camera = id_camera;
}

void World::update_worm(const int& id, std::shared_ptr<Worm> worm) {
    worms.at(id)->update(std::move(worm));
}

void World::present_background(Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale,
                        float& camera_x,
                        float& camera_y) {
    
    // Busco textura
    std::string texture_name("Background");
    Texture& background_tex = texture_manager.get_texture(texture_name);

    // Encuentro posicion relativa (esta en el (0, 0))
    float pos_rel_x = 0 - camera_x;
    float pos_rel_y = 0 - camera_y;

    //Grafico
    background_tex.SetAlphaMod(255); // El fondo es totalmente opaco
    renderer.Copy(
				background_tex,
				Rect(0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT), // El sprite
				Rect(static_cast<int>(pos_rel_x * x_scale),
					static_cast<int>(pos_rel_y * y_scale),
					_map_width * x_scale, _map_height * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}

void World::present_hud(Renderer& renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale) {
    
    // Busco textura
    std::string texture_name("HUDWeapons");
    Texture& hud_tex = texture_manager.get_texture(texture_name);

    //Grafico
    hud_tex.SetAlphaMod(255); // El HUD es totalmente opaco
    renderer.Copy(
				hud_tex,
				Rect(0, 0, HUD_SPRITE_WIDTH, HUD_SPRITE_HEIGHT), // El sprite
				Rect(0, 0, HUD_WIDTH * x_scale, HUD_HEIGHT * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}

void World::present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        int& window_width,
                        int& window_height,
                        float& x_scale,
                        float& y_scale){

    // Obtengo la posicion de la camara:
    float pos_foco_x = worms.at(_id_camera)->get_x();    //Por ahora solo enfoca gusanos
    float pos_foco_y = worms.at(_id_camera)->get_y();

    float camera_x = pos_foco_x - (window_width / (2 * x_scale));
    float camera_y = pos_foco_y - (window_height / (2 * y_scale));

    if (camera_x < 0) camera_x = 0;
    if (camera_y < 0) camera_y = 0;

    // Grafico fondo
    present_background(renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);

    // Grafico HUD
    present_hud(renderer, texture_manager, x_scale, y_scale);

    // Grafico gusanos
    for (auto& worm : worms) {
        worm.second->present(it_inc, renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);
    }

    // Grafico vigas
    for (auto& beam : beams) {
        beam.present(renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);
    }

    renderer.Present();
}