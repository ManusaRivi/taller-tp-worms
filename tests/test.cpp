#include "gtest/gtest.h"

#define _TESTING

#include "../server/snapshots/snapshot.h"
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
    WormWrapper worm_1({{0.5,1.2},1,0,0,1.2,0, 100, 0});
    std::vector<WormWrapper> worms({worm_1});

    svr_protocolo.enviar_gusanos(worms);
    
    std::shared_ptr<MensajeSnapshot> msg = std::dynamic_pointer_cast<MensajeSnapshot>(clte_protocolo.recibir_snap());
    std::shared_ptr<SnapshotCliente> snapshot = msg->get_snap();

    std::map<int, std::shared_ptr<Worm>> cl = snapshot->get_worms();

    EXPECT_TRUE(compare_gusanos(worms,cl));
}

TEST(Test_se_envian_snapshot, TEST_SE_ENVIA_POR_SNAPSHOT_DOS_GUSANOS){
    Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    //(posicion, worm->get_facing_direction(), worm->get_status(), worm->get_id(), worm->get_angulo(), worm->aiming_angle())
    WormWrapper worm_1({{0.5,1.2}, //posicion
                        0, //dir
                        0, //status
                        0, //id
                        1.2, //angulo
                        0, // angulo_disparo
                        100, // vida
                        0}); //equipo
    WormWrapper worm_2({{13.15,18.6}, 
                        0, 
                        12, 
                        1, 
                        1, 
                        0, 
                        100, 
                        1});
    ProjectileWrapper proyectlile_1(10,12.5,1.2,ProjectileType::ROCKET,15);
    ExplosionWrapper explosion_1(20,10,20.5,7);
    ProvisionWrapper provision_1(10,10,ProvisionType::VIDA,1);
    std::vector<WormWrapper> worms({worm_1,worm_2});
    std::vector<ProjectileWrapper> projectiles({proyectlile_1});
    std::vector<ExplosionWrapper> explosiones({explosion_1});
    std::vector<ProvisionWrapper> provisiones({provision_1});
    std::shared_ptr<Snapshot> snap = std::make_shared<SnapshotPartida>(worms,projectiles,explosiones,provisiones,0,0,std::vector<SoundTypes>(),std::vector<std::pair<uint8_t,std::vector<float>>>(),std::vector<std::pair<int,int>>(),0);
    svr_protocolo.enviar_gusanos(worms);
    svr_protocolo.enviar_proyectiles(projectiles);
    svr_protocolo.enviar_explosiones(explosiones);
    svr_protocolo.enviar_provisiones(provisiones);
    // uint8_t cd;
    // bool was_closed = false;
    // skt.recvall(&cd,1,&was_closed);
    // printf("El cd que se recibio es %u\n",cd);
    std::shared_ptr<SnapshotCliente> snapshot_cliente= std::make_shared<SnapshotCliente>(0);
    clte_protocolo.recibir_gusanos(snapshot_cliente);
    clte_protocolo.recibir_projectiles(snapshot_cliente);
    clte_protocolo.recibir_explosiones(snapshot_cliente);
    clte_protocolo.recibir_provisiones(snapshot_cliente);

    // std::shared_ptr<MensajeSnapshot> msg = std::dynamic_pointer_cast<MensajeSnapshot>(std::move(mensaje));
    // std::shared_ptr<SnapshotCliente> snapshot = msg->get_snap();
    // printf("asdasdasd\n");
    // char asd = 'a';
    // bool was_closed = false;
    // skt.sendall(&asd,1,&was_closed);
    // printf("asdasdasd\n");

    std::map<int, std::shared_ptr<Worm>> cl = snapshot_cliente->get_worms();

    EXPECT_TRUE(compare_gusanos(worms,cl));

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

    //std::vector<float> position, 
    //uint8_t dir, 
    //uint8_t status,
    //uint32_t id, 
    //float angulo, 
    //float angulo_disparo, 
    //uint8_t vida, 
    //uint32_t equipo
    
    WormWrapper worm_1({{0.5,1.2}, //posicion
                        1, //dir
                        0, //status
                        0, //id
                        1.2, //angulo
                        0, // angulo_disparo
                        100, // vida
                        0}); //equipo
    WormWrapper worm_2({{13.15,18.6}, 
                        0, 
                        12, 
                        1, 
                        0, 
                        0.1, 
                        100, 
                        1});
                        
    WormWrapper worm_3({{12.5,7.5}, 1, 12, 2, 1.2, 1.5, 100, 0});
    WormWrapper worm_4({{15,16.7}, 1, 12, 3, 0, 1.4, 100, 1});
    std::vector<WormWrapper> worms({worm_1,worm_2,worm_3,worm_4});
    std::vector<float> viga_1({10, 15.7, 3, 6});
    std::vector<float> viga_2({10, 15.7, 3, 6});
    std::vector<float> viga_3({10, 15.7, 3, 6});
    std::vector<float> viga_4({10, 15.7, 3, 6});
    std::vector<std::vector<float>> vigas({viga_1,viga_2,viga_3,viga_4});
    
    std::shared_ptr<SnapshotHandshake> snap = std::make_shared<SnapshotHandshake>(worms,vigas,1);
    svr_protocolo.enviar_handshake(id_gusanos_por_player,snap);


    // Se recibe el handshake del lado del cliente


    
    std::shared_ptr<MensajeHandshake> msg = std::dynamic_pointer_cast<MensajeHandshake>(clte_protocolo.recibir_handshake());
    
    
    std::shared_ptr<World> world = msg->get_world();
    std::vector<WormWrapper> srv = worms;
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
        EXPECT_EQ(client_worm->getEquipo(),server_worm.get_id());
        EXPECT_EQ(state->get_direction(),server_worm.get_direccion());
        
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