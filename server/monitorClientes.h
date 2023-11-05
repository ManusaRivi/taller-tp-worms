#include "Cliente.h"


struct MonitorClientes{

    std::mutex lck;
    std::list<Cliente*> clientes;

    MonitorClientes();

    void add_cliente(Cliente* clte);

    Cliente* buscar_cliente(uint8_t id);

};