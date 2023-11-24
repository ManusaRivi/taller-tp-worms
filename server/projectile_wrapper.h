#ifndef PROJECTILE_WRAPPER_H
#define PROJECTILE_WRAPPER_H

#include "../common/projectile_types.h"

class ProjectileWrapper {
private:
    float x_pos;
    float y_pos;
    float angulo;
    ProjectileType tipo;
public:
    ProjectileWrapper(float x_pos, float y_pos, float angulo, ProjectileType tipo);
};

#endif
