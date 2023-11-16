#include "world.h"

World::World() {}

void World::add_worm(std::shared_ptr<Worm> worm, int id) {
    worms.emplace(id, worm);
}

void World::update_worm(const int& id, std::shared_ptr<Worm> worm) {
    worms.at(id)->update(std::move(worm));
}

void World::present(int& it,
                    Renderer& renderer,
                    TextureManager& texture_manager,
                    float& x_scale,
                    float& y_scale) {
                    
    for (auto& worm : worms) {
        worm.second->present(it, renderer, texture_manager, x_scale, y_scale);
    }

    /*
    for (auto& beam : beams) {
        beam->present(renderer, texture_manager, x_scale, y_scale);
    }
    */
    renderer.Present();
}