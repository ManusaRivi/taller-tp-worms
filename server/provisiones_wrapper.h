#ifndef PROVISIONES_WRAPPER_H
#define PROVISIONES_WRAPPER_H

#include "../common/provision_types.h"

class ProvisionWrapper {
private:
    float x_pos;
    float y_pos;
    ProvisionType tipo;
public:
    ProvisionWrapper(float x_pos, float y_pos, ProvisionType tipo) :
        x_pos(x_pos), y_pos(y_pos), tipo(tipo) {}

    float get_x() {
        return this->x_pos;
    }
    
    float get_y() {
        return this->y_pos;
    }

    uint8_t get_tipo() {
        return this->tipo;
    }
};

#endif
