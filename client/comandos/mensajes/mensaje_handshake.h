#include "mensaje_cliente.h"
#include <vector>
#include "../../game/world.h"


class MensajeHandshake:public MensajeCliente{

    uint32_t id_player;
    std::vector<uint32_t> id_gusanos;
    std::shared_ptr<World> world;

    public:
    MensajeHandshake(uint32_t id_player_, std::vector<uint32_t> id_gusanos_,std::shared_ptr<World> world_);
    uint32_t get_id();
    std::vector<uint32_t> get_gusanos();
    std::shared_ptr<World> get_world();
};