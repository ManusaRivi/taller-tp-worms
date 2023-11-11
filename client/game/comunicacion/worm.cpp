#include "worm.h"

Worm::Worm(std::vector<float> position, std::unique_ptr<WormState> state): 
            position(position), state(std::move(state)) {}

Worm::Worm(const Worm& other) : position(other.position) {
    state = std::make_unique<WormState>(*other.state);
}

 Worm& Worm::operator=(const Worm& other) {
    if (this != &other) {
        position = other.position;
        state = std::make_unique<WormState>(*other.state);
    }
    return *this;
 }

void Worm::present(int& it, Renderer& renderer, TextureManager& texture_manager, int& vcenter) {
    state->present(it, renderer, texture_manager, position);
}