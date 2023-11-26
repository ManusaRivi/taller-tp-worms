#ifndef GRANADA_ARMA_H
#define GRANADA_ARMA_H

#include "arma.h"

class GranadaArma : public Arma {
protected:
    int seconds = 1;
public:
    void SetTime(int seconds) {
        this->seconds = seconds;
    }
};

#endif
