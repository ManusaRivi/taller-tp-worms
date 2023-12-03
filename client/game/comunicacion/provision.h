#ifndef PROVISION_CLIENT_H
#define PROVISION_CLIENT_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include "../Texturas/texture_manager.h"

#define CLIENT_PROVISION_WIDTH 1.2
#define CLIENT_PROVISION_HEIGHT 1.2

#define PROVISION_SPRITE_WIDTH 60
#define PROVISION_SPRITE_HEIGHT 60

#define PROVISION_FRAMES 15

using namespace SDL2pp;

class ProvisionClient {
    protected:
    std::string texture_name;
    float _pos_x;
    float _pos_y;
    uint32_t id;
    uint8_t estado;

    public:
    ProvisionClient(float& pos_x, float& pos_y, uint32_t id_, uint8_t estado_);
    void present(int& it, SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y);

    int get_id();
    uint8_t get_estado();
    float get_x();
    float get_y();

    void update(ProvisionClient other);
    
    ~ProvisionClient() {}

};

#endif
