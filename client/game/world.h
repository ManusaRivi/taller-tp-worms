#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include "comunicacion/worm.h"

//#include "comunicacion/beam.h"

class World {
    std::map<int, Worm> worms;
    //std::vector<Beams> beams;

    World();

    void add_worm(std::shared_ptr<Worm> worm, int& id);

    void update_worm(int& id, std::shared_ptr<Worm> worm);

    //void add_beam(Beam beam);

    void present(int& it,
                    Renderer& renderer,
                    TextureManager& texture_manager,
                    float& x_scale,
                    float& y_scale);
};

#endif