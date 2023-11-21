#ifndef COLISIONABLE_H
#define COLISIONABLE_H

enum bodyType {
    BEAM,
    WORM,
    PROJECTILE
};

class Colisionable
{
public:
    Colisionable() {}
    virtual bodyType identificar() = 0;
    virtual ~Colisionable() {}
};

#endif
