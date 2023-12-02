#include "protocoloCliente.h"
#include "../../common/socket.h"
#include "../game/comunicacion/snapshot.h"
#include "../comandos/mensajes/mensaje_handshake.h"
#include "../comandos/mensajes/mensaje_snapshot.h"



ClienteProtocolo::ClienteProtocolo(Socket& peer):Protocolo(peer) {
            was_closed = false;
        }


void ClienteProtocolo::enviar_movimiento(uint8_t dir){
    // printf("Se envia un pedido de mover el gusano\n");
    bool was_closed = false;
    std::vector<uint8_t> buf;
    buf.push_back(CODIGO_MOVER);
    buf.push_back(dir);
    skt.sendall(buf.data(),2,&was_closed);
}

void ClienteProtocolo::detener_movimiento(){
    // printf("Se envia una pedido de detener movimiento\n");
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
    if (cmd == CODIGO_HANDSHAKE_EMPEZAR_PARTIDA){
        // printf("Se recibe un handshake del server\n");
        return recibir_handshake();
    }

    if (was_closed){
        return nullptr;
    }

    if (cmd == CODIGO_SNAPSHOT){
        return recibir_snap();
    }
 
    return nullptr;
}
// El segundo argumento no se usa
void ClienteProtocolo::crear_partida(std::string nombre,uint16_t id_mapa){
    uint8_t cmd = CODIGO_CREAR_PARTIDA;
    enviar_1_byte(cmd);
    enviar_string(nombre);
    enviar_2_byte(id_mapa);
}

void ClienteProtocolo::empezar_partida(){
    uint8_t cmd = CODIGO_EMPEZAR_PARTIDA;
    enviar_1_byte(cmd);
}


std::map<uint32_t,std::string> ClienteProtocolo::listar_partidas(){
    std::map<uint32_t,std::string> map;
    uint16_t size = recibir_2_bytes();
    for(uint16_t i = 0; i < size; i++ ){
        uint32_t id_mapa = recibir_4_bytes();
        std::string nombre_mapa = recibir_string();
        map.insert({id_mapa,nombre_mapa});
    }
    return map;
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

void ClienteProtocolo::unirse_partida(uint32_t id_partida){
    // uint32_t id = static_cast<uint32_t>(std::stoul(id_partida));
    uint8_t cmd = CODIGO_UNIRSE_PARTIDA;
    enviar_1_byte(cmd);
    enviar_4_bytes(id_partida);
}


std::shared_ptr<MensajeCliente> ClienteProtocolo::recibir_handshake(){
    std::shared_ptr<SnapshotCliente> snap= std::make_shared<SnapshotCliente>(0);
    std::vector<uint32_t> id_gusanos;
    uint32_t id_propio = recibir_4_bytes();
    uint16_t cantidad_gusanos = recibir_2_bytes();
    //std::cout << "El id de player que se recibe es " << id_propio << std::endl;
    for(uint16_t i = 0; i < cantidad_gusanos; i++){
        uint32_t id_gus = recibir_4_bytes();
        id_gusanos.push_back(id_gus);
        // printf("Se recibe id de gusano = %u \n", id_gus);
    }
    uint32_t turno_player_actual = recibir_4_bytes();
    snap->actulizar_camara(turno_player_actual);
    snap->agregar_turno_actual(turno_player_actual);
    recibir_gusanos(snap);
    std::map<int, std::shared_ptr<Worm>> worms = snap->get_worms();
    std::shared_ptr<World> world = std::make_shared<World>(100,100);
    std::vector<std::vector<float>> vigas = recibir_vigas();
    for (auto &viga : vigas){
        int tamanio = viga[3];
        Beam beam(tamanio,viga[0],viga[1],viga[2]);
        world->add_beam(beam);
    }
    for (auto &worm : worms){
        world->add_worm(worm.second,worm.first);
    }



    std::shared_ptr<MensajeHandshake> msg = std::make_shared<MensajeHandshake>(id_propio,id_gusanos,world);
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
    // printf("Se llega hasta aca\n");
    std::shared_ptr<SnapshotCliente> snap = std::make_shared<SnapshotCliente>(0);
    uint32_t turno_player_actual = recibir_4_bytes();
    snap->actulizar_camara(turno_player_actual);
    snap->agregar_turno_actual(turno_player_actual);
    int carga_actual_del_arma = recibir_2_bytes();
    snap->set_weapon_power(carga_actual_del_arma);
    recibir_datos_especiales(snap);
    recibir_municiones(snap);
    recibir_gusanos(snap);
    recibir_projectiles(snap);
    recibir_explosiones(snap);
    recibir_sonidos(snap);
    
    /*
    int tamano = 6;
    float posx = 1.5;
    float posy = 0.8;
    Beam beam(tamano, posx, posy);
    snap->add_beam(beam);
    */
    //std::cout << "Es el turno del gusano con ID = " << unsigned(turno_player_actual) << std::endl;
    
    std::shared_ptr<MensajeSnapshot> msg = std::make_shared<MensajeSnapshot>(snap);
    return msg;
}


std::vector<std::vector<float>> ClienteProtocolo::recibir_vigas(){
    uint16_t cantidad_vigas = recibir_2_bytes();
    std::vector<std::vector<float>> vigas;
    for(uint16_t i = 0; i < cantidad_vigas; i++){
          
        float x = recibir_4_bytes_float();
        float y = recibir_4_bytes_float();
        float angulo = recibir_4_bytes_float() * 180 / 3.14;
        float largo = recibir_4_bytes_float();


        std::vector<float> viga({x,y,angulo,largo});
        vigas.push_back(viga);
        // printf("Se recibe una viga con datos = [%f, %f, %f, %f] \n",x,y,angulo,largo);
    }
    return vigas;
}

void ClienteProtocolo::recibir_gusanos(std::shared_ptr<SnapshotCliente> snap){

    
    uint16_t cantidad_gusanos = recibir_2_bytes();
    // printf("La cantidad de gusanos recibida es %u\n",cantidad_gusanos);
    // printf("La cantidad de gusanos que se reciben es %u",cantidad_gusanos);
    for(uint16_t i = 0; i < cantidad_gusanos; i++){
        uint32_t id_gusano = recibir_4_bytes();
        float pos_x = recibir_4_bytes_float();
        float pos_y = recibir_4_bytes_float();

        float angulo = recibir_4_bytes_float();
        uint8_t direccion = recibir_1_byte();
        uint8_t estado = recibir_1_byte();
        float angulo_disparo = (recibir_4_bytes_float() - 1.57)*180/3.14;
        // printf("el angulo de dispaor que se recibe es %f", angulo_disparo);
        uint8_t vida = recibir_1_byte();
        uint32_t equipo = recibir_4_bytes();

        // printf("id= %d, x= %f, y= %f  angulo = %f  dir = %u estado = %u disparo = %f\n\n", id_gusano,pos_x,pos_y,angulo,direccion,estado,angulo_disparo);
        std::unique_ptr<WormState> state = WormStateGenerator::get_state_with_code(estado, direccion == 0, angulo, angulo_disparo);
        std::shared_ptr<Worm> worm = std::make_shared<Worm>(pos_x, pos_y, vida, equipo, std::move(state));
        snap->add_worm(worm, id_gusano);
    }
    
}

void ClienteProtocolo::recibir_projectiles(std::shared_ptr<SnapshotCliente> snap){
    uint16_t cantidad = recibir_2_bytes();
    // printf("La cantidad de proyectiles que se reciben es %u\n",cantidad);
    for(uint16_t i = 0; i < cantidad; i++){

        uint32_t id = recibir_4_bytes();
        float x = recibir_4_bytes_float();
        float y = recibir_4_bytes_float();
        float angulo = (recibir_4_bytes_float() +3.14 - 1.57)*180/3.14;
        uint8_t tipo = recibir_1_byte();
        std::unique_ptr<ProjectileClient> projectile =  ProjectileGenerator::get_proyectile_with_code(tipo,
                                                                        x,
                                                                        y,
                                                                        angulo,id);
        // printf("Los datos que llegan son  %u  %f    %f   %f de tipo = %u\n",id,x,y,angulo,tipo);
        snap->add_projectile(std::move(projectile));
    }
}

void ClienteProtocolo::recibir_explosiones(std::shared_ptr<SnapshotCliente> snap){
    uint16_t cantidad = recibir_2_bytes();
        // printf("La cantidad de explosiones que se reciben es %u\n",cantidad);
    for(uint16_t i = 0; i < cantidad; i++){

        uint32_t id = recibir_4_bytes();
        float x = recibir_4_bytes_float();
        float y = recibir_4_bytes_float();
        float radio = recibir_4_bytes_float();
        // printf("Se recibio una explosion de datos %u   %f    %f    %f\n",id,x,y,radio);
        snap->add_explosion(ExplosionCliente(id,x,y,radio));
    }
}

void ClienteProtocolo::recibir_sonidos(std::shared_ptr<SnapshotCliente> snap) {
    uint16_t cantidad = recibir_2_bytes();
    //  printf("La cantidad de sonidos que se reciben es %u\n",cantidad);
    for (auto i = 0; i < cantidad; ++i) {
        uint8_t sonido = recibir_1_byte();
        snap->add_sound(sonido);
    }
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

void ClienteProtocolo::enviar_cambio_direccion_apuntado(uint8_t dir){
    uint8_t cd = CODIGO_CAMBIAR_DIRECCION_APUNTADO;
    enviar_1_byte(cd);
    enviar_1_byte(dir);
}

void ClienteProtocolo::enviar_timer(uint32_t time){
    uint8_t cd = CODIGO_SETEAR_TIMER;
    enviar_1_byte(cd);
    enviar_4_bytes(time);
}

void ClienteProtocolo::enviar_target(float x, float y){
    uint8_t cd = CODIGO_SETEAR_TARGET;
    enviar_1_byte(cd);
    enviar_4_bytes_float(x);
    enviar_4_bytes_float(y);
}

bool ClienteProtocolo::recibir_confirmacion_union(){
    uint8_t cd = recibir_1_byte();
    if(cd != CODIGO_ESTADO_UNIRSE_PARTIDA){
        return false;
    }
    uint8_t estado = recibir_1_byte();
    if(estado){
        return true;
    }
    else{
        return false;
    }
}

void ClienteProtocolo::recibir_datos_especiales(std::shared_ptr<SnapshotCliente> snap){
    uint8_t _has_tp = recibir_1_byte();
    float tp_pos_x = recibir_4_bytes_float();
    float tp_pos_y = recibir_4_bytes_float();

    bool has_tp = _has_tp;

    snap->set_tp(has_tp, tp_pos_x, tp_pos_y);

    uint8_t _has_ataque_aereo = recibir_1_byte();
    float ataque_pos_x = recibir_4_bytes_float();
    float ataque_pos_y = recibir_4_bytes_float();

    bool has_ataque_aereo = _has_ataque_aereo;

    snap->set_air_attack(has_ataque_aereo, ataque_pos_x, ataque_pos_y);

    uint8_t _has_timer = recibir_1_byte();
    uint32_t _timer = recibir_4_bytes();

    bool has_timer = _has_timer;
    int timer = _timer;

    snap->set_timer(has_timer, timer);
}

void ClienteProtocolo::recibir_municiones(std::shared_ptr<SnapshotCliente> snap){
    uint16_t cantidad = recibir_2_bytes();
    for(uint16_t i = 0; i < cantidad; i++){
        int tipo_arma = recibir_1_byte();
        int municion = recibir_2_bytes();
        snap->set_ammo(tipo_arma, municion);
    }
}