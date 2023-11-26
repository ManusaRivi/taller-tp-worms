#include "projectile_generator.h"

std::unique_ptr<ProjectileClient> ProjectileGenerator::get_proyectile_with_code(int proy_type,
                                                                        float& pos_x,
                                                                        float& pos_y,
                                                                        float& angle) {
    switch(proy_type) {
        case ProjectileType::ROCKET:
            return std::make_unique<ProjectileClient>(std::string("Missile"), pos_x, pos_y, angle);
        case ProjectileType::MORTAR:
            return std::make_unique<ProjectileClient>(std::string("Mortar"), pos_x, pos_y, angle);
        case ProjectileType::GREEN_GRANADE:
            return std::make_unique<ProjectileClient>(std::string("GreenGranade"), pos_x, pos_y, angle);
        case ProjectileType::HOLY_GRANADE:
            return std::make_unique<ProjectileClient>(std::string("HolyGranade"), pos_x, pos_y, angle);
        case ProjectileType::RED_GRANADE:
            return std::make_unique<ProjectileClient>(std::string("RedGranade"), pos_x, pos_y, angle);
        case ProjectileType::BANANA_GRENADE:
            return std::make_unique<ProjectileClient>(std::string("Banana"), pos_x, pos_y, angle);
        case ProjectileType::AIR_MISSILE:
            return std::make_unique<ProjectileClient>(std::string("AirMissile"), pos_x, pos_y, angle);
        case ProjectileType::FRAGMENT:
            return std::make_unique<Fragment>(pos_x, pos_y, angle);
        case ProjectileType::DYNAMITE:
            return std::make_unique<Dynamite>(pos_x, pos_y, angle);
        
        default:
            throw std::runtime_error("No existe ese codigo de proyectil");
    }
}