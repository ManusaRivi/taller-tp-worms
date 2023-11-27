#include "worm.h"

Worm::Worm(float& pos_x, float& pos_y, uint8_t& vida, uint32_t& equipo, std::unique_ptr<WormState> state): 
            _pos_x(pos_x), _pos_y(pos_y), _vida(vida), _equipo(equipo), state(std::move(state)) {}

Worm::Worm(const Worm& other) : _pos_x(other._pos_x), _pos_y(other._pos_y), _vida(other._vida), _equipo(other._equipo) {
    state = std::make_unique<WormState>(*other.state);
}

Worm& Worm::operator=(const Worm& other) {
    if (this != &other) {
        _pos_x = other._pos_x;
        _pos_y = other._pos_y;
        _vida = other._vida;
        _equipo = other._equipo;
        state = std::make_unique<WormState>(*other.state);
    }
    return *this;
}

void Worm::update(std::shared_ptr<Worm> updated_worm) {
    //Si no finalizo la animacion del estado anterior, no se actualiza
    _vida = updated_worm->getVida();
    _equipo = updated_worm->getEquipo();
    if (state->change_position()) {
        _pos_x = updated_worm->get_x();
        _pos_y = updated_worm->get_y();
    }
    if (!state->is_finished()) {
        return;
    }
    // Si el estado ya finalizo actualizo el estado
    int it = 0;
    if (typeid(*state) == typeid(*(updated_worm->state))) {
        it = state->get_iteration();
    }
    state = std::move(updated_worm->get_state());
    state->set_iteration(it);
}

void Worm::present(int& it_inc, Renderer& renderer,
                    TextureManager& texture_manager,
                    float& map_height,
                    float& x_scale, float& y_scale,
                    float& camera_x, float& camera_y) {
    float pos_rel_x = _pos_x - camera_x;
    float pos_rel_y = map_height - _pos_y - camera_y;
    int vida = _vida;
    uint32_t equipo = _equipo;

    state->present(it_inc, renderer, texture_manager, pos_rel_x, pos_rel_y, x_scale, y_scale, vida, equipo);
    //state->present(it_inc, renderer, texture_manager, _pos_x, _pos_y, x_scale, y_scale);
}

std::unique_ptr<WormState> Worm::get_state() {
    return std::move(state);
}

float Worm::get_x(){
    return this->_pos_x;
}

float Worm::get_y() {
    return this->_pos_y;
}

uint8_t Worm::getVida() {
    return this->_vida;
}

uint32_t Worm::getEquipo() {
    return this->_equipo;
}
