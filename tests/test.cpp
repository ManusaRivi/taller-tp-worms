// #include <gtest/gtest.h>

// #define _TESTING
// #include "../server/protocolo/protocoloServer.h"
// #include "../server/snapshot.h"
// #include "test_socket.h"


// TEST(Test_se_envian_vigas_correctamente, Se_envia_una_viga)
// {
//     Socket skt;
//     ServerProtocolo server(skt);
//     // std::vector<int> una_viga({5,4,54,8});
//     // std::vector<std::vector<int>> vigas({una_viga});
//     // Snapshot snap(vigas);
//     // std::vector<float> position(0.50,0.10); int dir = 1; int status = 1;
//     // WormWrapper worm(position,dir,status);
//     // snap.add_worm(worm);

//     // server.enviar_vigas(snap);
//     // std::vector<uint8_t> buffer(1*(4+4+4+4),1);
//     // bool was_closed = false;
//     // skt.recvall(buffer.data(),4+4+4+4,&was_closed);
//     // size_t offset = 0;
//     // uint32_t x;
//     // memcpy(&x,buffer.data() + offset, 4);
//     // uint32_t y;
//     // offset += 4;
//     // memcpy(&y,buffer.data() + offset, 4);
//     // uint32_t angulo;
//     // offset += 4;
//     // memcpy(&angulo,buffer.data() + offset, 4);
//     // uint32_t tamanio;
//     // offset += 4;
//     // memcpy(&tamanio,buffer.data() + offset, 4);

//     // x = ntohl(x);
//     // y = ntohl(y);
//     // angulo = ntohl(angulo);
//     // tamanio = ntohl(tamanio);

//     // EXPECT_EQ(x,una_viga[0]);
//     // EXPECT_EQ(y,una_viga[1]);
//     // EXPECT_EQ(angulo,una_viga[2]);
//     // EXPECT_EQ(tamanio,una_viga[3]);

// }

// TEST(sample_test_case, smple_case){
//     EXPECT_EQ(4,4);
// }

// TEST(sample_test_case, Simple){
//     EXPECT_EQ(1,2);
// }
