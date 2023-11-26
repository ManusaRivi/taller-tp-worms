#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "projectile.h"
#include "../worm.h"

#define	RAND_LIMIT 32767

#define FRAG_HEIGHT 0.2f
#define FRAG_WIDTH 0.2f

#define FRAG_DENSITY 0.05f

#define MIN_X_IMPULSE -0.1f
#define MAX_X_IMPULSE 0.1f
#define Y_IMPULSE 0.3f

#define FRAG_BLAST_POWER 1.0

class Fragment : public Projectile {
private:
    b2World& world;
    inline float RandomFloat(float lo, float hi) {
        float r = (float)(rand() & (RAND_LIMIT));
        r /= RAND_LIMIT;
        r = (hi - lo) * r + lo;
        return r;
    }
public:
    Fragment(b2World& world, float x_pos, float y_pos, int dmg, int radius);
    virtual void explotar() override;
};

#endif
