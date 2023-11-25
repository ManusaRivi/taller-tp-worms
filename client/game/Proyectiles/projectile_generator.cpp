#include "projectile_generator.h"

std::unique_ptr<ProjectileClient> ProjectileGenerator::get_proyectile_with_code(int proy_code,
                                                                        float& pos_x,
                                                                        float& pos_y,
                                                                        float& angle) {
    switch(proy_code) {
        case MISSILE:
            return std::make_unique<ProjectileClient>(std::string("Missile"), pos_x, pos_y, angle);
        case MORTAR:
            return std::make_unique<ProjectileClient>(std::string("Mortar"), pos_x, pos_y, angle);
        case GREEN_GRANADE:
            return std::make_unique<ProjectileClient>(std::string("GreenGranade"), pos_x, pos_y, angle);
        case HOLY_GRANADE:
            return std::make_unique<ProjectileClient>(std::string("HolyGranade"), pos_x, pos_y, angle);
        case RED_GRANADE:
            return std::make_unique<ProjectileClient>(std::string("RedGranade"), pos_x, pos_y, angle);
        case BANANA:
            return std::make_unique<ProjectileClient>(std::string("Banana"), pos_x, pos_y, angle);
        case AIR_MISSILE:
            return std::make_unique<ProjectileClient>(std::string("AirMissile"), pos_x, pos_y, angle);
        /*
        case DROP:
            return std::make_unique<Drop>(pos_x, pos_y, angle);
        case DYNAMITE:
            return std::make_unique<Dynamite>(pos_x, pos_y, angle, tiempo a explotar);
        */
        default:
            throw std::runtime_error("No existe ese codigo de proyectil");
    }
}