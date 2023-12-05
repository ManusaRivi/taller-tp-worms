#include "mensaje_partida_termino.h"


MensajePartidaTermino::MensajePartidaTermino( uint32_t equipo_ganador_, bool fue_empate_):MensajeCliente(CMD_PARTIDA_TERMINADA),equipo_ganador(equipo_ganador_),fue_empate(fue_empate_){
    
}


uint32_t MensajePartidaTermino::get_equipo_ganador(){
    return this->equipo_ganador;
}

bool MensajePartidaTermino::fue_empate_(){
    return this->fue_empate;
}
