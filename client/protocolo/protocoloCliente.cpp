#include "protocoloCliente.h"
#include "../../common/socket.h"
#include "../game/comunicacion/snapshot.h"



ClienteProtocolo::ClienteProtocolo(Socket &peer):Protocolo(peer) {
            was_closed = false;
        }


void ClienteProtocolo::enviar_movimiento(uint8_t dir){
    printf("Se envia un pedido de mover el gusano\n");
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(CODIGO_MOVER);
    buf.push_back(dir);
    skt.sendall(buf.data(),2,&was_closed);
}

void ClienteProtocolo::detener_movimiento(){
    printf("Se envia una pedido de detener movimiento\n");
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(CODIGO_DETENER_MOVIMIENTO);
    skt.sendall(buf.data(),1,&was_closed);
}


std::shared_ptr<MensajeCliente> ClienteProtocolo::recibir_snapshot(){
    bool was_closed = false;
    SnapshotCliente sn(0);
    uint8_t cmd;
    skt.recvall(&cmd,1,&was_closed);

    if(cmd == CODIGO_PARTIDA_POR_COMENZAR){
        std::shared_ptr<MensajeCliente> msg = std::make_shared<MensajeCliente>(COMANDO::CMD_PARTIDA_EMPEZO);
        return msg;
    }
    if(cmd == CODIGO_LISTAR_PARTIDA){
        std::map<uint32_t,std::string> map = listar_partidas();
        std::shared_ptr<MensajeCliente> msg = std::make_shared<MensajeCliente>(map);
        return msg;
    }
    if (cmd == CODIGO_HANDSHAKE_EMPEZAR_PARTIDA){
        printf("Se recibe un handshake del server\n");
        return recibir_id_gusanos();
    }

    if (was_closed){
        return nullptr;
    }

    if (cmd == CODIGO_SNAPSHOT){
        return recibir_snap();
    }
 
    return nullptr;
}

void ClienteProtocolo::crear_partida(std::string nombre){
    uint8_t cmd = CODIGO_CREAR_PARTIDA;
    enviar_1_byte(cmd);
    enviar_string(nombre);
}

void ClienteProtocolo::empezar_partida(){
    uint8_t cmd = CODIGO_EMPEZAR_PARTIDA;
    enviar_1_byte(cmd);
}


std::map<uint32_t,std::string> ClienteProtocolo::listar_partidas(){
    std::map<uint32_t,std::string> map;
    
    uint16_t size = recibir_2_bytes();
    for(uint16_t i = 0; i < size; i++ ){
        uint32_t id = recibir_4_bytes();
        std::string nombre = recibir_string();
        map.insert({id,nombre});
    }
    return map;
    
    //std::string nombreMapa = recibir_string();
    //map.insert({1,nombreMapa});
    //return map;
}

std::map<uint32_t,std::string> ClienteProtocolo::pedir_mapas(){
    uint8_t cmd = CODIGO_LISTAR_MAPAS;
    enviar_1_byte(cmd);
    return listar_partidas();
}

std::map<uint32_t,std::string> ClienteProtocolo::pedir_lista_partidas(){
    uint8_t cmd = CODIGO_LISTAR_PARTIDA;
    enviar_1_byte(cmd);
    return listar_partidas();
}

void ClienteProtocolo::unirse_partida(std::string id_partida){
    uint32_t id = static_cast<uint32_t>(std::stoul(id_partida));
    uint8_t cmd = CODIGO_UNIRSE_PARTIDA;
    enviar_1_byte(cmd);
    enviar_4_bytes(id);
}


std::shared_ptr<MensajeCliente> ClienteProtocolo::recibir_id_gusanos(){
    std::vector<uint32_t> id_gusanos;
    uint32_t id_propio = recibir_4_bytes();
    uint16_t cantidad_gusanos = recibir_2_bytes();
    std::cout << "El id de player que se recibe es " << id_propio << std::endl;
    for(uint16_t i = 0; i < cantidad_gusanos; i++){
        uint32_t id_gus = recibir_4_bytes();
        id_gusanos.push_back(id_gus);
        printf("Se recibe id de gusano = %u \n", id_gus);
    }
    uint16_t cantidad_vigas = recibir_2_bytes();
    std::vector<std::vector<float>> vigas;
    for(uint16_t i = 0; i < cantidad_vigas; i++){
          
        uint32_t x = recibir_4_bytes();
        uint32_t y = recibir_4_bytes();
        uint32_t angulo = recibir_4_bytes();
        uint32_t largo = recibir_4_bytes();

        float x_pos = x/100;
        float y_pos = y/100;
        float angulo_bis = angulo/100;
        float largo_bis = largo/100;

        std::vector<float> viga({x_pos,y_pos,angulo_bis,largo_bis});
        vigas.push_back(viga);
        printf("Se recibe una viga con datos = [%f, %f, %f, %f] \n",x_pos,y_pos,angulo_bis,largo_bis);
    }
    
    std::shared_ptr<MensajeCliente> msg = std::make_shared<MensajeCliente>(id_propio,id_gusanos,vigas);
    return msg;
}

void ClienteProtocolo::enviar_handshake(uint32_t id_player, std::vector<uint32_t> id_gusanos){
    uint8_t cmd = CODIGO_HANDSHAKE_EMPEZAR_PARTIDA;
    enviar_1_byte(cmd);
    enviar_4_bytes(id_player);
    uint16_t cantidad_gusanos = id_gusanos.size();
    enviar_2_byte(cantidad_gusanos);
    for (uint16_t i = 0; i < cantidad_gusanos;i++){
        enviar_4_bytes(id_gusanos[i]);
    }

}

std::shared_ptr<MensajeCliente> ClienteProtocolo::recibir_snap(){
    std::shared_ptr<SnapshotCliente> snap= std::make_shared<SnapshotCliente>(0);

    uint32_t turno_player_actual = recibir_4_bytes();
    uint16_t cantidad_gusanos = recibir_2_bytes();
    for(uint16_t i = 0; i < cantidad_gusanos; i++){
        uint32_t id_gusano = recibir_4_bytes();
        uint32_t pos_x = recibir_4_bytes();
        uint32_t pos_y = recibir_4_bytes();

        float x_pos = pos_x;
        float y_pos = pos_y;
        float xpos = x_pos/100;
        float ypos = y_pos/100;

        uint32_t angulo = recibir_4_bytes();
        uint8_t direccion = recibir_1_byte();
        uint8_t estado = recibir_1_byte();
        std::unique_ptr<WormState> state = WormStateGenerator::get_state_with_code(estado, direccion == 0, angulo, 0.0);
        std::shared_ptr<Worm> worm = std::make_shared<Worm>(xpos, ypos, std::move(state));
        snap->add_worm(worm, id_gusano);
    }
    /*
    int tamano = 6;
    float posx = 1.5;
    float posy = 0.8;
    Beam beam(tamano, posx, posy);
    snap->add_beam(beam);
    */
    //std::cout << "Es el turno del gusano con ID = " << unsigned(turno_player_actual) << std::endl;
    snap->agregar_turno_actual(turno_player_actual);
    std::shared_ptr<MensajeCliente> msg = std::make_shared<MensajeCliente>(snap);
    return msg;
}

bool ClienteProtocolo::recibir_comienzo_de_partida(){
    uint8_t cd = recibir_1_byte();
    if(cd == CODIGO_PARTIDA_POR_COMENZAR){
        return true;
    }
    return false;
}

void ClienteProtocolo::cambio_angulo(uint8_t direccion){
    uint8_t cd = CODIGO_CAMBIAR_ANGULO;
    enviar_1_byte(cd);
    uint8_t angulo = direccion;
    enviar_1_byte(angulo);
}

void ClienteProtocolo::cargar_arma(){
    uint8_t cd = CODIGO_CARGAR_ARMA;
    enviar_1_byte(cd);
}

void ClienteProtocolo::disparar_arma(){
    uint8_t cd = CODIGO_DISPARAR;
    enviar_1_byte(cd);
}

void ClienteProtocolo::enviar_salto(uint8_t direccion){
    uint8_t cd = CODIGO_SALTAR;
    enviar_1_byte(cd);
    uint8_t dir = direccion;
    enviar_1_byte(dir);
}

void ClienteProtocolo::detener_cambio_angulo(){
    uint8_t cd = CODIGO_DETENER_CAMBIO_ANGULO;
    enviar_1_byte(cd);
}

void ClienteProtocolo::enviar_cambio_de_arma(uint8_t id_arma){
    uint8_t cd = CODIGO_CAMBIAR_ARMA;
    enviar_1_byte(cd);
    enviar_1_byte(id_arma);
}