#include "gtest/gtest.h"

#define _TESTING

#include "../server/snapshot.h"
#include "../client/protocolo/protocoloCliente.h"
#include "../server/protocolo/protocoloServer.h"
#include "../client/game/comunicacion/snapshot.h"
#include "test_socket.h"
#include <cmath>
#include "../../client/comandos/mensajes/mensaje_handshake.h"
#include "../../client/comandos/mensajes/mensaje_snapshot.h"
#include "../../client/comandos/mensajes/mensaje_handshake_enviar.h"
#include "../../client/comandos/mensajes/mensaje_accion_jugador.h"

class SnapshotCliente;
bool compare_gusanos(std::vector<WormWrapper> srv , std::map<int, std::shared_ptr<Worm>> cl);
bool compare_beams(std::vector<std::vector<float>> vigas_server,std::vector<Beam> vigas);
float round_up(float value, int decimal_places);

TEST(Test_se_envian_snapshot,TEST_SE_ENVIA_POR_SNAPSHOT_UN_GUSANO )
{

    Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    //(posicion, worm->get_facing_direction(), worm->get_status(), worm->get_id(), worm->get_angulo(), worm->aiming_angle())
    WormWrapper worm_1({{0.5,1.2},1,0,0,1.2,0, 100});
    std::vector<WormWrapper> worms({worm_1});
    Snapshot snap(worms);
    svr_protocolo.enviar_gusanos(snap);
    
    std::shared_ptr<MensajeSnapshot> msg = std::dynamic_pointer_cast<MensajeSnapshot>(clte_protocolo.recibir_snap());
    std::shared_ptr<SnapshotCliente> snapshot = msg->get_snap();

        std::vector<WormWrapper> srv = snap.get_worms();
    std::map<int, std::shared_ptr<Worm>> cl = snapshot->get_worms();

    EXPECT_TRUE(compare_gusanos(srv,cl));
}

TEST(Test_se_envian_snapshot, TEST_SE_ENVIA_POR_SNAPSHOT_DOS_GUSANOS){
        Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    //(posicion, worm->get_facing_direction(), worm->get_status(), worm->get_id(), worm->get_angulo(), worm->aiming_angle())
    WormWrapper worm_1({{0.5,1.2},1,0,0,1.2,0, 100});
    WormWrapper worm_2({{0.5,1.2},1,12,1,34,54, 100});
    std::vector<WormWrapper> worms({worm_1,worm_2});
    Snapshot snap(worms);
    svr_protocolo.enviar_gusanos(snap);
    
    std::shared_ptr<MensajeSnapshot> msg = std::dynamic_pointer_cast<MensajeSnapshot>(clte_protocolo.recibir_snap());
    std::shared_ptr<SnapshotCliente> snapshot = msg->get_snap();


    std::vector<WormWrapper> srv = snap.get_worms();
    std::map<int, std::shared_ptr<Worm>> cl = snapshot->get_worms();

    EXPECT_TRUE(compare_gusanos(srv,cl));
}

TEST(Test_se_envian_snapshot, TEST_SE_ENVIA_UN_HANDSHAKE){
    Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    //

    // Se Setea el handshake del lado del server
    
    //
    std::pair<uint32_t,std::vector<uint32_t>> id_gusanos_por_player({0,{0,1,2,3}});
    // std::vector<float> position, uint8_t dir, uint8_t status, uint32_t id_, float angulo_, float angulo_disparo_
    WormWrapper worm_1({{0.5,1.2}, 1, 0, 0, 1.2, 0, 100});
    WormWrapper worm_2({{13.15,18.6}, 1, 12, 1, 0.58, 0.1, 100});
    WormWrapper worm_3({{12.5,7.5}, 1, 12, 2, 1.2, 1.5, 100});
    WormWrapper worm_4({{15,16.7}, 1, 12, 3, 0, 1.4, 100});
    std::vector<WormWrapper> worms({worm_1,worm_2,worm_3,worm_4});
    std::vector<float> viga_1({10, 15.7, 3, 6});
    std::vector<float> viga_2({10, 15.7, 3, 6});
    std::vector<float> viga_3({10, 15.7, 3, 6});
    std::vector<float> viga_4({10, 15.7, 3, 6});
    std::vector<std::vector<float>> vigas({viga_1,viga_2,viga_3,viga_4});
    Snapshot snap(worms,vigas);
    svr_protocolo.enviar_handshake(id_gusanos_por_player,snap);


    // Se recibe el handshake del lado del cliente



    std::shared_ptr<MensajeHandshake> msg = std::dynamic_pointer_cast<MensajeHandshake>(clte_protocolo.recibir_snapshot());
    
    
    std::shared_ptr<World> world = msg->get_world();
    std::vector<WormWrapper> srv = snap.get_worms();
    std::map<int, std::shared_ptr<Worm>> cl = world->get_worms();


    // Se compara la posicion de gusanos recibida
    EXPECT_TRUE(compare_gusanos(srv,cl));


    std::vector<Beam> beams = world->get_beams();


    EXPECT_TRUE(compare_beams(vigas,beams));

}

TEST(sample_test_case, Simple){
    EXPECT_EQ(2,2);
}
// 
bool compare_gusanos(std::vector<WormWrapper> srv , std::map<int, std::shared_ptr<Worm>> cl){

    for(uint8_t i = 0; i < cl.size();i++){
        WormWrapper server_worm = srv[i];
        std::shared_ptr<Worm> client_worm = cl[i];
        client_worm->get_x();
        std::unique_ptr<WormState> state = client_worm->get_state();
        EXPECT_TRUE(cl.find(i) != cl.end());
        EXPECT_EQ(i,server_worm.get_id());
        EXPECT_EQ(state->get_direction(),server_worm.get_direccion());
        float clte_shot_angle = round_up(state->get_shooting_angle(),4);
        float server_shot_angle = round_up(server_worm.get_angulo_disparo()*180/3.14,4);
        EXPECT_FLOAT_EQ(clte_shot_angle,server_shot_angle);
        EXPECT_FLOAT_EQ(state->get_worm_angle(), server_worm.get_angulo());
        // if() return false;
        EXPECT_FLOAT_EQ(client_worm->get_x(),server_worm.get_position()[0]);
        EXPECT_FLOAT_EQ(client_worm->get_y(), server_worm.get_position()[1]);
    }
    return true;
}

bool compare_beams(std::vector<std::vector<float>> vigas_server,std::vector<Beam> vigas){
    for (uint8_t i = 0; i < vigas.size();i++){
        std::vector<float> srv = vigas_server[i];
        Beam clte = vigas[i];
        EXPECT_FLOAT_EQ(srv[0],clte.get_pos_x());
        EXPECT_FLOAT_EQ(srv[1],clte.get_pos_y());
        EXPECT_FLOAT_EQ(srv[2],clte.get_angulo());
        EXPECT_FLOAT_EQ(srv[3],clte.get_tamaio());
    }   
    return true;
}


float round_up(float value, int decimal_places) {
    const float multiplier = std::pow(10.0, decimal_places);
    return std::ceil(value * multiplier) / multiplier;
}