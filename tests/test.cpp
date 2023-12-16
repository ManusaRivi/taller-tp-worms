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
bool compare_municiones(std::vector<std::pair<int,int>> server, std::map<int,int> cliente);
bool comapre_datos_especiales(std::vector<std::pair<uint8_t,std::vector<float>>> server, std::vector<std::pair<uint8_t,std::vector<float>>> cliente);
bool compare_projectiles(std::vector<ProjectileWrapper> server,std::vector<std::unique_ptr<ProjectileClient>>& cliente);
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

TEST(Test_unitario, TEST_SE_ENVIAN_MULTIPLES_MUNICIONES)
{

    Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    std::pair<int,int> bazzoka({Armas::BAZOOKA,1});
    std::pair<int,int> dinamita({Armas::DINAMITA,30});
    std::pair<int,int> ataque_aereo({Armas::ATAQUE_AEREO,14});
    std::pair<int,int> g_verde({Armas::GRANADA_VERDE,20});
    std::pair<int,int> g_santa({Armas::GRANADA_SANTA,3});
    std::pair<int,int> g_roja({Armas::GRANADA_ROJA,40});

    std::vector<std::pair<int,int>> municiones({bazzoka,dinamita,ataque_aereo,g_verde,g_santa,g_roja});
    svr_protocolo.enviar_municiones(municiones);
    std::shared_ptr<SnapshotCliente> snap = std::make_shared<SnapshotCliente>(0);
    clte_protocolo.recibir_municiones(snap);
    std::map<int,int> municiones_cliente = snap->get_municiones();
    EXPECT_TRUE(compare_municiones(municiones,municiones_cliente));
}

TEST(Test_unitario, TEST_SE_ENVIA_ARMAS_ESPECIALES){
    Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    std::vector<std::pair<uint8_t,std::vector<float>>> armas_especiales;
    armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({1,{12.8,17.2}})); //TELEPORTER
    armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0,{0.8,1.5}})); // AtaqueArereo
    armas_especiales.push_back(std::pair<uint8_t,std::vector<float>>({0,{0}})); //TELEPORTER
    svr_protocolo.enviar_datos_especiales(armas_especiales);

    std::shared_ptr<SnapshotCliente> snap = std::make_shared<SnapshotCliente>(0);
    clte_protocolo.recibir_datos_especiales(snap);
    EXPECT_TRUE(comapre_datos_especiales(armas_especiales,snap->get_datos_especiales()));
}

TEST(Test_unitario, TEST_SE_ENVIAR_PROYECTILES){
    Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    std::vector<ProjectileWrapper> vectProyectiles;
    ProjectileWrapper proy(1.157,21,0.178,ProjectileType::RED_GRENADE,1);
    ProjectileWrapper proy1(21.58,12.54,0.347,ProjectileType::MORTAR,3);
    vectProyectiles.push_back(proy);
    vectProyectiles.push_back(proy1);
    svr_protocolo.enviar_proyectiles(vectProyectiles);

    std::shared_ptr<SnapshotCliente> snap = std::make_shared<SnapshotCliente>(0);
    clte_protocolo.recibir_projectiles(snap);

    EXPECT_TRUE(compare_projectiles(vectProyectiles,snap->get_proyectiles()));

    //(posicion, worm->get_facing_direction(), worm->get_status(), worm->get_id(), worm->get_angulo(), worm->aiming_angle())


}


TEST(Test_se_envian_snapshot, TEST_SE_ENVIA_UN_HANDSHAKE){
    
    Socket skt;
    ClienteProtocolo clte_protocolo(skt);
    ServerProtocolo svr_protocolo(skt);
    //

    // Se Setea el handshake del lado del server
    
    //
    
    std::pair<uint32_t,std::vector<uint32_t>> id_gusanos_por_player({0,{0,1,2,3}});

    
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
    
    std::shared_ptr<SnapshotHandshake> snap = std::make_shared<SnapshotHandshake>(worms,vigas,1,0);
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

bool compare_municiones(std::vector<std::pair<int,int>> server, std::map<int,int> cliente){
    for(int i = 0; i < static_cast<int>(server.size()); i++){
        int municion_server = server[i].second;
        int municion_cliente = cliente[server[i].first];
        EXPECT_EQ(municion_server,municion_cliente);
    }
    return true;
}

bool comapre_datos_especiales(std::vector<std::pair<uint8_t,std::vector<float>>> server, std::vector<std::pair<uint8_t,std::vector<float>>> cliente){
    std::pair<uint8_t,std::vector<float>> tp = server[0];
    std::pair<uint8_t,std::vector<float>> ataque = server[1];
    std::pair<uint8_t,std::vector<float>> bomb = server[2];

    std::pair<uint8_t,std::vector<float>> tp_cliente = cliente[0];
    std::pair<uint8_t,std::vector<float>> ataque_cliente = cliente[1];
    std::pair<uint8_t,std::vector<float>> bomb_cliente = cliente[2];

    EXPECT_EQ(tp.first,tp_cliente.first);
    EXPECT_EQ(ataque.first,ataque_cliente.first);
    EXPECT_EQ(bomb.first,bomb_cliente.first);

    EXPECT_FLOAT_EQ(tp.second[0],tp_cliente.second[0]);
    EXPECT_FLOAT_EQ(tp.second[1],tp_cliente.second[1]);
    EXPECT_FLOAT_EQ(ataque.second[0],ataque_cliente.second[0]);
    EXPECT_FLOAT_EQ(ataque.second[1],ataque_cliente.second[1]);

    EXPECT_FLOAT_EQ(bomb.second[0],bomb_cliente.second[0]);
    return true;
}


bool compare_projectiles(std::vector<ProjectileWrapper> server,std::vector<std::unique_ptr<ProjectileClient>>& cliente){
    for(uint16_t i = 0; i < server.size(); i++){
        ProjectileWrapper proy = server[i];

        EXPECT_FLOAT_EQ(round_up(proy.get_x(),1),round_up(cliente[i]->get_x_test(),1));
        EXPECT_FLOAT_EQ(round_up(proy.get_y(),1),round_up(cliente[i]->get_y_test(),1));
    }
    return true;
}

float round_up(float value, int decimal_places) {
    const float multiplier = std::pow(10.0, decimal_places);
    return std::ceil(value * multiplier) / multiplier;
}



