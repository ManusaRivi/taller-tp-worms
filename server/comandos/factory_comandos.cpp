#include "factory_comandos.h"

FactoryComandos::FactoryComandos(){

}

ComandoMovimiento FactoryComandos::comando_movimient(uint8_t dir){
        ComandoMovimiento comando(dir);
        comando.dir = dir;
        return comando;
}