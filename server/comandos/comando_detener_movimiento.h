#include "comando.h"


class DetenerMovimientoCliente:public Comando{

    uint8_t responsable_id;

    public:
    DetenerMovimientoCliente(uint32_t id);

    void agregar_id(uint8_t id) override;

    void realizar_accion(Mapa &mapa , uint32_t id) override;

    uint8_t get_comando() override;


};