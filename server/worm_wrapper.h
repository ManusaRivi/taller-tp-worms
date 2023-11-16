#ifndef WORM_WRAPPER_H
#define WORM_WRAPPER_H

#include <vector>
#include <iostream>

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
    uint32_t angulo;            
    
    public:
    //Constructor
    WormWrapper(std::vector<float> position, uint8_t dir, uint8_t status, uint32_t id, uint32_t angulo);

    std::vector<float> get_position();

    uint8_t get_direccion();

    uint8_t get_estado();

    uint32_t get_angulo();

    uint32_t get_id();

};

#endif
