#include "comando.h"


class DetenerMovimiento:public Comando{

    uint8_t responsable_id;

    public:
    DetenerMovimiento();

    void agregar_id(uint8_t id) override;

    void realizar_accion(Mapa &mapa) override;

    uint8_t get_comando() override;


};