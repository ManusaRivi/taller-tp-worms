#include "projectile.h"
using namespace SDL2pp;
ProjectileClient::ProjectileClient(const std::string texture, float& pos_x, float& pos_y, float& angle, uint32_t id_):
                        texture_name(texture), _pos_x(pos_x), _pos_y(pos_y), _angle(angle), id(id_) {}

int ProjectileClient::get_id() {
    return id;
}

float ProjectileClient::get_x() {
    return _pos_x;
}

float ProjectileClient::get_y() {
    return _pos_y;
}

void ProjectileClient::update(ProjectileClient other) {
    this->_pos_x = other._pos_x;
    this->_pos_x = other._pos_y;
    this->_angle = other._angle;
}

void ProjectileClient::present(int& it, Renderer& renderer, TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y) {
    
    // Calculo posicion relativa:
    float pos_rel_x = _pos_x - camera_x;
    float pos_rel_y = map_height - _pos_y - camera_y;

    // Determino cual frame usar:
    //Normalizo el angulo
    float normalized_angle = fmodf(_angle, 360.0f);

    if (normalized_angle < 0.0f) {
        normalized_angle += 360.0f;
    }

    //Calculo el frame
    int src_x = 0;
    int src_y = static_cast<int>((_angle - START_ANGLE) / INC_ANGLE);
    src_y = (src_y + CANT_FRAMES) % CANT_FRAMES;
    src_y = 60* src_y;

    // Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);

    // Grafico
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    
    renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>((pos_rel_x - PROJECTILE_WIDTH/2) * x_scale),
					static_cast<int>((pos_rel_y - PROJECTILE_HEIGHT /2) * y_scale),
					PROJECTILE_WIDTH * x_scale, PROJECTILE_HEIGHT * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}



    float& ProjectileClient::get_x_test(){
        return this->_pos_x;
    }
    float& ProjectileClient::get_y_test(){
        return this->_pos_y;
    }