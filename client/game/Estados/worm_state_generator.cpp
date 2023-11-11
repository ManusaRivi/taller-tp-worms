#include "worm_state_generator.h"

std::unique_ptr<WormState> WormStateGenerator::get_state_with_code(int status_code,
                                                            bool facing_right,
                                                            float worm_angle,
                                                            float shot_angle) {
    switch (status_code)
    {
    case WORM_STATE_IDLE:
        return std::make_unique<WIdle>(facing_right, worm_angle);
    
    case WORM_STATE_WALKING:
        return std::make_unique<WWalk>(facing_right, worm_angle);
    
    default:
        throw std::runtime_error("WormStateGenerator: No existe ese codigo de estado");
    }
                                                            }