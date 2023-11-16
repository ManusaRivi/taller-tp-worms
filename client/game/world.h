#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include "comunicacion/worm.h"
#include "comunicacion/beam.h"

class World {
    private:
    std::map<int, std::shared_ptr<Worm>> worms;
    std::vector<Beam> beams;
    int _id_camera;

    public:
    World();

    void update_camera(int id_camera);

    void add_worm(std::shared_ptr<Worm> worm, int id);

    void update_worm(const int& id, std::shared_ptr<Worm> worm);

    void add_beam(Beam beam);

    void present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        int& window_width,
                        int& window_height,
                        float& x_scale,
                        float& y_scale);
};

#endif