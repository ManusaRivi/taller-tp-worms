#ifndef ARMA_H
#define ARMA_H

class Arma
{
public:
    Arma() {};
    virtual void Shoot(float x_pos, float y_pos, float angle, float power) = 0;
    virtual ~Arma() {}
};

#endif
