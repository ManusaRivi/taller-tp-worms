#include <cstdint>

class ExplosionesCliente{

    uint32_t id;
    float x;
    float y;
    float radio_explosion;

    public:
    ExplosionesCliente( uint32_t id_,
    float x_,
    float y_,
    float radio_explosion_):id(id_), x(x_), y(y_),radio_explosion(radio_explosion_){

    }

};