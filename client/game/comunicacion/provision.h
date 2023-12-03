#ifndef PROVISION_CLIENT_H
#define PROVISION_CLIENT_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include "../Texturas/texture_manager.h"

#define PROVISION_WIDTH 1.2
#define PROVISION_HEIGHT 1.2

using namespace SDL2pp;

class ProvisionClient {
    protected:
    std::string texture_name;
    float _pos_x;
    float _pos_y;
    uint32_t id;

    public:
    ProvisionClient(float& pos_x, float& pos_y, uint32_t id_);
    void present(SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y);

    int get_id();

    float get_x();
    float get_y();

    void update(ProvisionClient other);
    
    ~ProvisionClient() {}

};

#endif
