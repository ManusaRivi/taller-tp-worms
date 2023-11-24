#ifndef WORM_WRAPPER_H
#define WORM_WRAPPER_H

#include <vector>
#include <stdint.h>

//Direcciones (despues quizas cambie a un angulo)
#define DIR_RIGHT 1
#define DIR_LEFT 0

//Estados (Despues va a haber mas)
#define STATUS_IDLE 0
#define STATUS_MOVING 1

class WormWrapper {
private:
    std::vector<float> position;  // (x,y)
    uint8_t dir;                  // Despues quizas cambie a un angulo
    
    uint8_t status;    
    uint32_t id; 
    float angulo;  
    float angulo_disparo;          
    uint8_t vida;

public:
    //Constructor
    WormWrapper(std::vector<float> position, uint8_t dir, uint8_t status,
                uint32_t id, float angulo, float angulo_disparo, uint8_t vida) :
                    position(position), dir(dir), status(status), id(id),
                    angulo(angulo), angulo_disparo(angulo_disparo), vida(vida) {}

    std::vector<float> get_position() {
        return position;
    }

    uint8_t get_direccion() {
        return dir;
    }

    uint8_t get_estado() {
        return status;
    }

    uint32_t get_id() {
        return id;
    }

    float get_angulo() {
        return angulo;
    }

    float get_angulo_disparo() {
        return angulo_disparo;
    }

    uint8_t get_vida() {
        return vida;
    }

};

#endif
