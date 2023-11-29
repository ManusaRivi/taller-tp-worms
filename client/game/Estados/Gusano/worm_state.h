#ifndef WORM_STATE_H
#define WORM_STATE_H

#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "../../Texturas/texture_manager.h"

#define WORM_WIDTH 1.2
#define WORM_HEIGHT 1.2

#define NUM_COLORES 5

/*
 * Modela el estado del gusano para poder renderizarlo.
 */
class WormState {
    protected:
    std::string texture_name;
    int frames;
    bool facing_right;
    float worm_angle;
    float shot_angle;
    bool finished;
    int iteration;

    //Constructor protegido para que solo las hijas puedan acceder a el
    WormState();

    public:
    //Renderiza el gusano en este estado
    virtual void present(int& it_inc,
                        SDL2pp::Renderer& renderer,
                        TextureManager& texture_manager,
                        float& pos_x,
                        float& pos_y,
                        float& x_scale,
                        float& y_scale,
                        int& vida,
                        uint32_t& equipo);
    
    virtual bool is_finished();

    virtual bool change_position();

    int get_iteration();

    void set_iteration(int& it);
    
    //Destructor virtual
    virtual ~WormState() {}

    float get_direction();

    float get_shooting_angle();

    float get_worm_angle();

    SDL_Color hashEquipo(uint32_t& equipo);

    void setBarraVida(SDL2pp::Renderer& renderer, float& pos_x, float& pos_y, float& x_scale, float& y_scale, int& vida, uint32_t& equipo);

};

#endif