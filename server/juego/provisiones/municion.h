#ifndef MUNICION_H
#define MUNICION_H

#include "provision.h"

class Municion : public Provision {
public:
    Municion(b2World& world, uint32_t id, float x_pos, float y_pos);
    virtual void usar(Worm* interactor) override;
};

#endif
