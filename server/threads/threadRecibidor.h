#include "../../common/socket.h"
#include "../../common/thread.h"


struct Recibidor:public Thread{


    Socket &skt;
    std::atomic<bool> is_alive;

    Recibidor(Socket &peer);

    void run() override;

    bool is_dead();

};