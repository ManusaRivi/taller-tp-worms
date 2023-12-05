#include "provision.h"

ProvisionClient::ProvisionClient(float& pos_x, float& pos_y, uint32_t id_, uint8_t estado_):
                        _pos_x(pos_x), _pos_y(pos_y), id(id_), estado(estado_) {}

int ProvisionClient::get_id() {
    return id;
}

float ProvisionClient::get_x() {
    return _pos_x;
}

float ProvisionClient::get_y() {
    return _pos_y;
}

uint8_t ProvisionClient::get_estado() {
    return estado;
}

void ProvisionClient::update(ProvisionClient other) {
    this->_pos_x = other._pos_x;
    this->_pos_x = other._pos_y;
}

void ProvisionClient::present(int& it, Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale,
                    float& y_scale,
                    float& camera_x,
                    float& camera_y) {

    int src_x = 0;
    int src_y = PROVISION_SPRITE_HEIGHT * (it % PROVISION_FRAMES);

    // Obtengo la textura
    std::string texture_name("Provision");
	Texture& texture = texture_manager.get_texture(texture_name);

    float pos_rel_x = _pos_x - camera_x;
    float pos_rel_y = map_height - _pos_y - camera_y;

    // Grafico la viga
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>((pos_rel_x - CLIENT_PROVISION_WIDTH/2) * x_scale),
					static_cast<int>((pos_rel_y - CLIENT_PROVISION_HEIGHT/2) * y_scale),
                    CLIENT_PROVISION_HEIGHT * x_scale, CLIENT_PROVISION_WIDTH * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}
