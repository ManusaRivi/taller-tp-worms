#include "comando.h"


class DetenerMovimiento:public Comando{


    public:
    DetenerMovimiento(uint32_t id);



    void realizar_accion(Mapa* mapa , uint32_t id) override;





};