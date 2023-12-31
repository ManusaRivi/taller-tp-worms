#ifndef TRAMPA_H
#define TRAMPA_H

#include "provision.h"

#define PROV_EXPLOSION_RADIUS 1.0f

class Trampa : public Provision {
private:
    int dmg;
public:
    Trampa(b2World& world, uint32_t id, float x_pos, float y_pos, int dmg);
    virtual void usar() override;
};

#endif
