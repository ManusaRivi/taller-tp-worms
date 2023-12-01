#ifndef COLISIONABLE_H
#define COLISIONABLE_H

enum bodyType {
    BEAM,
    WORM,
    PROJECTILE,
    WATER
};

class Colisionable
{
    bodyType body;
public:
    Colisionable(bodyType body_):body(body_) {}
    bodyType identificar(){
        return this->body;
    }
    virtual ~Colisionable() = default;
};

#endif
