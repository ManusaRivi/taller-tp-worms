#include "projectile_generator.h"

std::unique_ptr<Projectile> ProjectileGenerator::get_proyectile_with_code(int proy_code,
                                                                        float& pos_x,
                                                                        float& pos_y,
                                                                        float& angle) {
    switch(proy_code) {
        case PROYECTILE_MISSILE:
            return std::make_unique<Missile>(pos_x, pos_y, angle);
        default:
            throw std::runtime_error("No existe ese codigo de proyectil");
    }
}