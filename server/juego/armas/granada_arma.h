#ifndef GRANADA_ARMA_H
#define GRANADA_ARMA_H

#include "arma.h"
#include "../proyectiles/grenade.h"

#define GRENADE_BASE_RESTITUTION 0.5f

class GranadaArma : public Arma {
protected:
    int seconds = 5;
public:
    void SetTime(int seconds) {
        this->seconds = seconds;
    }
    virtual bool isGrenade() override {
        return true;
    }
    virtual bool isRocket() override {
        return false;
    }
};

#endif
