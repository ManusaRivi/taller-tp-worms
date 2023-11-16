#include "world.h"

World::World() {}

void World::add_worm(std::shared_ptr<Worm> worm, int id) {
    worms.emplace(id, worm);
}

void World::add_beam(Beam beam) {
    beams.push_back(beam)
}

void World::update_worm(const int& id, std::shared_ptr<Worm> worm) {
    worms.at(id)->update(std::move(worm));
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

    for (auto& worm : worms) {
        worm.second->present(it_inc, renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);
    }

    for (auto& beam : beams) {
        beam.present(renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);
    }

    renderer.Present();
}