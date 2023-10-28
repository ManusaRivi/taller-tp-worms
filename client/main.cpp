#include "client.h"

int main(int argc, char* argv[]) {
    const char *serv_name = "127.0.0.1";
    const char *port = "8080";
    Client client(argc, argv,serv_name,port);
    client.iniciar();
}