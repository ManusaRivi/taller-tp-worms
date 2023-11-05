#include "monitorClientes.h"


MonitorClientes::MonitorClientes(){

}

void MonitorClientes::add_cliente(Cliente* clte){
    std::lock_guard<std::mutex> lock(lck);
    clientes.push_back(clte);
}


Cliente* MonitorClientes::buscar_cliente(uint8_t id){
    std::lock_guard<std::mutex> lock(lck);
    Cliente *clte;
    for( auto &c: clientes){
        if(c->get_id() == id){
            clte = c;
            break;
        }
    }
    return clte;
}