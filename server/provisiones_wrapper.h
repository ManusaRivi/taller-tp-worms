#ifndef PROVISIONES_WRAPPER_H
#define PROVISIONES_WRAPPER_H

#include "../common/provision_types.h"

class ProvisionWrapper {
private:
    float x_pos;
    float y_pos;
    ProvisionType tipo;
    uint32_t id;
    uint8_t estado;
public:
    ProvisionWrapper(float x_pos, float y_pos, ProvisionType tipo, uint32_t id, uint8_t estado) :
        x_pos(x_pos), y_pos(y_pos), tipo(tipo), id(id), estado(estado) {}

    uint32_t get_id() {
        return id;
    }

    float get_x() {
        return this->x_pos;
    }
    
    float get_y() {
        return this->y_pos;
    }

    uint8_t get_tipo() {
        return this->tipo;
    }

    uint8_t get_estado() {
        return this->estado;
    }
};

#endif
